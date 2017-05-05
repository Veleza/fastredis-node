// connection.cc
#include <node.h>
#include <string.h>
#include "connection.h"

#include <time.h>

namespace fastredis {

using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;

const char* ToCString(const String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}

Persistent<Function> Connection::constructor;

Connection::Connection(const char* host, int port) : host_(host), port_(port) {
    if (!host) {
        host = "127.0.0.1";
    }

    if (!port) {
        port = 6379;
    }

    struct timeval timeout = { 1, 500000 }; // 1.5 seconds

    ctx_ = redisConnectWithTimeout(host, port, timeout);
    if (ctx_ == NULL || ctx_->err) {
        if (ctx_) {
            printf("Connection error: %s\n", ctx_->errstr);
            redisFree(ctx_);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }
}

Connection::~Connection() {
}

void Connection::Init(Isolate* isolate) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "Connection"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "select", Select);
  NODE_SET_PROTOTYPE_METHOD(tpl, "get", Get);

  constructor.Reset(isolate, tpl->GetFunction());
}

void Connection::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.IsConstructCall()) {
    // Invoked as constructor: `new Connection(...)`
    String::Utf8Value str(args[0]);
    const char* host = args[0]->IsUndefined() ? NULL : ToCString(str);
    double port = args[1]->IsUndefined() ? 0 : args[1]->NumberValue();
    Connection* obj = new Connection(host, port);
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } else {
    // Invoked as plain function `Connection(...)`, turn into construct call.
    const int argc = 2;
    Local<Value> argv[argc] = { args[0], args[1] };
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    Local<Context> context = isolate->GetCurrentContext();
    Local<Object> instance =
        cons->NewInstance(context, argc, argv).ToLocalChecked();
    args.GetReturnValue().Set(instance);
  }
}

void Connection::NewInstance(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  const unsigned argc = 1;
  Local<Value> argv[argc] = { args[0] };
  Local<Function> cons = Local<Function>::New(isolate, constructor);
  Local<Context> context = isolate->GetCurrentContext();
  Local<Object> instance =
      cons->NewInstance(context, argc, argv).ToLocalChecked();

  args.GetReturnValue().Set(instance);
}

void Connection::Select(const FunctionCallbackInfo<Value>& args) {
    Connection* obj = ObjectWrap::Unwrap<Connection>(args.Holder());

    int db = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
    char* cmd = (char*) malloc(128);
    sprintf(cmd, "SELECT %i", db);
    redisReply* reply = (redisReply*) redisCommand(obj->ctx_, cmd);
    freeReplyObject(reply);
    free(cmd);
}

void Connection::Get(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    Connection* obj = ObjectWrap::Unwrap<Connection>(args.Holder());

    String::Utf8Value str(args[0]);
    const char* key = args[0]->IsUndefined() ? "" : ToCString(str);

    char* cmd = (char*) malloc(strlen(key) + 8);
    sprintf(cmd, "GET %s", key);
    redisReply* reply = (redisReply*) redisCommand(obj->ctx_, cmd);
    if (reply->str) {
        args.GetReturnValue().Set(String::NewFromUtf8(isolate, reply->str));
    }
    freeReplyObject(reply);
    free(cmd);
}

}  // namespace fastredis

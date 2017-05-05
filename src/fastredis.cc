// fastredis.cc
#include <node.h>
#include "connection.h"

namespace fastredis {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void CreateConnection(const FunctionCallbackInfo<Value>& args) {
    Connection::NewInstance(args);
}

void InitAll(Local<Object> exports, Local<Object> module) {
    Connection::Init(exports->GetIsolate());
    NODE_SET_METHOD(module, "exports", CreateConnection);
}

NODE_MODULE(fastredis, InitAll)

}  // namespace fastredis

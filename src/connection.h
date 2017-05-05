// connection.h
#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <node.h>
#include <node_object_wrap.h>
#include "../deps/hiredis/hiredis.h"

namespace fastredis {

using v8::String;

class Connection : public node::ObjectWrap {
 public:
  static void Init(v8::Isolate* isolate);
  static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);

 private:
  explicit Connection(const char* host = NULL, int port = 0);
  ~Connection();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Select(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Get(const v8::FunctionCallbackInfo<v8::Value>& args);
  static v8::Persistent<v8::Function> constructor;
  const char* host_;
  int port_;
  redisContext *ctx_;
};

}  // namespace fastredis

#endif

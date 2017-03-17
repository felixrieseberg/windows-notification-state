#include <node.h>
#include <v8.h>

#ifdef _WIN32
#include "notificationstate-query.h"
#endif

using namespace v8;

void Method(const v8::FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  int returnValue = -1;

  #ifdef _WIN32
    returnValue = queryUserNotificationState();
  #endif

  args.GetReturnValue().Set(Int32::New(isolate, returnValue));
}

void Init(Handle<Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();
  exports->Set(String::NewFromUtf8(isolate, "getNotificationState"),
      FunctionTemplate::New(isolate, Method)->GetFunction());
}

NODE_MODULE(quiethours, Init)
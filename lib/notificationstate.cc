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

void Init(Local<Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();

  Nan::Set(exports, String::NewFromUtf8(isolate, "getNotificationState"),
     Nan::GetFunction(FunctionTemplate::New(isolate, Method)).ToLocalChecked()
  );
}

NODE_MODULE(quiethours, Init)

#include <node.h>
#include <v8.h>
#include <nan.h>

#ifdef _WIN32
#include "notificationstate-query.h"
#endif

using namespace v8;

void GetNotificationState(const v8::FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  int returnValue = -1;

  #ifdef _WIN32
    returnValue = queryUserNotificationState();
  #endif

  args.GetReturnValue().Set(Int32::New(isolate, returnValue));
}

NAN_MODULE_INIT(Init) {
  Nan::Set(target, Nan::New<String>("getNotificationState").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(GetNotificationState)).ToLocalChecked());
}

NODE_MODULE(quiethours, Init)

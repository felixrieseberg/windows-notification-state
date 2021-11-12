#include <node.h>
#include <v8.h>
#include <nan.h>

#ifdef _WIN32
#include "notificationstate-query.h"
#endif

using namespace v8;

NAN_METHOD(GetNotificationState)
{
  Isolate *isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  int returnValue = -1;

  returnValue = queryUserNotificationState();
  info.GetReturnValue().Set(Int32::New(isolate, returnValue));
}
NAN_METHOD(GetQuietHoursState)
{
  Isolate *isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  int returnValue = -1;

  returnValue = queryQuietHoursState();
  info.GetReturnValue().Set(Int32::New(isolate, returnValue));
}

NAN_MODULE_INIT(Init)
{
  Nan::SetMethod(target, "getNotificationState", GetNotificationState);
  Nan::SetMethod(target, "getQuietHours", GetQuietHoursState);
}

NODE_MODULE(quiethours, Init)

#include <napi.h>
#include <uv.h>

#ifdef _WIN32
#include "notificationstate-query.h"
#endif

using namespace Napi;

Napi::Value GetNotificationState(const Napi::CallbackInfo& info) {
  int returnValue = -1;

  #ifdef _WIN32
    returnValue = queryUserNotificationState();
  #endif

  return Napi::Number::New(info.Env(), returnValue);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "getNotificationState"),
              Napi::Function::New(env, GetNotificationState));

  return exports;
}

NODE_API_MODULE(quiethours, Init)

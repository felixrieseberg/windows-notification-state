#include <windows.h>
#include <shlobj.h>
#pragma comment(lib, "shell32.lib")

#include "notificationstate-query.h"

int queryUserNotificationState() {
  QUERY_USER_NOTIFICATION_STATE notificationState;
  HRESULT hr = SHQueryUserNotificationState(&notificationState);
  int returnValue = -1;

  if (SUCCEEDED(hr))
  {
    // We'll do this the dumb way
    // typedef enum  {
    //   QUNS_NOT_PRESENT              = 1,
    //   QUNS_BUSY                     = 2,
    //   QUNS_RUNNING_D3D_FULL_SCREEN  = 3,
    //   QUNS_PRESENTATION_MODE        = 4,
    //   QUNS_ACCEPTS_NOTIFICATIONS    = 5,
    //   QUNS_QUIET_TIME               = 6,
    //   QUNS_APP                      = 7
    // } QUERY_USER_NOTIFICATION_STATE;

    switch(notificationState) {
      case QUNS_NOT_PRESENT:
        returnValue = 1;
        break;
      case QUNS_BUSY:
        returnValue = 2;
        break;
      case QUNS_RUNNING_D3D_FULL_SCREEN:
        returnValue = 3;
        break;
      case QUNS_PRESENTATION_MODE:
        returnValue = 4;
        break;
      case QUNS_ACCEPTS_NOTIFICATIONS:
        returnValue = 5;
        break;
      case QUNS_QUIET_TIME:
        returnValue = 6;
        break;
      case QUNS_APP:
        returnValue = 7;
        break;
    }
  }

  return returnValue;
}
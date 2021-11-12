#define _WINSOCKAPI_

#include <windows.h>
#include <shlobj.h>
#include <tchar.h>
#pragma comment(lib, "shell32.lib")

#include <iostream>
#include <string>
#include <map>
#include "notificationstate-query.h"

// from ntdef.h
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

// from ntdef.h
typedef struct _WNF_STATE_NAME
{
    ULONG Data[2];
} WNF_STATE_NAME;

typedef struct _WNF_STATE_NAME* PWNF_STATE_NAME;
typedef const struct _WNF_STATE_NAME* PCWNF_STATE_NAME;

typedef struct _WNF_TYPE_ID
{
    GUID TypeId;
} WNF_TYPE_ID, *PWNF_TYPE_ID;

typedef const WNF_TYPE_ID* PCWNF_TYPE_ID;

typedef ULONG WNF_CHANGE_STAMP, *PWNF_CHANGE_STAMP;

enum FocusAssistResult
{
    not_supported = -2,
    failed = -1,
    off = 0,
    priority_only = 1,
    alarms_only = 2
};

std::map<int, std::string> result_map = {
    {-2, "Not Supported"},
    {-1, "Failed"},
    {0, "Off"},
    {1, "Priority Only"},
    {2, "Alarm Only"}
};

typedef NTSTATUS (NTAPI *PNTQUERYWNFSTATEDATA)(
    _In_ PWNF_STATE_NAME StateName,
    _In_opt_ PWNF_TYPE_ID TypeId,
    _In_opt_ const VOID* ExplicitScope,
    _Out_ PWNF_CHANGE_STAMP ChangeStamp,
    _Out_writes_bytes_to_opt_(*BufferSize, *BufferSize) PVOID Buffer,
    _Inout_ PULONG BufferSize);

int queryQuietHoursState()
{
    const auto h_ntdll = GetModuleHandle(_T("ntdll"));
    int returnValue = -1;

    // get pointer to function
    const auto pNtQueryWnfStateData = PNTQUERYWNFSTATEDATA(GetProcAddress(h_ntdll, "NtQueryWnfStateData"));
    if (!pNtQueryWnfStateData)
    {
        std::cerr << "[-] Error: couldn't get pointer to NtQueryWnfStateData() function." << std::endl;
        return 3;
    }

    // state name for active hours (Focus Assist)
    WNF_STATE_NAME WNF_SHEL_QUIETHOURS_ACTIVE_PROFILE_CHANGED{0xA3BF1C75, 0xD83063E};

    // note: we won't use it but it's required
    WNF_CHANGE_STAMP change_stamp = {0};

    // on output buffer will tell us the status of Focus Assist
    DWORD buffer = 0;
    ULONG buffer_size = sizeof(buffer);

    if (NT_SUCCESS(pNtQueryWnfStateData(&WNF_SHEL_QUIETHOURS_ACTIVE_PROFILE_CHANGED, nullptr, nullptr, &change_stamp, 
        &buffer, &buffer_size)))
    {
        if (result_map.count(buffer) == 0)
        {
            returnValue = 2;
        }
        else
        {
            if (buffer > 0) {
              returnValue = 1;
            }else {
              returnValue = 0;
            }
        }

    }
    else
    {
        std::cerr << "[-] Error while calling NtQueryWnfStateData." << std::endl;
        returnValue = 3;
    }

    return returnValue;
}

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
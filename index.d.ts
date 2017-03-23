declare module 'windows-notification-state' {
  export function getNotificationState(): QUERY_USER_NOTIFICATION_STATE | 'UNKNOWN_ERROR';
  export function shQueryUserNotificationState(): number;
  export type QUERY_USER_NOTIFICATION_STATE = 'QUNS_NOT_PRESENT' | 'QUNS_BUSY' | 'QUNS_RUNNING_D3D_FULL_SCREEN' | 'QUNS_PRESENTATION_MODE' | 'QUNS_ACCEPTS_NOTIFICATIONS' | 'QUNS_QUIET_TIME' | 'QUNS_APP';
}

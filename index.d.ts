declare module 'windows-notification-state' {
  export function getNotificationState(): string;
  export function shQueryUserNotificationState(): number;
}

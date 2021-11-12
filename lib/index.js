const addon = process.platform === 'win32' ? require('bindings')('notificationstate') : {};

/**
 * Returns the QUERY_USER_NOTIFICATION_STATE directly from windows.
 *
 * @returns {number} QUERY_USER_NOTIFICATION_STATE
 */
 function shQueryUserNotificationState () {
  if (process.platform !== 'win32') {
    throw new Error('windows-notification-state only works on windows')
  }

  return addon.getNotificationState()
}

/**
 * Returns the if quiet hours is enabled
 *
 * @returns {boolean} QUERY_IS_QUIET_HOURS_ENABLED
 */
function isQuietHoursEnabled () {
  if (process.platform !== 'win32') {
    throw new Error('windows-notification-state only works on windows')
  }

  return addon.getQuietHours() === 1
}

/**
 * Returns the name of the QUERY_USER_NOTIFICATION_STATE enum rather than a
 * number.
 *
 * @returns {string} QUERY_USER_NOTIFICATION_STATE
 */
function getNotificationState () {
  if (process.platform !== 'win32') {
    throw new Error('windows-notification-state only works on windows')
  }

  const QUERY_USER_NOTIFICATION_STATE = [
    '',
    'QUNS_NOT_PRESENT',
    'QUNS_BUSY',
    'QUNS_RUNNING_D3D_FULL_SCREEN',
    'QUNS_PRESENTATION_MODE',
    'QUNS_ACCEPTS_NOTIFICATIONS',
    'QUNS_QUIET_TIME',
    'QUNS_APP'
  ]

  const result = addon.getNotificationState()

  if (QUERY_USER_NOTIFICATION_STATE[result]) {
    return QUERY_USER_NOTIFICATION_STATE[result]
  } else {
    return 'UNKNOWN_ERROR'
  }
}

module.exports = {
  shQueryUserNotificationState: shQueryUserNotificationState,
  isQuietHoursEnabled: isQuietHoursEnabled,
  getNotificationState: getNotificationState
}

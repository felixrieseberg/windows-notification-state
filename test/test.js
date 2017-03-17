/* global describe, it */

const assert = require('assert')
const { spawn, execSync } = require('child_process')
const { getNotificationState, shQueryUserNotificationState } = require('../lib/index')

if (process.platform !== 'win32') {
  console.error(`You can't run this test on a non-windows machine. Sorry!`)
}

describe('shQueryUserNotificationState', () => {
  it('should return a non-negative value', () => {
    const num = shQueryUserNotificationState()
    assert.equal((num !== -1), true, 'Result is not -1 (error indiciation)')
  })

  it('should return a 5 (this test is flaky, but in most test cases, this should be true)', () => {
    const num = shQueryUserNotificationState()
    assert.equal((num === 5), true, 'Result is 5 (normal result)')
  })
})

describe('getNotificationState', () => {
  it('should return a non-error value', () => {
    const val = getNotificationState()
    assert.equal((val !== 'UNKNOWN_ERROR'), true, 'String result is okay')
  })

  it('should return a 5 (this test is flaky, but in most test cases, this should be true)', () => {
    const val = getNotificationState()
    assert.equal((val === 'QUNS_ACCEPTS_NOTIFICATIONS'), true, 'String result is okay')
  })
})

describe('Screensaver (QUNS_BUSY) test', () => {
  it('should correctly identify QUNS_BUSY', function (done) {
    this.timeout(8000)

    let secondsLeft = 3
    const interval = setInterval(() => {
      process.stdout.clearLine()
      process.stdout.cursorTo(5)
      process.stdout.write(`Starting screensaver in ${secondsLeft}s...`)
      secondsLeft = secondsLeft - 1

      if (secondsLeft === 0) {
        console.log('')
        clearInterval(interval)

        spawn(`start-screensaver.bat`, { cwd: __dirname })

        setTimeout(() => assert.equal(getNotificationState(), 'QUNS_BUSY'), 1500)
        setTimeout(() => {
          execSync('Taskkill /IM Mystify.scr /F')
          done()
        }, 2000)
      }
    }, 1000)
  })
})

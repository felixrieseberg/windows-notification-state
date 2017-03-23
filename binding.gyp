{
  "targets": [
    {
      "target_name": "notificationstate",
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "conditions": [
        ['OS=="win"', {
          "sources": [ "lib/notificationstate-query.cc", "lib/notificationstate.cc" ],
        }]
      ]
    }
  ]
}

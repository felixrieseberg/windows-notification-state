{
  "targets": [
    {
      "target_name": "notificationstate",
      "sources": [ "lib/notificationstate-query.cc", "lib/notificationstate.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}

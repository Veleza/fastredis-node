{
  'targets': [
    {
      'target_name': 'fastredis',
      'sources': [
          'src/fastredis.cc',
          'src/connection.cc'
      ],
      'include_dirs': ["<!(node -e \"require('nan')\")"],
      'dependencies': [
        'deps/hiredis.gyp:hiredis-c'
      ],
      'defines': [
          '_GNU_SOURCE'
      ],
      'cflags': [
          '-Wall',
          '-O3'
      ]
    }
  ]
}

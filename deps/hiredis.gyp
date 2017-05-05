{
  'targets': [
    {
      'target_name': 'hiredis-c',
      'type': 'static_library',
      'direct_dependent_settings': {
        'include_dirs': [ '.' ],
      },
      'sources': [
        './hiredis/sds.c',
        './hiredis/read.c',
        './hiredis/async.c',
        './hiredis/dict.c',
        './hiredis/net.c',
        './hiredis/hiredis.c',
      ],
      'conditions': [
        ['OS=="mac"', {
          'xcode_settings': {
            'GCC_C_LANGUAGE_STANDARD': 'c99'
          }
        }],
        ['OS=="solaris"', {
          'cflags+': [ '-std=c99' ]
        }]
      ]
    }
  ]
}


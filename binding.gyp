{
	'target_defaults': {
		'default_configuration': 'Release',
		'configurations': {
			'Common': {
				'cflags_cc': [ '-std=c++17', '-g', '-Wno-unknown-pragmas' ],
				'cflags!': [ '-fno-exceptions' ],
				'cflags_cc!': [ '-fno-exceptions' ],
				'include_dirs': [ './src',  '<!(node -p "require(\'node-addon-api\').include_dir")' ],
				'xcode_settings': {
					'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
					'GCC_GENERATE_DEBUGGING_SYMBOLS': 'YES',
					'CLANG_CXX_LANGUAGE_STANDARD': 'c++17',
					'MACOSX_DEPLOYMENT_TARGET': '10.9',
				},
				'msvs_settings': {
					'VCCLCompilerTool': {
						'AdditionalOptions': [ '/GR' ],
						'ExceptionHandling': '1',
					},
				},
				'msvs_disabled_warnings': [
					4101, # Unreferenced local (msvc fires these for ignored exception)
					4068, # Unknown pragma
				],
				'conditions': [
					[ 'OS == "win"', { 'defines': [ 'NOMSG', 'NOMINMAX', 'WIN32_LEAN_AND_MEAN' ] } ],
				],
			},
			'Release': {
				'inherit_from': [ 'Common' ],
				'cflags': [ '-Wno-deprecated-declarations' ],
				'xcode_settings': {
					'GCC_OPTIMIZATION_LEVEL': '3',
					'OTHER_CFLAGS': [ '-Wno-deprecated-declarations' ],
				},
				'msvs_disabled_warnings': [
					4996, # Deprecation
				],
			},
			'Debug': {
				'inherit_from': [ 'Common' ],
				'defines': [ 'V8_IMMINENT_DEPRECATION_WARNINGS' ],
			},
		},
	},
	'targets': [
		{
			'target_name': 'hzplatform',
			'cflags_cc!': [ '-fno-rtti' ],
			'xcode_settings': {
				'GCC_ENABLE_CPP_RTTI': 'YES',
			},
			'msvs_settings': {
				'VCCLCompilerTool': {
					'RuntimeTypeInfo': 'true',
				},
			},
			'conditions': [
				[ 'OS == "linux"', { 'defines': [ 'USE_CLOCK_THREAD_CPUTIME_ID' ] } ],
				[ 'OS == "mac"', {
                    'cflags+': ['-fvisibility=hidden'],
                    'xcode_settings': {
                        'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES', # -fvisibility=hidden
                    }
                } ],
			],
			'sources': [
				'src/platform/thread.cc',
				'src/platform.cc'
			],
		},
		{
			'target_name': 'action_after_build',
			'type': 'none',
			'dependencies': [ 'hzplatform' ],
			'copies': [ {
				'files': [ '<(PRODUCT_DIR)/hzplatform.node' ],
				'destination': 'out',
			} ],
		},
	],
}

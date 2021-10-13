{
	"targets": [
		{
			"target_name": "native",
			"sources": [
				"src/binding/binding.cpp",
				"src/piTest/piControlIf.c",
				"src/binding/control.c"
			],
			"include_dirs": [
				"src/",
				"src/binding",
				"<!@(node -p \"require('node-addon-api').include\")"
			],
			"dependencies": [
				"<!(node -p \"require('node-addon-api').gyp\")"
			],
			"cflags!": [ "-fno-exceptions"],
			"cflags_cc!": ["-fno-exceptions"],
			"defines": ["NAPI_CPP_EXCEPTIONS"],
			'conditions': [
				['OS=="mac"', {
				'xcode_settings': {
					'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
				}
				}]
			]
		}
	]
}
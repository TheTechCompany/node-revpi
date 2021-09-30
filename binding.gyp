{
	"targets": [
		{
			"target_name": "native",
			"sources": [
				"src/binding/binding.cpp",
				"src/piTest/piControlIf.c"
			],
			"include_dirs": [
				"src/",
				"<!@(node -p \"require('node-addon-api').include\")"
			],
			"dependencies": [
				"<!(node -p \"require('node-addon-api').gyp\")"
			],
			"cflags!": ["-I.", "-I..", "-fno-exceptions"],
			"cflags_cc!": ["-fno-exceptions"],
			"defines": ["NAPI_CPP_EXCEPTIONS"]
		}
	]
}
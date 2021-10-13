#define __cplusplus 201112L
#include <napi.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <termios.h>
#include <getopt.h>
#include <time.h>
#include <sys/types.h>
#include <stdbool.h>
#include "control.h"
#include "../piTest/piControlIf.h"
#include "../piControl.h"
using namespace Napi;

extern "C" {
	uint8_t *readVariableValue(char *pszVariableName, bool cyclic, char format, bool quiet);
	SDeviceInfo *showDeviceList();
	char *getModuleName(uint16_t moduletype);

}

Napi::Array ShowDeviceList(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
	Napi::Array device_list = Napi::Array::New(env);

	int devcount;
	int dev;
	SDeviceInfo asDevList[REV_PI_DEV_CNT_MAX];

	// Get device info
	devcount = piControlGetDeviceInfoList(asDevList);

	if (devcount < 0) {
		printf("Cannot retrieve device list: %s\n", strerror(-devcount));
		return device_list;
	}

	printf("Found %d devices:\n\n", devcount);

	 for (dev = 0; dev < devcount; dev++) {
	// 	// Show device number, address and module type
		Napi::Object obj = Napi::Object::New(env);
		obj.Set(Napi::String::New(env, "name"), getModuleName(asDevList[dev].i16uModuleType & PICONTROL_NOT_CONNECTED_MASK));

		device_list.Set(Napi::Number::New(env, dev), obj);
	 }

	return device_list;

}

Napi::Value readValue(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();

	std::string variableName = info[0].ToString().Utf8Value();

	char* var = variableName.c_str();

	Napi::Value value = Napi::Number::New(env, readVariableValue(var, false, 'd', false));
	return value;
}


Napi::Object Init(Napi::Env env, Napi::Object exports) {
	exports.Set(Napi::String::New(env, "getDeviceList"), Napi::Function::New(env, ShowDeviceList));        
    return exports;
}

NODE_API_MODULE(addon, Init)
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
	SDeviceInfo *showDeviceList();
	char *getModuleName(uint16_t moduletype);

}
Napi::String Method(const Napi::CallbackInfo& info) {
          Napi::Env env = info.Env();
          showDeviceList();
            return Napi::String::New(env, "world");
}

Napi::Object ShowDeviceList(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
	Napi::Array device_list = Napi::Array::New(env);

	SDeviceInfo *devices = showDeviceList();

	int devCount = piControlGetDeviceInfoList(devices);
	for(int dev = 0; dev < devCount; dev++){
		char *name = getModuleName(devices[dev].i16uModuleType & PICONTROL_NOT_CONNECTED_MASK);

		Napi::Object obj = Napi::Object::New(env);
		obj.Set(Napi::String::New(env, "name"), name);

		device_list.Set(Napi::Number::New(env, dev), obj);
	} 

}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
	exports.Set(Napi::String::New(env, "getDeviceList"), Napi::Function::New(env, ShowDeviceList));
          exports.Set(Napi::String::New(env, "HelloWorld"),
                                        Napi::Function::New(env, Method));
            return exports;
}

NODE_API_MODULE(addon, Init)
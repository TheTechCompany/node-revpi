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

Napi::String Method(const Napi::CallbackInfo& info) {
          Napi::Env env = info.Env();
          showDeviceList();
            return Napi::String::New(env, "world");
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
          exports.Set(Napi::String::New(env, "HelloWorld"),
                                        Napi::Function::New(env, Method));
            return exports;
}

NODE_API_MODULE(addon, Init)
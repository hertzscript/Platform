#include <platform/thread.h>
#include <napi.h>

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    return HertzScript::Platform::ThreadId::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)

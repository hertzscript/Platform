#include <platform/thread.h>

namespace HertzScript {
namespace Platform {

Napi::Object ThreadId::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ThreadId", {
        InstanceMethod("equals", &ThreadId::Equals),
    });

    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);

    exports.Set("ThreadId", func);
    return exports;
}

ThreadId::ThreadId(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<ThreadId>(info), thread_id(std::this_thread::get_id()) {
}

Napi::Value ThreadId::Equals(const Napi::CallbackInfo& info) {
    if (info.Length() <= 0 || !info[0].IsObject()) {
        Napi::TypeError::New(info.Env(), "ThreadId expected as a first argument").ThrowAsJavaScriptException();
        return Napi::Boolean::New(info.Env(), false);
    }

    Napi::Object obj = info[0].As<Napi::Object>();
    ThreadId* objUnwrap = Napi::ObjectWrap<ThreadId>::Unwrap(obj);

    return Napi::Boolean::New(info.Env(), this->thread_id == objUnwrap->thread_id);
}

} // Platform
} // HertzScript

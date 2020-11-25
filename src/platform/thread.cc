#include <platform/thread.h>

namespace HertzScript {
namespace Platform {

Napi::Object ThreadId::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "ThreadId", {
        InstanceMethod("equals", &ThreadId::Equals),
        InstanceMethod("serialize", &ThreadId::Serialize),
    });

    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);

    exports.Set("ThreadId", func);
    return exports;
}

ThreadId::ThreadId(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<ThreadId>(info) {
    if (info.Length() == 1 && info[0].IsArrayBuffer()) {
        Napi::ArrayBuffer buf = info[0].As<Napi::ArrayBuffer>();
        this->thread_id = *static_cast<std::thread::id*>(buf.Data());
    } else if (info.Length() <= 0) {
        this->thread_id = std::this_thread::get_id();
    } else {
        Napi::TypeError::New(info.Env(), "ThreadId constructor needs to be empty or expect a serialized buffer").ThrowAsJavaScriptException();
    }
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

Napi::Value ThreadId::Serialize(const Napi::CallbackInfo& info) {
    return Napi::ArrayBuffer::New(info.Env(), static_cast<void*>(&this->thread_id), sizeof(std::thread::id));
}

} // Platform
} // HertzScript

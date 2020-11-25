#ifndef HERTZSCRIPT_PLATFORM_THREAD_H
#define HERTZSCRIPT_PLATFORM_THREAD_H 1

#include <thread>
#include <napi.h>

namespace HertzScript {
namespace Platform {

class ThreadId : public Napi::ObjectWrap<ThreadId> {
  public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    ThreadId(const Napi::CallbackInfo& info);

  private:
    Napi::Value Equals(const Napi::CallbackInfo& info);

    std::thread::id thread_id;
};

} // Platform
} // HertzScript

#endif // HERTZSCRIPT_PLATFORM_THREAD_H

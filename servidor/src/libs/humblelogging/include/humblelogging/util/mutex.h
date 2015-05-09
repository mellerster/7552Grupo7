#ifndef HUMBLE_MUTEX_HEADER
#define HUMBLE_MUTEX_HEADER

#include "humblelogging/defines.h"

#ifdef _WIN32
#include "mutex_windows.h"
#else
#include "mutex_linux.h"
#endif

HL_NAMESPACE_BEGIN

class HUMBLE_EXPORT_API MutexLockGuard
{
public:
  MutexLockGuard(Mutex &lockable)
    : _lockable(lockable)
  {
    _lockable.lock();
  }

  ~MutexLockGuard()
  {
    _lockable.unlock();
  }

private:
  Mutex &_lockable;
};

HL_NAMESPACE_END
#endif

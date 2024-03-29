cmake_minimum_required(VERSION 2.8)

project(HumbleLogging)

set(VERSION_MAJOR 3)
set(VERSION_MINOR 0)
set(VERSION_EXTRA "DEVELOPMENT")

option(BuildShared "BuildShared" OFF)
option(BuildLockFree "BuildLockFree" OFF)
option(IncludeFunctionSignature "IncludeFunctionSignature" OFF)

if(BuildShared)
  set(StaticOrShared "SHARED")
  add_definitions(-DHUMBLELOGGING_EXPORT)
else(BuildShared)
  set(StaticOrShared "STATIC")
endif(BuildShared)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-std=c++11 -Wno-unused-parameter -Wno-unused-variable -Wno-sign-compare -Wno-reorder")
endif(CMAKE_COMPILER_IS_GNUCXX)

# Sources
set(headers
  include/humblelogging/appender/consoleappender.h
  include/humblelogging/appender/fileappender.h
  include/humblelogging/appender/nullappender.h
  include/humblelogging/appender/rollingfileappender.h
  include/humblelogging/util/mutex.h
  include/humblelogging/util/spinlock.h
  include/humblelogging/util/patternconfigregistry.h
  include/humblelogging/util/processinfo.h
  include/humblelogging/util/ternarytree.h
  include/humblelogging/api.h
  include/humblelogging/appender.h
  include/humblelogging/configuration.h
  include/humblelogging/defines.h
  include/humblelogging/factory.h
  include/humblelogging/formatter.h
  include/humblelogging/logevent.h
  include/humblelogging/logger.h
  include/humblelogging/loglevel.h
)

set(sources
  src/appender/consoleappender.cpp
  src/appender/fileappender.cpp
  src/appender/nullappender.cpp
  src/appender/rollingfileappender.cpp
  src/util/patternconfigregistry.cpp
  src/util/processinfo.cpp
  src/appender.cpp
  src/configuration.cpp
  src/factory.cpp
  src/formatter.cpp
  src/logevent.cpp
  src/logger.cpp
  src/loglevel.cpp
)

if(WIN32)
  add_definitions(/Zc:wchar_t-)
  add_definitions(/INCREMENTAL:NO)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  if(NOT BuildLockFree)
    list(APPEND headers include/humblelogging/util/mutex_windows.h)
    list(APPEND headers include/humblelogging/util/spinlock_windows.h)
    list(APPEND sources src/util/mutex_windows.cpp)
    list(APPEND sources src/util/spinlock_windows.cpp)
  endif()
else(WIN32)
  if(NOT BuildLockFree)
    list(APPEND headers include/humblelogging/util/mutex_linux.h)
    list(APPEND headers include/humblelogging/util/spinlock_linux.h)
    list(APPEND sources src/util/mutex_linux.cpp)
    list(APPEND sources src/util/spinlock_linux.cpp)
  endif()
endif(WIN32)

if(BuildLockFree)
  list(APPEND headers include/humblelogging/util/mutex_nolock.h)
  list(APPEND headers include/humblelogging/util/spinlock_nolock.h)
  list(APPEND sources src/util/mutex_nolock.cpp)
  list(APPEND sources src/util/spinlock_nolock.cpp)
endif(BuildLockFree)

if(IncludeFunctionSignature)
  add_definitions(-DHUMBLE_INCLUDE_PRETTY_FUNCTION)
endif(IncludeFunctionSignature)

include_directories(include)

# Target
add_library(humblelogging ${StaticOrShared} ${sources} ${headers})



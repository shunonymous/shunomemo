cmake_minimum_required(VERSION 3.2)

### C++ Version
set(CMAKE_CXX_STANDARD 17)

### Set depended libraries
# Thread
find_package(Threads)
if(CMAKE_USE_PTHREADS_INIT)
  set(THREADS_PREFER_PTHREAD_FLAG ON)
endif()

foreach(NAME IN ITEMS cxx11sleep cxx14sleep newcxx14sleep)
  add_executable(${NAME} ${NAME}.cpp)
endforeach(NAME)

find_package(PkgConfig)
pkg_check_modules(FLUIDSYNTH REQUIRED fluidsynth)

include_directories(${FLUIDSYNTH_INCLUDE_DIRS})
foreach(NAME IN ITEMS smfplayer smfplayer-final)
  add_executable(${NAME} ${NAME}.cpp)
  target_link_libraries(${NAME} ${FLUIDSYNTH_LIBRARIES})
endforeach(NAME)

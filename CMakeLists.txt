cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    threads-samples
    VERSION 0.1.0
    DESCRIPTION "Samples codes for parallel and concurrent programming in c++"
    HOMEPAGE_URL "www.github.com/FabioNevesRezende"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare executable ----

add_executable(barrier.exe source/barrier.cpp)
add_executable(producer-consumer.exe source/producer-consumer.cpp)
add_executable(condition-variable.exe source/condition-variable.cpp)
add_executable(barrier::exe ALIAS barrier.exe)

set_property(TARGET barrier.exe PROPERTY OUTPUT_NAME barrier.exe)
set_property(TARGET producer-consumer.exe PROPERTY OUTPUT_NAME producer-consumer.exe)
set_property(TARGET condition-variable.exe PROPERTY OUTPUT_NAME condition-variable.exe)

target_compile_features(barrier.exe PRIVATE cxx_std_20)
target_compile_features(producer-consumer.exe PRIVATE cxx_std_20)
target_compile_features(condition-variable.exe PRIVATE cxx_std_20)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT threads-samples_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of threads-samples"
  )
endif()

include(cmake/dev-mode.cmake)

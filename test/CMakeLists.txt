# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(threads-samplesTests LANGUAGES CXX)

# ---- Tests ----

add_executable(threads-samples_test source/threads-samples_test.cpp)
target_link_libraries(threads-samples_test PRIVATE threads-samples_lib)
target_compile_features(threads-samples_test PRIVATE cxx_std_20)

add_test(NAME threads-samples_test COMMAND threads-samples_test)

# ---- End-of-file commands ----

add_folders(Test)

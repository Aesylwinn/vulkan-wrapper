# test directory CMakeLists.txt file.
set(VWTEST_SOURCE_FILES
    test.cpp
)

add_executable(vwtest ${VWTEST_SOURCE_FILES})
target_link_libraries(vwtest vwrapper vulkan)


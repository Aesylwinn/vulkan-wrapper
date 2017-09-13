# src directory CMakeLists.txt
set(VW_SOURCE_FILES
    vw.cpp
    exception.cpp
    instance.cpp
)

add_library(vwrapper SHARED ${VW_SOURCE_FILES})
target_link_libraries(vwrapper vulkan)


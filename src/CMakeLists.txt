# src directory CMakeLists.txt
set(VW_SOURCE_FILES
    vw.cpp
    device.cpp
    exception.cpp
    instance.cpp
    physicaldevice.cpp
    queuefamily.cpp
)

add_library(vwrapper SHARED ${VW_SOURCE_FILES})
target_link_libraries(vwrapper vulkan)


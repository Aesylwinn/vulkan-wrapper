# gen CMakeLists.txt file.

configure_file(version.h.in ${CMAKE_CURRENT_BINARY_DIR}/vw/version.h)
configure_file(Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

if(Build_Documentation)
    find_package(Doxygen REQUIRED)
    add_custom_target(
        doc
        ${DOXYGEN_EXECUTABLE}
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating Doxygen documentation." VERBATIM
    )
endif(Build_Documentation)

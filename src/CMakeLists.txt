file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE HEADERS *.h)

find_package(Python3 COMPONENTS Development)

Python3_add_library(py_tiny_sea MODULE ${SOURCES} ${HEADERS})
target_include_directories(py_tiny_sea PUBLIC ".")
target_link_libraries(py_tiny_sea PRIVATE CONAN_PKG::pybind11 CONAN_PKG::tiny_sea)
set_target_properties(py_tiny_sea PROPERTIES OUTPUT_NAME "pytinysea")

install(TARGETS py_tiny_sea DESTINATION lib)

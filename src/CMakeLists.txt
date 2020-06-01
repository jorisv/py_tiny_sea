file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE HEADERS *.h)

find_package(Python3 COMPONENTS Development)

Python3_add_library(pytinysea MODULE WITH_SOABI ${SOURCES} ${HEADERS})
target_include_directories(pytinysea PUBLIC ".")
target_link_libraries(pytinysea PRIVATE CONAN_PKG::pybind11 CONAN_PKG::tiny_sea)

install(TARGETS pytinysea DESTINATION lib)

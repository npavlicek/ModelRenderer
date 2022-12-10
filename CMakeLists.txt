cmake_minimum_required (VERSION 3.8)

project(MR)

set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/lib/cmake)

add_executable (ModelRenderer "ModelRenderer.cpp" "ModelRenderer.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ModelRenderer PROPERTY CXX_STANDARD 20)
endif()

if (MSVC)
	target_compile_options(ModelRenderer PUBLIC "/ZI")
	target_link_options(ModelRenderer PUBLIC "/INCREMENTAL")
endif()

find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(ModelRenderer glfw)
target_link_libraries(ModelRenderer GLEW::glew)
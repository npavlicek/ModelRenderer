cmake_minimum_required (VERSION 3.8)

project(MR)

set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/lib/cmake)

add_executable(ModelRenderer "main.cpp"   "Shader.h" "Shader.cpp" "Camera.h" "Camera.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ModelRenderer PROPERTY CXX_STANDARD 20)
endif()

if (MSVC)
	target_compile_options(ModelRenderer PUBLIC "/ZI")
	target_link_options(ModelRenderer PUBLIC "/INCREMENTAL")
endif()

find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(ModelRenderer glfw)
target_link_libraries(ModelRenderer GLEW::glew)
target_link_libraries(ModelRenderer glm::glm)

add_custom_target(copy_shaders COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/shaders ${CMAKE_CURRENT_BINARY_DIR}/shaders)
add_dependencies(ModelRenderer copy_shaders)

add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
add_dependencies(ModelRenderer copy_assets)
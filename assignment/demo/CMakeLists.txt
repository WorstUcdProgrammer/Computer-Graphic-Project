# ---> demo 1 (a rotating triangle)
add_executable(d0_hello_triangle d0_hello_triangle/main.cpp)
target_link_libraries(d0_hello_triangle PUBLIC util-compatible)
set_target_properties(d0_hello_triangle PROPERTIES CXX_STANDARD 11) 

# ---> demo 2 (famous glxgears)
add_executable(d1_glgears d1_glgears/main.cpp d1_glgears/draw.cpp)
target_link_libraries(d1_glgears PUBLIC util-compatible)
set_target_properties(d1_glgears PROPERTIES CXX_STANDARD 11) 

# ---> demo 3 (usage of imgui + opengl2)
add_executable(d2_imgui d2_imgui/main.cpp)
target_link_libraries(d2_imgui PUBLIC util-compatible)
set_target_properties(d2_imgui PROPERTIES CXX_STANDARD 11) 

# ---> demo 3 (usage of imgui + opengl3)
add_executable(d3_imgui d3_imgui/main.cpp)
target_link_libraries(d3_imgui PUBLIC util-core-3.3)
set_target_properties(d3_imgui PROPERTIES CXX_STANDARD 11) 

# ---> demo 4 (simple shaders + loading from file)
add_executable(d4_simple_shader d4_simple_shader/main.cpp)
target_link_libraries(d4_simple_shader PUBLIC util-core-3.3)
set_target_properties(d4_simple_shader PROPERTIES CXX_STANDARD 11) 
message(STATUS "Copying shader to build directory [d4_simple_shader]")
foreach(f 
    d4_simple_shader/SimpleVertexShader.vertexshader 
    d4_simple_shader/SimpleFragmentShader.fragmentshader)
  file(COPY ${f} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach()

# ---> demo 5 (simple shaders + embeded into C)
add_executable(d5_simple_shader d5_simple_shader/main.cpp)
target_link_libraries(d5_simple_shader PUBLIC util-core-3.3)
set_target_properties(d5_simple_shader PROPERTIES CXX_STANDARD 11) 
target_add_embeded_shaders(d5_simple_shader
  OUTPUT_NAME d5_simple_shader/shaders.h
  SHADERS
  vertexshader=d5_simple_shader/SimpleVertexShader.glsl 
  fragmentshader=d5_simple_shader/SimpleFragmentShader.glsl)

# ---> demo 6 (matrices)
add_executable(d6_matrices d6_matrices/main.cpp)
target_link_libraries(d6_matrices PUBLIC util-core-3.3 glm)
set_target_properties(d6_matrices PROPERTIES CXX_STANDARD 11) 
target_add_embeded_shaders(d6_matrices
  OUTPUT_NAME d6_matrices/shaders.h
  SHADERS
  vertexshader=d6_matrices/SimpleTransform.glsl
  fragmentshader=d6_matrices/SingleColor.glsl)

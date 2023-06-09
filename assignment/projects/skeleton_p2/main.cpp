//===========================================================================//
//                                                                           //
// Copyright(c) ECS 175 (2020)                                               //
// University of California, Davis                                           //
// MIT Licensed                                                              //
//                                                                           //
//===========================================================================//

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include "shaders.h"
#include "util.hpp"
#include <fstream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace glm;

std::vector<float> xs;
std::vector<float> ys;
std::vector<float> zs;

struct Point {
    float x, y, z;
};

struct Pair {
    int a, b;
};

struct Geometry {
  std::vector<float> g_vertex_buffer_lines;
  std::vector<Point> points;
  std::vector<Pair> pairs;
  GLuint vertex_buffer_id_lines;
};

std::vector<Geometry> Geos;

template<typename T>
T
SafeRead(std::ifstream& is)
{
    T ret;
    is >> ret;
    auto rdstate = is.rdstate();
    if ((rdstate & std::ifstream::eofbit) != 0)
        throw std::runtime_error("End-of-File reached on input operation");
    if ((rdstate & std::ifstream::failbit) != 0)
        throw std::runtime_error("Logical error on i/o operation");
    if ((rdstate & std::ifstream::badbit) != 0)
        throw std::runtime_error("Read/writing error on i/o operation");
    return ret;
}

void
ReadFile(const std::string& input)
{
    std::ifstream file(input);
    if (!file.is_open())
        throw std::runtime_error("cannot open input: " + input);

    int n = SafeRead<int>(file);
    std::cout << "there are " << n << " objects" << std::endl;

    Geos.resize(n);

    for (auto& g : Geos) {
        int m = SafeRead<int>(file);
        std::cout << "there are " << m << "points" << std::endl;
        for (auto i = 0; i < m; ++i) {
            float x = SafeRead<float>(file), y = SafeRead<float>(file), z = SafeRead<float>(file);
            xs.push_back(x);
            ys.push_back(y);
            zs.push_back(z);
            g.points.push_back(Point{x, y, z});
            std::cout << "x: " << x << ",y: " << y << ",z: " << z << std::endl;
        }
        int mm = SafeRead<int>(file);
        std::cout << "there are " << mm << "edges" << std::endl;
        for (auto i = 0; i < mm; ++i) {
            int first = SafeRead<int>(file), second = SafeRead<int>(file);
            g.pairs.push_back(Pair{first, second});
            std::cout << "first: " << first << ",second: " << second << std::endl;
        }
    }
    std::sort(xs.begin(), xs.end());
    std::sort(ys.begin(), ys.end());
    std::sort(zs.begin(), zs.end());
    float x_min = xs[0];
    float y_min = ys[0];
    float z_min = zs[0];
    float x_max = xs[xs.size() - 1];
    float y_max = ys[ys.size() - 1];
    float z_max = zs[zs.size() - 1];
    float dx = x_max - x_min;
    float dy = y_max - y_min;
    float dz = z_max - z_min;
    float d = std::max({dx, dy, dz});
    for (auto& g : Geos) {
        for (int i = 0; i < g.pairs.size(); i++) {
            g.g_vertex_buffer_lines.push_back((g.points[g.pairs[i].a - 1].x - x_min) / d);
            g.g_vertex_buffer_lines.push_back((g.points[g.pairs[i].a - 1].y - y_min) / d);
            g.g_vertex_buffer_lines.push_back((g.points[g.pairs[i].a - 1].z - z_min) / d);
            g.g_vertex_buffer_lines.push_back((g.points[g.pairs[i].b - 1].x - x_min) / d);
            g.g_vertex_buffer_lines.push_back((g.points[g.pairs[i].b - 1].y - y_min) / d);
            g.g_vertex_buffer_lines.push_back((g.points[g.pairs[i].b - 1].z - z_min) / d);
        }
    }
    file.close();

    std::cout << "done" << std::endl;
}

static bool
CapturedByGUI()
{
  ImGuiIO& io = ImGui::GetIO();
  return (io.WantCaptureMouse);
}

static void
ErrorCallback(int error, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
}

static void
KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE); // close window
  }
}

static void
CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
  if (!CapturedByGUI()) {
    int left_state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int right_state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    /* cursor projection */
    // TODO (optional)

    // right click
    if (right_state == GLFW_PRESS || right_state == GLFW_REPEAT) {
      // TODO (optional)
    }

    // left click
    if (left_state == GLFW_PRESS || left_state == GLFW_REPEAT) {
      // TODO (optional)
    }

    // TODO (optional)
  }
}

void
WindowSizeCallback(GLFWwindow* window, int width, int height)
{
  // TODO (optional)
}

glm::mat4
cal_rotate(float x1, float y1, float z1, float x2, float y2, float z2, float angle)
{
    float rad = angle *  0.0175;
    float dx = x2 - x1;
    float dy = y2 - y1;
    float dz = z2 - z1;
    glm::vec3 dl= {dx,
                   dy,
                   dz};
    float l = sqrt(pow(dx, 2.0)+pow(dy, 2.0)+pow(dz, 2.0));
    dl = dl / l;
    glm::mat4 M1 = {1.0, 0.0, 0.0, (-1 * x1),
                    0.0, 1.0, 0.0, (-1 * y1),
                    0.0, 0.0, 1.0, (-1 * z1),
                    0.0, 0.0, 0.0, 1.0};
    float l2 = sqrt(pow(dy, 2.0) + pow(dz, 2.0));
    float cosb = dz / l2;
    float sinb = dy / l2;
    glm::mat4 M21 = {1.0, 0.0, 0.0, 0.0,
                     0.0, cosb, (-1 * sinb), 0.0,
                     0.0, sinb, cosb, 0.0,
                     0.0, 0.0, 0.0, 1.0};
    glm::mat4 M22 = {l2, 0.0, (-1 * dx), 0.0,
                     0.0, 1.0, 0.0, 0.0,
                     dx, 0.0, l2, 0.0,
                     0.0, 0.0, 0.0, 1.0};
    glm::mat4 M3 = {cos(rad), (-1 * sin(rad)), 0.0, 0.0,
                    sin(rad), cos(rad), 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0};
    glm::mat4 M21inverse = {1.0, 0.0, 0.0, 0.0,
                            0.0, (-1 * (cosb/((-1 * pow(sinb, 2.0)) - pow(cosb, 2.0)))), (-1 * (sinb/((-1 * pow(sinb, 2.0)) - pow(cosb, 2.0)))), 0.0,
                            0.0, (1 * (sinb/((-1 * pow(sinb, 2.0)) - pow(cosb, 2.0)))), (-1 * (cosb/((-1 * pow(sinb, 2.0)) - pow(cosb, 2.0)))), 0.0,
                            0.0, 0.0, 0.0, 1.0};
    glm::mat4 M22inverse = {(-1 * (l2 / ((-1 * pow(dx, 2.0)) - pow(l2, 2.0)))), 0.0, (-1 * (dx / ((-1 * pow(dx, 2.0)) - pow(l2, 2.0)))), 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            (1 * (1 / ((-1 * pow(dx, 2.0)) - pow(l2, 2.0)))), 0.0, (-1 * (l2 / ((-1 * pow(dx, 2.0)) - pow(l2, 2.0)))), 0.0,
                            0.0, 0.0, 0.0, 1.0};
    glm::mat4 M1inverse = {1.0, 0.0, 0.0, x1,
                           0.0, 1.0, 0.0, y1,
                           0.0, 0.0, 1.0, z1,
                           0.0, 0.0, 0.0, 1.0};
    glm::mat4 M = M1inverse * (M21inverse * M22inverse) * M3 * (M22 * M21) * M1;

    return M;




}

int
main(const int argc, const char** argv)
{

  // Initialise GLFW
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    getchar();
    return -1;
  }

  // Read in data
  if (argc < 2)
      throw std::runtime_error("missing input file");

  ReadFile(argv[1]);

  // Open a window and create its OpenGL context
  const char* glsl_version = "#version 150"; // GL 3.3 + GLSL 150
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  auto window = glfwCreateWindow(1920, 1080, "ECS 175 (P2)", NULL, NULL);
  if (window == NULL) {
    fprintf(stderr,
            "Failed to open GLFW window. If you have a GPU that is "
            "not 3.3 compatible, try a lower OpenGL version.\n");
    getchar();
    glfwTerminate();
    return -1;
  }

  // Callback
  glfwSetKeyCallback(window, KeyCallback);
  glfwSetWindowSizeCallback(window, WindowSizeCallback);
  glfwSetCursorPosCallback(window, CursorPositionCallback);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  // Load GLAD symbols
  int err = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0;
  if (err) {
    throw std::runtime_error("Failed to initialize OpenGL loader!");
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // for user menu
  static int geo_id = 0;
  static float translatex = 0.0f;
  static float translatey = 0.0f;
  static float translatez = 0.0f;
  static float scale_x = 1.0f;
  static float scale_y = 1.0f;
  static float scale_z = 1.0f;
  static float rot_x1 = 0.5f;
  static float rot_y1 = 0.5f;
  static float rot_z1 = 0.5f;
  static float rot_x2 = 0.5f;
  static float rot_y2 = 0.5f;
  static float rot_z2 = 0.5f;
  static float rot_an = 0.0f;
  // ImGui
  {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // or ImGui::StyleColorsClassic();

    // Initialize Dear ImGui
    ImGui_ImplGlfw_InitForOpenGL(
      window, true /* 'true' -> allow imgui to capture keyboard inputs */);
    ImGui_ImplOpenGL3_Init(glsl_version);
  }

  // Dark blue background (avoid using black)
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  // Enable depth test
  glEnable(GL_DEPTH_TEST);
  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);

  // TODO Create and compile our GLSL program from the shaders
  GLuint program_id = LoadProgram_FromEmbededTexts((char*)vshader, (char*)fshader);
  // TODO Create a shared vertex array
  GLuint vertex_array_id;
  glGenVertexArrays(1, &vertex_array_id);
  glBindVertexArray(vertex_array_id);
  // TODO Get handles for uniforms
  GLuint matrix_id = glGetUniformLocation(program_id, "Matrix");
  GLuint trans_matrix = glGetUniformLocation(program_id, "transMatrix");
  GLuint rotate_matrix = glGetUniformLocation(program_id, "rotateMatrix");
  GLuint render_indicator = glGetUniformLocation(program_id, "render");
  glm::mat4 matrixxy(1.0, 0.0, 0.0, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 1.0);
  glm::mat4 matrixxz(1.0, 0.0, 0.0, 0.0,
                     0.0, 0.0, 1.0, 0.0,
                     0.0, 0.0, 0.0, 0.0,
                     0.0, 0.0, 0.0, 1.0);
  glm::mat4 matrixyz(0.0, 1.0, 0.0, 0.0,
                     0.0, 0.0, 1.0, 0.0,
                     0.0, 0.0, 0.0, 0.0,
                     0.0, 0.0, 0.0, 1.0);
  // TODO Load input geometries, compute bounding boxes
  unsigned int buffer;
  //here
  unsigned int indicator_buffer;
  // TODO Create vertex buffer objects

  // Check if the ESC key was pressed or the window was closed
  while (!glfwWindowShouldClose(window)) {
    // Clear the screen and start rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    {
      // TODO Draw geometries correctly
      glGenBuffers(1, &buffer);
      glBindBuffer(GL_ARRAY_BUFFER, buffer);
      glBufferData(GL_ARRAY_BUFFER, Geos[geo_id].g_vertex_buffer_lines.size() * sizeof(float), &Geos[geo_id].g_vertex_buffer_lines[0], GL_STATIC_DRAW);
      glUseProgram(program_id);
      glEnableVertexAttribArray(0);

      glVertexAttribPointer(0,
                            3,
                            GL_FLOAT,
                            GL_FALSE,
                            0,
                            (void*) 0);
      glm::mat4 transMat(scale_x, 0.0, 0.0, translatex,
                         0.0, scale_y, 0.0, translatey,
                         0.0, 0.0, scale_z, translatez,
                         0.0, 0.0, 0.0, 1.0);
      glm::mat4 rotMat = cal_rotate(rot_x1, rot_y1, rot_z1, rot_x2, rot_y2, rot_z2, rot_an);
      if (rot_an == 0.0f){
          rotMat = {1.0, 0.0, 0.0, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0};
      }
      // here
      std::vector<float> indicator = {};
      indicator.push_back(rot_x1);
      indicator.push_back(rot_y1);
      indicator.push_back(rot_z1);
      indicator.push_back(rot_x2);
      indicator.push_back(rot_y2);
      indicator.push_back(rot_z2);
      glGenBuffers(2, &indicator_buffer);
      // end here

      glViewport(0, 0, 960, 540);
      glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &matrixxy[0][0]);
      glUniformMatrix4fv(trans_matrix, 1, GL_FALSE, &transMat[0][0]);
      glUniformMatrix4fv(rotate_matrix, 1, GL_FALSE, &rotMat[0][0]);
      // here
      glUniform1i(render_indicator, 1);
      glDrawArrays(GL_LINES, 0, Geos[geo_id].g_vertex_buffer_lines.size());

      // here
      glBindBuffer(GL_ARRAY_BUFFER, indicator_buffer);
      glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), &indicator[0], GL_STATIC_DRAW);
      glVertexAttribPointer(0,
                            3,
                            GL_FLOAT,
                            GL_FALSE,
                            0,
                            (void*) 0);
      glUniform1i(render_indicator, 0);
      glDrawArrays(GL_LINES, 0, indicator.size());
      glBindBuffer(GL_ARRAY_BUFFER, buffer);
      glBufferData(GL_ARRAY_BUFFER, Geos[geo_id].g_vertex_buffer_lines.size() * sizeof(float), &Geos[geo_id].g_vertex_buffer_lines[0], GL_STATIC_DRAW);
      glVertexAttribPointer(0,
                            3,
                            GL_FLOAT,
                            GL_FALSE,
                            0,
                            (void*) 0);
      // end here

      glViewport(0, 540, 960, 540);
      glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &matrixxz[0][0]);
      glUniformMatrix4fv(trans_matrix, 1, GL_FALSE, &transMat[0][0]);
      glUniformMatrix4fv(rotate_matrix, 1, GL_FALSE, &rotMat[0][0]);
      // here
      glUniform1i(render_indicator, 1);
      glDrawArrays(GL_LINES, 0, Geos[geo_id].g_vertex_buffer_lines.size());


        // here
        glBindBuffer(GL_ARRAY_BUFFER, indicator_buffer);
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), &indicator[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void*) 0);
        glUniform1i(render_indicator, 0);
        glDrawArrays(GL_LINES, 0, indicator.size());
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, Geos[geo_id].g_vertex_buffer_lines.size() * sizeof(float), &Geos[geo_id].g_vertex_buffer_lines[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void*) 0);
        // end here
        
      glViewport(960, 0, 960, 540);
      glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &matrixyz[0][0]);
      glUniformMatrix4fv(trans_matrix, 1, GL_FALSE, &transMat[0][0]);
      glUniformMatrix4fv(rotate_matrix, 1, GL_FALSE, &rotMat[0][0]);
      // here
      glUniform1i(render_indicator, 1);
      glDrawArrays(GL_LINES, 0, Geos[geo_id].g_vertex_buffer_lines.size());
        // here
        glBindBuffer(GL_ARRAY_BUFFER, indicator_buffer);
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), &indicator[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void*) 0);
        glUniform1i(render_indicator, 0);
        glDrawArrays(GL_LINES, 0, indicator.size());
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, Geos[geo_id].g_vertex_buffer_lines.size() * sizeof(float), &Geos[geo_id].g_vertex_buffer_lines[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void*) 0);
        // end here
      glDisableVertexAttribArray(0);
    }

    // Initialization
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    {
        ImGui::Begin("user menus");
        ImGui::Text("--------------------------------------");
        ImGui::Text("select the id of geo to change");
        ImGui::Text("--------------------------------------");
        ImGui::SliderInt("id", &geo_id, 0, Geos.size() - 1);
        ImGui::Text("--------------------------------------");
        ImGui::SliderFloat("translation of x", &translatex, -0.5f, 0.5f);
        ImGui::Text("--------------------------------------");
        ImGui::SliderFloat("translation of y", &translatey, -0.5f, 0.5f);
        ImGui::Text("--------------------------------------");
        ImGui::SliderFloat("translation of z", &translatez, -0.5f, 0.5f);
        ImGui::Text("--------------------------------------");
        ImGui::SliderFloat("scale of x", &scale_x, 0.5f, 5.0f);
        ImGui::Text("--------------------------------------");
        ImGui::SliderFloat("scale of y", &scale_y, 0.5f, 5.0f);
        ImGui::Text("--------------------------------------");
        ImGui::SliderFloat("scale of z", &scale_z, 0.5f, 5.0f);
        ImGui::Text("--------------------------------------");
        ImGui::SliderFloat("point of x1", &rot_x1, -1.0f, rot_x2);
        ImGui::Text("--------------------------------------");
        ImGui::SliderFloat("point of y1", &rot_y1, -1.0f, rot_y2);
        ImGui::Text("--------------------------------------");
        ImGui::SliderFloat("point of z1", &rot_z1, -1.0f, rot_z2);
        ImGui::Text("--------------------------------------");
        ImGui::SliderFloat("point of x2", &rot_x2, rot_x1, 1.0f);
        ImGui::Text("--------------------------------------");
        ImGui::SliderFloat("point of y2", &rot_y2, rot_y1, 1.0f);
        ImGui::Text("--------------------------------------");
        ImGui::SliderFloat("point of z2", &rot_z2, rot_z1, 1.0f);
        ImGui::Text("--------------------------------------");
        ImGui::SliderFloat("rotation angle", &rot_an, -360.0f, 360.0f);
        ImGui::Text("--------------------------------------");
        ImGui::Text("Click save to write to the txt file");
        if (ImGui::Button("Save"))
        {
            std::ofstream file;
            file.open(argv[1]);
            file << Geos.size() << "\n" << "\n";
            for (auto& g : Geos) {
                file << g.points.size() << "\n";
                for (auto& pts : g.points) {
                    glm::vec4 new_pt = glm::vec4(pts.x, pts.y, pts.z, 1);
                    glm::mat4 rotMat = cal_rotate(rot_x1, rot_y1, rot_z1, rot_x2, rot_y2, rot_z2, rot_an);
                    if (rot_an == 0.0f){
                        rotMat = {1.0, 0.0, 0.0, 0.0,
                                  0.0, 1.0, 0.0, 0.0,
                                  0.0, 0.0, 1.0, 0.0,
                                  0.0, 0.0, 0.0, 1.0};
                    }
                    glm::mat4 transMat(scale_x, 0.0, 0.0, translatex,
                                       0.0, scale_y, 0.0, translatey,
                                       0.0, 0.0, scale_z, translatez,
                                       0.0, 0.0, 0.0, 1.0);
                    new_pt = (new_pt * transMat) * rotMat;
                    file << (float) new_pt.x << " " << (float) new_pt.y << " " << (float) new_pt.z << "\n";
                }
                file << g.pairs.size() << "\n";
                for (auto& pairs : g.pairs) {
                    file << (int) pairs.a << " " << (int) pairs.b << "\n";
                }
                file << "\n";
            }
            file.close();
        }
        ImGui::End();
    }
    // Render GUI
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // TODO Cleanup VBO, VAO and shader
    glDeleteBuffers(1, &buffer);
    glDeleteVertexArrays(1, &vertex_array_id);
    glDeleteProgram(program_id);


    // Cleanup ImGui
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;
}

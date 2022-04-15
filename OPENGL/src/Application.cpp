#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Tests/TestClearColor.h"
#include "Tests/TestTranslation.h"
#include "Tests/Test3D.h"

int main(void)
{
    GLFWwindow* window;
    bool keys[1024];
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (glewInit() != GLEW_OK) {
        std::cout << "Error" << std::endl;
    }
    
    {
        std::cout << glGetString(GL_VERSION) << std::endl;
        glEnable(GL_DEPTH_TEST);
        // imgui Initialization
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
        //ImGui state variables
        bool show_demo_window = false;
        bool show_another_window = false;
        /* Loop until the user closes the window */


        test::Test* CurrentTest = nullptr;
        test::Test* Current = nullptr;
        
        test::TestMenu* testMenu = new test::TestMenu(CurrentTest, window);
        CurrentTest = testMenu;
        test::TestClearColor g;
        test::Test3D o;
        testMenu->RegisterTest<test::TestClearColor>("Sid Clear Color", &g);
        Current = new test::TestTranslation(); // look at this if the child class is inheriting it publicly you can equate it
        // yaakandre publicly inherit maadideevi ondu and virtual functions nu override maadi use maadboodu
        test::TestTranslation* a = new test::TestTranslation();
        Current = a;
        testMenu->RegisterTest<test::TestTranslation>("Translation Test" , a);
        testMenu->RegisterTest<test::Test3D>("Test3D", &o);
        Renderer renderer;
        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();// illa multiple windows baratte comment maad try maad noodu
            //imgui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            Current->OnImGuiRender();
            //Current->OnHandleKeys(window)
            if (CurrentTest) {
                CurrentTest->OnUpdate(0.0f);
                CurrentTest->OnRender();
                ImGui::Begin("Test");
                if (CurrentTest != testMenu && ImGui::Button("<-")) {
                    delete CurrentTest;
                    CurrentTest = testMenu;
                }
                CurrentTest->OnImGuiRender();
                ImGui::End();
            }
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            /* Swap front and back buffers */
            glfwSwapBuffers(window);
            /* Poll for and process events */
            glfwPollEvents();
            
        }
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();


    glfwTerminate();
    return 0;
}
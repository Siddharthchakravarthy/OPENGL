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

int main(void)
{
    GLFWwindow* window;

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



        float arr_of_positions[] = {
            -50.0f, -50.0f, 0.0f , 0.0f,            //// this is actually the position of the points of the image
            50.0f, -50.0f, 1.0f , 0.0f,          //// alva so changing this would change the resolution of the image
            50.0f, 50.0f, 1.0f , 1.0f,  
            -50.0f, 50.0f, 0.0f , 1.0f
        };

        unsigned int indexBuffer[] = {
            0 , 1 , 2,
            2 , 3 , 0
        };
    


        VertexArray va;
        VertexBuffer VerB(arr_of_positions, 4 * 4 * sizeof(float));
        //VerB.Bind();
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(VerB, layout);

        GLCall(unsigned int count_len = sizeof(indexBuffer) / sizeof(indexBuffer[0]));
        IndexBuffer Indb(indexBuffer, count_len);

        //the souce code from another file
        Shader shader("res/shader/Shader.shader");
        //shader.Bind();
        //uniform use maadkondu shader inda color na tagoladu
        //shader.SetUniform4f("u_color", 0.5f, 0.3f, 0.8f, 1.0f);
        //glUniform4f(location, 1.0f, 0.3f, 0.8f, 1.0f);
        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        
        //GLCall(glEnable(GL_BLEND));
        //GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        

        
    
    
         // ee ond value mele kalsiro bind nalli iro slot ge equal aagirbeku


        //for testing purpose i will unselect the GL_ARRAY_BUFFER and just select it using the vertex array object
        // in the while loop itself
        //as we know this is a state machine
        //va.UnBind();
        //VerB->Unbind();
        //Indb->Unbind();
    

        float col = 0.0f;
        float incre = 0.05f;
        float decre = -0.05f;
        float real_incre = 0.05f;
        Renderer renderer;


        // imgui Initialization
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
        //ImGui state variables
        bool show_demo_window = false;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        //texture initialization
        shader.Bind();
        Texture texture("res/textures/Peru_open_gl.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);
        

        glm::vec3 translationA(100.0f, 100.0f, 0.0f);
        glm::vec3 translationB(200.0f, 100.0f, 0.0f);
        /* Loop until the user closes the window */


        test::Test* CurrentTest = nullptr;
        test::Test* Current = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(CurrentTest);
        CurrentTest = testMenu;

        testMenu->RegisterTest<test::TestClearColor>("Sid Clear Color");
        Current = new test::TestClearColor(); // look at this if the child class is inheriting it publicly you can equate it
        // yaakandre publicly inherit maadideevi ondu and virtual functions nu override maadi use maadboodu 


        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            // glClear(GL_COLOR_BUFFER_BIT);
            renderer.Clear();


            //imgui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            Current->OnImGuiRender();
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
            
            
            // Dear ImGui du window implementation
            /*
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window or Help to learn ImGui", &show_demo_window);      // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &show_another_window);

                ImGui::SliderFloat3("translationA", &translationA.x, 0.0f, 960.0f);
                ImGui::SliderFloat3("translationB", &translationB.x, 0.0f, 960.0f);
                // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            } */
            //rendering imgui
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
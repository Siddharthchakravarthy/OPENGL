#include "Test.h"

namespace test {
	TestMenu::TestMenu(Test*& CurrentTest, GLFWwindow* window) :
		m_CurrentTest(CurrentTest),
		xChange(0.0f),
		yChange(0.0f)
	{
		this->CreateCallback(window);
		this->SetWindowUserPointer(window);
	}

	TestMenu::~TestMenu()
	{
	}

	void TestMenu::OnImGuiRender()
	{
		for (auto &tests : m_Tests) {
			if (ImGui::Button(tests.first.c_str())) {
				m_CurrentTest = tests.second(); // illi current aa test* variable en ide adu equal to that clear color test du * andre instance
				// ge equal aagatte amele once it gets equal alli while loop nalli application.cpp li, OnRender() and OnImGuiRender() functions
				// aa clear color test nalli overload aagidyalla adna use maadatte 
				
				/// theeeeee whole idea is that when publicly inherited a test* ee ondu test * en ide 
				/// ee test* can be made equal to a testmenu* and also all the child classes
				/// like testClearColor* and so on idu nange gottirlilla
			}
		}
	}
	void TestMenu::CreateCallback(GLFWwindow *window)
	{
		glfwSetKeyCallback(window, OnHandleKeys);
		glfwSetCursorPosCallback(window, OnHandleMouse);
	}
	void TestMenu::SetWindowUserPointer(GLFWwindow* mainWindow)
	{
		glfwSetWindowUserPointer(mainWindow, this);
	}
	void TestMenu::OnHandleKeys(GLFWwindow* window, int key, int code, int action, int mode )
	{
		TestMenu* TheMainWindow = static_cast<TestMenu*>(glfwGetWindowUserPointer(window));

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		
		if (key >= 0 && key < 1024) {
			if (action == GLFW_PRESS) {
				TheMainWindow->keys[key] = true;
				printf("Pressed: %d\n", key);
			}
			else if (action == GLFW_RELEASE) {
				TheMainWindow->keys[key] = false;
				printf("Released: %d\n", key);
			}
		}

	}
	void TestMenu::OnHandleMouse(GLFWwindow* window, double xpos, double ypos)
	{
		TestMenu* TheMainWindow = static_cast<TestMenu*> (glfwGetWindowUserPointer(window));

		if (TheMainWindow->mouseFirstMoved) {
			TheMainWindow->lastX = xpos;
			TheMainWindow->lastY = ypos;
			TheMainWindow->mouseFirstMoved = false;
		}
		
		TheMainWindow->xChange = xpos - TheMainWindow->lastX;
		TheMainWindow->yChange = TheMainWindow->lastY - ypos;

		TheMainWindow->lastX = xpos;
		TheMainWindow->lastY = ypos;
		printf("x: %.6f, y: %.6f \n", xpos, ypos);
	}
}
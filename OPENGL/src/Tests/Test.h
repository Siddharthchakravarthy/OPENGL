#pragma once
#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <functional>
#include "imgui/imgui.h"
namespace test {
	class Test {
	public:
		Test() {}
		virtual ~Test() {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Test {
	public:

		TestMenu(Test*& CurrentTest, GLFWwindow * window);
		~TestMenu();
		void OnImGuiRender() override;

		template <typename T>
		void RegisterTest(const std::string &name, T* tests) {
			m_Tests.push_back(std::make_pair(name, []() {	 return new T();	}));
		}

		/*template<>
		void RegisterTest<TestTranslation>(const std::string& name, TestTranslation tests) {
			//Test g = tests;
			// Test* ptr = &g;
			std::function<Test* ()> F_Test = &Compute;
			m_Tests.push_back(std::make_pair(name, F_Test() ) );
		}

		Test* Compute() {
			Test* G;
			TestTranslation* S;
			G = S;
			return G;
		}
		*/
	private:
		bool keys[1024];
		void CreateCallback(GLFWwindow* window);
		void SetWindowUserPointer(GLFWwindow* mainWindow);
		static void OnHandleKeys(GLFWwindow* window, int key, int code, int action, int mode);

		bool mouseFirstMoved;
		float lastX;
		float lastY;
		float xChange;
		float yChange;
		static void OnHandleMouse(GLFWwindow* window, double xpos, double ypos);
		Test*& m_CurrentTest;
		std::vector<std::pair< std::string, std::function<Test*()> > > m_Tests;
	};
}
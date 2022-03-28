#include "Test.h"

namespace test {
	TestMenu::TestMenu(Test*& CurrentTest) :
		m_CurrentTest(CurrentTest)
	{
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
}
#include "Test.h"
#include "imgui/imgui.h"

namespace test {

	TestMenu::TestMenu(Test*& currentTestPointer)
		: m_CurrentTest(currentTestPointer)
	{
	}

	void TestMenu::OnImGuiRender() // erzeugt die buttons für jeden test im Vector m_Tests
	{
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str())) // holt sich aus dem paar die erste Variable und holt sich den str ptr
				m_CurrentTest = test.second(); // setzt den aktuellen test auf die zweite variable
		}
	}
}
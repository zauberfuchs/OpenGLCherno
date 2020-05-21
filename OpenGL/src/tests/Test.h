#pragma once
#include <functional>
#include <vector>
#include <string>
#include <iostream>

namespace test {

	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);

		void OnImGuiRender() override; // sagt das die OnImGuiRender aus der Test Klasse Überschrieben wird

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering test " << name << std::endl;

			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));// fügt dem vector ein neuen test hinzu
		}
	private:
		Test*& m_CurrentTest; // referrenz pointer zum aktuellen test
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests; // Collection von paaren(String, und function die Testspointer erzeugt
	};
}
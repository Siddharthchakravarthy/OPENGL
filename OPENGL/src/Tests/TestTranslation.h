#pragma once
#include "Test.h"
namespace test {
	class TestTranslation : public Test{
	public:
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}

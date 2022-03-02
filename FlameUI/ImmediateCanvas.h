#pragma once
#include "View.h"
#include "ImGui.h"
namespace FlameUI
{
	class ImmediateCanvas :
		public View
	{

		ImGui::Context context;
		virtual void Intereact();
		volatile bool lockk;
	protected:
		LRESULT OnEvent(Message msg, WPARAM wParam, LPARAM lParam) override;
		void Draw() override;
		void IntereactPrepare();
	public:
		ImmediateCanvas(View* parent);

	};
}
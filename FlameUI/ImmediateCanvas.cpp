#include "ImmediateCanvas.h"
#include "RootView.h"

#include <iostream>
using namespace FlameUI;
using namespace D2D1;
using namespace ImGui;

ImmediateCanvas::ImmediateCanvas(View* parent) :View(parent)
{
	IntereactPrepare();
	lockk = false;
}

LRESULT ImmediateCanvas::OnEvent(Message msg, WPARAM wParam, LPARAM lParam)
{
	context.event = msg;
	switch (msg)
	{
	case FE_MOUSEMOVE:
	{
		float x = GET_X_LPARAM(lParam);
		float y = GET_Y_LPARAM(lParam);
		context.cursorPos = { x,y };
		//context.renderContext.ClearCommands();
		//context.renderContext.DrawEllipse({ x,y }, { 5,10 }, ColorF(ColorF::LemonChiffon));
		//context.renderContext.DrawEllipse({ x,y }, { 10,5 }, ColorF(ColorF::Goldenrod), 1.f);
		//context.renderContext.DrawLine({ 0,0 }, { x,y }, ColorF(ColorF::Teal));
		//context.renderContext.PushClipRect({ x / 2,y / 2,x / 2 + 100,y / 2 + 100 });
		//context.renderContext.DrawText(L"Deffered Render Context Text Drawing.", { x / 2,y / 2, x / 2 + 250, y / 2 + 250 }, ColorF(ColorF::White));
		//context.renderContext.PopClipRect();
		//context.renderContext.DrawRect({ 50,20 , 100,70 }, ColorF(ColorF::Khaki));
		//context.renderContext.DrawRect({ 80,60 , 180,100 }, ColorF(ColorF::RosyBrown), 1.f);

		//context.renderContext.DrawRoundedRect({ 150,120 , 200,170 }, { 15,10 }, ColorF(ColorF::Azure, 0.5f));
		//context.renderContext.DrawRoundedRect({ 180,160 , 230,200 }, { 10,10 }, ColorF(ColorF::Firebrick), 3.f);
		IntereactPrepare();
		break;
	}
	case FE_LBUTTONDOWN:
	{
		context.lButtonDown = true;
		IntereactPrepare();
		break;
	}
	case FE_RBUTTONDOWN:
	{
		context.rButtonDown = true;
		IntereactPrepare();
		break;
	}
	case FE_MBUTTONUP:
	{
		context.mButtonDown = true;
		IntereactPrepare();
		break;
	}
	case FE_LBUTTONUP:
	{
		context.lButtonDown = false;
		IntereactPrepare();
		break;
	}
	case FE_RBUTTONUP:
	{
		context.rButtonDown = false;
		IntereactPrepare();
		break;
	}
	case FE_MBUTTONDOWN:
	{
		context.mButtonDown = false;
		IntereactPrepare();
		break;
	}
	default:
		break;
	}
	return 0;
}
void ImmediateCanvas::Draw()
{
	while (lockk);
	lockk = true;
	auto ctx = BeginDraw({});
	context.renderContext.Excute(ctx, root->dTextFormat);
	EndDraw();
	lockk = false;
}
void ImmediateCanvas::IntereactPrepare()
{
	while (lockk);
	lockk = true;
	defaultFont = root->dTextFormat;
	context.drawPos = { 0,0 };
	context.currentClipRect = { 0,0,rect.width(),rect.height() };
	context.renderContext.ClearCommands();
	context.prevX = 0;
	context.prevX = 0;
	context.seed = 0;
	currentCotext = &context;
	Intereact();
	lockk = false;
	UpdateView();
}

void ImmediateCanvas::Intereact()
{
	ImGui::Text(L"Auto calculated sized text.");
	if (ImGui::Button(L"Button"))
	{
		std::cout << "ImGu::Button Clicked" << std::endl;
	}
	ImGui::Button(L"Button");
	ImGui::Seperator();
	ImGui::Text(L"SameLine() test.");
	ImGui::Button(L"Left"); ImGui::SameLine();
	ImGui::Button(L"Right");
	ImGui::Text(L" ");
	ImGui::Text(L"Text");
	ImGui::Seperator();
	ImGui::Text(L"Seperator");
	ImGui::Text(L"LinePadding");
}

#include "MenuFrame.h"
#include <iostream>
using namespace FlameUI;


MenuFrame::MenuFrame(Frame* parent, POINT rPos, SIZE size) :Frame(parent, size, rPos, WS_EX_TOPMOST | WS_EX_NOACTIVATE)
{
	sizable = false;
	maximal = false;
	minimal = false;
	dragble = false;
	close = false;
	Title(L"MenuFrame");
	titled = false;
	//cout << rPos.x << "," << rPos.y << endl;
	AddEventListener(this, &MenuFrame::OnKillFocus, WM_KILLFOCUS);
}

void MenuFrame::OnKillFocus(View* v, Message m, WPARAM w, LPARAM l)
{
	//std::wcout << L"KillFocus: " << (HWND)w << L":" << GetNative() << std::endl;
	if (Disposed() || (HWND)w == GetNative()) return;
	MenuFrame* ppmf = dynamic_cast<MenuFrame*>(parent);
	View* last;
	bool isc = false;
	while (ppmf)
	{
		if (ppmf->GetNative() == (HWND)w)
		{
			isc = true;
			break;
		}
		last = ppmf;
		ppmf = dynamic_cast<MenuFrame*>(ppmf->parent);
	}
	ppmf == currentSubMenu;
	while (ppmf)
	{
		if (ppmf->GetNative() == (HWND)w)
		{
			isc = true;
			break;
		}
		ppmf = ppmf->currentSubMenu;
	}


	if (ignore == 0 || w == -1)
	{
		//std::wcout << L"Success KillFocus: " << name << L":" << GetNative() << L"  Focus to:" << (HWND)w << std::endl;
		Close();
		MenuFrame* pmf = dynamic_cast<MenuFrame*>(parent);
		Frame* pf = dynamic_cast<Frame*>(parent);
		if (pf && w != -1)
		{
			SetFocus(pf->GetNative());
			//std::cout << "SetFocusTo(MF): " << pf->GetNative() << std::endl;
		}


		if (pmf)
		{
			if (w == -1)
			{
				pmf->OnKillFocus(nullptr, 0, -1, 0);
			}
		}
	}
	if (ignore > 0)
	{
		ignore--;
		std::wcout << name << L"--" << std::endl;

	}

}



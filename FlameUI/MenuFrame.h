#pragma once
#include "Frame.h"
namespace FlameUI
{
    class MenuFrame :
        public Frame
    {
        friend class MenuPainter;
        MenuFrame* currentSubMenu = nullptr;
        bool isSubMenu = false;
        void OnKillFocus(View* v, Message m, WPARAM w, LPARAM l);

        int ignore = 0;
    public:
        MenuFrame(Frame* parent,POINT rPos,SIZE size);
    };
}

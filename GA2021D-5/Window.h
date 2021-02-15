/*==============================================================================

 ウィンドウの設定 [Window.h]
 Author : Kobayashi Ryota
 Date : 2021/02/12
 --------------------------------------------------------------------------------*/

#include <Windows.h>
class Window
{
public:
	Window();
	~Window();
	static HWND Create(HINSTANCE hInstance, int nCmdShow);
};


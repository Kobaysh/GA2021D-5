/*==============================================================================

 ウィンドウの設定 [Window.cpp]
 Author : Kobayashi Ryota
 Date : 2021/02/12
 --------------------------------------------------------------------------------*/

// kobayashi you


#include "Window.h"
#include "config.h"
//#include "keyboard.h"
//	ウィンドウプロシージャ(コールバック関数)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

Window::Window()
{
}

Window::~Window()
{
}

HWND Window::Create(HINSTANCE hInstance, int nCmdShow)
{


	//	ウィンドウクラス構造体の設定
	//	オリジナルのウィンドウをシステムに登録→呼び出す
	WNDCLASS wc = {};									//	初期化して使わない部分も0にする
	wc.lpfnWndProc = WndProc;							//	ウィンドウプロシージャの指定(関数を登録:関数ポインタ)
	wc.lpszClassName = CLASS_NAME;						//	クラス名の設定(入れた名前で呼び出す)
	wc.hInstance = hInstance;							//	インスタンスハンドルの指定
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			//	マウスカーソルの設定
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);	//	ウィンドウのクライアント領域の背景色を設定(+1した値を入れる決まり)

	//	WNDCLASSEXもある	構造体の内容が増えている
	//	RegisterClassExで登録

	//	クラス登録
	RegisterClass(&wc);									//	クラスのポインタ(先頭アドレス)を指定

	//	都合の良いウィンドウサイズの算出
	RECT window_rect = { WINRECT_LEFT, WINRECT_TOP, WINRECT_RIGHT, WINRECT_BOT };
	AdjustWindowRect(&window_rect, GAME_WIN_STYLE, FALSE);
	//	left -8,top -31, right 1288, bottom 728

	// ウィンドウの矩形から幅と高さを求める
	int window_width = window_rect.right - window_rect.left;
	int window_height = window_rect.bottom - window_rect.top;

	// デスクトップのサイズを取得
	//// 方法1
	//// デスクトップの矩形を取得
	//RECT desktop_rect;
	//GetWindowRect(GetDesktopWindow(), &desktop_rect);
	//
	//// デスクトップの幅と高さを算出
	//int desktop_width = desktop_rect.right - desktop_rect.left;
	//int desktop_height = desktop_rect.bottom - desktop_rect.top;

	// 方法2
	// プライマリモニターの画面解像度取得
	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);

	//// 方法3
	//// 仮想画面の解像度取得
	//int virtual_desktop_width  = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	//int virtual_desktop_height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	//// 仮想画面の左上端座標
	//int virtual_desktop_x = GetSystemMetrics(SM_XVIRTUALSCREEN);
	//int virtual_desktop_y = GetSystemMetrics(SM_YVIRTUALSCREEN);

	// デスクトップの中心に座標を合わせる
	int window_cx = max((desktop_width - window_width) / 2, 0);
	int window_cy = max((desktop_height - window_height) / 2, 0);


	//	ウィンドウの生成
	//	ウィンドウハンドルが戻り値	HWND
	HWND hWnd = CreateWindow(
		CLASS_NAME,					//	ウィンドウ　クラス
		WINDOW_CAPTION,				//	ウィンドウ　テキスト(キャプション)
		GAME_WIN_STYLE,		//	ウィンドウ	スタイル(ビットフラグ:条件をいくつも重ねて色々な状態を作れる)
		// ^(XOR)	THICKFRAME:サイズ変更可能, MAXIMIZEBOX:最大化ボタン使用可能
		//	WS_POPUPWINDOW,	//メニュー無し

		//	サイズと位置
		window_cx,	/*左上の位置x*/		window_cy,	/*左上の位置y*/
		window_width,/*サイズx*/		window_height, /*サイズy*/

		NULL,						//	親ウィンドウハンドル(子供ウィンドウの場合)
		NULL,						//	メニューハンドル:アプリケーションメニュー(ゲームの場合重くなるので極力つけない)
		hInstance,					//	インスタンスハンドル
		NULL						//	追加のアプリケーションデータ(ほとんど使わない)
	);
	//	CreateWindowEx	ファイルのドラッグ&ドロップなどに対応

	if (hWnd == NULL) {
		//	ウィンドウが何かの理由で生成できなかった場合
		return false;	//	強制終了
	}

	//	指定のウィンドウハンドルのウィンドウを指定の方法で表示
	ShowWindow(hWnd, nCmdShow);	//	1:出したいウィンドウのハンドル,2:ウィンドウの状態(nCmdShowだとそのまま)
	UpdateWindow(hWnd);
	return hWnd;
}


//	ウィンドウプロシージャ(コールバック関数)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//	終わりの処理は必ずする	
	switch (uMsg) {
		//	WM_～のメッセージがuMsgに入りそれに対応した処理をする
	case WM_KEYDOWN:	//	キーが押されたら
		if (wParam == VK_ESCAPE) {	//	押されたキーがエスケープキーがだった場合
			SendMessage(hWnd, WM_CLOSE, 0, 0);	//	WM_CLOSEメッセージの送信

		}


	case WM_ACTIVATEAPP:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		//Keyboard_ProcessMessage(uMsg, wParam, lParam);

		break;

	case WM_CLOSE:	//	ウィンドウを閉じるメッセージ
		if (MessageBox(hWnd, "本当に終了してよろしいですか？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);	//	指定のウィンドウにWM_DESTROYメッセージを送る

		}
		return 0;	//	DefWindowProc関数にメッセージを流さず終了させ何もなかったことにする

	case WM_DESTROY:	//ウィンドウの破棄メッセージ
		PostQuitMessage(0);	//	WM_QUITメッセージの送信
		return 0;

	};

	//	通常メッセージ処理はこの関数に任せる
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
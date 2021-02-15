/*==============================================================================

 GameAward2021Amature [main.cpp]
 Author : Kobayashi Ryota
 Date : 2021/02/10
 --------------------------------------------------------------------------------

 -----------------------------------------------------------------------------------
 Todo

 ==============================================================================*/
#include <Windows.h>
#include <d3dx9.h>
#include "config.h"
#include "system_timer.h"
#include "Window.h"

 /*------------------------------------------------------------------------------
  プロトタイプ宣言
  ------------------------------------------------------------------------------*/

// メインの初期化関数
bool Main_Init(HWND hwnd);
// メインの更新関数
void Main_Update(void);
// メインの描画関数
void Main_Draw(void);
// メインの終了関数
void Main_Fin(void);
/*------------------------------------------------------------------------------
 グローバル変数宣言
------------------------------------------------------------------------------*/
static int g_frameCount = 0;
static double g_baseTime = 0;
static double g_fps = 0.0;
static double g_reserveTime = 0.0;
static double g_baseFrame = 60.0;


/*------------------------------------------------------------------------------
メイン
------------------------------------------------------------------------------*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//	使用しない一時変数を明示する
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	Window mainWindow;
	HWND hWnd = mainWindow.Create(hInstance, nCmdShow);

	if (hWnd == false) {
		MessageBox(NULL, "初期化に失敗しました", "起動失敗", MES_ERROR);
		return 1;
	}

	if (!Main_Init(hWnd)) {
		MessageBox(NULL, "初期化に失敗しました", "起動失敗", MES_ERROR);
		return 1;
	}

	//	ウィンドウメッセージの取得(メッセージループ)
	MSG msg = {};

	//	システムからのメッセージを取得するまで続ける→ループを作りたい場合、メッセージを取得しないと動かない
	//	GetMessage→PeekMessageに
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);	//	メッセージの翻訳
			DispatchMessage(&msg);	//	メッセージに対する処理	ウィンドウプロシージャが呼ばれる
		}
		else {
			//	ここがゲームループ処理
			double time = SystemTimer_GetTime();
			if ((time - g_reserveTime) < 1.0f / 60.0f) {
				Sleep(0);
				continue;
			}
			g_reserveTime = time;
			// 更新
			Main_Update();
			// 描画
			Main_Draw();

			//// シーンの切り替え処理
			//Scene_ExecuteChange();
		}
	}
	Main_Fin();
	return (int)msg.wParam;	//0が入って終了
}


bool Main_Init(HWND hwnd)
{
	// システムタイマーモジュールの初期化
	SystemTimer_Initialize();
	g_reserveTime =
		g_baseTime = SystemTimer_GetTime();
	g_frameCount = 0;
	g_baseFrame = 0;
	g_fps = 0.0f;


	

	return true;
}
// 更新関数
void Main_Update(void)
{
	// シーンのアップデート
	
	// 計測
	double time = SystemTimer_GetTime();
	if (time - g_baseTime > 1.0) {
		g_fps = (g_frameCount - g_baseFrame) / (time - g_baseTime);
		g_baseTime = time;
		g_baseFrame = g_frameCount;
	}
	g_frameCount++;
}
// 描画関数
void Main_Draw(void)
{
//	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
//	if (!pDevice) {
//		return;
//	}
//
//	// 画面のクリア
//	pDevice->Clear(0, NULL,
//		/*				配列の範囲	RECTのクリア(NULLなら全部クリア)*/
//			//D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(100, 80, 200, 255), 1.0f,			0);	// 紫背景
//		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(96, 96, 255, 255), 1.0f, 0);	// 紫背景
//	/*	色					深さ				色のクリア値				深さのクリア値	ステンシルのクリア値*/
//	// 描画パッチ命令の開始
//	pDevice->BeginScene();	//　BeginとEndはセットで
//
//
//	// シーンの描画
////	Scene_Draw();
//
//
//
//	//	pDevice->EndScene();
//	//	pDevice->BeginScene();
//		// 2次元のドローを使う
//	//	pDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
//		// デバッグ
//#ifdef _DEBUG
//
//
//#endif
//
//
//	// 描画パッチ命令の終了
//	pDevice->EndScene();
//
//	// バックバッファをフリップ(タイミングはD3DPRESENT_PARANETERSの設定による)
//	pDevice->Present(NULL, NULL, NULL, NULL);	// モニターに都合がいい時に入れ替える　1フレームに1度だけ
}
// 終了関数
void Main_Fin(void)
{
	// 終了処理は初期化の順番の逆

	
}

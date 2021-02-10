/*==============================================================================

 ゲームの設定 [config.h]
 Author : Kobayashi Ryota
 Date : 2020/06/17
 --------------------------------------------------------------------------------*/
#ifndef _CONFIG_H_
#define _CONFIG_H_

 /*------------------------------------------------------------------------------
 定数定義
 ------------------------------------------------------------------------------*/
#define CLASS_NAME "GameWindow"					//	ウィンドウクラスの名前
#define WINDOW_CAPTION "WindowCaption"			//	ウィンドウの名前

#define	SCREEN_WIDTH	1280					//	スクリーンの幅
#define	SCREEN_HEIGHT	720						//	スクリーンの高さ

#define	WINSIZE_X	500							//	ウィンドウのサイズ横
#define	WINSIZE_Y	500							//	ウィンドウのサイズ縦

#define WINRECT_LEFT	0						//	
#define WINRECT_TOP		0						//	
#define WINRECT_RIGHT	SCREEN_WIDTH			//	
#define WINRECT_BOT		SCREEN_HEIGHT			//	
#define GAME_WIN_STYLE (WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX))
 // WS_OVERLAPPEDWINDOW & ~ (WS_THICKFRAME | WS_MAXIMIZEBOX)
#define MES_ERROR (MB_OK |MB_ICONHAND)



#endif
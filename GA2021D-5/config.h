/*==============================================================================

 �Q�[���̐ݒ� [config.h]
 Author : Kobayashi Ryota
 Date : 2020/06/17
 --------------------------------------------------------------------------------*/
#ifndef _CONFIG_H_
#define _CONFIG_H_

 /*------------------------------------------------------------------------------
 �萔��`
 ------------------------------------------------------------------------------*/
#define CLASS_NAME "GameWindow"					//	�E�B���h�E�N���X�̖��O
#define WINDOW_CAPTION "WindowCaption"			//	�E�B���h�E�̖��O

#define	SCREEN_WIDTH	1280					//	�X�N���[���̕�
#define	SCREEN_HEIGHT	720						//	�X�N���[���̍���

#define	WINSIZE_X	500							//	�E�B���h�E�̃T�C�Y��
#define	WINSIZE_Y	500							//	�E�B���h�E�̃T�C�Y�c

#define WINRECT_LEFT	0						//	
#define WINRECT_TOP		0						//	
#define WINRECT_RIGHT	SCREEN_WIDTH			//	
#define WINRECT_BOT		SCREEN_HEIGHT			//	
#define GAME_WIN_STYLE (WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX))
 // WS_OVERLAPPEDWINDOW & ~ (WS_THICKFRAME | WS_MAXIMIZEBOX)
#define MES_ERROR (MB_OK |MB_ICONHAND)



#endif
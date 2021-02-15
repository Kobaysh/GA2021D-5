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
  �v���g�^�C�v�錾
  ------------------------------------------------------------------------------*/

// ���C���̏������֐�
bool Main_Init(HWND hwnd);
// ���C���̍X�V�֐�
void Main_Update(void);
// ���C���̕`��֐�
void Main_Draw(void);
// ���C���̏I���֐�
void Main_Fin(void);
/*------------------------------------------------------------------------------
 �O���[�o���ϐ��錾
------------------------------------------------------------------------------*/
static int g_frameCount = 0;
static double g_baseTime = 0;
static double g_fps = 0.0;
static double g_reserveTime = 0.0;
static double g_baseFrame = 60.0;


/*------------------------------------------------------------------------------
���C��
------------------------------------------------------------------------------*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//	�g�p���Ȃ��ꎞ�ϐ��𖾎�����
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	Window mainWindow;
	HWND hWnd = mainWindow.Create(hInstance, nCmdShow);

	if (hWnd == false) {
		MessageBox(NULL, "�������Ɏ��s���܂���", "�N�����s", MES_ERROR);
		return 1;
	}

	if (!Main_Init(hWnd)) {
		MessageBox(NULL, "�������Ɏ��s���܂���", "�N�����s", MES_ERROR);
		return 1;
	}

	//	�E�B���h�E���b�Z�[�W�̎擾(���b�Z�[�W���[�v)
	MSG msg = {};

	//	�V�X�e������̃��b�Z�[�W���擾����܂ő����遨���[�v����肽���ꍇ�A���b�Z�[�W���擾���Ȃ��Ɠ����Ȃ�
	//	GetMessage��PeekMessage��
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);	//	���b�Z�[�W�̖|��
			DispatchMessage(&msg);	//	���b�Z�[�W�ɑ΂��鏈��	�E�B���h�E�v���V�[�W�����Ă΂��
		}
		else {
			//	�������Q�[�����[�v����
			double time = SystemTimer_GetTime();
			if ((time - g_reserveTime) < 1.0f / 60.0f) {
				Sleep(0);
				continue;
			}
			g_reserveTime = time;
			// �X�V
			Main_Update();
			// �`��
			Main_Draw();

			//// �V�[���̐؂�ւ�����
			//Scene_ExecuteChange();
		}
	}
	Main_Fin();
	return (int)msg.wParam;	//0�������ďI��
}


bool Main_Init(HWND hwnd)
{
	// �V�X�e���^�C�}�[���W���[���̏�����
	SystemTimer_Initialize();
	g_reserveTime =
		g_baseTime = SystemTimer_GetTime();
	g_frameCount = 0;
	g_baseFrame = 0;
	g_fps = 0.0f;


	

	return true;
}
// �X�V�֐�
void Main_Update(void)
{
	// �V�[���̃A�b�v�f�[�g
	
	// �v��
	double time = SystemTimer_GetTime();
	if (time - g_baseTime > 1.0) {
		g_fps = (g_frameCount - g_baseFrame) / (time - g_baseTime);
		g_baseTime = time;
		g_baseFrame = g_frameCount;
	}
	g_frameCount++;
}
// �`��֐�
void Main_Draw(void)
{
//	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
//	if (!pDevice) {
//		return;
//	}
//
//	// ��ʂ̃N���A
//	pDevice->Clear(0, NULL,
//		/*				�z��͈̔�	RECT�̃N���A(NULL�Ȃ�S���N���A)*/
//			//D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(100, 80, 200, 255), 1.0f,			0);	// ���w�i
//		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(96, 96, 255, 255), 1.0f, 0);	// ���w�i
//	/*	�F					�[��				�F�̃N���A�l				�[���̃N���A�l	�X�e���V���̃N���A�l*/
//	// �`��p�b�`���߂̊J�n
//	pDevice->BeginScene();	//�@Begin��End�̓Z�b�g��
//
//
//	// �V�[���̕`��
////	Scene_Draw();
//
//
//
//	//	pDevice->EndScene();
//	//	pDevice->BeginScene();
//		// 2�����̃h���[���g��
//	//	pDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
//		// �f�o�b�O
//#ifdef _DEBUG
//
//
//#endif
//
//
//	// �`��p�b�`���߂̏I��
//	pDevice->EndScene();
//
//	// �o�b�N�o�b�t�@���t���b�v(�^�C�~���O��D3DPRESENT_PARANETERS�̐ݒ�ɂ��)
//	pDevice->Present(NULL, NULL, NULL, NULL);	// ���j�^�[�ɓs�����������ɓ���ւ���@1�t���[����1�x����
}
// �I���֐�
void Main_Fin(void)
{
	// �I�������͏������̏��Ԃ̋t

	
}

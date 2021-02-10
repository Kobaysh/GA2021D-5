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

 /*------------------------------------------------------------------------------
  �v���g�^�C�v�錾
  ------------------------------------------------------------------------------*/
  //	�E�B���h�E�v���V�[�W��(�R�[���o�b�N�֐�)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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

	//	�E�B���h�E�N���X�\���̂̐ݒ�
	//	�I���W�i���̃E�B���h�E���V�X�e���ɓo�^���Ăяo��
	WNDCLASS wc = {};									//	���������Ďg��Ȃ�������0�ɂ���
	wc.lpfnWndProc = WndProc;							//	�E�B���h�E�v���V�[�W���̎w��(�֐���o�^:�֐��|�C���^)
	wc.lpszClassName = CLASS_NAME;						//	�N���X���̐ݒ�(���ꂽ���O�ŌĂяo��)
	wc.hInstance = hInstance;							//	�C���X�^���X�n���h���̎w��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			//	�}�E�X�J�[�\���̐ݒ�
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);	//	�E�B���h�E�̃N���C�A���g�̈�̔w�i�F��ݒ�(+1�����l�����錈�܂�)

	//	WNDCLASSEX������	�\���̂̓��e�������Ă���
	//	RegisterClassEx�œo�^

	//	�N���X�o�^
	RegisterClass(&wc);									//	�N���X�̃|�C���^(�擪�A�h���X)���w��

	//	�s���̗ǂ��E�B���h�E�T�C�Y�̎Z�o
	RECT window_rect = { WINRECT_LEFT, WINRECT_TOP, WINRECT_RIGHT, WINRECT_BOT };
	AdjustWindowRect(&window_rect, GAME_WIN_STYLE, FALSE);
	//	left -8,top -31, right 1288, bottom 728

	// �E�B���h�E�̋�`���畝�ƍ��������߂�
	int window_width = window_rect.right - window_rect.left;
	int window_height = window_rect.bottom - window_rect.top;

	// �f�X�N�g�b�v�̃T�C�Y���擾
	//// ���@1
	//// �f�X�N�g�b�v�̋�`���擾
	//RECT desktop_rect;
	//GetWindowRect(GetDesktopWindow(), &desktop_rect);
	//
	//// �f�X�N�g�b�v�̕��ƍ������Z�o
	//int desktop_width = desktop_rect.right - desktop_rect.left;
	//int desktop_height = desktop_rect.bottom - desktop_rect.top;

	// ���@2
	// �v���C�}�����j�^�[�̉�ʉ𑜓x�擾
	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);

	//// ���@3
	//// ���z��ʂ̉𑜓x�擾
	//int virtual_desktop_width  = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	//int virtual_desktop_height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	//// ���z��ʂ̍���[���W
	//int virtual_desktop_x = GetSystemMetrics(SM_XVIRTUALSCREEN);
	//int virtual_desktop_y = GetSystemMetrics(SM_YVIRTUALSCREEN);

	// �f�X�N�g�b�v�̒��S�ɍ��W�����킹��
	int window_cx = max((desktop_width - window_width) / 2, 0);
	int window_cy = max((desktop_height - window_height) / 2, 0);


	//	�E�B���h�E�̐���
	//	�E�B���h�E�n���h�����߂�l	HWND
	HWND hWnd = CreateWindow(
		CLASS_NAME,					//	�E�B���h�E�@�N���X
		WINDOW_CAPTION,				//	�E�B���h�E�@�e�L�X�g(�L���v�V����)
		GAME_WIN_STYLE,		//	�E�B���h�E	�X�^�C��(�r�b�g�t���O:�������������d�˂ĐF�X�ȏ�Ԃ�����)
		// ^(XOR)	THICKFRAME:�T�C�Y�ύX�\, MAXIMIZEBOX:�ő剻�{�^���g�p�\
		//	WS_POPUPWINDOW,	//���j���[����

		//	�T�C�Y�ƈʒu
		window_cx,	/*����̈ʒux*/		window_cy,	/*����̈ʒuy*/
		window_width,/*�T�C�Yx*/		window_height, /*�T�C�Yy*/

		NULL,						//	�e�E�B���h�E�n���h��(�q���E�B���h�E�̏ꍇ)
		NULL,						//	���j���[�n���h��:�A�v���P�[�V�������j���[(�Q�[���̏ꍇ�d���Ȃ�̂ŋɗ͂��Ȃ�)
		hInstance,					//	�C���X�^���X�n���h��
		NULL						//	�ǉ��̃A�v���P�[�V�����f�[�^(�قƂ�ǎg��Ȃ�)
	);
	//	CreateWindowEx	�t�@�C���̃h���b�O&�h���b�v�ȂǂɑΉ�

	if (hWnd == NULL) {
		//	�E�B���h�E�������̗��R�Ő����ł��Ȃ������ꍇ
		return 1;	//	�����I��
	}

	//	�w��̃E�B���h�E�n���h���̃E�B���h�E���w��̕��@�ŕ\��
	ShowWindow(hWnd, nCmdShow);	//	1:�o�������E�B���h�E�̃n���h��,2:�E�B���h�E�̏��(nCmdShow���Ƃ��̂܂�)
	UpdateWindow(hWnd);

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

//	�E�B���h�E�v���V�[�W��(�R�[���o�b�N�֐�)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//	�I���̏����͕K������	
	switch (uMsg) {
		//	WM_�`�̃��b�Z�[�W��uMsg�ɓ��肻��ɑΉ���������������
	case WM_KEYDOWN:	//	�L�[�������ꂽ��
		if (wParam == VK_ESCAPE) {	//	�����ꂽ�L�[���G�X�P�[�v�L�[���������ꍇ
			SendMessage(hWnd, WM_CLOSE, 0, 0);	//	WM_CLOSE���b�Z�[�W�̑��M

		}


	case WM_ACTIVATEAPP:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
	//	Keyboard_ProcessMessage(uMsg, wParam, lParam);

		break;

	case WM_CLOSE:	//	�E�B���h�E����郁�b�Z�[�W
		if (MessageBox(hWnd, "�{���ɏI�����Ă�낵���ł����H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);	//	�w��̃E�B���h�E��WM_DESTROY���b�Z�[�W�𑗂�

		}
		return 0;	//	DefWindowProc�֐��Ƀ��b�Z�[�W�𗬂����I�����������Ȃ��������Ƃɂ���

	case WM_DESTROY:	//�E�B���h�E�̔j�����b�Z�[�W
		PostQuitMessage(0);	//	WM_QUIT���b�Z�[�W�̑��M
		return 0;

	};

	//	�ʏ탁�b�Z�[�W�����͂��̊֐��ɔC����
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
// �������֐�
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

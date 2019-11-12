

#include "main.h"
#include <list>
#include <vector>

#include "game_object.h"
#include "scene.h"
#include "manager.h"


const char* CLASS_NAME = "DX11AppClass";
const char* WINDOW_NAME = "Miku of Duty";


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


HWND g_Window;

HWND GetWindow()
{
	return g_Window;
}


int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	g_Window = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		(GetSystemMetrics(SM_CXSCREEN) * 0.5f - SCREEN_WIDTH * 0.5f) * 0.5f,
		(GetSystemMetrics(SM_CYSCREEN) * 0.5f - SCREEN_HEIGHT * 0.5f) * 0.5f,
		(GetSystemMetrics(SM_CXSCREEN) * 0.5f + SCREEN_WIDTH * 0.5f),
		(GetSystemMetrics(SM_CYSCREEN) * 0.5f + SCREEN_HEIGHT * 0.5f),
		NULL,
		NULL,
		hInstance,
		NULL);


	// ����������(�E�B���h�E���쐬���Ă���s��)
	CManager::Init();


	// �E�C���h�E�̕\��(�����������̌�ɍs��)
	ShowWindow(g_Window, nCmdShow);
	UpdateWindow(g_Window);



	//�t���[���J�E���g������
	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;


	// ���b�Z�[�W���[�v
	MSG msg;
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				CManager::Update();

				// �`�揈��
				CManager::Draw();
			}
		}
	}

	timeEndPeriod(1);				// ����\��߂�

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	CManager::Uninit();

	return (int)msg.wParam;
}


//=============================================================================
// �E�C���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

float ToRadian(float degree)
{
	return (degree) * (D3DX_PI / 180.0f);
}

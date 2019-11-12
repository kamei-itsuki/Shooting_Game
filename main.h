#ifndef MAIN_H_
#define MAIN_H_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <assert.h>

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

#define D3DX_PI	((float)3.141592)

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "xaudio2.lib")


#define SCREEN_WIDTH	(960)			// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(540)			// �E�C���h�E�̍���


HWND GetWindow();

float ToRadian(float degree);			//�x�����W�A���ɕϊ�����֐�

#endif // !MAIN_H_

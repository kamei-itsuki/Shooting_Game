#include "main.h"
#include "input.h"


BYTE CInput::m_OldKeyState[256];
BYTE CInput::m_KeyState[256];
POINT CInput::m_MousePt;

void CInput::Init()
{

	memset( m_OldKeyState, 0, 256 );
	memset( m_KeyState, 0, 256 );

}

void CInput::Uninit()
{


}

void CInput::Update()
{
	GetCursorPos(&m_MousePt);

	memcpy( m_OldKeyState, m_KeyState, 256 );

	GetKeyboardState( m_KeyState );

}

bool CInput::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool CInput::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}

float CInput::GetMousePosX()
{
	return m_MousePt.x;
}

float CInput::GetMousePosY()
{
	return m_MousePt.y;
}

void CInput::MouseReset()
{
	SetCursorPos(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);
}

bool CInput::MouseLeftClick()
{
	if (MOUSEEVENTF_LEFTDOWN == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

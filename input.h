#ifndef INPUT_H_
#define INPUT_H_

class CInput
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];
	static POINT m_MousePt;
public:
	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );

	static float GetMousePosX();
	static float GetMousePosY();
	static void MouseReset();
	static bool MouseLeftClick();

};

#endif // !INPUT_H_

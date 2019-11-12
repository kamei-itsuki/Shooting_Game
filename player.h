#ifndef PLAYER_H_
#define PLAYER_H_

class CPlayer : public CGameObject
{
private:
	XMFLOAT3 m_FrontVec;
	XMFLOAT3 m_RightVec;
	float m_MousePosX;
	float m_MousePosY;
	float m_MoveMouseX;
	float m_MoveMouseY;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	XMFLOAT3 GetFlontVec();
	XMFLOAT3 GetRightVec();
	
};

#endif // !PLAYER_H_

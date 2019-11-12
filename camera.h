#ifndef CAMERA_H_
#define CAMERA_H_

class CCamera : public CGameObject
{
private:
	RECT     m_Viewport;
	XMMATRIX m_ViewMatrix;
	XMMATRIX m_InvViewMatrix;
	XMMATRIX m_ProjectionMatrix;
	XMVECTOR m_Quaternion;
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
	XMMATRIX GetViewMatrix();
};

#endif // !CAMERA_H_

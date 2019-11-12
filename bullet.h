#ifndef BULLET_H_
#define BULLET_H_

class CBullet : public CGameObject
{
private:
	CModel m_Model;
	XMFLOAT3 m_FrontVec;

public:
	CBullet();
	~CBullet();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetPosition(XMFLOAT3 position);
};


#endif // !BULLET_H_

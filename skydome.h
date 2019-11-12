#ifndef SKYDOME_H_
#define SKYDOME_H_

class CSkydome : public CGameObject
{
private:
	CModel* m_Model;

public:
	CSkydome();
	~CSkydome();
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

#endif // !SKYDOME_H_

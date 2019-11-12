#ifndef GUN_H_
#define GUN_H_

class CGun : public CGameObject
{
private:
	CModel* m_Model;

public:
	CGun();
	~CGun();
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

#endif // !GUN_H_

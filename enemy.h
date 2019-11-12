#ifndef ENEMY_H_
#define ENEMY_H_

class CEnemy : public CGameObject
{
private:
	CModel* m_Model;

public:
	CEnemy();
	~CEnemy();
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

#endif // !ENEMY_H_
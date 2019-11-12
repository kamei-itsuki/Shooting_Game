#ifndef TITLE_H_
#define TITLE_H_

class CTitle : public CScene
{
private:
	CAudioClip* m_BGM;
public:
	void Init();
	void Uninit();
	void Update();
};

#endif // !TITLE_H_

#ifndef TUTORIAL_H_
#define TUTORIAL_H_

class CTutorial : public CScene
{
private:
	CAudioClip* m_BGM;
public:
	void Init();
	void Uninit();
	void Update();
};

#endif // !TUTORIAL_H_

#ifndef RESULT_H_
#define RESULT_H_

class CResult : public CScene
{
private:
	CAudioClip* m_BGM;
public:
	void Init();
	void Uninit();
	void Update();
};
#endif // !RESULT_H_

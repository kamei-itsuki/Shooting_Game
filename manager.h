#ifndef MANAGER_H_
#define MANAGER_H_

class CScene;		//前方宣言（ポインタの時だけ使える）

class CManager
{
private:
	static CScene* m_Scene;

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static CScene* GetScene();

	template <typename T>
	static void SetScene()
	{
		if (m_Scene != nullptr)
		{
			m_Scene->Uninit();
			delete m_Scene;

			m_Scene = new T();
			m_Scene->Init();
		}
		else
		{
			m_Scene = new T();
			m_Scene->Init();
		}
	}
};

#endif // !MANAGER_H_

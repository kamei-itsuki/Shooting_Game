#ifndef SCENE_H_
#define SCENE_H_

#define LAYER_MAX_NUM	(5)

#include "audio_clip.h"

class CScene
{
protected:
	std::list<CGameObject*> m_GameObject[LAYER_MAX_NUM];
	CAudioClip* m_BGM;

public:
	CScene(){}
	virtual ~CScene(){}

	template <typename T>

	T* AddGameObject(int Layer)		//�����Ȃ�Init�̃e���v���[�g�֐�
	{
		T* object = new T();
		object->Init();
		m_GameObject[Layer].push_back(object);
		return object;
	}

	template <typename T>
	T* GetGameObject(int Layer)
	{
		for (CGameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))
			{
				return (T*)object;
			}
		}
		//����������Ȃ�������nullptr��Ԃ�
		return nullptr;
	}

	template <typename T>
	std::vector<T*> GetGameObjects(int Layer)
	{
		std::vector<T*> objects;
		for (CGameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}
		//����������Ȃ�������nullptr��Ԃ�
		return objects;	
	}

	virtual void Init() = 0;	//�������z�֐�

	virtual void Uninit()
	{
		for (int i = 0; i < LAYER_MAX_NUM; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();	//�g���I�������clear�Œ��g����ɂ���
		}
	}

	virtual void Update()
	{
		for (int i = 0; i < LAYER_MAX_NUM; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Update();
			}
									//��[]�͖��O�̖����֐���������Ă����錾
			m_GameObject[i].remove_if([](CGameObject* object) {return object->Destroy(); });
		}
	}

	virtual void Draw()
	{
		for (int i = 0; i < LAYER_MAX_NUM; i++)
		{
			for (CGameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}

	void DestroyGameObject(CGameObject* GameObject)
	{
		GameObject->SetDestroy();
	}
};

#endif // !SCENE_H_

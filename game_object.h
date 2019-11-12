#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "main.h"
#include "audio_clip.h"

class CGameObject
{
protected:
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;
	XMMATRIX m_World;
	bool m_Destroy = false;
	CAudioClip* m_SE;

public:
	CGameObject(){}
	virtual ~CGameObject(){}
	virtual void Init(){}
	virtual void Uninit(){}
	virtual void Update(){}
	virtual void Draw(){}

	XMFLOAT3 GetPosition()
	{
		return m_Position;
	}

	XMFLOAT3 GetRotation()
	{
		return m_Rotation;
	}

	void SetDestroy()
	{
		m_Destroy = true;
	}

	bool Destroy()
	{
		if (m_Destroy == true)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}
};


#endif // !GAMEOBJECT_H_

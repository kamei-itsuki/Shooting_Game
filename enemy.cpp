#include "main.h"

#include "input.h"

#include "renderer.h"
#include "game_object.h"
#include "model.h"
#include "enemy.h"


CEnemy::CEnemy()
{

}

CEnemy::~CEnemy()
{

}

void CEnemy::Init()
{
	float PosX = rand() % 100 - 50.0f;
	float PosZ = rand() % 100 - 50.0f;
	float Rotat = rand() % 360;
	m_Position = XMFLOAT3(PosX, 0.7f, PosZ);
	m_Rotation = XMFLOAT3(0.0f, ToRadian(Rotat), 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	m_Model = new CModel;

	m_Model->Load("asset/model/miku_01.obj");


}

void CEnemy::Uninit()
{
	m_Model->Unload();
	delete m_Model;
}

void CEnemy::Update()
{
	XMFLOAT3 flont = XMFLOAT3(m_World.r[2].m128_f32[0], m_World.r[2].m128_f32[1], m_World.r[2].m128_f32[2]);	//行列の3行目の値

//移動処理
	if (CInput::GetKeyPress('U'))
	{
		m_Position.x += flont.x * 0.05f;
		m_Position.y += flont.y * 0.05f;
		m_Position.z += flont.z * 0.05f;
	}

	if (CInput::GetKeyPress('J'))
	{
		m_Position.x -= flont.x * 0.05f;
		m_Position.y -= flont.y * 0.05f;
		m_Position.z -= flont.z * 0.05f;
	}

	//回転処理
	if (CInput::GetKeyPress('K'))
	{
		m_Rotation.y -= 0.05;
	}

	if (CInput::GetKeyPress('H'))
	{
		m_Rotation.y += 0.05;
	}
}

void CEnemy::Draw()
{
	// マトリクス設定
	m_World = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	m_World *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	m_World *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	CRenderer::SetWorldMatrix(&m_World);

	m_Model->Draw();
}

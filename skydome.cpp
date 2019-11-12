#include "main.h"
#include "input.h"
#include "renderer.h"
#include "game_object.h"
#include "model.h"
#include "skydome.h"

CSkydome::CSkydome()
{
}

CSkydome::~CSkydome()
{
}

void CSkydome::Init()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(20.0f, 20.0f, 20.0f);

	m_Model = new CModel;

	m_Model->Load("asset/model/sky.obj");
}

void CSkydome::Uninit()
{
	m_Model->Unload();
	delete m_Model;
}

void CSkydome::Update()
{
}

void CSkydome::Draw()
{
	// マトリクス設定
	m_World = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	m_World *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	m_World *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	CRenderer::SetWorldMatrix(&m_World);

	m_Model->Draw();
}

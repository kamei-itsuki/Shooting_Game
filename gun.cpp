#include "main.h"
#include <list>
#include <typeinfo>
#include <vector>

#include "input.h"
#include "audio_clip.h"

#include "renderer.h"
#include "game_object.h"
#include "scene.h"
#include "manager.h"
#include "game.h"

#include "model.h"
#include "enemy.h"
#include "bullet.h"
#include "meshfield.h"
#include "player.h"
#include "gun.h"

CGun::CGun()
{
}

CGun::~CGun()
{
}

void CGun::Init()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	m_Model = new CModel;

	m_Model->Load("asset/model/gun.obj");
}

void CGun::Uninit()
{
	m_Model->Unload();
	delete m_Model;
}

void CGun::Update()
{
	CPlayer* player;
	player = CManager::GetScene()->GetGameObject<CPlayer>(2);

	m_Position.x = player->GetPosition().x + (player->GetFlontVec().x * 20.0f) + (player->GetRightVec().x * 10.0f);
	m_Position.y = player->GetPosition().y + (player->GetFlontVec().y * 20.0f) + (player->GetRightVec().y * 10.0f) - 0.3f;
	m_Position.z = player->GetPosition().z + (player->GetFlontVec().z * 20.0f) + (player->GetRightVec().z * 10.0f);

	m_Rotation.x = player->GetRotation().x;
	m_Rotation.y = player->GetRotation().y + ToRadian(90.0f);
}

void CGun::Draw()
{
	// マトリクス設定
	m_World = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	m_World *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	m_World *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	CRenderer::SetWorldMatrix(&m_World);

	m_Model->Draw();
}

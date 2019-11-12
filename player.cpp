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

#include "camera.h"
#include "model.h"
#include "bullet.h"
#include "enemy.h"
#include "meshfield.h"
#include "player.h"


void CPlayer::Init()
{
	m_Position = XMFLOAT3(0.0f, 0.5f, 0.0);
	m_Rotation = XMFLOAT3(0.0f, 0.0, 0.0f);
	m_Scale = XMFLOAT3(0.1f, 0.1f, 0.1f);

	m_MousePosX = 0;
	m_MousePosY = 0;
	m_MoveMouseX = 0;
	m_MoveMouseY = 0;

	m_SE = new CAudioClip();
	m_SE->Load("asset/sound/shot.wav");
}

void CPlayer::Uninit()
{
	m_SE->Unload();
	delete m_SE;
}

void CPlayer::Update()
{
	//X軸回転の制御

	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		CScene* scene = CManager::GetScene();
		CBullet* bullet = scene->AddGameObject<CBullet>(3);
		bullet->SetPosition(m_Position);

		m_SE->Play(false);	//引数trueでループ、なしもしくはfalseで一回だけ流す
	}
}

void CPlayer::Draw()
{
	// マトリクス設定
	m_World = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	m_World *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	m_World *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	CRenderer::SetWorldMatrix(&m_World);
}

XMFLOAT3 CPlayer::GetFlontVec()
{
	return m_FrontVec;
}

XMFLOAT3 CPlayer::GetRightVec()
{
	return m_RightVec;
}

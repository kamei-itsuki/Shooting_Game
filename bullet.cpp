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
#include "player.h"
#include "enemy.h"
#include "bullet.h"


CBullet::CBullet()
{
	CPlayer* player;
	player = CManager::GetScene()->GetGameObject<CPlayer>(2);

	m_FrontVec = player->GetFlontVec();
}

CBullet::~CBullet()
{

}

void CBullet::Init()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(-ToRadian(90.0f), 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.5f, 0.5f, 0.5f);

	m_Model.Load("asset/model/bullet.obj");

	m_SE = new CAudioClip();
	m_SE->Load("asset/sound/hit.wav");
}

void CBullet::Uninit()
{
	m_SE->Unload();
	delete m_SE;


	m_Model.Unload();
}

void CBullet::Update()
{
	//移動処理
	m_Position.x += m_FrontVec.x * 25.0f;
	m_Position.y += m_FrontVec.y * 25.0f;
	m_Position.z += m_FrontVec.z * 25.0f;

	//m_Position.x += 0.5f;

	//とりあえずの弾の消去処理
	if (m_Position.x > 50.0f || m_Position.x < -50.0f || m_Position.z > 50.0f || m_Position.z < -50.0f)
	{
		CManager::GetScene()->DestroyGameObject(this);
		return;
	}

	//複数のエネミーとの当たり判定
	std::vector<CEnemy*> enemys;
	enemys = CManager::GetScene()->GetGameObjects<CEnemy>(2);

	for (CEnemy* enemy : enemys)
	{
		XMFLOAT3 enemyPos = enemy->GetPosition();
		if (m_Position.x > enemyPos.x - 1.0f && m_Position.x < enemyPos.x + 1.0f &&
			m_Position.z > enemyPos.z - 1.0f && m_Position.z < enemyPos.z + 1.0f)
		{
			CManager::GetScene()->DestroyGameObject(enemy);
			CManager::GetScene()->DestroyGameObject(this);
			m_SE->Play(false);	//引数trueでループ、なしもしくはfalseで一回だけ流す

			return;
		}
	}

	/*CEnemy* enemy;
	enemy = CManager::GetScene()->GetGameObject<CEnemy>(2);

	if (enemy != nullptr)
	{
		XMFLOAT3 enemyPos = enemy->GetPosition();
		if (m_Position.x > enemyPos.x - 1 && m_Position.x < enemyPos.x + 1 &&
			m_Position.z > enemyPos.z - 1 && m_Position.z < enemyPos.z + 1)
		{
			CManager::GetScene()->DestroyGameObject(enemy);
			CManager::GetScene()->DestroyGameObject(this);
			return;
		}
	}*/

}

void CBullet::Draw()
{
	// マトリクス設定
	m_World = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	m_World *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	m_World *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	CRenderer::SetWorldMatrix(&m_World);

	m_Model.Draw();
}

void CBullet::SetPosition(XMFLOAT3 position)
{
	m_Position = position;
}

#include "main.h"
#include <list>
#include <vector>

#include "input.h"
#include "audio_clip.h"

#include "renderer.h"
#include "game_object.h"
#include "scene.h"
#include "manager.h"
#include "result.h"
#include "game.h"

#include "camera.h"
#include "field.h"
#include "model.h"
#include "skydome.h"
#include "bullet.h"
#include "player.h"
#include "gun.h"
#include "enemy.h"
#include "meshfield.h"
#include "polygon.h"

static int g_FrameCounter;

void CGame::Init()
{
	//カメラの初期化
	AddGameObject<CCamera>(0);

	//フィールドの初期化
	AddGameObject<CField>(1);

	//メッシュフィールドの初期化
	CMeshfield* meshfield = new CMeshfield();
	meshfield->Init(1.0f, 1.0f, 200, 200);
	m_GameObject[1].push_back(meshfield);

	//スカイドームの初期化
	AddGameObject<CSkydome>(1);

	//プレイヤーの初期化
	AddGameObject<CPlayer>(2);

	//銃の初期化
	AddGameObject<CGun>(2);

	//エネミーの初期化
	//AddGameObject<CEnemy>(2);

	//ビルボード
	//AddGameObject<CBillboard>(3);

	//ポリゴンの初期化
	CPolygon* polygon = new CPolygon();
	polygon->Init("asset/texture/UI.tga");
	m_GameObject[4].push_back(polygon);

	m_BGM = new CAudioClip();
	m_BGM->Load("asset/sound/test.wav");
	m_BGM->Play(true);	//引数trueでループ、なしもしくはfalseで一回だけ流す

	//カーソル非表示
	//ShowCursor(false);

	g_FrameCounter = 0;
}

void CGame::Uninit()
{
	m_BGM->Stop();
	m_BGM->Unload();
	delete m_BGM;

	//カーソル表示
	ShowCursor(true);

	CScene::Uninit();
}

void CGame::Update()
{
	CScene::Update();
	

	//if (g_FrameCounter % 60 == 0)
	//{
	//	CScene* scene = CManager::GetScene();
	//	CEnemy* enemy = scene->AddGameObject<CEnemy>(2);
	//}

	//if (g_FrameCounter == 1800)
	//{
	//	CManager::SetScene<CResult>();
	//}

	//g_FrameCounter++;
}

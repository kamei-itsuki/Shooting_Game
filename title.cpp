#include "main.h"
#include <list>
#include <vector>

#include "input.h"
#include "audio_clip.h"

#include "renderer.h"
#include "game_object.h"
#include "scene.h"
#include "manager.h"
#include "tutorial.h"
#include "title.h"

#include "polygon.h"

void CTitle::Init()
{
	//ポリゴンの初期化
	CPolygon* polygon = new CPolygon();
	polygon->Init("asset/texture/title.tga");
	m_GameObject[4].push_back(polygon);

	m_BGM = new CAudioClip();
	m_BGM->Load("asset/sound/title.wav");
	m_BGM->Play(true);	//引数trueでループ、なしもしくはfalseで一回だけ流す
}

void CTitle::Uninit()
{
	m_BGM->Stop();
	m_BGM->Unload();
	delete m_BGM;

	CScene::Uninit();
}

void CTitle::Update()
{
	CScene::Update();

	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CManager::SetScene<CTutorial>();
	}
}

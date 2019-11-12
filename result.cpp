#include "main.h"
#include <list>
#include <vector>

#include "input.h"
#include "audio_clip.h"

#include "renderer.h"
#include "game_object.h"
#include "scene.h"
#include "manager.h"
#include "title.h"
#include "result.h"

#include "polygon.h"

void CResult::Init()
{
	//�|���S���̏�����
	CPolygon* polygon = new CPolygon();
	polygon->Init("asset/texture/result.tga");
	m_GameObject[4].push_back(polygon);

	m_BGM = new CAudioClip();
	m_BGM->Load("asset/sound/result.wav");
	m_BGM->Play(true);	//����true�Ń��[�v�A�Ȃ���������false�ň�񂾂�����
}

void CResult::Uninit()
{
	m_BGM->Stop();
	m_BGM->Unload();
	delete m_BGM;

	CScene::Uninit();
}

void CResult::Update()
{
	CScene::Update();

	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CManager::SetScene<CTitle>();
	}
}

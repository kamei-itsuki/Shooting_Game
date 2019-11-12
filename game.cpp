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
	//�J�����̏�����
	AddGameObject<CCamera>(0);

	//�t�B�[���h�̏�����
	AddGameObject<CField>(1);

	//���b�V���t�B�[���h�̏�����
	CMeshfield* meshfield = new CMeshfield();
	meshfield->Init(1.0f, 1.0f, 200, 200);
	m_GameObject[1].push_back(meshfield);

	//�X�J�C�h�[���̏�����
	AddGameObject<CSkydome>(1);

	//�v���C���[�̏�����
	AddGameObject<CPlayer>(2);

	//�e�̏�����
	AddGameObject<CGun>(2);

	//�G�l�~�[�̏�����
	//AddGameObject<CEnemy>(2);

	//�r���{�[�h
	//AddGameObject<CBillboard>(3);

	//�|���S���̏�����
	CPolygon* polygon = new CPolygon();
	polygon->Init("asset/texture/UI.tga");
	m_GameObject[4].push_back(polygon);

	m_BGM = new CAudioClip();
	m_BGM->Load("asset/sound/test.wav");
	m_BGM->Play(true);	//����true�Ń��[�v�A�Ȃ���������false�ň�񂾂�����

	//�J�[�\����\��
	//ShowCursor(false);

	g_FrameCounter = 0;
}

void CGame::Uninit()
{
	m_BGM->Stop();
	m_BGM->Unload();
	delete m_BGM;

	//�J�[�\���\��
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

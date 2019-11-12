#include "main.h"
#include <list>
#include <vector>

#include "input.h"

#include "renderer.h"
#include "game_object.h"
#include "scene.h"
#include "manager.h"
#include "title.h"
#include "game.h"

CScene* CManager::m_Scene = nullptr;

void CManager::Init()
{
	CRenderer::Init();

	CInput::Init();

	CAudioClip::Init();

	//m_Scene = new CScene();
	//m_Scene->Init();

	//SetScene<CTitle>();
	SetScene<CGame>();
}

void CManager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;

	CInput::Uninit();

	CAudioClip::Uninit();

	CRenderer::Uninit();
}

void CManager::Update()
{
	CInput::Update();

	m_Scene->Update();
}

void CManager::Draw()
{

	CRenderer::Begin();

	m_Scene->Draw();

	CRenderer::End();

}

CScene* CManager::GetScene()
{
	return m_Scene;
}

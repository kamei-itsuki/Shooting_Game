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
#include "camera.h"

#define MOVE_SPEED (0.25f)

void CCamera::Init()
{

	m_Position = XMFLOAT3( 0.0f, 1.5f, 0.0f );
	m_Rotation = XMFLOAT3( 0.0f, 0.0f, 0.0f );

	m_Viewport.left = 0;
	m_Viewport.top = 0;
	m_Viewport.right = SCREEN_WIDTH;
	m_Viewport.bottom = SCREEN_HEIGHT;

}


void CCamera::Uninit()
{


}


void CCamera::Update()
{
	m_FrontVec = XMFLOAT3(m_InvViewMatrix.r[2].m128_f32[0], m_InvViewMatrix.r[2].m128_f32[1], m_InvViewMatrix.r[2].m128_f32[2]);	//�s���3�s�ڂ̒l
	m_RightVec = XMFLOAT3(m_InvViewMatrix.r[0].m128_f32[0], m_InvViewMatrix.r[0].m128_f32[1], m_InvViewMatrix.r[0].m128_f32[2]);	//�s���1�s�ڂ̒l

	//���b�V���t�B�[���h�Ƃ̓����蔻��
	CMeshfield* field = CManager::GetScene()->GetGameObject<CMeshfield>(1);
	m_Position.y = field->GetHeight(m_Position) + 1.5f;
	
	//�ړ�����
	if (CInput::GetKeyPress('W'))
	{
		m_Position.x += m_FrontVec.x * MOVE_SPEED;
		m_Position.y += m_FrontVec.y * MOVE_SPEED;
		m_Position.z += m_FrontVec.z * MOVE_SPEED;
	}									  

	if (CInput::GetKeyPress('S'))
	{
		m_Position.x -= m_FrontVec.x * MOVE_SPEED;
		m_Position.y -= m_FrontVec.y * MOVE_SPEED;
		m_Position.z -= m_FrontVec.z * MOVE_SPEED;
	}

	if (CInput::GetKeyPress('D'))
	{
		m_Position.x += m_RightVec.x * MOVE_SPEED;
		m_Position.y += m_RightVec.y * MOVE_SPEED;
		m_Position.z += m_RightVec.z * MOVE_SPEED;
	}

	if (CInput::GetKeyPress('A'))
	{
		m_Position.x -= m_RightVec.x * 0.25f;
		m_Position.y -= m_RightVec.y * 0.25f;
		m_Position.z -= m_RightVec.z * 0.25f;
	}


	//�}�E�X�̃J��������
	m_Rotation.x = m_MousePosY;
	m_MoveMouseY = (float)(CInput::GetMousePosY() - GetSystemMetrics(SM_CYSCREEN) / 2) * 0.005f;
	m_MousePosY += m_MoveMouseY;

	m_Rotation.y = m_MousePosX;
	m_MoveMouseX = (float)(CInput::GetMousePosX() - GetSystemMetrics(SM_CXSCREEN) / 2) * 0.0025f;
	m_MousePosX += m_MoveMouseX;

	//�}�E�X�̍��W��(0, 0)�Ƀ��Z�b�g
	CInput::MouseReset();


}


void CCamera::Draw()
{
	// �r���[�|�[�g�ݒ�
	D3D11_VIEWPORT dxViewport;
	dxViewport.Width = (float)(m_Viewport.right - m_Viewport.left);
	dxViewport.Height = (float)(m_Viewport.bottom - m_Viewport.top);
	dxViewport.MinDepth = 0.0f;
	dxViewport.MaxDepth = 1.0f;
	dxViewport.TopLeftX = (float)m_Viewport.left;
	dxViewport.TopLeftY = (float)m_Viewport.top;

	CRenderer::GetDeviceContext()->RSSetViewports(1, &dxViewport);



	// �r���[�}�g���N�X�ݒ�
	m_InvViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	m_InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMVECTOR det;
	m_ViewMatrix = XMMatrixInverse(&det, m_InvViewMatrix);

	CRenderer::SetViewMatrix(&m_ViewMatrix);



	// �v���W�F�N�V�����}�g���N�X�ݒ�
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(1.0f, dxViewport.Width / dxViewport.Height, 1.0f, 1000.0f);

	CRenderer::SetProjectionMatrix(&m_ProjectionMatrix);

}

XMMATRIX CCamera::GetViewMatrix()
{
	return m_ViewMatrix;
}


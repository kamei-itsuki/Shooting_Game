//#include <list>
//#include <typeinfo>
//#include <vector>
//#include "main.h"
//#include "renderer.h"
//#include "manager.h"
//#include "texture.h"
//#include "game_object.h"
//#include "camera.h"
//#include "field.h"
//#include "model.h"
//#include "bullet.h"
//#include "player.h"
//#include "enemy.h"
//#include "meshfield.h"
//#include "billboard.h"
//#include "polygon.h"
//#include "scene.h"
//#include "input.h"
//
//void CBillboard::Init()
//{
//	//���_�z��̍쐬
//	VERTEX_3D vertex[4];
//
//	//��XM��DirectX Math���C�u�����̂��Ƃ���D3DX�`�͎g��Ȃ�
//	vertex[0].Position = XMFLOAT3(-5.0f, 5.0f, 0.0f);
//	vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
//	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
//	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);
//	
//	vertex[1].Position = XMFLOAT3(5.0f, 5.0f, 0.0f);
//	vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
//	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
//	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);
//	
//	vertex[2].Position = XMFLOAT3(-5.0f, 0.0f, 0.0f);
//	vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
//	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
//	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);
//	
//	vertex[3].Position = XMFLOAT3(5.0f, 0.0f, 0.0f);
//	vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
//	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
//	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
//
//	//���_�o�b�t�@����
//	D3D11_BUFFER_DESC bd;
//	ZeroMemory(&bd, sizeof(bd));
//	bd.Usage = D3D11_USAGE_DEFAULT;
//	bd.ByteWidth = sizeof(VERTEX_3D) * 4;	//*4�͗p�ӂ������_��
//	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	bd.CPUAccessFlags = 0;
//	D3D11_SUBRESOURCE_DATA sd;
//	ZeroMemory(&sd, sizeof(sd));
//	sd.pSysMem = vertex;
//	//�������Œ��_�o�b�t�@�����@��3�ڂ̈����ɏ�񂪓���
//	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
//
//	//�e�N�X�`���ǂݍ���
//	m_Texture = new CTexture();
//	m_Texture->Load("asset/texture/TakahashiFace.tga");	//�摜�t�H�[�}�b�g��.tga�Œ�@����ȊO�̂��g������������m_Texture����������
//}
//
//void CBillboard::Uninit()
//{
//
//}
//
//void CBillboard::Update()
//{
//	m_VertexBuffer->Release();
//	m_Texture->Unload();
//	delete m_Texture;
//
//}
//
//void CBillboard::Draw()
//{
//
//	XMMATRIX mtxWorld;		//���[���h���W�ϊ��s��̍쐬
//	XMMATRIX mtxView;		//�J�����̃r���[�s��
//	XMMATRIX mtxIView;		//�J�����̃r���[�s��̋t�s��
//
//	CCamera* camera;
//	camera = CManager::GetScene()->GetGameObject<CCamera>(0);
//
//	//�r���{�[�h����
//	mtxView = camera->GetViewMatrix();
//
//	//�r���[�s��̕��s�ړ����J�b�g
//	mtxView.r[3].m128_f32[0] = 0.0f;
//	mtxView.r[3].m128_f32[1] = 0.0f;
//	mtxView.r[3].m128_f32[2] = 0.0f;
//
//	XMMatrixInverse(nullptr, mtxIView);		//�t�s�񐶐�
//
//	XMMatrixTranslation(0, 0, 0);	//���s�ړ�
//
//	//���W�ϊ������s���������
//	mtxWorld *= mtxIView;
//
//	//�}�g���N�X�Z�b�g
//	CRenderer::SetWorldMatrix(&mtxWorld);
//
//	//�g�|���W�[(���_���ǂ��������菇�Ō��Ԃ��̃��[���̂���)�̐ݒ�
//	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//	//�|���S���`��
//	CRenderer::GetDeviceContext()->Draw(4, 0);
//}
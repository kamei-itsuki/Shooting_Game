#include "main.h"
#include <math.h>
#include "renderer.h"
#include "game_object.h"
#include "texture.h"
#include "field.h"

#define D3DX_PI ((FLOAT) 3.141592654f) 

void CField::Init()
{
	//���_�z��̍쐬
	VERTEX_3D vertex[4];

	//��XM��DirectX Math���C�u�����̂��Ƃ���D3DX�`�͎g��Ȃ�
	vertex[0].Position = XMFLOAT3(-5.0, 0.0f, 5.0);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(5.0, 0.0f, 5.0);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-5.0, 0.0f, -5.0);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(5.0, 0.0f,-5.0);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	//���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;	//*4�͗p�ӂ������_��
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	//�������Œ��_�o�b�t�@�����@��3�ڂ̈����ɏ�񂪓���
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//�e�N�X�`���ǂݍ���
	m_Texture = new CTexture();
	m_Texture->Load("asset/texture/field004.tga");	//�摜�t�H�[�}�b�g��.tga�Œ�@����ȊO�̂��g������������m_Texture����������

}

void CField::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Unload();
	delete m_Texture;

}

void CField::Update()
{

}

void CField::Draw()
{

	//UINT stride = sizeof(VERTEX_3D);
	//UINT offset = 0;
	////���_�o�b�t�@�̐ݒ�
	//CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	////�e�N�X�`���̐ݒ�
	//CRenderer::SetTexture(m_Texture);

	////2D�p�̃}�g���N�X�ݒ�
	////CRenderer::SetWorldViewProjection2D();
	//XMMATRIX world;
	//world = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	//world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
	//world *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	//CRenderer::SetWorldMatrix(&world);

	////�g�|���W�[(���_���ǂ��������菇�Ō��Ԃ��̃��[���̂���)�̐ݒ�
	//CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	////�|���S���`��
	//CRenderer::GetDeviceContext()->Draw(4, 0);
}

void CField::Draw(float pitch, float yaw, float roll)
{

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	//���_�o�b�t�@�̐ݒ�
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	//�e�N�X�`���̐ݒ�
	CRenderer::SetTexture(m_Texture);

	//3D�p�̃}�g���N�X�ݒ�
	//CRenderer::SetWorldViewProjection2D();
	XMMATRIX world;
	world = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	world *= XMMatrixRotationRollPitchYaw((pitch) * (D3DX_PI / 180.0f), (yaw) * (D3DX_PI / 180.0f), (roll) * (D3DX_PI / 180.0f));
	world *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	CRenderer::SetWorldMatrix(&world);

	//�g�|���W�[(���_���ǂ��������菇�Ō��Ԃ��̃��[���̂���)�̐ݒ�
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//�|���S���`��
	CRenderer::GetDeviceContext()->Draw(4, 0);
}
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "game_object.h"
#include "meshfield.h"

static int g_IndexNum = 0;

void CMeshfield::Init(float sizeX, float sizeZ, int numX, int numZ)
{
	m_sizeX = sizeX;
	m_sizeZ = sizeZ;
	m_numX = numX;
	m_numZ = numZ;

	//�C���f�b�N�X�̍쐬
	unsigned short* pMeshIndex;

	int vertexNum = (numX + 1) * (numZ + 1);					//���_���̌v�Z
	int indexNum = (numX + 1) * 2 * numZ + ((numZ - 1) * 2);	//�C���f�b�N�X��
	g_IndexNum = indexNum;

	m_pMeshVertex = new VERTEX_3D[vertexNum];		//���_�����̃f�[�^�̊m��
	pMeshIndex = new unsigned short[indexNum];				//�C���f�b�N�X�����̃f�[�^�̊m��

	//���_�f�[�^�̊i�[
	for (int i = 0; i < vertexNum; i++)
	{
		//if (i / (numX + 1) == 7)
		//{
		//	m_pMeshVertex[i].Position = XMFLOAT3(sizeX * (i % (numX + 1)) - (sizeX * numX / 2), 1.0f, -(sizeZ * (i / (numX + 1))) + (sizeZ * numZ / 2));
		//	m_pMeshVertex[i].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		//	m_pMeshVertex[i].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		//	m_pMeshVertex[i].TexCoord = XMFLOAT2((float)(i % (numX + 1)), (float)(i / (numX + 1)));
		//}
		//else if (i / (numX + 1) == 10)
		//{
		//	m_pMeshVertex[i].Position = XMFLOAT3(sizeX * (i % (numX + 1)) - (sizeX * numX / 2), -1.0f, -(sizeZ * (i / (numX + 1))) + (sizeZ * numZ / 2));
		//	m_pMeshVertex[i].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		//	m_pMeshVertex[i].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		//	m_pMeshVertex[i].TexCoord = XMFLOAT2((float)(i % (numX + 1)), (float)(i / (numX + 1)));
		//}
		//else
		//{
			m_pMeshVertex[i].Position = XMFLOAT3(sizeX * (i % (numX + 1)) - (sizeX * numX / 2), 0.0f, -(sizeZ * (i / (numX + 1))) + (sizeZ * numZ / 2));
			m_pMeshVertex[i].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			m_pMeshVertex[i].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			m_pMeshVertex[i].TexCoord = XMFLOAT2((float)(i % (numX + 1)), (float)(i / (numX + 1)));
		//}
	}

	//�@���̐ݒ�
	XMFLOAT3 va, vb, n;

	for (int z = 1; z < numZ; z++)
	{
		for (int x = 1; x < numX; x++)
		{
			va.x = m_pMeshVertex[(z - 1) * (numX + 1) + x].Position.x - m_pMeshVertex[(z + 1) * (numX + 1) + x].Position.x;
			va.y = m_pMeshVertex[(z - 1) * (numX + 1) + x].Position.y - m_pMeshVertex[(z + 1) * (numX + 1) + x].Position.y;
			va.z = m_pMeshVertex[(z - 1) * (numX + 1) + x].Position.z - m_pMeshVertex[(z + 1) * (numX + 1) + x].Position.z;

			vb.x = m_pMeshVertex[z * (numX + 1) + (x + 1)].Position.x - m_pMeshVertex[(z - 1) * (numX + 1) + (x - 1)].Position.x;
			vb.y = m_pMeshVertex[z * (numX + 1) + (x + 1)].Position.y - m_pMeshVertex[(z - 1) * (numX + 1) + (x - 1)].Position.y;
			vb.z = m_pMeshVertex[z * (numX + 1) + (x + 1)].Position.z - m_pMeshVertex[(z - 1) * (numX + 1) + (x - 1)].Position.z;

			//va��vb�̊O�ς̌v�Z
			n.x = va.y * vb.z - va.z * vb.y;
			n.y = va.z * vb.x - va.x * vb.z;
			n.z = va.x * vb.y - va.y * vb.x;

			float length = sqrtf(n.x * n.x + n.y * n.y + n.z * n.z);

			//���K��
			n.x /= length;
			n.y /= length;
			n.z /= length;

			m_pMeshVertex[z * (numX + 1) + x].Normal = n;

		}
	}

	//���_�o�b�t�@����
	D3D11_BUFFER_DESC Vbd;
	ZeroMemory(&Vbd, sizeof(Vbd));
	Vbd.Usage = D3D11_USAGE_DEFAULT;
	Vbd.ByteWidth = sizeof(VERTEX_3D) * vertexNum;
	Vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Vbd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA Vsd;
	ZeroMemory(&Vsd, sizeof(Vsd));
	Vsd.pSysMem = m_pMeshVertex;

	//�������Œ��_�o�b�t�@�����@��3�ڂ̈����ɏ�񂪓���
	CRenderer::GetDevice()->CreateBuffer(&Vbd, &Vsd, &m_VertexBuffer);

	//�C���f�b�N�X�f�[�^�̊i�[
	int i, cnt;

	for (cnt = 0, i = 0; i < indexNum; i += 2, cnt++)
	{
		pMeshIndex[i] = (cnt % (numX + 1)) + (numX + 1) * ((cnt / (numX + 1) + 1));
		pMeshIndex[i + 1] = (cnt % (numX + 1)) + (numX + 1) * (cnt / (numX + 1));

		if (cnt % (numX + 1) == numX)
		{
			i += 2;
			if (i >= indexNum) { break; }

			pMeshIndex[i] = pMeshIndex[i - 1];
			pMeshIndex[i + 1] = ((cnt + 1) % (numX + 1)) + (numX + 1) * (((cnt + 1) / (numX + 1) + 1));
		}
	}

	//�C���f�b�N�X�o�b�t�@����
	D3D11_BUFFER_DESC Ibd;
	ZeroMemory(&Ibd, sizeof(Ibd));
	Ibd.Usage = D3D11_USAGE_DEFAULT;
	Ibd.ByteWidth = sizeof(unsigned short) * indexNum;
	Ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	Ibd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA Isd;
	ZeroMemory(&Isd, sizeof(Isd));
	Isd.pSysMem = pMeshIndex;

	//�������ŃC���f�b�N�X�o�b�t�@�����@��3�ڂ̈����ɏ�񂪓���
	CRenderer::GetDevice()->CreateBuffer(&Ibd, &Isd, &m_IndexBuffer);

	delete[] pMeshIndex;

	//�e�N�X�`���ǂݍ���
	m_Texture = new CTexture();
	m_Texture->Load("asset/texture/koke.tga");	//�摜�t�H�[�}�b�g��.tga�Œ�@����ȊO�̂��g������������m_Texture����������

}

void CMeshfield::Uninit()
{

	m_VertexBuffer->Release();
	delete[] m_pMeshVertex;
	
	m_IndexBuffer->Release();
	m_Texture->Unload();
	delete m_Texture;

}

void CMeshfield::Update()
{

}

void CMeshfield::Draw()
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	//���_�o�b�t�@�̐ݒ�
	//CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	//�C���f�b�N�X�o�b�t�@�̐ݒ�
	//CRenderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	CRenderer::SetVertexBuffers(m_VertexBuffer);
	CRenderer::SetIndexBuffer(m_IndexBuffer);
	//�e�N�X�`���̐ݒ�
	CRenderer::SetTexture(m_Texture);

	XMMATRIX world;
	//3D�p�̃}�g���N�X�ݒ�
	world = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
	world *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	//�}�g���N�X�Z�b�g
	CRenderer::SetWorldMatrix(&world);
	//�g�|���W�[(���_���ǂ��������菇�Ō��Ԃ��̃��[���̂���)�̐ݒ�
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//�|���S���`��
	CRenderer::GetDeviceContext()->DrawIndexed(g_IndexNum, 0, 0);
}

float CMeshfield::GetHeight(XMFLOAT3 position)
{
	int x, z;
	XMFLOAT3 p0, p1, p2, v01, v02, n, v, hp, va, vb;
	float dp0n, dvn, dpn, t;

	v = XMFLOAT3(0.0f, -10.0f, 0.0f);

	x = ( position.x + (m_sizeX * m_numX / 2)) / m_sizeX;	//���㒸�_�����_�ɂ���ꍇ�͂��ꂾ����ok
	z = (-position.z + (m_sizeZ * m_numZ / 2)) / m_sizeZ;	//1�u���b�N�T�C�Y

	va.x = m_pMeshVertex[(z + 1) * (m_numX + 1) + (x + 1)].Position.x - m_pMeshVertex[z * (m_numX + 1) + x].Position.x;
	va.y = m_pMeshVertex[(z + 1) * (m_numX + 1) + (x + 1)].Position.y - m_pMeshVertex[z * (m_numX + 1) + x].Position.y;
	va.z = m_pMeshVertex[(z + 1) * (m_numX + 1) + (x + 1)].Position.z - m_pMeshVertex[z * (m_numX + 1) + x].Position.z;

	vb.x = position.x - m_pMeshVertex[z * (m_numX + 1) + x].Position.x;
	vb.y = position.y - m_pMeshVertex[z * (m_numX + 1) + x].Position.y;
	vb.z = position.z - m_pMeshVertex[z * (m_numX + 1) + x].Position.z;

	if ((va.z * vb.x - va.x * vb.z) > 0.0f)
	{
		//�����̎O�p�`�̍��W����
		p0 = m_pMeshVertex[(z + 1) * (m_numX + 1) + x].Position;			//����
		p1 = m_pMeshVertex[z * (m_numX + 1) + x].Position;					//����
		p2 = m_pMeshVertex[(z + 1) * (m_numX + 1) + (x + 1)].Position;		//�E��
	}
	else
	{
		//�E��̎O�p�`�̍��W����
		p0 = m_pMeshVertex[z * (m_numX + 1) + (x + 1)].Position;			//�E��
		p1 = m_pMeshVertex[(z + 1) * (m_numX + 1) + (x + 1)].Position;		//�E��
		p2 = m_pMeshVertex[z * (m_numX + 1) + x].Position;					//����
	}

	v01.x = p1.x - p0.x;
	v01.y = p1.y - p0.y;
	v01.z = p1.z - p0.z;

	v02.x = p2.x - p0.x;
	v02.y = p2.y - p0.y;
	v02.z = p2.z - p0.z;

	//v01��v02�̊O�ς̌v�Z
	n.x = v01.y * v02.z - v01.z * v02.y;
	n.y = v01.z * v02.x - v01.x * v02.z;
	n.z = v01.x * v02.y - v01.y * v02.x;

	//v��n�̓��ς̌v�Z
	dvn = (v.x * n.x) + (v.y * n.y) + (v.z * n.z);

	//p0n��n�̓��ς̌v�Z
	dp0n = (p0.x * n.x) + (p0.y * n.y) + (p0.z * n.z);

	//Player��Position��n�̓��ς̌v�Z
	dpn = (position.x * n.x) + (position.y * n.y) + (position.z * n.z);

	t = (dp0n - dpn) / dvn;

	//hp.x = position.x + v.x * t;	//��������Ȃ�
	hp.y = position.y + v.y * t;
	//hp.z = position.z + v.z * t;	//��������Ȃ�

	return hp.y;
}


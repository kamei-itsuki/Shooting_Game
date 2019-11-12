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

	//インデックスの作成
	unsigned short* pMeshIndex;

	int vertexNum = (numX + 1) * (numZ + 1);					//頂点数の計算
	int indexNum = (numX + 1) * 2 * numZ + ((numZ - 1) * 2);	//インデックス数
	g_IndexNum = indexNum;

	m_pMeshVertex = new VERTEX_3D[vertexNum];		//頂点数分のデータの確保
	pMeshIndex = new unsigned short[indexNum];				//インデックス数分のデータの確保

	//頂点データの格納
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

	//法線の設定
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

			//vaとvbの外積の計算
			n.x = va.y * vb.z - va.z * vb.y;
			n.y = va.z * vb.x - va.x * vb.z;
			n.z = va.x * vb.y - va.y * vb.x;

			float length = sqrtf(n.x * n.x + n.y * n.y + n.z * n.z);

			//正規化
			n.x /= length;
			n.y /= length;
			n.z /= length;

			m_pMeshVertex[z * (numX + 1) + x].Normal = n;

		}
	}

	//頂点バッファ生成
	D3D11_BUFFER_DESC Vbd;
	ZeroMemory(&Vbd, sizeof(Vbd));
	Vbd.Usage = D3D11_USAGE_DEFAULT;
	Vbd.ByteWidth = sizeof(VERTEX_3D) * vertexNum;
	Vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Vbd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA Vsd;
	ZeroMemory(&Vsd, sizeof(Vsd));
	Vsd.pSysMem = m_pMeshVertex;

	//↓こいつで頂点バッファを作る　↓3つ目の引数に情報が入る
	CRenderer::GetDevice()->CreateBuffer(&Vbd, &Vsd, &m_VertexBuffer);

	//インデックスデータの格納
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

	//インデックスバッファ生成
	D3D11_BUFFER_DESC Ibd;
	ZeroMemory(&Ibd, sizeof(Ibd));
	Ibd.Usage = D3D11_USAGE_DEFAULT;
	Ibd.ByteWidth = sizeof(unsigned short) * indexNum;
	Ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	Ibd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA Isd;
	ZeroMemory(&Isd, sizeof(Isd));
	Isd.pSysMem = pMeshIndex;

	//↓こいつでインデックスバッファを作る　↓3つ目の引数に情報が入る
	CRenderer::GetDevice()->CreateBuffer(&Ibd, &Isd, &m_IndexBuffer);

	delete[] pMeshIndex;

	//テクスチャ読み込み
	m_Texture = new CTexture();
	m_Texture->Load("asset/texture/koke.tga");	//画像フォーマットは.tga固定　それ以外のを使いたかったらm_Textureを改造する

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
	//頂点バッファの設定
	//CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	//インデックスバッファの設定
	//CRenderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	CRenderer::SetVertexBuffers(m_VertexBuffer);
	CRenderer::SetIndexBuffer(m_IndexBuffer);
	//テクスチャの設定
	CRenderer::SetTexture(m_Texture);

	XMMATRIX world;
	//3D用のマトリクス設定
	world = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
	world *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	//マトリクスセット
	CRenderer::SetWorldMatrix(&world);
	//トポロジー(頂点をどういった手順で結ぶかのルールのこと)の設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//ポリゴン描画
	CRenderer::GetDeviceContext()->DrawIndexed(g_IndexNum, 0, 0);
}

float CMeshfield::GetHeight(XMFLOAT3 position)
{
	int x, z;
	XMFLOAT3 p0, p1, p2, v01, v02, n, v, hp, va, vb;
	float dp0n, dvn, dpn, t;

	v = XMFLOAT3(0.0f, -10.0f, 0.0f);

	x = ( position.x + (m_sizeX * m_numX / 2)) / m_sizeX;	//左上頂点が原点にある場合はこれだけでok
	z = (-position.z + (m_sizeZ * m_numZ / 2)) / m_sizeZ;	//1ブロックサイズ

	va.x = m_pMeshVertex[(z + 1) * (m_numX + 1) + (x + 1)].Position.x - m_pMeshVertex[z * (m_numX + 1) + x].Position.x;
	va.y = m_pMeshVertex[(z + 1) * (m_numX + 1) + (x + 1)].Position.y - m_pMeshVertex[z * (m_numX + 1) + x].Position.y;
	va.z = m_pMeshVertex[(z + 1) * (m_numX + 1) + (x + 1)].Position.z - m_pMeshVertex[z * (m_numX + 1) + x].Position.z;

	vb.x = position.x - m_pMeshVertex[z * (m_numX + 1) + x].Position.x;
	vb.y = position.y - m_pMeshVertex[z * (m_numX + 1) + x].Position.y;
	vb.z = position.z - m_pMeshVertex[z * (m_numX + 1) + x].Position.z;

	if ((va.z * vb.x - va.x * vb.z) > 0.0f)
	{
		//左下の三角形の座標を代入
		p0 = m_pMeshVertex[(z + 1) * (m_numX + 1) + x].Position;			//左下
		p1 = m_pMeshVertex[z * (m_numX + 1) + x].Position;					//左上
		p2 = m_pMeshVertex[(z + 1) * (m_numX + 1) + (x + 1)].Position;		//右下
	}
	else
	{
		//右上の三角形の座標を代入
		p0 = m_pMeshVertex[z * (m_numX + 1) + (x + 1)].Position;			//右上
		p1 = m_pMeshVertex[(z + 1) * (m_numX + 1) + (x + 1)].Position;		//右下
		p2 = m_pMeshVertex[z * (m_numX + 1) + x].Position;					//左上
	}

	v01.x = p1.x - p0.x;
	v01.y = p1.y - p0.y;
	v01.z = p1.z - p0.z;

	v02.x = p2.x - p0.x;
	v02.y = p2.y - p0.y;
	v02.z = p2.z - p0.z;

	//v01とv02の外積の計算
	n.x = v01.y * v02.z - v01.z * v02.y;
	n.y = v01.z * v02.x - v01.x * v02.z;
	n.z = v01.x * v02.y - v01.y * v02.x;

	//vとnの内積の計算
	dvn = (v.x * n.x) + (v.y * n.y) + (v.z * n.z);

	//p0nとnの内積の計算
	dp0n = (p0.x * n.x) + (p0.y * n.y) + (p0.z * n.z);

	//PlayerのPositionとnの内積の計算
	dpn = (position.x * n.x) + (position.y * n.y) + (position.z * n.z);

	t = (dp0n - dpn) / dvn;

	//hp.x = position.x + v.x * t;	//正直いらない
	hp.y = position.y + v.y * t;
	//hp.z = position.z + v.z * t;	//正直いらない

	return hp.y;
}


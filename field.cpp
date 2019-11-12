#include "main.h"
#include <math.h>
#include "renderer.h"
#include "game_object.h"
#include "texture.h"
#include "field.h"

#define D3DX_PI ((FLOAT) 3.141592654f) 

void CField::Init()
{
	//頂点配列の作成
	VERTEX_3D vertex[4];

	//↓XMはDirectX MathライブラリのこともうD3DX～は使わない
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

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;	//*4は用意した頂点数
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	//↓こいつで頂点バッファを作る　↓3つ目の引数に情報が入る
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//テクスチャ読み込み
	m_Texture = new CTexture();
	m_Texture->Load("asset/texture/field004.tga");	//画像フォーマットは.tga固定　それ以外のを使いたかったらm_Textureを改造する

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
	////頂点バッファの設定
	//CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	////テクスチャの設定
	//CRenderer::SetTexture(m_Texture);

	////2D用のマトリクス設定
	////CRenderer::SetWorldViewProjection2D();
	//XMMATRIX world;
	//world = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	//world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
	//world *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	//CRenderer::SetWorldMatrix(&world);

	////トポロジー(頂点をどういった手順で結ぶかのルールのこと)の設定
	//CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	////ポリゴン描画
	//CRenderer::GetDeviceContext()->Draw(4, 0);
}

void CField::Draw(float pitch, float yaw, float roll)
{

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	//頂点バッファの設定
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	//テクスチャの設定
	CRenderer::SetTexture(m_Texture);

	//3D用のマトリクス設定
	//CRenderer::SetWorldViewProjection2D();
	XMMATRIX world;
	world = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	world *= XMMatrixRotationRollPitchYaw((pitch) * (D3DX_PI / 180.0f), (yaw) * (D3DX_PI / 180.0f), (roll) * (D3DX_PI / 180.0f));
	world *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	CRenderer::SetWorldMatrix(&world);

	//トポロジー(頂点をどういった手順で結ぶかのルールのこと)の設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);
}
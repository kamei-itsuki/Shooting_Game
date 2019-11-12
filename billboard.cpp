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
//	//頂点配列の作成
//	VERTEX_3D vertex[4];
//
//	//↓XMはDirectX MathライブラリのこともうD3DX～は使わない
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
//	//頂点バッファ生成
//	D3D11_BUFFER_DESC bd;
//	ZeroMemory(&bd, sizeof(bd));
//	bd.Usage = D3D11_USAGE_DEFAULT;
//	bd.ByteWidth = sizeof(VERTEX_3D) * 4;	//*4は用意した頂点数
//	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	bd.CPUAccessFlags = 0;
//	D3D11_SUBRESOURCE_DATA sd;
//	ZeroMemory(&sd, sizeof(sd));
//	sd.pSysMem = vertex;
//	//↓こいつで頂点バッファを作る　↓3つ目の引数に情報が入る
//	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
//
//	//テクスチャ読み込み
//	m_Texture = new CTexture();
//	m_Texture->Load("asset/texture/TakahashiFace.tga");	//画像フォーマットは.tga固定　それ以外のを使いたかったらm_Textureを改造する
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
//	XMMATRIX mtxWorld;		//ワールド座標変換行列の作成
//	XMMATRIX mtxView;		//カメラのビュー行列
//	XMMATRIX mtxIView;		//カメラのビュー行列の逆行列
//
//	CCamera* camera;
//	camera = CManager::GetScene()->GetGameObject<CCamera>(0);
//
//	//ビルボード生成
//	mtxView = camera->GetViewMatrix();
//
//	//ビュー行列の平行移動をカット
//	mtxView.r[3].m128_f32[0] = 0.0f;
//	mtxView.r[3].m128_f32[1] = 0.0f;
//	mtxView.r[3].m128_f32[2] = 0.0f;
//
//	XMMatrixInverse(nullptr, mtxIView);		//逆行列生成
//
//	XMMatrixTranslation(0, 0, 0);	//平行移動
//
//	//座標変換した行列を代入する
//	mtxWorld *= mtxIView;
//
//	//マトリクスセット
//	CRenderer::SetWorldMatrix(&mtxWorld);
//
//	//トポロジー(頂点をどういった手順で結ぶかのルールのこと)の設定
//	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//	//ポリゴン描画
//	CRenderer::GetDeviceContext()->Draw(4, 0);
//}
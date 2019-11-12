#ifndef  POLYGON_H_
#define POLYGON_H_

class CPolygon : public CGameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;		//頂点バッファ
	CTexture* m_Texture = NULL;					//テクスチャ

public:
	void Init(const char* texture);
	void Uninit();
	void Update();
	void Draw();
};

#endif // ! POLYGON_H_

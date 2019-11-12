#ifndef FIELD_H_
#define FIELD_H_

class CField : public CGameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;		//頂点バッファ
	CTexture* m_Texture = NULL;					//テクスチャ

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Draw(float pitch, float yaw, float roll);

};

#endif // ! FIELD_H_
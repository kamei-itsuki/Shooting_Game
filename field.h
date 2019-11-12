#ifndef FIELD_H_
#define FIELD_H_

class CField : public CGameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;		//���_�o�b�t�@
	CTexture* m_Texture = NULL;					//�e�N�X�`��

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Draw(float pitch, float yaw, float roll);

};

#endif // ! FIELD_H_
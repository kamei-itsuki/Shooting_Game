#ifndef MESHFIELD_H_
#define MESHFIELD_H_

class CMeshfield : public CGameObject
{
private:
	VERTEX_3D* m_pMeshVertex;					//���_�z��
	ID3D11Buffer* m_VertexBuffer = NULL;		//���_�o�b�t�@
	ID3D11Buffer* m_IndexBuffer = NULL;			//�C���f�b�N�X�o�b�t�@
	CTexture* m_Texture = NULL;					//�e�N�X�`��
	float m_sizeX, m_sizeZ;
	int m_numX, m_numZ;

public:
	void Init(float sizeX, float sizeZ, int numX, int numZ);
	void Uninit();
	void Update();
	void Draw();
	float GetHeight(XMFLOAT3 position);
};

#endif // !MESHFIELD_H_

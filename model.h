#ifndef MODEL_H_
#define MODEL_H_

// �}�e���A���\����
struct MODEL_MATERIAL
{
	char	 Name[256];
	MATERIAL Material;
	char     TextureName[256];
};

// �`��T�u�Z�b�g�\����
struct SUBSET
{
	unsigned short	StartIndex;
	unsigned short	IndexNum;
	MODEL_MATERIAL	Material;
};

// ���f���\����
struct MODEL
{
	VERTEX_3D		*VertexArray;
	unsigned short	VertexNum;
	unsigned short	*IndexArray;
	unsigned short	IndexNum;
	SUBSET			*SubsetArray;
	unsigned short	SubsetNum;
};



class CModel
{
private:
	ID3D11Buffer*	m_VertexBuffer = NULL;
	ID3D11Buffer*	m_IndexBuffer = NULL;

	DX11_SUBSET*	m_SubsetArray = NULL;
	unsigned short	m_SubsetNum;

	void LoadObj( const char *FileName, MODEL *Model );
	void LoadMaterial( const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned short *MaterialNum );

public:
	void Draw();

	void Load( const char *FileName );
	void Unload();

};

#endif // !MODEL_H_

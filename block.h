#ifndef _BLOCK_H_
#define _BLOCK_H_ //��d�C���N���[�h�h�~

#include"main.h"
#include"object2D.h"

class CBlock : public CObject2D
{
public:
	bool bDisp;        //�g���Ă��邩�ǂ���

	CBlock();          //�R���X�g���N�^
	~CBlock();		   //�f�X�g���N�^

	//==========================
	//�����o�֐�
	//==========================
	static CBlock * Create(D3DXVECTOR3 pos, int nType);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff1;		  //���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture1[NUM_OBJECT] = {};  //�e�N�X�`��
};

#endif
#ifndef _3DOBJECT_H_
#define _SDOBJECT_H_

#include"main.h"
#include"manager.h"
#include"object.h"

//�}�N����`
#define WALLSIZE (400) //�ǂ̃T�C�Y
#define MAX_Wall (4)  //�ǂ̐�

//�I�u�W�F�N�g3D�N���X
class C3DObject :public CObject
{
public:
	C3DObject();
	~C3DObject();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos, int nType);
	static C3DObject *Create(D3DXVECTOR3 pos, int nType);

	D3DXVECTOR3 GetPosition(void); //�ʒu�擾

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL; //���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;      //�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;                         //�ʒu
	D3DXVECTOR3 m_rot;                         //����
	D3DXMATRIX m_mtxWorld;                     //���[���h�}�b�N�X
	VERTEX_3D m_aVertex[4];
};

#endif 
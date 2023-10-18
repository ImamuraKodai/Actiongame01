#ifndef _3DOBJECT_H_
#define _SDOBJECT_H_

#include<windows.h>
#include"d3dx9.h" //�`�揈���ɕK�v
#include"main.h"
#include"object.h"

//�}�N����`
#define WALLSIZE (400) //�ǂ̃T�C�Y
#define MAX_Wall (4)   //�ǂ̐�

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
	void SetPosition1(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
	static C3DObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);

	D3DXVECTOR3 GetPosition(void); //�ʒu�擾

private:
	static int m_NumObject;					   //�I�u�W�F�N�g����
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		   //���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;			   //�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;                         //�ʒu
	D3DXVECTOR3 m_rot;                         //����
	int nType;								   //���
	bool m_bUse;                               //�g���Ă��邩�ǂ���
	D3DXMATRIX m_mtxWorld;                     //���[���h�}�b�N�X
	VERTEX_3D m_aVertex[4];					   //�ǂ̐�
};

#endif 
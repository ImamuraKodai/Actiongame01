#ifndef _OBJECT2D_H_ 
#define _OBJECT2D_H_ //��d�C���N���[�h�h�~

#include<windows.h>
#include"d3dx9.h" //�`�揈���ɕK�v
#include"object.h"
#include"main.h"

//�}�N����`
#define MAX_OBJECT (128) //�I�u�W�F�N�g�̍ő吔

//���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;  //���_���W�̐ݒ�
	D3DXVECTOR3 move; //�ړ�
	D3DXVECTOR3 rot;  //���� 
	float rhw;        //rhw�̐ݒ�
	D3DCOLOR col;     //���_�J���[�̐ݒ�lkpm
	int nType;		  //���     
	float fWidth;	  //��
	float fHeiht;	  //����

}Object2D;

//�I�u�W�F�N�g2D�N���X
class CObject2D :public CObject
{
public:
	CObject2D();
	~CObject2D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos, int nType);
	static CObject2D *Create(D3DXVECTOR3 pos, int nType);

	D3DXVECTOR3 GetPosition(void); //�ʒu�擾

private:

	void MovePlayer(void);

	//static CObject2D *m_apObject[MAX_OBJECT];
	//static CObject2D *m_apObject1[MAX_OBJECT];
	static int m_NumObject;						    //�I�u�W�F�N�g����
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			    //���_�o�b�t�@

protected:
	float fWidth;									//��
	float fHeiht;									//����
	int nType;										//���
	D3DXVECTOR2 tex;								//���_�̐ݒ�
	D3DXVECTOR3 m_pos;								//�I�u�W�F�N�g�̈ʒu
	D3DXVECTOR3 move;								//�ړ�
};

#endif
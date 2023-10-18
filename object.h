#ifndef _OBJECT_H_ 
#define _OBJECT_H_ //��d�C���N���[�h�h�~

#include<windows.h>
#include"d3dx9.h" //�`�揈���ɕK�v

#define MAX_OBJECT (128) //�G�̑���
#define NUM_OBJECT (4)   //�I�u�W�F�N�g�̎��

//�I�u�W�F�N�g�N���X
class CObject
{
public:
	CObject();  //�R���X�g���N�^
	virtual ~CObject(); //�f�X�g���N�^

	virtual HRESULT Init(void) = 0; //�|���S���̏���������
	virtual void Uninit(void) = 0;  //�|���S���̏I������
	virtual void Update(void) = 0;  //�|���S���̍X�V����
	virtual void Draw(void) = 0;    //�|���S���̕`�揈��

	void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType); //�ʒu�Ǝ��	

	/*virtual void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType) = 0;*/

	static void ReleaseAll(void); //���ׂẴI�u�W�F�N�g�̔j��
	static void UpdateAll(void);  //���ׂĂ̍X�V����
	static void DrawAll(void);    //���ׂĂ̕`�揈��

protected:
	void Release(void); //�I�u�W�F�N�g�̔j��

public:
	static CObject *m_apObject[MAX_OBJECT]; //�I�u�W�F�N�g�̑���
	static int m_nNumAll;					//�I�u�W�F�N�g����
	int m_nID;								//�������g��ID
	D3DXVECTOR3 m_pos;						//�����̈ʒu

private:
};

#endif
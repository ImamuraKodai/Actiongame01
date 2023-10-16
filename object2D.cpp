//==================
//
//�I�u�W�F�N�g2D����[object2D.cpp]
//Aoutor:�����W��
//
//==================
#include<Windows.h>
#include"d3dx9.h" //�`�揈���ɕK�v
#include"main.h"
#include"object2D.h"
#include"manager.h"
#include"input.h"

//�}�N����`
#define NUM_OBJECT (4) //�I�u�W�F�N�g�̎��

//�ÓI�����o�ϐ�
//CObject2D *CObject2D::m_apObject[MAX_OBJECT] = {}; //�I�u�W�F�N�g�̏��
int CObject2D::m_NumObject = 0;					     //�I�u�W�F�N�g�̑���

//�R���X�g���N�^
CObject2D::CObject2D()
{

}

//�f�X�g���N�^
CObject2D::~CObject2D()
{

}

//��������
CObject2D * CObject2D::Create(D3DXVECTOR3 pos, int nType)
{
	CObject2D * pObject2D;

	//�I�u�W�F�N�g2D�̐���
	pObject2D = new CObject2D;

	//����������
	pObject2D->Init();

	pObject2D->SetPosition(pos, nType);

	return pObject2D;
}

//����������
HRESULT CObject2D::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ʒu
	int nType = 0;                         //���
	float fWidth = 30.0f;				   //��
	float fHeiht = 30.0f;				   //����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_OBJECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx; //

					 //���_�o�b�t�@�����b�N����
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fWidth / 2, m_pos.y - fHeiht / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fWidth / 2, m_pos.y - fHeiht / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fWidth / 2, m_pos.y + fHeiht / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fWidth / 2, m_pos.y + fHeiht / 2, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//�I������
void CObject2D::Uninit(void)
{
	////�e�N�X�`���̔j��
	//if (m_pTexture[0] != NULL)
	//{
	//	m_pTexture[0]->Release();
	//	m_pTexture[0] = NULL;
	//}

	////�e�N�X�`���̔j��
	//if (m_pTexture[1] != NULL)
	//{
	//	m_pTexture[1]->Release();
	//	m_pTexture[1] = NULL;
	//}

	////���_�o�b�t�@�̔j��
	//if (m_pVtxBuff != NULL)
	//{
	//	m_pVtxBuff->Release();
	//	m_pVtxBuff = NULL;
	//}

	//�I�u�W�F�N�g(�������g)�̔j��
	m_apObject[m_nID] = NULL;
}

//�X�V����
void CObject2D::Update(void)
{
	VERTEX_2D *pVtx; //

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fWidth / 2, m_pos.y - fHeiht / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fWidth / 2, m_pos.y - fHeiht / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fWidth / 2, m_pos.y + fHeiht / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fWidth / 2, m_pos.y + fHeiht / 2, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//���쏈��
void CObject2D::MovePlayer(void)
{

}

//�`�揈��
void CObject2D::Draw(void)
{
	////�f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	////���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	//pDevice->SetStreamSource(0, m_pVtxBuff,
	//	0,
	//	sizeof(VERTEX_2D));

	////���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_2D);

	////�e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, m_pTexture[nType]);

	////�|���S���̕`��	
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
	//	0,
	//	2);
}

//�I�u�W�F�N�g�̎擾
Object2D * GetCObject2D(void)
{
	return S_OK;
}

//�I�u�W�F�N�g�̈ʒu�ݒ�
void CObject2D::SetPosition(D3DXVECTOR3 pos, int nType)
{
	int nCntObject = 0;

	VERTEX_2D * pVtx; //

	m_pos = pos;

	nType = nType;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (nType == 0)
	{
		fHeiht = 200.0f;
		fWidth = 250.0f;
	}

	else if (nType == 1)
	{
		fHeiht = 200.0f;
		fWidth = 250.0f;
	}

	else if (nType == 2)
	{
		fHeiht = 100.0f;
		fWidth = 200.0f;
	}

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nCntObject * 4); //�Y���̈ʒu�܂Ői�߂�

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fWidth / 2, m_pos.y - fHeiht / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fWidth / 2, m_pos.y - fHeiht / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fWidth / 2, m_pos.y + fHeiht / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fWidth / 2, m_pos.y + fHeiht / 2, 0.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//�ʒu�擾
D3DXVECTOR3 CObject2D::GetPosition(void)
{
	return m_pos;
}
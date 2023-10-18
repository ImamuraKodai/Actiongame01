//==================
//
//�u���b�N���Ǘ����鏈��[block.cpp]
//Aoutor:�����W��
//
//==================
#include "block.h"
#include "object2D.h"
#include "renderer.h"
#include "manager.h"

//********************************************
//�ÓI�����o�ϐ�
//********************************************
LPDIRECT3DVERTEXBUFFER9 CBlock::m_pVtxBuff1 = NULL;  //���_�o�b�t�@�̃|�C���^ 

//==============================================
//�u���b�N�̃R���X�g���N�^
//==============================================
CBlock::CBlock()  
{

}

//==============================================
//�u���b�N�̃f�X�g���N�^
//==============================================
CBlock::~CBlock()
{

}

//==============================================
//�u���b�N�̐�������
//==============================================
CBlock * CBlock::Create(D3DXVECTOR3 pos, int nType)
{
	//�����p�̃I�u�W�F�N�g
	CBlock *pBlock = NULL;

	if (pBlock == NULL)
	{//NULL��������

	 //�������̊m��
		pBlock = new CBlock;

		if (pBlock != NULL)
		{//�������̊m�ۂ��o���Ă�����

			//����������
			pBlock->Init();

			//�e�N�X�`���̊��蓖��
			pBlock->SetPosition(pos, nType);
		}
		return pBlock;
	}
	return NULL;
}

//===============================================
//�u���b�N�̏���������
//===============================================
HRESULT CBlock::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevise = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\shikaku-illust1.png",
		&m_pTexture1[0]);

	//���_�o�b�t�@�̐���
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff1,
		NULL);

	VERTEX_2D *pVtx; //���_�o�b�t�@�̐ݒ�

	//���_�o�b�t�@�����b�N����
	m_pVtxBuff1->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff1->Unlock();

	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ړ��ʂ�����������
	fWidth = 30.0f;				          //��
	fHeiht = 30.0f;				          //����

	//����������
	CObject2D::Init();

	return S_OK;
}

//==============================================
//�u���b�N�̏I������
//==============================================
void CBlock::Uninit(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture1[0] != NULL)
	{
		m_pTexture1[0]->Release();
		m_pTexture1[0] = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff1 != NULL)
	{
		m_pVtxBuff1->Release();
		m_pVtxBuff1 = NULL;
	}

	// �I������
	CObject2D::Uninit();
}

//=========================================
//�u���b�N�̍X�V����
//=========================================
void CBlock::Update(void)
{
	VERTEX_2D *pVtx; //���_�o�b�t�@�̐ݒ�

	//���_�o�b�t�@�����b�N
	m_pVtxBuff1->Lock(0, 0, (void**)&pVtx, 0);

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
	m_pVtxBuff1->Unlock();
}

//=======================================================
//�u���b�N�̕`�揈��
//=======================================================
void CBlock::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff1,
		0,
		sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture1[nType]);

	//�|���S���̕`��	
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}
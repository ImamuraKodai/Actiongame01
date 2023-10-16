#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include"Object2D.h"

//******************************************
//�ÓI�����o�ϐ��錾
//******************************************
CObject2D *CObject2D::m_apObject1[MAX_OBJECT] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 CPlayer::m_pVtxBuff = NULL; //���_�o�b�t�@�̃|�C���^ 

//===========================================================================t
//�v���C���[�̃R���X�g���N�^
//===========================================================================
CPlayer::CPlayer()
{
	nCounterState = 0;  //�A�j���[�V�����J�E���^�[

	m_PatternAnim = 0; //�A�j���[�V�����p�^�[��No.
}

//<==========================================================================
//�v���C���[�̃f�X�g���N�^
//<==========================================================================
CPlayer::~CPlayer()
{

}

//===========================================================================
//�v���C���[�̐���
//===========================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, int nType)
{
	//�����p�̃I�u�W�F�N�g
	CPlayer *pPlayer = NULL;

	if (pPlayer == NULL)
	{//NULL��������

	 //�������̊m��
		pPlayer = new CPlayer;

		if (pPlayer != NULL)
		{//�������̊m�ۂ��o���Ă�����

			//����������
			pPlayer->Init();

			//�e�N�X�`���̊��蓖��
			pPlayer->SetPosition(pos, nType);
		}
		return pPlayer;
	}

	return NULL;
}

//==============================================
//�v���C���[�̏���������
//==============================================
HRESULT CPlayer::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevise = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\Skeleton-Walk001.png",
		&m_pTexture[0]);

	//���_�o�b�t�@�̐���
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx; //���_�o�b�t�@�̐ݒ�

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
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�ړ��ʂ�����������
	fWidth = 30.0f;				          //��
	fHeiht = 30.0f;				          //����
	m_CounterAnim = 0;                    //�A�j���[�V�����J�E���^�[
	m_PatternAnim = 0;                    //�A�j���[�V�����p�^�[��No.

										  //����������
	CObject2D::Init();

	return S_OK;
}

//<==========================================================================
//�v���C���[�̏I������
//<==========================================================================
void CPlayer::Uninit(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture[0] != NULL)
	{
		m_pTexture[0]->Release();
		m_pTexture[0] = NULL;
	}

	//�e�N�X�`���̔j��
	if (m_pTexture[1] != NULL)
	{
		m_pTexture[1]->Release();
		m_pTexture[1] = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �I������
	CObject2D::Uninit();
}

//<==========================================================================
//�v���C���[�̍X�V����
//<==========================================================================
void CPlayer::Update(void)
{
	//�v���C���[�̈ړ�����
	MovePlayer();

	VERTEX_2D *pVtx; //���_�o�b�t�@�̐ݒ�

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

//===========================================================================
//�v���C���[�̑��쏈��
//===========================================================================
void CPlayer::MovePlayer(void)
{
	//�v���C���[�̈ړ�
	CInputKeyboard * pInputKeyboard;

	//�L�[�{�[�h�̎擾
	pInputKeyboard = CManager::GetKeyboard();

	if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		if (pInputKeyboard->GetPress(DIK_W) == true)
		{//����ړ�
			move.x += sinf(-D3DX_PI *0.75f)*2.0f;
			move.y += cosf(-D3DX_PI *0.75f)*2.0f;
		}

		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{//�����ړ�
			move.x += sinf(-D3DX_PI *0.25f)*2.0f;
			move.y += cosf(-D3DX_PI *0.25f)*2.0f;
		}

		else
		{//���ړ�
			move.x -= 1.0f;
		}
	}

	else if (pInputKeyboard->GetPress(DIK_D) == true)
	{//D�L�[�������ꂽ

		if (pInputKeyboard->GetPress(DIK_W) == true)
		{//�E��ړ�
			move.x += sinf(D3DX_PI *0.75f)*2.0f;
			move.y += cosf(D3DX_PI *0.75f)*2.0f;
		}

		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{//�����ړ�
			move.x += sinf(D3DX_PI *0.25f)*2.0f;
			move.y += cosf(D3DX_PI *0.25f)*2.0f;
		}

		else
		{//�E�ړ�
			move.x += 1.0f;
		}
	}

	else if (pInputKeyboard->GetPress(DIK_W) == true)
	{//W�L�[�������ꂽ
		move.y += cosf(D3DX_PI *1.0f)*2.0f;
	}

	else if (pInputKeyboard->GetPress(DIK_S) == true)
	{//S�L�[�������ꂽ
		move.y += cosf(D3DX_PI *0.0f)*2.0f;
	}

	VERTEX_2D * pVtx; //�v���C���[�̒��_

					  //���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_CounterAnim++; //�J�E���^�[�����Z

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fWidth / 2, m_pos.y - fHeiht / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fWidth / 2, m_pos.y - fHeiht / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fWidth / 2, m_pos.y + fHeiht / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fWidth / 2, m_pos.y + fHeiht / 2, 0.0f);

	////�e�N�X�`�����W�̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	//pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	if (m_CounterAnim % 8 == 0)
	{//��莞�Ԍo��
	 //�p�^�[��No.���X�V����
		m_PatternAnim = (m_PatternAnim + 1) % 8;

		if (pInputKeyboard->GetPress(DIK_A) == true) //����A�L�[��������Ă����牺�̏��������s
		{
			//�e�N�X�`�����W�̍X�V
			pVtx[0].tex = D3DXVECTOR2(0.0f + 0.25f*m_PatternAnim, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.25f + 0.25f*m_PatternAnim, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + 0.25f*m_PatternAnim, 0.5f);
			pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f*m_PatternAnim, 0.5f);
		}

		if (pInputKeyboard->GetPress(DIK_D) == true) //����D�L�[��������Ă����牺�̏��������s
		{
			//�e�N�X�`�����W�̍X�V
			pVtx[0].tex = D3DXVECTOR2(0.0f + 0.25f*m_PatternAnim, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(-0.25f + 0.25f*m_PatternAnim, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + 0.25f*m_PatternAnim, 0.5f);
			pVtx[3].tex = D3DXVECTOR2(-0.25f + 0.25f*m_PatternAnim, 0.5f);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�ʒu�̎擾
	D3DXVECTOR3 p_pos;

	p_pos = GetPosition();

	//�ʒu���X�V
	p_pos += move;

	move.x += (0.0f - move.x) *2.0f;//�ړ��ʂ�����������
	move.y += (0.0f - move.y) *2.0f;//[g_movePlayer.�Z += (�ړI�̐��l{0.0f�ŌŒ�}�[���݂̐��l{g_movePlayer.�Z})*�����W��(0.0f�`1.0f)]

	//�ʒu�ݒ�
	SetPosition(p_pos, nType);
}
//==========================================================================
//�v���C���[�̕`�揈��
//==========================================================================
void CPlayer::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture[nType]);

	//�|���S���̕`��	
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}
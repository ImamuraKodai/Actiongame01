//==================
//
//�I�u�W�F�N�g����[object.cpp]
//Aoutor:�����W��
//
//==================
#include<Windows.h>
#include"d3dx9.h" //�`�揈���ɕK�v
#include"main.h"
#include"object.h"
#include"manager.h"
#include"camera.h"
#include"light.h"

//�ÓI�����o�ϐ�
int CObject::m_nNumAll = 0;
CObject *CObject::m_apObject[MAX_OBJECT] = {};

//�R���X�g���N�^
CObject::CObject()
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] == NULL)
		{
			m_apObject[nCntObject] = this;		   //�������g����

			m_nID = MAX_OBJECT;					   //�������g��ID��ۑ�

			m_nNumAll++;						   //�������J�E���g�A�b�v

			m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�v���C���[�̈ʒu

			break;
		}
	}
}

//�f�X�g���N�^
CObject::~CObject()
{

}

//�S�ẴI�u�W�F�N�g�̔j��
void CObject::ReleaseAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			//�I������
			m_apObject[nCntObject]->Uninit();

			delete m_apObject[nCntObject];

			m_apObject[nCntObject] = NULL;
		}
	}
}

//�S�ẴI�u�W�F�N�g�̍X�V����
void CObject::UpdateAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->Update();
		}
	}
}

//�S�ẴI�u�W�F�N�g�̕`�揈��
void CObject::DrawAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->Draw();
		}
	}

	CCamera * pCamera = CManager::GetCamera();

	//�J�����̐ݒ�
	pCamera->SetCamera();
}

//�I�u�W�F�N�g�̔j��
void CObject::Release(void)
{
	if (m_apObject[m_nID] != NULL)
	{
		delete m_apObject[m_nID];

		m_apObject[m_nID] = NULL;

		m_nNumAll--;
	}
}
//==================
//
//�������o�͂��鏈��[manager.cpp]
//Aoutor:�����W��
//
//==================
#include<Windows.h>
#include"d3dx9.h" //�`�揈���ɕK�v
#include"manager.h"
#include"main.h"
#include"renderer.h"
#include"player.h"
#include"input.h"
#include"block.h"
#include"camera.h"
#include"3DObject.h"
#include"light.h"

//�ÓI�����o�ϐ�
CRenderer * CManager::m_pRenderer = NULL;
CInputKeyboard * CManager::m_pKeyboard = NULL;
CManager * pManager = NULL;
CCamera * CManager::m_pCamera = NULL;
CLight * CManager::m_pLight = NULL;

//�R���X�g���N�^
CManager::CManager()
{

}

//�f�X�g���N�^
CManager::~CManager()
{

}

//����������
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�����_���[�̎擾
	m_pRenderer = GetRenderer();

	//�L�[�{�[�h�̎擾
	m_pKeyboard = GetKeyboard();

	if (m_pRenderer == NULL)
	{
		//�����_���[�̐���
		m_pRenderer = new CRenderer;

		//�����_���[�̏���������
		m_pRenderer->Init(hWnd, TRUE);
	}

	if (m_pKeyboard == NULL)
	{
		//�L�[�{�[�h�̐���
		m_pKeyboard = new CInputKeyboard;

		//�L�[�{�[�h�̏���������
		m_pKeyboard->Init(hInstance, hWnd);
	}

	if (m_pCamera == NULL)
	{
		//�J�����̐���
		m_pCamera = new CCamera;

		//�J�����̏���������
		m_pCamera->Init();
	}

	if (m_pLight == NULL)
	{
		//���C�g�̐���
		m_pLight = new CLight;

		//���C�g�̏���������
		m_pLight->Init();
	}

	////�I�u�W�F�N�g�̐���
	//CObject2D::Create(D3DXVECTOR3(1000.0f, 500.0f, 0.0f), 0);

	/*C3DObject::Create(D3DXVECTOR3(0, 0, WALLSIZE), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);*/

	CPlayer::Create(D3DXVECTOR3(200.0f, 200.0f, 0.0f), 1);

	CBlock::Create(D3DXVECTOR3(500.0f, 100.0f, 0.0f), 2);

	return S_OK;
}

//�I������	
void CManager::Uninit(void)
{
	//���ׂẴI�u�W�F�N�g�̔j��(+�I������)
	CObject::ReleaseAll();

	//�����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		//�����_���[�̏I������
		m_pRenderer->Uninit();

		delete m_pRenderer;

		m_pRenderer = NULL;
	}

	//�L�[�{�[�h�̔j��
	if (m_pKeyboard != NULL)
	{
		//�L�[�{�[�h�̏I������
		m_pKeyboard->Uninit();

		delete m_pKeyboard;

		m_pKeyboard = NULL;
	}
}

//�X�V����
void CManager::Update(void)
{
	//�I�u�W�F�N�g�̍X�V����
	CObject::UpdateAll();

	//�����_���[�̍X�V����
	m_pRenderer->Update();

	//�L�[�{�[�h�̍X�V����
	m_pKeyboard->Update();
}

//�`�揈��
void CManager::Draw(void)
{
	//�I�u�W�F�N�g�̕`�揈��
	CObject::DrawAll();

	//�����_���[�̕`�揈��
	m_pRenderer->Draw();
}

//�����_���[�̎擾
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

CObject * CManager::GetObject(void)
{
	return S_OK;
}

//�L�[�{�[�h�̎擾
CInputKeyboard * CManager::GetKeyboard(void)
{
	return m_pKeyboard;
}

//�J�����̎擾
CCamera * CManager::GetCamera(void)
{
	return m_pCamera;
}

//���C�g�̎擾
CLight * CManager::GetLight(void)
{
	return m_pLight;
}

////static�̈ꊇ�Ǘ�
//CManager * CManager::GetInstance(void)
//{
//	if (pManager == NULL)
//	{
//		return pManager = new CManager;
//	}
//
//	return pManager;
//}
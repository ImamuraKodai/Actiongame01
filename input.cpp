#include "input.h"

//�ÓI�����o�֐�
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//�R���X�g���N�^
CInput::CInput()
{
	m_pDevice = NULL;
}

//�f�X�g���N�^
CInput::~CInput()
{

}

//����������
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (m_pInput == NULL)
	{
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

//�L�[�{�[�h�̏I������
void CInput::Uninit(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire(); //�L�[�{�[�h�ւ̃A�N�Z�X�������

		m_pDevice->Release();

		m_pDevice = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();

		m_pInput = NULL;
	}
}

//�R���X�g���N�^
CInputKeyboard::CInputKeyboard()
{
	//�L�[�̃N���A
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = NULL;
	}
}

//�f�X�g���N�^
CInputKeyboard::~CInputKeyboard()
{

}

//�L�[�{�[�h�̏���������
HRESULT CInputKeyboard::Init(HINSTANCE hInstans, HWND hWnd)
{
	//����������
	CInput::Init(hInstans, hWnd);

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))

	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}

//�L�[�{�[�h�̏I������
void CInputKeyboard::Uninit(void)
{
	//�I������
	CInput::Uninit();
}

//�L�[�{�[�h�̍X�V����
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX]; //�L�[�{�[�h�̃v���X���

	int nCntkey; //�L�[�{�[�h�̃J�E���g

				 //���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			m_aKeyStateTrigger[nCntkey] = (m_aKeyState[nCntkey] ^ aKeyState[nCntkey]) & aKeyState[nCntkey]; //�L�[�{�[�h�̃g���K�[����ۑ�

			m_aKeyState[nCntkey] = aKeyState[nCntkey]; //�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire(); //�L�[�{�[�h�̃A�N�Z�X�����l��
	}

	////�X�V����
	//CInput::Updete();
}

//�L�[�v���X��Ԋl��
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//�L�[�g���K�[��Ԋl��
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
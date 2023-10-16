#include "input.h"

//静的メンバ関数
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//コンストラクタ
CInput::CInput()
{
	m_pDevice = NULL;
}

//デストラクタ
CInput::~CInput()
{

}

//初期化処理
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (m_pInput == NULL)
	{
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

//キーボードの終了処理
void CInput::Uninit(void)
{
	//入力デバイス(キーボード)の破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire(); //キーボードへのアクセス権を放棄

		m_pDevice->Release();

		m_pDevice = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();

		m_pInput = NULL;
	}
}

//コンストラクタ
CInputKeyboard::CInputKeyboard()
{
	//キーのクリア
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = NULL;
	}
}

//デストラクタ
CInputKeyboard::~CInputKeyboard()
{

}

//キーボードの初期化処理
HRESULT CInputKeyboard::Init(HINSTANCE hInstans, HWND hWnd)
{
	//初期化処理
	CInput::Init(hInstans, hWnd);

	//入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))

	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

//キーボードの終了処理
void CInputKeyboard::Uninit(void)
{
	//終了処理
	CInput::Uninit();
}

//キーボードの更新処理
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX]; //キーボードのプレス情報

	int nCntkey; //キーボードのカウント

				 //入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			m_aKeyStateTrigger[nCntkey] = (m_aKeyState[nCntkey] ^ aKeyState[nCntkey]) & aKeyState[nCntkey]; //キーボードのトリガー情報を保存

			m_aKeyState[nCntkey] = aKeyState[nCntkey]; //キーボードのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire(); //キーボードのアクセス権を獲得
	}

	////更新処理
	//CInput::Updete();
}

//キープレス状態獲得
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//キートリガー状態獲得
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
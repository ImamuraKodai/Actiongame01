//==================
//
//文字を出力する処理[manager.cpp]
//Aoutor:今村晃大
//
//==================
#include<Windows.h>
#include"d3dx9.h" //描画処理に必要
#include"manager.h"
#include"main.h"
#include"renderer.h"
#include"player.h"
#include"input.h"
#include"block.h"
#include"camera.h"

//静的メンバ変数
CRenderer * CManager::m_pRenderer = NULL;
CInputKeyboard * CManager::m_pKeyboard = NULL;
CManager * pManager = NULL;
//CCamera * CManager::m_pCamera = NULL;

//コンストラクタ
CManager::CManager()
{

}

//デストラクタ
CManager::~CManager()
{

}

//初期化処理
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//レンダラーの取得
	m_pRenderer = GetRenderer();

	//キーボードの取得
	m_pKeyboard = GetKeyboard();

	if (m_pRenderer == NULL)
	{
		//レンダラーの生成
		m_pRenderer = new CRenderer;

		//レンダラーの初期化処理
		m_pRenderer->Init(hWnd, TRUE);
	}

	if (m_pKeyboard == NULL)
	{
		//キーボードの生成
		m_pKeyboard = new CInputKeyboard;

		//キーボードの初期化処理
		m_pKeyboard->Init(hInstance, hWnd);
	}

	//if (m_pCamera == NULL)
	//{
	//	//カメラの生成
	//	m_pCamera = new CCamera;

	//	//カメラの初期化処理
	//	m_pCamera->Init();
	//}

	//オブジェクトの生成
	CObject2D::Create(D3DXVECTOR3(1000.0f, 500.0f, 0.0f), 0);

	CPlayer::Create(D3DXVECTOR3(200.0f, 200.0f, 0.0f), 1);

	CBlock::Create(D3DXVECTOR3(500.0f, 100.0f, 0.0f), 2);

	return S_OK;
}

//終了処理	
void CManager::Uninit(void)
{
	//すべてのオブジェクトの破棄(+終了処理)
	CObject::ReleaseAll();

	//レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		//レンダラーの終了処理
		m_pRenderer->Uninit();

		delete m_pRenderer;

		m_pRenderer = NULL;
	}

	//キーボードの破棄
	if (m_pKeyboard != NULL)
	{
		//キーボードの終了処理
		m_pKeyboard->Uninit();

		delete m_pKeyboard;

		m_pKeyboard = NULL;
	}
}

//更新処理
void CManager::Update(void)
{
	//オブジェクトの更新処理
	CObject::UpdateAll();

	//レンダラーの更新処理
	m_pRenderer->Update();

	//キーボードの更新処理
	m_pKeyboard->Update();
}

//描画処理
void CManager::Draw(void)
{
	//オブジェクトの描画処理
	CObject::DrawAll();

	//レンダラーの描画処理
	m_pRenderer->Draw();
}

//レンダラーの取得
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

CObject * CManager::GetObject(void)
{
	return S_OK;
}

//キーボードの取得
CInputKeyboard * CManager::GetKeyboard(void)
{
	return m_pKeyboard;
}

////staticの一括管理
//CManager * CManager::GetInstance(void)
//{
//	if (pManager == NULL)
//	{
//		return pManager = new CManager;
//	}
//
//	return pManager;
//}
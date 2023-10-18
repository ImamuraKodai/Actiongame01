//==================
//
//文字を出力する処理[renderer.cpp]
//Aoutor:今村晃大
//
//==================
#include<Windows.h>
#include"d3dx9.h" //描画処理に必要
#include"main.h"
#include"renderer.h"
#include"object.h"

//コンストラクタ
CRenderer::CRenderer()
{

}

//デストラクタ
CRenderer::~CRenderer()
{

}

//初期化処理
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;        //ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp; //プレゼンテーションパラメータ
	HDC hPC = 0;
	char aString[256] = "test";
	static POINT pos = { 100,100 }; //
	static POINT move = { 2,3 };    //
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }; //

	//Direct3Dオブジェクトの生成
	m_PD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_PD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(m_PD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp)); //

	d3dpp.BackBufferWidth = SCREEN_WIDTH;      //
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;    //
	d3dpp.BackBufferFormat = d3ddm.Format;     //
	d3dpp.BackBufferCount = 1;                 //
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;  //
	d3dpp.EnableAutoDepthStencil = TRUE;       //
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16; //
	d3dpp.Windowed = bWindow;                  //
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;   //

	//Direct3Dデバイスの生成
	if (FAILED(m_PD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		if (FAILED(m_PD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			if (FAILED(m_PD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	return S_OK;
}

//終了処理
void CRenderer::Uninit(void)
{
	//Direct3Dデバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	//Direct3Dデバイスの除去
	if (m_PD3D != NULL)
	{
		m_PD3D->Release();
		m_PD3D = NULL;
	}
}

//更新処理
void CRenderer::Update(void)
{
	//オブジェクトの更新処理
	CObject::UpdateAll();
}

//描画処理
void CRenderer::Draw(void)
{
	//画面クリア(バックバッファとZバッファのクリア)
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合

		//オブジェクトの描画処理
		CObject::DrawAll();

		//描画終了
		m_pD3DDevice->EndScene();
	}
	//バックバッファとフロントバッファの切り替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//デバイスの取得
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}
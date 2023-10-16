////==================
////
////ライトの管理する処理[light.cpp]
////Aoutor:今村晃大
////
////==================
//#include"light.h"
//#include"manager.h"
//#include"main.h"
//
////コンストラクタ
//CLight::CLight()
//{
//	
//}
//
////デストラクタ
//CLight::~CLight()
//{
//
//}
//
////ライトの初期化処理
//HRESULT CLight::Init(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice(); //デバイスの取得
//	D3DXVECTOR3 vecDir;											      //設定用方向ベクトル
//
//	//ライトの情報をクリアする
//	ZeroMemory(&m_aLight[3], sizeof(D3DLIGHT9));
//
//	//ライトの種類を設定
//	m_aLight.Type = D3DLIGHT_DIRECTIONAL;
//
//	//ライトの拡張光を設定
//	m_aLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//	//ライトの方向を設定
//	vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
//	D3DXVec3Normalize(&vecDir, &vecDir);      //ベクトルを正規化する
//	m_aLight.Direction = vecDir;
//
//	//ライトを設定する
//	pDevice->SetLight(0, &m_aLight[3]);
//
//	//ライトを有効にする
//	pDevice->LightEnable(0, TRUE);
//}
//
////ライトの終了処理
//void CLight::Uninit(void)
//{
//
//}
//
////ライトの更新処理
//void CLight::Update(void)
//{
//
//}
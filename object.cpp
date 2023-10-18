//==================
//
//オブジェクト処理[object.cpp]
//Aoutor:今村晃大
//
//==================
#include<Windows.h>
#include"d3dx9.h" //描画処理に必要
#include"main.h"
#include"object.h"
#include"manager.h"
#include"camera.h"
#include"light.h"

//静的メンバ変数
int CObject::m_nNumAll = 0;
CObject *CObject::m_apObject[MAX_OBJECT] = {};

//コンストラクタ
CObject::CObject()
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] == NULL)
		{
			m_apObject[nCntObject] = this;		   //自分自身を代入

			m_nID = MAX_OBJECT;					   //自分自身のIDを保存

			m_nNumAll++;						   //総数をカウントアップ

			m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //プレイヤーの位置

			break;
		}
	}
}

//デストラクタ
CObject::~CObject()
{

}

//全てのオブジェクトの破棄
void CObject::ReleaseAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			//終了処理
			m_apObject[nCntObject]->Uninit();

			delete m_apObject[nCntObject];

			m_apObject[nCntObject] = NULL;
		}
	}
}

//全てのオブジェクトの更新処理
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

//全てのオブジェクトの描画処理
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

	//カメラの設定
	pCamera->SetCamera();
}

//オブジェクトの破棄
void CObject::Release(void)
{
	if (m_apObject[m_nID] != NULL)
	{
		delete m_apObject[m_nID];

		m_apObject[m_nID] = NULL;

		m_nNumAll--;
	}
}
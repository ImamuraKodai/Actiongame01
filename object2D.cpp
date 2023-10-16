//==================
//
//オブジェクト2D処理[object2D.cpp]
//Aoutor:今村晃大
//
//==================
#include<Windows.h>
#include"d3dx9.h" //描画処理に必要
#include"main.h"
#include"object2D.h"
#include"manager.h"
#include"input.h"

//マクロ定義
#define NUM_OBJECT (4) //オブジェクトの種類

//静的メンバ変数
//CObject2D *CObject2D::m_apObject[MAX_OBJECT] = {}; //オブジェクトの情報
int CObject2D::m_NumObject = 0;					     //オブジェクトの総数

//コンストラクタ
CObject2D::CObject2D()
{

}

//デストラクタ
CObject2D::~CObject2D()
{

}

//生成処理
CObject2D * CObject2D::Create(D3DXVECTOR3 pos, int nType)
{
	CObject2D * pObject2D;

	//オブジェクト2Dの生成
	pObject2D = new CObject2D;

	//初期化処理
	pObject2D->Init();

	pObject2D->SetPosition(pos, nType);

	return pObject2D;
}

//初期化処理
HRESULT CObject2D::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置
	int nType = 0;                         //種類
	float fWidth = 30.0f;				   //幅
	float fHeiht = 30.0f;				   //高さ

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_OBJECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx; //

					 //頂点バッファをロックする
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fWidth / 2, m_pos.y - fHeiht / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fWidth / 2, m_pos.y - fHeiht / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fWidth / 2, m_pos.y + fHeiht / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fWidth / 2, m_pos.y + fHeiht / 2, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//終了処理
void CObject2D::Uninit(void)
{
	////テクスチャの破棄
	//if (m_pTexture[0] != NULL)
	//{
	//	m_pTexture[0]->Release();
	//	m_pTexture[0] = NULL;
	//}

	////テクスチャの破棄
	//if (m_pTexture[1] != NULL)
	//{
	//	m_pTexture[1]->Release();
	//	m_pTexture[1] = NULL;
	//}

	////頂点バッファの破棄
	//if (m_pVtxBuff != NULL)
	//{
	//	m_pVtxBuff->Release();
	//	m_pVtxBuff = NULL;
	//}

	//オブジェクト(自分自身)の破棄
	m_apObject[m_nID] = NULL;
}

//更新処理
void CObject2D::Update(void)
{
	VERTEX_2D *pVtx; //

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fWidth / 2, m_pos.y - fHeiht / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fWidth / 2, m_pos.y - fHeiht / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fWidth / 2, m_pos.y + fHeiht / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fWidth / 2, m_pos.y + fHeiht / 2, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//操作処理
void CObject2D::MovePlayer(void)
{

}

//描画処理
void CObject2D::Draw(void)
{
	////デバイスの取得
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	////頂点バッファをデータストリームに設定
	//pDevice->SetStreamSource(0, m_pVtxBuff,
	//	0,
	//	sizeof(VERTEX_2D));

	////頂点フォーマットの設定
	//pDevice->SetFVF(FVF_VERTEX_2D);

	////テクスチャの設定
	//pDevice->SetTexture(0, m_pTexture[nType]);

	////ポリゴンの描画	
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
	//	0,
	//	2);
}

//オブジェクトの取得
Object2D * GetCObject2D(void)
{
	return S_OK;
}

//オブジェクトの位置設定
void CObject2D::SetPosition(D3DXVECTOR3 pos, int nType)
{
	int nCntObject = 0;

	VERTEX_2D * pVtx; //

	m_pos = pos;

	nType = nType;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (nType == 0)
	{
		fHeiht = 200.0f;
		fWidth = 250.0f;
	}

	else if (nType == 1)
	{
		fHeiht = 200.0f;
		fWidth = 250.0f;
	}

	else if (nType == 2)
	{
		fHeiht = 100.0f;
		fWidth = 200.0f;
	}

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nCntObject * 4); //該当の位置まで進める

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fWidth / 2, m_pos.y - fHeiht / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fWidth / 2, m_pos.y - fHeiht / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fWidth / 2, m_pos.y + fHeiht / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fWidth / 2, m_pos.y + fHeiht / 2, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//位置取得
D3DXVECTOR3 CObject2D::GetPosition(void)
{
	return m_pos;
}
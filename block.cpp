//==================
//
//ブロックを管理する処理[block.cpp]
//Aoutor:今村晃大
//
//==================
#include "block.h"
#include "object2D.h"
#include "renderer.h"
#include "manager.h"

//********************************************
//静的メンバ変数
//********************************************
LPDIRECT3DVERTEXBUFFER9 CBlock::m_pVtxBuff1 = NULL;  //頂点バッファのポインタ 

//==============================================
//ブロックのコンストラクタ
//==============================================
CBlock::CBlock()  
{

}

//==============================================
//ブロックのデストラクタ
//==============================================
CBlock::~CBlock()
{

}

//==============================================
//ブロックの生成処理
//==============================================
CBlock * CBlock::Create(D3DXVECTOR3 pos, int nType)
{
	//生成用のオブジェクト
	CBlock *pBlock = NULL;

	if (pBlock == NULL)
	{//NULLだったら

	 //メモリの確保
		pBlock = new CBlock;

		if (pBlock != NULL)
		{//メモリの確保が出来ていたら

			//初期化処理
			pBlock->Init();

			//テクスチャの割り当て
			pBlock->SetPosition(pos, nType);
		}
		return pBlock;
	}
	return NULL;
}

//===============================================
//ブロックの初期化処理
//===============================================
HRESULT CBlock::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevise = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\shikaku-illust1.png",
		&m_pTexture1[0]);

	//頂点バッファの生成
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff1,
		NULL);

	VERTEX_2D *pVtx; //頂点バッファの設定

	//頂点バッファをロックする
	m_pVtxBuff1->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//頂点バッファをアンロックする
	m_pVtxBuff1->Unlock();

	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //移動量を初期化する
	fWidth = 30.0f;				          //幅
	fHeiht = 30.0f;				          //高さ

	//初期化処理
	CObject2D::Init();

	return S_OK;
}

//==============================================
//ブロックの終了処理
//==============================================
void CBlock::Uninit(void)
{
	//テクスチャの破棄
	if (m_pTexture1[0] != NULL)
	{
		m_pTexture1[0]->Release();
		m_pTexture1[0] = NULL;
	}

	//頂点バッファの破棄
	if (m_pVtxBuff1 != NULL)
	{
		m_pVtxBuff1->Release();
		m_pVtxBuff1 = NULL;
	}

	// 終了処理
	CObject2D::Uninit();
}

//=========================================
//ブロックの更新処理
//=========================================
void CBlock::Update(void)
{
	VERTEX_2D *pVtx; //頂点バッファの設定

	//頂点バッファをロック
	m_pVtxBuff1->Lock(0, 0, (void**)&pVtx, 0);

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
	m_pVtxBuff1->Unlock();
}

//=======================================================
//ブロックの描画処理
//=======================================================
void CBlock::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff1,
		0,
		sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture1[nType]);

	//ポリゴンの描画	
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}
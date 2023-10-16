#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include"Object2D.h"

//******************************************
//静的メンバ変数宣言
//******************************************
CObject2D *CObject2D::m_apObject1[MAX_OBJECT] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 CPlayer::m_pVtxBuff = NULL; //頂点バッファのポインタ 

//===========================================================================t
//プレイヤーのコンストラクタ
//===========================================================================
CPlayer::CPlayer()
{
	nCounterState = 0;  //アニメーションカウンター

	m_PatternAnim = 0; //アニメーションパターンNo.
}

//<==========================================================================
//プレイヤーのデストラクタ
//<==========================================================================
CPlayer::~CPlayer()
{

}

//===========================================================================
//プレイヤーの生成
//===========================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, int nType)
{
	//生成用のオブジェクト
	CPlayer *pPlayer = NULL;

	if (pPlayer == NULL)
	{//NULLだったら

	 //メモリの確保
		pPlayer = new CPlayer;

		if (pPlayer != NULL)
		{//メモリの確保が出来ていたら

			//初期化処理
			pPlayer->Init();

			//テクスチャの割り当て
			pPlayer->SetPosition(pos, nType);
		}
		return pPlayer;
	}

	return NULL;
}

//==============================================
//プレイヤーの初期化処理
//==============================================
HRESULT CPlayer::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevise = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevise,
		"data\\TEXTURE\\Skeleton-Walk001.png",
		&m_pTexture[0]);

	//頂点バッファの生成
	pDevise->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx; //頂点バッファの設定

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
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //移動量を初期化する
	fWidth = 30.0f;				          //幅
	fHeiht = 30.0f;				          //高さ
	m_CounterAnim = 0;                    //アニメーションカウンター
	m_PatternAnim = 0;                    //アニメーションパターンNo.

										  //初期化処理
	CObject2D::Init();

	return S_OK;
}

//<==========================================================================
//プレイヤーの終了処理
//<==========================================================================
void CPlayer::Uninit(void)
{
	//テクスチャの破棄
	if (m_pTexture[0] != NULL)
	{
		m_pTexture[0]->Release();
		m_pTexture[0] = NULL;
	}

	//テクスチャの破棄
	if (m_pTexture[1] != NULL)
	{
		m_pTexture[1]->Release();
		m_pTexture[1] = NULL;
	}

	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// 終了処理
	CObject2D::Uninit();
}

//<==========================================================================
//プレイヤーの更新処理
//<==========================================================================
void CPlayer::Update(void)
{
	//プレイヤーの移動処理
	MovePlayer();

	VERTEX_2D *pVtx; //頂点バッファの設定

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

//===========================================================================
//プレイヤーの操作処理
//===========================================================================
void CPlayer::MovePlayer(void)
{
	//プレイヤーの移動
	CInputKeyboard * pInputKeyboard;

	//キーボードの取得
	pInputKeyboard = CManager::GetKeyboard();

	if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		if (pInputKeyboard->GetPress(DIK_W) == true)
		{//左上移動
			move.x += sinf(-D3DX_PI *0.75f)*2.0f;
			move.y += cosf(-D3DX_PI *0.75f)*2.0f;
		}

		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{//左下移動
			move.x += sinf(-D3DX_PI *0.25f)*2.0f;
			move.y += cosf(-D3DX_PI *0.25f)*2.0f;
		}

		else
		{//左移動
			move.x -= 1.0f;
		}
	}

	else if (pInputKeyboard->GetPress(DIK_D) == true)
	{//Dキーが押された

		if (pInputKeyboard->GetPress(DIK_W) == true)
		{//右上移動
			move.x += sinf(D3DX_PI *0.75f)*2.0f;
			move.y += cosf(D3DX_PI *0.75f)*2.0f;
		}

		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{//左下移動
			move.x += sinf(D3DX_PI *0.25f)*2.0f;
			move.y += cosf(D3DX_PI *0.25f)*2.0f;
		}

		else
		{//右移動
			move.x += 1.0f;
		}
	}

	else if (pInputKeyboard->GetPress(DIK_W) == true)
	{//Wキーが押された
		move.y += cosf(D3DX_PI *1.0f)*2.0f;
	}

	else if (pInputKeyboard->GetPress(DIK_S) == true)
	{//Sキーが押された
		move.y += cosf(D3DX_PI *0.0f)*2.0f;
	}

	VERTEX_2D * pVtx; //プレイヤーの頂点

					  //頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_CounterAnim++; //カウンターを加算

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fWidth / 2, m_pos.y - fHeiht / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fWidth / 2, m_pos.y - fHeiht / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fWidth / 2, m_pos.y + fHeiht / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fWidth / 2, m_pos.y + fHeiht / 2, 0.0f);

	////テクスチャ座標の設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	//pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	if (m_CounterAnim % 8 == 0)
	{//一定時間経過
	 //パターンNo.を更新する
		m_PatternAnim = (m_PatternAnim + 1) % 8;

		if (pInputKeyboard->GetPress(DIK_A) == true) //もしAキーが押されていたら下の処理を実行
		{
			//テクスチャ座標の更新
			pVtx[0].tex = D3DXVECTOR2(0.0f + 0.25f*m_PatternAnim, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.25f + 0.25f*m_PatternAnim, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + 0.25f*m_PatternAnim, 0.5f);
			pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f*m_PatternAnim, 0.5f);
		}

		if (pInputKeyboard->GetPress(DIK_D) == true) //もしDキーが押されていたら下の処理を実行
		{
			//テクスチャ座標の更新
			pVtx[0].tex = D3DXVECTOR2(0.0f + 0.25f*m_PatternAnim, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(-0.25f + 0.25f*m_PatternAnim, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + 0.25f*m_PatternAnim, 0.5f);
			pVtx[3].tex = D3DXVECTOR2(-0.25f + 0.25f*m_PatternAnim, 0.5f);
		}
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//位置の取得
	D3DXVECTOR3 p_pos;

	p_pos = GetPosition();

	//位置を更新
	p_pos += move;

	move.x += (0.0f - move.x) *2.0f;//移動量を減衰させる
	move.y += (0.0f - move.y) *2.0f;//[g_movePlayer.〇 += (目的の数値{0.0fで固定}ー現在の数値{g_movePlayer.〇})*減衰係数(0.0f～1.0f)]

	//位置設定
	SetPosition(p_pos, nType);
}
//==========================================================================
//プレイヤーの描画処理
//==========================================================================
void CPlayer::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture[nType]);

	//ポリゴンの描画	
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}
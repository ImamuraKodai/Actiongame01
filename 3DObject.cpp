//==================
//
//3Dオブジェクトを管理する処理[3DObject.cpp]
//Aoutor:今村晃大
//
//==================
#include<Windows.h>
#include"d3dx9.h" //描画処理に必要
#include"main.h"
#include"manager.h"
#include"3DObject.h"

//静的メンバ変数
LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;
LPDIRECT3DTEXTURE9 m_pTexture = NULL;

//コンストラクタ
C3DObject::C3DObject()
{

}

//コンストラクタ
C3DObject::~C3DObject()
{

}

//生成処理
C3DObject * C3DObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	//3Dオブジェクトのポインタ
	C3DObject * p3DObject;

	//3Dオブジェクトの生成
	p3DObject = new C3DObject;

	//3Dオブジェクトの初期化処理
	p3DObject->Init();

	//3Dオブジェクトの位置
	p3DObject->SetPosition1(pos, rot, nType);

	//値を返す
	return p3DObject;
}

//初期化処理
HRESULT C3DObject::Init(void)
{
	int nCntWall; //壁の数

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&m_pTexture);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_Wall,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報のポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_Wall; nCntWall++)
	{
		//頂点座標の設定	
		pVtx[0].pos = D3DXVECTOR3(-WALLSIZE, WALLSIZE, 0);
		pVtx[1].pos = D3DXVECTOR3(WALLSIZE, WALLSIZE, 0);
		pVtx[2].pos = D3DXVECTOR3(-WALLSIZE, -WALLSIZE, 0);
		pVtx[3].pos = D3DXVECTOR3(WALLSIZE, -WALLSIZE, 0);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	for (nCntWall = 0; nCntWall < MAX_Wall; nCntWall++)
	{
		//初期化処理
		m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向き
		m_bUse = false;						   //使用していない状態にする
	}

	return S_OK;
}

//終了処理
void C3DObject::Uninit(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//頂点バッファの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//オブジェクト(自分自身)の破棄
	m_apObject[m_nID] = NULL;
}

//更新処理
void C3DObject::Update(void)
{

}

//描画処理
void C3DObject::Draw(void)
{
	int nCntWall;

	for (nCntWall = 0; nCntWall < MAX_Wall; nCntWall++)
	{
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice(); //デバイスの取得

		D3DXMATRIX mtxRot, mtxTrans;									  //計算用マトリックス

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		//向きを反映	
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntWall * 4,
			2);
	}
}

//オブジェクトの位置設定
void C3DObject::SetPosition1(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	int nCntWall;

	VERTEX_3D *pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報のポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_Wall; nCntWall++)
	{
		//頂点座標の設定	
		pVtx[0].pos = D3DXVECTOR3(-WALLSIZE, WALLSIZE, 0);
		pVtx[1].pos = D3DXVECTOR3(WALLSIZE, WALLSIZE, 0);
		pVtx[2].pos = D3DXVECTOR3(-WALLSIZE, -WALLSIZE, 0);
		pVtx[3].pos = D3DXVECTOR3(WALLSIZE, -WALLSIZE, 0);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;

		if (m_bUse == false)
		{//使われない場合

			nType = nType;

			m_pos = pos;

			m_rot = rot;

			m_bUse = true; //使用している状態にする

			break;
		}
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//位置取得
D3DXVECTOR3 C3DObject::GetPosition(void)
{
	return m_pos;
}
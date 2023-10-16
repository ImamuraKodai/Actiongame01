////==================
////
////3Dオブジェクトを管理する処理[3DObject.cpp]
////Aoutor:今村晃大
////
////==================
//#include"main.h"
//#include"manager.h"
//#include"3DObject.h"
//
////コンストラクタ
//C3DObject::C3DObject()
//{
//
//}
//
////コンストラクタ
//C3DObject::~C3DObject()
//{
//
//}
//
////初期化処理
//HRESULT C3DObject::Init(void)
//{
//	int nCntWall; //壁の数
//
//	//デバイスの取得
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
//
//	//テクスチャの読み込み
//	D3DXCreateTextureFromFile(pDevice,
//		"data\\TEXTURE\\wall000.jpg",
//		&m_pTexture);
//
//	//頂点バッファの生成
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_Wall,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_3D,
//		D3DPOOL_MANAGED,
//		&m_pVtxBuff,
//		NULL);
//
//	VERTEX_3D *pVtx; //頂点情報へのポインタ
//
//	//頂点バッファをロックし、頂点情報のポインタを取得
//	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntWall = 0; nCntWall < MAX_Wall; nCntWall++)
//	{
//		//頂点座標の設定	
//		pVtx[0].pos = D3DXVECTOR3(-WALLSIZE, WALLSIZE, 0);
//		pVtx[1].pos = D3DXVECTOR3(WALLSIZE, WALLSIZE, 0);
//		pVtx[2].pos = D3DXVECTOR3(-WALLSIZE, -WALLSIZE, 0);
//		pVtx[3].pos = D3DXVECTOR3(WALLSIZE, -WALLSIZE, 0);
//
//		//法線ベクトルの設定
//		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//
//		//頂点カラーの設定
//		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//
//		//テクスチャ座標の設定
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx += 4;
//	}
//
//	//頂点バッファをアンロックする
//	m_pVtxBuff->Unlock();
//
//	for (nCntWall = 0; nCntWall < MAX_Wall; nCntWall++)
//	{
//		//初期化処理
//		g_Wall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //位置
//		g_Wall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向き
//		g_Wall[nCntWall].bUse = false;						  //使用していない状態にする
//	}
//
//}
//
////終了処理
//void C3DObject::Uninit(void)
//{
//	//テクスチャの破棄
//	if (m_pTexture != NULL)
//	{
//		m_pTexture->Release();
//		m_pTexture = NULL;
//	}
//
//	//頂点バッファの破棄
//	if (m_pTexture != NULL)
//	{
//		m_pTexture->Release();
//		m_pTexture = NULL;
//	}
//}
//
////更新処理
//void C3DObject::Update(void)
//{
//
//}
//
////描画処理
//void C3DObject::Draw(void)
//{
//	int nCntWall = 0;
//
//	for (nCntWall = 0; nCntWall < MAX_Wall; nCntWall++)
//	{
//		//デバイスの取得
//		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
//		D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
//
//		//ワールドマトリックスの初期化
//		D3DXMatrixIdentity(&m_mtxWorld);
//
//		//向きを反映	
//		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCntWall].rot.y, g_Wall[nCntWall].rot.x, g_Wall[nCntWall].rot.z);
//
//		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
//
//		//位置を反映
//		D3DXMatrixTranslation(&mtxTrans, g_Wall[nCntWall].pos.x, g_Wall[nCntWall].pos.y, g_Wall[nCntWall].pos.z);
//
//		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
//
//		//ワールドマトリックスの設定
//		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
//
//		//頂点バッファをデータストリームに設定
//		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
//
//		//頂点フォーマットの設定
//		pDevice->SetFVF(FVF_VERTEX_3D);
//
//		//テクスチャの設定
//		pDevice->SetTexture(0, m_pTexture);
//
//		//ポリゴンの描画
//		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
//			nCntWall * 4,
//			2);
//	}
//}
//
////設定処理
//void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
//{
//	int nCntWall;
//
//	for (nCntWall = 0; nCntWall < MAX_Wall; nCntWall++)
//	{
//		if (g_Wall[nCntWall].bUse == false)
//		{//ブロックが使用されていない
//
//			g_Wall[nCntWall].pos = pos;
//
//			g_Wall[nCntWall].rot = rot;
//
//			g_Wall[nCntWall].bUse = true; //使用している状態にする
//
//			break;
//		}
//	}
//}
//
////オブジェクトの取得
//C3DObject * GetC3DObject(void)
//{
//	return S_OK;
//}
//
////オブジェクトの位置設定
//void C3DObject::SetPosition(D3DXVECTOR3 pos, int nType)
//{
//	int nCntObject = 0;
//
//	VERTEX_3D * pVtx; //頂点バッファ
//
//	m_pos = pos;
//
//	nType = nType;
//
//	//頂点バッファをロック
//	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntObject = 0; nCntObject < MAX_Wall; nCntObject++)
//	{
//		//頂点座標の設定	
//		pVtx[0].pos = D3DXVECTOR3(-WALLSIZE, WALLSIZE, 0);
//		pVtx[1].pos = D3DXVECTOR3(WALLSIZE, WALLSIZE, 0);
//		pVtx[2].pos = D3DXVECTOR3(-WALLSIZE, -WALLSIZE, 0);
//		pVtx[3].pos = D3DXVECTOR3(WALLSIZE, -WALLSIZE, 0);
//
//		//法線ベクトルの設定
//		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//
//		//頂点カラーの設定
//		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//
//		//テクスチャ座標の設定
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx += 4;
//	}
//
//	//頂点バッファをアンロックする
//	m_pVtxBuff->Unlock();
//}
//
////位置取得
//D3DXVECTOR3 C3DObject::GetPosition(void)
//{
//	return m_pos;
//}
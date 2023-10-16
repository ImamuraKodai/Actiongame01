#ifndef _BLOCK_H_
#define _BLOCK_H_ //二重インクルード防止

#include"main.h"
#include"object2D.h"

class CBlock : public CObject2D
{
public:
	bool bDisp;        //使っているかどうか

	CBlock();          //コンストラクタ
	~CBlock();		   //デストラクタ

	//==========================
	//メンバ関数
	//==========================
	static CBlock * Create(D3DXVECTOR3 pos, int nType);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff1;		  //頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture1[NUM_OBJECT] = {};  //テクスチャ
};

#endif
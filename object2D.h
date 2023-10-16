#ifndef _OBJECT2D_H_ 
#define _OBJECT2D_H_ //二重インクルード防止

#include<windows.h>
#include"d3dx9.h" //描画処理に必要
#include"object.h"
#include"main.h"

//マクロ定義
#define MAX_OBJECT (128) //オブジェクトの最大数

//頂点情報[2D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos; //頂点座標の設定
	D3DXVECTOR3 move;  //移動
	D3DXVECTOR3 rot;   //向き
	float rhw;       //rhwの設定
	D3DCOLOR col;    //頂点カラーの設定lkpm
	int nType;         //種類     
	float fWidth; //幅
	float fHeiht; //高さ

}Object2D;

//オブジェクト2Dクラス
class CObject2D :public CObject
{
public:
	CObject2D();
	~CObject2D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos, int nType);
	static CObject2D *Create(D3DXVECTOR3 pos, int nType);

	D3DXVECTOR3 GetPosition(void); //位置取得

private:

	void MovePlayer(void);

	static CObject2D *m_apObject[MAX_OBJECT];
	static CObject2D *m_apObject1[MAX_OBJECT];
	static int m_NumObject;						    //オブジェクト総数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			    //頂点バッファ

protected:
	float fWidth; //幅
	float fHeiht; //高さ
	int nType;    //種類
	D3DXVECTOR2 tex;								//頂点の設定
	D3DXVECTOR3 m_pos;								//オブジェクトの位置
	D3DXVECTOR3 move;								//移動
};

#endif
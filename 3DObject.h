#ifndef _3DOBJECT_H_
#define _SDOBJECT_H_

#include<windows.h>
#include"d3dx9.h" //描画処理に必要
#include"main.h"
#include"object.h"

//マクロ定義
#define WALLSIZE (400) //壁のサイズ
#define MAX_Wall (4)   //壁の数

//オブジェクト3Dクラス
class C3DObject :public CObject
{
public:
	C3DObject();
	~C3DObject();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition1(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
	static C3DObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);

	D3DXVECTOR3 GetPosition(void); //位置取得

private:
	static int m_NumObject;					   //オブジェクト総数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		   //頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;			   //テクスチャへのポインタ
	D3DXVECTOR3 m_pos;                         //位置
	D3DXVECTOR3 m_rot;                         //向き
	int nType;								   //種類
	bool m_bUse;                               //使っているかどうか
	D3DXMATRIX m_mtxWorld;                     //ワールドマックス
	VERTEX_3D m_aVertex[4];					   //壁の数
};

#endif 
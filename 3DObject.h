#ifndef _3DOBJECT_H_
#define _SDOBJECT_H_

#include"main.h"
#include"manager.h"
#include"object.h"

//マクロ定義
#define WALLSIZE (400) //壁のサイズ
#define MAX_Wall (4)  //壁の数

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
	void SetPosition(D3DXVECTOR3 pos, int nType);
	static C3DObject *Create(D3DXVECTOR3 pos, int nType);

	D3DXVECTOR3 GetPosition(void); //位置取得

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL; //頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;      //テクスチャへのポインタ
	D3DXVECTOR3 m_pos;                         //位置
	D3DXVECTOR3 m_rot;                         //向き
	D3DXMATRIX m_mtxWorld;                     //ワールドマックス
	VERTEX_3D m_aVertex[4];
};

#endif 
#ifndef _OBJECT_H_ 
#define _OBJECT_H_ //二重インクルード防止

#include<windows.h>
#include"d3dx9.h" //描画処理に必要

#define MAX_OBJECT (128) //敵の総数
#define NUM_OBJECT (4) //オブジェクトの種類

//オブジェクトクラス
class CObject
{
public:
	CObject();  //コンストラクタ
	virtual ~CObject(); //デストラクタ

	virtual HRESULT Init(void) = 0; //ポリゴンの初期化処理
	virtual void Uninit(void) = 0;  //ポリゴンの終了処理
	virtual void Update(void) = 0;  //ポリゴンの更新処理
	virtual void Draw(void) = 0;    //ポリゴンの描画処理
	virtual void SetPosition(D3DXVECTOR3 pos, int nType) = 0; //位置と種類

	static void ReleaseAll(void); //すべてのオブジェクトの破棄
	static void UpdateAll(void);  //すべての更新処理
	static void DrawAll(void);    //すべての描画処理

protected:
	void Release(void); //オブジェクトの破棄

public:
	static CObject *m_apObject[MAX_OBJECT]; //オブジェクトの総数
	static int m_nNumAll;					//オブジェクト総数
	int m_nID;								//自分自身のID
	D3DXVECTOR3 m_pos;						//自分の位置

private:
};

#endif
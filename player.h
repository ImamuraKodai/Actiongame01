#ifndef _PLAYER_H_ 
#define _PLAYER_H_ //二重インクルード防止

#include"main.h"
#include"Object2D.h"

class CPlayer : public CObject2D
{
public:

	//プレイヤーの状態
	typedef enum
	{
		PLAYERSTATE_APPEAR, //出現状態(点滅)
		PLAYERSTATE_NORMAL, //通常状態
		PLAYERSTATE_DAMAGE, //ダメージ状態
		PLAYERSTATE_WAIT,   //出現待ち状態(表示なし)
		PLAYERSTATE_DEATH,  //死亡状態
		PLAYERSTATE_MAX
	}PLAYERSTATE;

	D3DXVECTOR3 move;  //移動
	D3DXVECTOR3 rot;   //向き
	bool bDisp;        //使っているかどうか
	PLAYERSTATE state; //プレイヤーの状態
	int nCounterState; //ダメージ状態
	int nAppearCounter;//出現状態
	int nLife;         //体力　

	CPlayer();
	~CPlayer();

	//==========================
	//メンバ関数
	//==========================
	static CPlayer * Create(D3DXVECTOR3 pos, int nType);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

protected:
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		  //頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture[NUM_OBJECT] = {};	  //テクスチャ

private:

	void MovePlayer(void); //プレイヤーの移動

	int m_CounterAnim;								  //アニメーションカウンター
	int m_PatternAnim;								  //アニメーションパターンNo.
};

#endif
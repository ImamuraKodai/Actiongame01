#ifndef _RENDERER_H_ 
#define _RENDERER_H_ //二重インクルード防止

#include<windows.h>
#include"d3dx9.h" //描画処理に必要

//レンダラークラス
class CRenderer
{
public:
	CRenderer();  //コンストラクタ
	~CRenderer(); //デストラクタ

	HRESULT Init(HWND hWnd, BOOL bWindow); //初期化処理
	void Uninit(void);                     //終了処理
	void Update(void);                     //更新処理
	void Draw(void);                       //描画処理
	LPDIRECT3DDEVICE9 GetDevice(void);     //デバイスの入手

private:
	LPDIRECT3D9 m_PD3D = NULL;             //3D
	LPDIRECT3DDEVICE9 m_pD3DDevice = NULL; //3Dデバイス
};

#endif

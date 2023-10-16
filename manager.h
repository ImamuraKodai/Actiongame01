#ifndef _MANAGER_H_ 
#define _MANAGER_H_ //二重インクルード防止

#include<windows.h>
#include"d3dx9.h" //描画処理に必要
#include"renderer.h"
#include"input.h"

//前方宣言
class CRenderer;
class CInputKeyboard;
class CObject;

//マネージャークラス
class CManager
{
public:
	CManager(); //コンストラクタ
	~CManager(); //デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRenderer *GetRenderer(void); //レンダラーの取得
	static CObject *GetObject(void);     //オブジェクトの取得
	static CInputKeyboard *GetKeyboard(void); //キーボードの取得
	static CManager * GetInstance(void);
	static HRESULT Release(void);
private:
	static CRenderer *m_pRenderer;       //レンダラー
	static CObject *m_apObject;          //オブジェクト
	static CInputKeyboard *m_pKeyboard;  //キーボード
	static CManager * pManager;			 //マネージャー	
	//static CCamera *m_pCamera;           //カメラ
};

#endif

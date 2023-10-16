#ifndef _INPUT_H_
#define _INPUT_H_ //二重インクルード防止

#include "main.h"

//マクロ定義
#define NUM_KEY_MAX (256) //キーの最大数

//入力クラス
class CInput
{
public:
	CInput();  //コンストラクタ
	~CInput(); //デストラクタ

	virtual HRESULT Init(HINSTANCE hInstans, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//キーボードクラス
class CInputKeyboard :public CInput
{
public:
	CInputKeyboard();   //コンストラクタ
	~CInputKeyboard();  //デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];        //キーボードのプレス情報
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX]; //キーボードのトリガー情報
};

#endif


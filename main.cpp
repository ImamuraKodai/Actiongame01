//==================
//
//文字を出力する処理[main.cpp]
//Aoutor:今村晃大
//
//==================
#include"main.h"
#include"renderer.h"
#include"object.h"
#include"object2D.h"
#include"3DObject.h"
#include"manager.h"

//マクロ定義
#define CLASS_NAME "windowclass"  //ウインドウクラスの名前
#define WINDOW_NAME "DirectX"     //ウインドウの名前(キャプションに表示)

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM WParam, LPARAM IPlam);
//CRenderer * g_pRenderer = NULL;

//================
//メイン関数
//================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInctancePlev, LPSTR IpCmdLine, int nCmdShow)
{
	CManager *pManager = NULL;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),//WNDCLASSEXのメモリサイズ
		CS_CLASSDC, //ウインドウのスタイル
		WindowProc, //ウインドウプロシージャ
		0, //0にする(通常は使用しない
		0, //0にする(通常は使用しない
		hInstance, //インスタンスハンドル
		LoadIcon(NULL, IDC_ARROW), //タスクバーのアイコン
		LoadCursor(NULL, IDC_ARROW), //マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1), //クライアント領域の背景色
		NULL, //メニューバー
		CLASS_NAME, //ウインドウクラスの名前
		LoadIcon(NULL, IDI_APPLICATION) //ファイルのアイコン
	};

	HWND hWnd; //ウインドウハンドル(識別子)
	MSG msg;   //メッセージを格納する変数	

	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	//ウインドウを生成
	hWnd = CreateWindowEx(0,        //拡張ウインドウスタイル
		CLASS_NAME,                 //ウインドウクラスの名前)
		WINDOW_NAME,                //ウインドウの名前
		WS_OVERLAPPEDWINDOW,        //ウインドウスタイル
		CW_USEDEFAULT,              //ウインドウの左上x座標
		CW_USEDEFAULT,              //ウインドウの左上Y座標
		SCREEN_WIDTH,               //ウインドウの左上の幅
		SCREEN_HEIGHT,              //ウインドウの左上の高さ
		NULL,                       //親ウインドウのハンドル
		NULL,                       //メニューハンドルまたはウインドウID
		hInstance,                  //インスタンスハンドル
		NULL);                      //ウインドウ作成データ

	//マネージャーの生成
	pManager = new CManager;

	//マネージャーの初期化処理
	pManager->Init(hInstance, hWnd, TRUE);

	//ウインドウの表示
	ShowWindow(hWnd, nCmdShow);     //ウインドウの表示状態を設定
	UpdateWindow(hWnd);             //クライアント領域を更新

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windowsの処理

			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける

				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectXの処理

			//マネージャーの更新処理
			pManager->Update();

			//マネージャーの描画処理
			pManager->Draw();
		}
	}

	//マネージャーの破棄
	if (pManager != NULL)
	{
		//マネージャーの終了処理
		pManager->Uninit();

		delete pManager;

		pManager = NULL;
	}

	//オブジェクトの終了処理
	CObject::ReleaseAll();

	//ウインドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//ウインドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
	int nID;
	HDC hPC = 0;
	char aString[256] = "test";
	static POINT pos = { 100,100 }; //
	static POINT move = { 2,3 };    //
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }; //

	switch (uMsg)
	{
	case WM_DESTROY: //ウインドウ破棄のメッセージ

		//WM_QUITメッセージを送る	
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //キー押下のメッセージ

		switch (wParam)
		{
		case VK_ESCAPE: //[ESC]キーが押された
			nID = MessageBox(hWnd, "終了しますか?", "終了メッセージ", MB_YESNO);
			if (nID == IDYES)
			{
				//ウインドウを破棄する(WM_DESTROY
				DestroyWindow(hWnd);
				break;
			}
			break;

		case VK_RIGHT: //
			pos.x++;   //
					   //
			InvalidateRect(hWnd, &rect, FALSE);
			break;
		}
		break;

	case WM_CLOSE: //閉じるボタン押下のメッセージ
		nID = MessageBox(hWnd, "終了しますか?", "終了メッセージ", MB_YESNO);
		{
			if (nID == IDYES)
			{
				//ウインドウを破壊する
				DestroyWindow(hWnd);
			}
			else
			{
				return 0; //0を返さないと終了してしまう
			}
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, IParam);
}

//オブジェクトの取得
CObject **GetObject(void)
{
	int nCntObject = 0;

	return &CObject::m_apObject[nCntObject];
}
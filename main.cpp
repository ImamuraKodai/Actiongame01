//==================
//
//�������o�͂��鏈��[main.cpp]
//Aoutor:�����W��
//
//==================
#include"main.h"
#include"renderer.h"
#include"object.h"
#include"object2D.h"
#include"3DObject.h"
#include"manager.h"

//�}�N����`
#define CLASS_NAME "windowclass"  //�E�C���h�E�N���X�̖��O
#define WINDOW_NAME "DirectX"     //�E�C���h�E�̖��O(�L���v�V�����ɕ\��)

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM WParam, LPARAM IPlam);
//CRenderer * g_pRenderer = NULL;

//================
//���C���֐�
//================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInctancePlev, LPSTR IpCmdLine, int nCmdShow)
{
	CManager *pManager = NULL;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC, //�E�C���h�E�̃X�^�C��
		WindowProc, //�E�C���h�E�v���V�[�W��
		0, //0�ɂ���(�ʏ�͎g�p���Ȃ�
		0, //0�ɂ���(�ʏ�͎g�p���Ȃ�
		hInstance, //�C���X�^���X�n���h��
		LoadIcon(NULL, IDC_ARROW), //�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL, IDC_ARROW), //�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1), //�N���C�A���g�̈�̔w�i�F
		NULL, //���j���[�o�[
		CLASS_NAME, //�E�C���h�E�N���X�̖��O
		LoadIcon(NULL, IDI_APPLICATION) //�t�@�C���̃A�C�R��
	};

	HWND hWnd; //�E�C���h�E�n���h��(���ʎq)
	MSG msg;   //���b�Z�[�W���i�[����ϐ�	

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(0,        //�g���E�C���h�E�X�^�C��
		CLASS_NAME,                 //�E�C���h�E�N���X�̖��O)
		WINDOW_NAME,                //�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,        //�E�C���h�E�X�^�C��
		CW_USEDEFAULT,              //�E�C���h�E�̍���x���W
		CW_USEDEFAULT,              //�E�C���h�E�̍���Y���W
		SCREEN_WIDTH,               //�E�C���h�E�̍���̕�
		SCREEN_HEIGHT,              //�E�C���h�E�̍���̍���
		NULL,                       //�e�E�C���h�E�̃n���h��
		NULL,                       //���j���[�n���h���܂��̓E�C���h�EID
		hInstance,                  //�C���X�^���X�n���h��
		NULL);                      //�E�C���h�E�쐬�f�[�^

	//�}�l�[�W���[�̐���
	pManager = new CManager;

	//�}�l�[�W���[�̏���������
	pManager->Init(hInstance, hWnd, TRUE);

	//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);     //�E�C���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);             //�N���C�A���g�̈���X�V

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windows�̏���

			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���

				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���

			//�}�l�[�W���[�̍X�V����
			pManager->Update();

			//�}�l�[�W���[�̕`�揈��
			pManager->Draw();
		}
	}

	//�}�l�[�W���[�̔j��
	if (pManager != NULL)
	{
		//�}�l�[�W���[�̏I������
		pManager->Uninit();

		delete pManager;

		pManager = NULL;
	}

	//�I�u�W�F�N�g�̏I������
	CObject::ReleaseAll();

	//�E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//�E�C���h�E�v���V�[�W��
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
	case WM_DESTROY: //�E�C���h�E�j���̃��b�Z�[�W

		//WM_QUIT���b�Z�[�W�𑗂�	
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //�L�[�����̃��b�Z�[�W

		switch (wParam)
		{
		case VK_ESCAPE: //[ESC]�L�[�������ꂽ
			nID = MessageBox(hWnd, "�I�����܂���?", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{
				//�E�C���h�E��j������(WM_DESTROY
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

	case WM_CLOSE: //����{�^�������̃��b�Z�[�W
		nID = MessageBox(hWnd, "�I�����܂���?", "�I�����b�Z�[�W", MB_YESNO);
		{
			if (nID == IDYES)
			{
				//�E�C���h�E��j�󂷂�
				DestroyWindow(hWnd);
			}
			else
			{
				return 0; //0��Ԃ��Ȃ��ƏI�����Ă��܂�
			}
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, IParam);
}

//�I�u�W�F�N�g�̎擾
CObject **GetObject(void)
{
	int nCntObject = 0;

	return &CObject::m_apObject[nCntObject];
}
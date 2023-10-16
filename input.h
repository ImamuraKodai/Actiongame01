#ifndef _INPUT_H_
#define _INPUT_H_ //��d�C���N���[�h�h�~

#include "main.h"

//�}�N����`
#define NUM_KEY_MAX (256) //�L�[�̍ő吔

//���̓N���X
class CInput
{
public:
	CInput();  //�R���X�g���N�^
	~CInput(); //�f�X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstans, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//�L�[�{�[�h�N���X
class CInputKeyboard :public CInput
{
public:
	CInputKeyboard();   //�R���X�g���N�^
	~CInputKeyboard();  //�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];        //�L�[�{�[�h�̃v���X���
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX]; //�L�[�{�[�h�̃g���K�[���
};

#endif


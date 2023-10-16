#ifndef _MANAGER_H_ 
#define _MANAGER_H_ //��d�C���N���[�h�h�~

#include<windows.h>
#include"d3dx9.h" //�`�揈���ɕK�v
#include"renderer.h"
#include"input.h"

//�O���錾
class CRenderer;
class CInputKeyboard;
class CObject;

//�}�l�[�W���[�N���X
class CManager
{
public:
	CManager(); //�R���X�g���N�^
	~CManager(); //�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRenderer *GetRenderer(void); //�����_���[�̎擾
	static CObject *GetObject(void);     //�I�u�W�F�N�g�̎擾
	static CInputKeyboard *GetKeyboard(void); //�L�[�{�[�h�̎擾
	static CManager * GetInstance(void);
	static HRESULT Release(void);
private:
	static CRenderer *m_pRenderer;       //�����_���[
	static CObject *m_apObject;          //�I�u�W�F�N�g
	static CInputKeyboard *m_pKeyboard;  //�L�[�{�[�h
	static CManager * pManager;			 //�}�l�[�W���[	
	//static CCamera *m_pCamera;           //�J����
};

#endif

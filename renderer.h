#ifndef _RENDERER_H_ 
#define _RENDERER_H_ //��d�C���N���[�h�h�~

#include<windows.h>
#include"d3dx9.h" //�`�揈���ɕK�v

//�����_���[�N���X
class CRenderer
{
public:
	CRenderer();  //�R���X�g���N�^
	~CRenderer(); //�f�X�g���N�^

	HRESULT Init(HWND hWnd, BOOL bWindow); //����������
	void Uninit(void);                     //�I������
	void Update(void);                     //�X�V����
	void Draw(void);                       //�`�揈��
	LPDIRECT3DDEVICE9 GetDevice(void);     //�f�o�C�X�̓���

private:
	LPDIRECT3D9 m_PD3D = NULL;             //3D
	LPDIRECT3DDEVICE9 m_pD3DDevice = NULL; //3D�f�o�C�X
};

#endif

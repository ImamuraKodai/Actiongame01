//==================
//
//�������o�͂��鏈��[renderer.cpp]
//Aoutor:�����W��
//
//==================
#include<Windows.h>
#include"d3dx9.h" //�`�揈���ɕK�v
#include"main.h"
#include"renderer.h"
#include"object.h"

//�R���X�g���N�^
CRenderer::CRenderer()
{

}

//�f�X�g���N�^
CRenderer::~CRenderer()
{

}

//����������
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;        //�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp; //�v���[���e�[�V�����p�����[�^
	HDC hPC = 0;
	char aString[256] = "test";
	static POINT pos = { 100,100 }; //
	static POINT move = { 2,3 };    //
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }; //

	//Direct3D�I�u�W�F�N�g�̐���
	m_PD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_PD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_PD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp)); //

	d3dpp.BackBufferWidth = SCREEN_WIDTH;      //
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;    //
	d3dpp.BackBufferFormat = d3ddm.Format;     //
	d3dpp.BackBufferCount = 1;                 //
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;  //
	d3dpp.EnableAutoDepthStencil = TRUE;       //
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16; //
	d3dpp.Windowed = bWindow;                  //
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;   //

	//Direct3D�f�o�C�X�̐���
	if (FAILED(m_PD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		if (FAILED(m_PD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			if (FAILED(m_PD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	return S_OK;
}

//�I������
void CRenderer::Uninit(void)
{
	//Direct3D�f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	//Direct3D�f�o�C�X�̏���
	if (m_PD3D != NULL)
	{
		m_PD3D->Release();
		m_PD3D = NULL;
	}
}

//�X�V����
void CRenderer::Update(void)
{
	//�I�u�W�F�N�g�̍X�V����
	CObject::UpdateAll();
}

//�`�揈��
void CRenderer::Draw(void)
{
	//��ʃN���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

		//�I�u�W�F�N�g�̕`�揈��
		CObject::DrawAll();

		//�`��I��
		m_pD3DDevice->EndScene();
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̐؂�ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//�f�o�C�X�̎擾
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}
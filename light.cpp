//==================
//
//���C�g�̊Ǘ����鏈��[light.cpp]
//Aoutor:�����W��
//
//==================
#include"light.h"
#include"manager.h"
#include"main.h"

//�R���X�g���N�^
CLight::CLight()
{
	
}

//�f�X�g���N�^
CLight::~CLight()
{

}

//���C�g�̏���������
HRESULT CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice(); //�f�o�C�X�̎擾
	D3DXVECTOR3 vecDir;											      //�ݒ�p�����x�N�g��

	//���C�g�̏����N���A����
	ZeroMemory(&m_aLight[0], sizeof(D3DLIGHT9));

	//���C�g�̎�ނ�ݒ�
	m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g������ݒ�
	m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);      //�x�N�g���𐳋K������
	m_aLight[0].Direction = vecDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(0, &m_aLight[0]);


	//���C�g�̏����N���A����
	ZeroMemory(&m_aLight[1], sizeof(D3DLIGHT9));

	//���C�g�̎�ނ�ݒ�
	m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g������ݒ�
	m_aLight[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);      //�x�N�g���𐳋K������
	m_aLight[1].Direction = vecDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(0, &m_aLight[1]);


	//���C�g�̏����N���A����
	ZeroMemory(&m_aLight[2], sizeof(D3DLIGHT9));

	//���C�g�̎�ނ�ݒ�
	m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g������ݒ�
	m_aLight[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);      //�x�N�g���𐳋K������
	m_aLight[2].Direction = vecDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(0, &m_aLight[2]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);

	return S_OK;
}

//���C�g�̏I������
void CLight::Uninit(void)
{

}

//���C�g�̍X�V����
void CLight::Update(void)
{

}
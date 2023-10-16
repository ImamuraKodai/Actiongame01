////==================
////
////�J�������Ǘ����鏈��[camera.cpp]
////Aoutor:�����W��
////
////==================
//#include "main.h"
//#include "manager.h"
//#include "camera.h"
//#include "input.h"
//
////�R���X�g���N�^
//CCamera::CCamera()
//{
//
//}
//
////�f�X�g���N�^
//CCamera::~CCamera()
//{
//
//}
//
////�J�����̏���������
//HRESULT CCamera::Init(void)
//{
//	m_posV = D3DXVECTOR3(0.0f, 100.0f, -100.0f);   //���_
//	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);        //�����_
//	m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);        //������x�N�g��
//	fDistance = (100.0f);						   //����
//	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		   //����
//	posVDest = D3DXVECTOR3(0.0f, 100.0f, -100.0f); //�ړI�̎��_
//	posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      //�ړI�̒����_
//	posMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	   //�ړ���
//}
//
////�J�����̏I������
//void CCamera::Uninit(void)
//{
//
//}
//
////�J�����̍X�V����
//void CCamera::Update(void)
//{
//	//�v���C���[�̈ړ�
//	CInputKeyboard * pInputKeyboard;
//
//	//�L�[�{�[�h�̎擾
//	pInputKeyboard = CManager::GetKeyboard();
//
//	//���ړ�
//	if (pInputKeyboard->GetPress(DIK_A) == true)
//	{
//		m_posV.x -= 0.5f;
//		m_posR.x -= 0.5f;
//	}
//
//	//�E�ړ�
//	if (pInputKeyboard->GetPress(DIK_D) == true)
//	{
//		m_posV.x += 0.5f;
//		m_posR.x += 0.5f;
//	}
//
//	//��ړ�
//	if (pInputKeyboard->GetPress(DIK_W) == true)
//	{
//		m_posV.z += 0.5f;
//		m_posR.z += 0.5f;
//	}
//
//	//���ړ�
//	if (pInputKeyboard->GetPress(DIK_S) == true)
//	{
//		m_posV.z -= 0.5f;
//		m_posR.z -= 0.5f;
//	}
//
//	//������ړ�
//	if (pInputKeyboard->GetPress(DIK_I) == true)
//	{
//		m_posV.y += 0.5f;
//		m_posR.y += 0.5f;
//	}
//
//	//�������ړ�
//	if (pInputKeyboard->GetPress(DIK_K) == true)
//	{
//		m_posV.y -= 0.5f;
//		m_posR.y -= 0.5f;
//	}
//
//	//���_�̍���]
//	if (pInputKeyboard->GetPress(DIK_Z) == true)
//	{
//		rot.y += 0.1f;
//
//		if (rot.y < -D3DX_PI)
//		{
//			rot.y = D3DX_PI;
//		}
//
//		m_posV.x = m_posR.x + cosf(rot.y) * fDistance;
//		m_posV.z = m_posR.z + sinf(rot.y) * fDistance;
//	}
//
//	//���_�̉E��]
//	if (pInputKeyboard->GetPress(DIK_C) == true)
//	{
//		rot.y -= 0.1f;
//
//		if (rot.y < -D3DX_PI)
//		{
//			rot.y = D3DX_PI;
//		}
//
//		m_posV.x = m_posR.x + cosf(rot.y) * fDistance;
//		m_posV.z = m_posR.z + sinf(rot.y) * fDistance;
//	}
//
//	//�����_�̍���]
//	if (pInputKeyboard->GetPress(DIK_Q) == true)
//	{
//		rot.y += 0.1f;
//
//		if (rot.y < -D3DX_PI)
//		{
//			rot.y = D3DX_PI;
//		}
//
//		m_posR.x = m_posV.x - cosf(rot.y) * fDistance;
//		m_posR.z = m_posV.z - sinf(rot.y) * fDistance;
//	}
//
//	//�����_�̉E��]
//	if (pInputKeyboard->GetPress(DIK_E) == true)
//	{
//		rot.y -= 0.1f;
//
//		if (rot.y < -D3DX_PI)
//		{
//			rot.y = D3DX_PI;
//		}
//
//		m_posR.x = m_posV.x - cosf(rot.y) * fDistance;
//		m_posR.z = m_posV.z - sinf(rot.y) * fDistance;
//	}
//
//	//�����_
//	//g_camera.posRDest = D3DXVECTOR3(pModel->pos.x + -sinf(pModel->rot.y)*50.0f, pModel->pos.y, pModel->pos.z + -cosf(pModel->rot.y)*50.0f);
//
//	//g_camera.posVDest.x = g_camera.posRDest.x + cosf(g_camera.rot.y) * g_camera.fDistance;
//
//	//g_camera.posVDest.z = g_camera.posRDest.z + sinf(g_camera.rot.y) * g_camera.fDistance;
//
//
//	//�����_�̊���
//	m_posR = pModel->pos;
//
//	//���_�̊���
//	m_posR.x = m_posR.x;
//
//	m_posR.z = m_posR.z - 100.0f;
//
//}
//
////�J�����̕`�揈��
//void CCamera::Draw(void)
//{
//
//}
//
////�J�����̐ݒ菈��
//void CCamera::SetCamera(void)
//{
//	//�f�o�C�X�̎擾
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
//
//	//�v���W�F�N�V�����}�g���b�N�X�̏�����
//	D3DXMatrixIdentity(&mtxProjection);
//
//	//�v���W�F�N�V�����}�g���b�N�X���쐬
//	D3DXMatrixPerspectiveFovLH(&mtxProjection,
//		D3DXToRadian(45.0f),
//		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
//		10.0f,
//		1000.0f);
//
//	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
//	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
//
//	//�r���[�}�g���b�N�X�̏�����
//	D3DXMatrixIdentity(&mtxView);
//
//	//�r���[�}�g���b�N�X���쐬
//	D3DXMatrixLookAtLH(&mtxView,
//		&m_posV,
//		&m_posR,
//		&m_posU);
//
//	//�r���[�}�g���b�N�X�̐ݒ�
//	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
//}
//
////�J�����̐ݒ菈��
//void CCamera::SetCamera(D3DXVECTOR3 pos)
//{
//	m_posR = pos;
//
//	posMove = D3DXVECTOR3(5.0f, 0.0f, 5.0f); //�ړ���
//
//	//�ړI�̒����_��ݒ�
//	m_posV.x = posMove.x + m_posR.x;
//	m_posV.z = posMove.z + m_posR.z;
//
//	//�ړI�̎��_��ݒ�
//	m_posR.x = pos.x + m_posV.x;
//	m_posR.z = pos.z + m_posV.z;
//}
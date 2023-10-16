#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//�J�����N���X
class CCamera
{
public:
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetCamera(void);

private:
	D3DMATRIX m_mtxView;		//�r���[�}�g���b�N�X
	D3DMATRIX m_mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXVECTOR3 m_posV;			//���_
	D3DXVECTOR3 m_posR;			//�����_
	D3DXVECTOR3 m_posU;			//������x�N�g��
	D3DXVECTOR3 rot;			//����
	D3DXVECTOR3 posVDest;		//�ړI�̎��_
	D3DXVECTOR3 posRDest;		//�ړI�̒����_
	D3DXVECTOR3 posMove;		//�ړ���
	float fDistance;			//����
	D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
};

#endif
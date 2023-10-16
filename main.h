#ifndef _MAIN_H_ 
#define _MAIN_H_ //��d�C���N���[�h�h�~

//DirectX�̏����ݒ�
#include<windows.h>
#include"d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800) //
#include "dinput.h" //
#include "xaudio2.h"

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib") //���͏����ɕK�v

//�}�N����`
#define SCREEN_WIDTH (1280)													//�E�C���h�E�̕�
#define SCREEN_HEIGHT (720)													//�E�C���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)			//2D�e�N�X�`��
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1) //3D�e�N�X�`��


//���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	float rhw;       //rhw
	D3DCOLOR col;    //�J���[
	D3DXVECTOR2 tex; //���_�o�b�t�@

}VERTEX_2D;

//���_���[3D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	D3DXVECTOR3 nor; //�@���x�N�g��
	D3DCOLOR col;    //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
}VERTEX_3D;

//�O���錾
class CRenderer;
class CObject;

//�v���g�^�C�v�錾
//CRenderer *GetRenderer(void);
CObject **GetObject(void);

#endif
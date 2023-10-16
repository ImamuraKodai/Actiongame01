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
#define SCREEN_WIDTH (1280)              //�E�C���h�E�̕�
#define SCREEN_HEIGHT (720)              //�E�C���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos; //
	float rhw;       //
	D3DCOLOR col;    //
	D3DXVECTOR2 tex; //

}VERTEX_2D;

//�O���錾
class CRenderer;
class CObject;

//�v���g�^�C�v�錾
//CRenderer *GetRenderer(void);
CObject **GetObject(void);

#endif
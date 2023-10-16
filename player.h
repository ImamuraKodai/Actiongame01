#ifndef _PLAYER_H_ 
#define _PLAYER_H_ //��d�C���N���[�h�h�~

#include"main.h"
#include"Object2D.h"

class CPlayer : public CObject2D
{
public:

	//�v���C���[�̏��
	typedef enum
	{
		PLAYERSTATE_APPEAR, //�o�����(�_��)
		PLAYERSTATE_NORMAL, //�ʏ���
		PLAYERSTATE_DAMAGE, //�_���[�W���
		PLAYERSTATE_WAIT,   //�o���҂����(�\���Ȃ�)
		PLAYERSTATE_DEATH,  //���S���
		PLAYERSTATE_MAX
	}PLAYERSTATE;

	D3DXVECTOR3 move;  //�ړ�
	D3DXVECTOR3 rot;   //����
	bool bDisp;        //�g���Ă��邩�ǂ���
	PLAYERSTATE state; //�v���C���[�̏��
	int nCounterState; //�_���[�W���
	int nAppearCounter;//�o�����
	int nLife;         //�̗́@

	CPlayer();
	~CPlayer();

	//==========================
	//�����o�֐�
	//==========================
	static CPlayer * Create(D3DXVECTOR3 pos, int nType);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

protected:
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		  //���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture[NUM_OBJECT] = {};	  //�e�N�X�`��

private:

	void MovePlayer(void); //�v���C���[�̈ړ�

	int m_CounterAnim;								  //�A�j���[�V�����J�E���^�[
	int m_PatternAnim;								  //�A�j���[�V�����p�^�[��No.
};

#endif
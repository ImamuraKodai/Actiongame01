#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//カメラクラス
class CCamera
{
public:
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetCamera(void);

private:
	D3DMATRIX m_mtxView;		//ビューマトリックス
	D3DMATRIX m_mtxProjection;	//プロジェクションマトリックス
	D3DXVECTOR3 m_posV;			//視点
	D3DXVECTOR3 m_posR;			//注視点
	D3DXVECTOR3 m_posU;			//上方向ベクトル
	D3DXVECTOR3 rot;			//向き
	D3DXVECTOR3 posVDest;		//目的の視点
	D3DXVECTOR3 posRDest;		//目的の注視点
	D3DXVECTOR3 posMove;		//移動量
	float fDistance;			//距離
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス
};

#endif
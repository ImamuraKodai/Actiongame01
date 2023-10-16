#ifndef _3DOBJECT_H_
#define _SDOBJECT_H_

#include "main.h"
#include "object.h"

//オブジェクト3Dクラス
class C3DOBJECT :public CObject
{
public:
	C3DOBJECT();
	~C3DOBJECT();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos, int nType);
	static C3DOBJECT *Create(D3DXVECTOR3 pos, int nType);

	D3DXVECTOR3 GetPosition(void); //位置取得

};

#endif 
// スカイドーム（空）

#pragma once
#include "skydome.h"
class CSky :
	public CSkyDome
{
private:


public:
	CSky(void);
	CSky(int n);
	virtual ~CSky(void);

	CSky* Create(CMesh* pMesh);
	//virtual void Update(void);
	//virtual void DrawAlpha(void);
	//virtual void Draw(void); 
	void Initialize(void);
};


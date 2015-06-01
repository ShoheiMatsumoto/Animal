#pragma once
#include "fade.h"




class CFadeOut :
	public CFade
{
public:
	CFadeOut(void);
	virtual ~CFadeOut(void);

	CFadeOut* Create(int nImage);
	void Initialize(int nImage);

	void Update();
	void Release();
};


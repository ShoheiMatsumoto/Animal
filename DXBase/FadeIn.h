#pragma once
#include "fade.h"


class CFadeIn :
	public CFade
{
public:
	CFadeIn(void);
	CFadeIn(int n);
	virtual ~CFadeIn(void);

	CFadeIn* Create(int nImage);
	void Initialize(int nImage);

	void Update();
	void Release();
};


#pragma once


typedef struct 
{
	int		nArrayNum;
	float	fData;
}SortData;


class CMySort
{
public:
	CMySort(void);
	virtual ~CMySort(void);

	void QuiqSort(SortData* Data, int nArrNum);
};


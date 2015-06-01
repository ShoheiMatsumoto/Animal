#include "MySort.h"
#include "define.h"

CMySort::CMySort(void)
{
}


CMySort::~CMySort(void)
{
}


void CMySort::QuiqSort(SortData* Data, int nArrNum)
{
	if(nArrNum < 3)
		return;

	int nHalf = (nArrNum - 1) / 2;		// 半分
	int nAmari = (nArrNum) % 2;
	float fBaseData = Data[nHalf].fData;		// 基準値
	int nCnt = nArrNum - 1;
	SortData Wk;

	// 添え字の小さい方から
	for(int i = 0; i <= nHalf; i++)
	{
		// 基準値以上
		if(Data[i].fData >= fBaseData)
		{
			// 添え字の大きい方から
			for(nCnt; nCnt > nHalf; nCnt--)
			{
				// 基準値未満
				if(Data[nCnt].fData < fBaseData)
				{
					// 交換
					Wk			= Data[i];
					Data[i]		= Data[nCnt];
					Data[nCnt]	= Data[i];
					break;
				}
			}
		}
	}

	if(nHalf < 3)		// 要素数が3以下なら
		return;

	// 配列を2つに分ける
	SortData* Data1 = new SortData[nHalf + 1];
	SortData* Data2 = new SortData[nArrNum - nHalf - 1];

	// 移す
	for(int i = 0; i <= nHalf; i++)
	{
		Data1[i] = Data[i];
	}

	for(int i = 0; i < nArrNum - nHalf - 1; i++)
	{
		Data2[i] = Data[i + nHalf + 1];
	}

	// 再起
	QuiqSort(Data1, nHalf + 1);
	QuiqSort(Data2, nArrNum - nHalf - 1);

	// 連結
	for(int i = 0; i <= nHalf; i++)
	{
		Data[i] = Data1[i];
	}

	for(int i = 0; i < nArrNum - nHalf - 1; i++)
	{
		Data[i + nHalf + 1] = Data2[i];
	}

	// 解放
	SAFE_DELETE_ARRAY(Data1);
	SAFE_DELETE_ARRAY(Data2);
}


// eof
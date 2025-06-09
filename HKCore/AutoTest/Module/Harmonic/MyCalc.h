//MyCalc.h
#if !defined MYCALC_H_
#define MYCALC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyCalc	//单通道输出参数
{
// Construction
public:
	CMyCalc();
	~CMyCalc();

	/////////////////////////////////////////////////////
public:
	void Long_to_Byte(long lTemp1, BYTE *buf);
	long Byte_to_Long(BYTE *buf);
};

#endif


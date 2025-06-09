//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UibGenChBase.h  CUibGenChBase

#pragma once


class CUibChGenInterface : public CExBaseList
{
public:
	CUibChGenInterface();
	virtual ~CUibChGenInterface();

	unsigned short* m_pnAttachBuffer;

public:
	virtual void Generate(long &nUibGenIndex, long &nCalIndex) = 0;
	virtual void InitGenerate(double dCoef_FreqAngleT) = 0;
};


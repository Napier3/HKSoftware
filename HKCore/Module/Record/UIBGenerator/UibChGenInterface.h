//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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


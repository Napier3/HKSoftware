#pragma once

#include "../Comtrade/ComtradeMngr.h"

#define BIG_COMTRADE_BINARY_READ_LENGTH                                      20*1024*1024

class CBigComtradeRead
{
public:
	CBigComtradeRead(void);
	virtual ~CBigComtradeRead(void);

public:
	long CalMaxDataBufPointNum();
	BOOL OpenBigComtradeFile(const CString &strComtradeFile);
	BOOL GenerateComtradeChDataFromDataFile();

protected:
	long ReadBigDataFile(const CString& strComtradeFile);
	long ReadBigDataAsBINARYMode(const CString& strComtradeFile);
	long ReadBigDataAsASIIMode(const CString& strComtradeFile);
	void BufferClear();
	void SetTotalSmpRates();
	long GetCurReadPointsNum();


public:
	CRcdComtradeFile m_oBigComtradeFile;////����������ͨ����ԭʼ����
	double m_nInsertFreq;//��ֵ��Ƶ��K3��ʵ�ʲ��Ų����ʣ���50K

private:
	CFile m_oFileRead;//ComtradeData�ļ�
	BOOL m_bHasOpenDataFile;

	BYTE *m_pFileReadBuffer;  //���ļ���ȡ�Ļ����� 20M
	long m_nCurTotalByteLength;

	long m_nFileReadLength;//ÿ�δ��ļ���ȡ�Ĵ�С

	//ԭʼͨ�������У���ѹ�������ֵ
	float m_fUMax;  
	float m_fUMin;
	float m_fIMax;  
	float m_fIMin;

	BOOL m_bReadFileFinish;	//���ļ�����
	BOOL m_bAnalysisFinish;	//�����ļ����ݽ���
	long m_nCurBeginPointIndex;//�ط���ͨ�����ݻ���1����ʼ���������ڼ���ʱ�䣬��ǰm_oBigComtradeFile����ʼ�������ʵ��Comtrade�ļ���ʼ���Index����
	long m_nCurPointNum;//��ǰ���������е���

	float* m_pdSamRate; //��ͬ�Ĳ�����
	long* m_pnDataPoints;//��ͬ�������µĲ�������
	long m_nSamAmount;//�����ʵ�����
	long m_nTotalPointsNum;//data�ļ��е��ܵĲ���������
};

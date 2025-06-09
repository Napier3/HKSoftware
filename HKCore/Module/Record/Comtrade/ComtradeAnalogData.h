// ComtradeAnalogData.h: interface for the CComtradeAnalogData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMTRADEANALOGDATA_H__E0AA22A6_09FD_4AF5_A855_D7E0CFBEE215__INCLUDED_)
#define AFX_COMTRADEANALOGDATA_H__E0AA22A6_09FD_4AF5_A855_D7E0CFBEE215__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ComtradeDataBase.h"
#include "ComtradeFileGlobal.h"

//RT_CalFrequency[0] ~ RT_CalHarm25Phase[55] + RT_CalImpedance[0]~RT_CalReserve10Value[16]
#define ANALOG_CAL_VALUE_MAX_COUNT  142

//	float fData=(float)(m_dFcoef_a*iVal+m_dFcoef_b);
class CComtradeAnalogData : public CComtradeDataBase  
{
public:
	CComtradeAnalogData();
	virtual ~CComtradeAnalogData();

public:
	CString m_strUnit;			//5
	double m_dCoefValue;		//6	
	double m_dCoefValueBK;		//6	
	double m_dZeroValue;		//7
	double m_dZeroValueBK;		//7
	double m_dTimeSkew;			//8
	long m_nMin;				//9
	long m_nMax;				//10	  zhouhj  20201016 short ��Ϊlong  �����65535 �ڴ���ʾΪ-1
	double m_dPrimaryValue;		//11	
	double m_dSecondaryValue;	//12
	char    m_cPSType;				//13???
	CString m_strPSType;//13
	
	short m_nMinCal;				//9
	short m_nMaxCal;				//10	

//	CString m_strAlgDataFile;//��ͨ����Ӧ��data�ļ��е�ֵ

	double m_dBeginAng_SpecialSmpRate;//�������Ƶ���µĿ�ʼ����λ  ����һ���ܲ�1�����2����Ĳ���Ƶ�ʣ���Ҫ����ǰһ������Ƶ�������ǰ����Ƶ�ʿ�ʼ����λzhouhj 20201007
	                                 //���ڴ��ι��ϻطŵ���������и�Ϊ�������ʱ����öβ��ε���ʼ����Ǵ��ֲ���Ƶ�ʣ���Ҫ���ȼ������һ�������ʼ��λ
	BOOL m_bInPhase_SpecialSmpRate;//����һ���ܲ�2������������Ҫ���ǣ��Ƿ��뿪ʼ�����180��������Ϊtrue�����뿪ʼ��ͬ��λ���������180��

	virtual void GetChanInfor(CString* pstrParse,long nOffSet = 0);
	virtual void SaveChanInfo(CString& strInfor);
	virtual BOOL IsAnalogData()		{	return TRUE;	}
	virtual void InitBuffer_Circle(long nDataFileType,long nTotalPoints);//zhouhj 20210918 �����ݻط�,ѭ������ʱ���г�ʼ��
	double GetRange();
	void CalMinMaxValue(long nPoints);
	void AdjustZeroValue(long nPoints, double dCoefCal);
	void AdjustCoefValue(long nPoints, double dNewCoefCal);//zhouhj 20201216 �����µ�Coef,���¼���ǰnPoints�����ֵ
	void CalMinMaxValue2(long nPoints);
	double GetUnitRadio();//zhouhj��ȡmA��kA��mV��kV��ת��ΪV��A
	BOOL IsChU0();//�ж��Ƿ�Ϊ�����ѹͨ��
	BOOL IsChI0();//�ж��Ƿ�Ϊ�������ͨ��
	BOOL GetMaxMinValue(long nPtBeginIndex, long nPointNum, double &dMaxValue, double &dMinValue);//�ӿ�ʼ����ʼ,�ܼ�nPointNum������,��ȡ���е����ֵ����Сֵ
	void UpdateCoef_SpecialSmpRate(double dMaxValue);//���ڰ���ÿ�ܲ�1�����2��������ݶ���,��ֹ����Чֵת��Ϊ���ֵʱ,Խ��,������Ӧ��ϵ��ֵ

	//zhouhj 2023.9.11 ��ȡ��ǰͨ���ڵ�ѹ���ߵ���ͨ����ĵ���˳��,��1��ʼ���
	long GetChCurrVolIndex();

	long GetValues_Double(double *pdFftCalPoint,long nPointNum,long nBeginPos);//��ȡ��ǰͨ���е�����doubleֵ
	double GetUShortPointValueDouble(long nPointIndex);
	BOOL Copy_AddSlowlyRising(float fSmpRate,long nAddRisingPoints,long nAddStartSteadyPoints,CComtradeDataBase *pDstData,
		BOOL bDealStartCircle = FALSE);//������ǰͨ�������ݵ�pDstData������,����ӻ�����������,�ڻ����������κ�,��ӵ���̬����,���һ��������ʶ�Ƿ���ǰ���ο�ʼ�����ܲ��Ĳ�����̬����
	BOOL SetSteadySineWave(float fSmpRate,long nStartPointIndex,long nSetSteadyPoints);//�������е�ĳһ������Ϊ���Ҳ�,���Ҳ�����ʼ����λ�����Ҳ��ķ�ֵ,�����õ���ʼ���������ó�
	virtual long InsertBySampleRate(float* pdSrcSamRate,long* pnSrcDataPoints,long nSrcSamAmount, double dDstSmpRate,CComtradeDataBase *pDstData,const double &dDstBeginOffsetTime/* = 0*/);//zhouhj 20200914
	long InsertBySampleRate_DoubleBuff(CMemBuffer_Double &oDoubleBuff,float* pdSrcSamRate,long* pnSrcDataPoints,long nSrcSamAmount, double dDstSmpRate,const double &dDstBeginOffsetTime/* = 0*/);//zhouhj 20200914
	double GetCurPointAng(float* pdSrcSamRate,long* pnSrcDataPoints,long nSrcSamAmount,const double &dCurFreq,const long &nCurPointIndex);
	BOOL GetWaveCircleAmpAng(const long &nStartPointIndex,const double &dSmpRate,//��ȡ�����У�ĳ���ܲ��ķ�ֵ��λ,ֱ��ֵ
		const double &dCurFreq,double &dAmp,double &dAng ,double &dDC_Value);//����1Ϊ��ʼ�ܲ����,��0��ʼ���

	//zhouhj 2024.2.4 �������ڲ�����̬����
	void InsertNormalCyclePoints(double dVolValue,double dCurrentValue,double dSmpRate,double dFreq,
		long nInsertPoints,long nDataFileType);

public:
	virtual long InsertBySampleRate(const long &nSrcBeginPoint,const long &nSrcEndPoint ,long &nDstBeginPoint,
		double &dSrcBeginPointTime,const double &dSrcGap,const double &dDstGap,CComtradeDataBase *pDstData,const double &dDstBeginOffsetTime);//zhouhj 20200914
	virtual long InsertBySampleRate_SteadyState(const double &dBeginPointAng,const double &dCurFreq,const long &nSrcBeginPoint,const long &nSrcEndPoint ,long &nDstBeginPoint,
		double &dSrcBeginPointTime,const double &dSrcGap,const double &dDstGap,CComtradeDataBase *pDstData,const double &dDstBeginOffsetTime);//zhouhj 20200916
	virtual long InsertBySampleRate_Double(double **ppdDoubleBuff,const long &nSrcBeginPoint,const long &nSrcEndPoint ,long &nDstBeginPoint,
		double &dSrcBeginPointTime,const double &dSrcGap,const double &dDstGap,const double &dDstBeginOffsetTime);//zhouhj 20200914
	virtual long InsertBySampleRate_SteadyState_Double(double **ppdDoubleBuff,const double &dBeginPointAng,const double &dCurFreq,const long &nSrcBeginPoint,const long &nSrcEndPoint ,long &nDstBeginPoint,
		double &dSrcBeginPointTime,const double &dSrcGap,const double &dDstGap,const double &dDstBeginOffsetTime);//zhouhj 20200916

	long GetAttachBuffer_long(long nDataFileType,long nIndex);//zhouhj 20210918 ��ȡָ�����з�������Bufferֵ,�������ݵ��ֵ,����1Ϊ�ļ�����

public:
	virtual UINT GetClassID() {    return CMTRDCLASSID_ANALOG;   }

	//������ͨ����ʾ�����ĺ���
	virtual void GetCountBeforeBind(int*ipBind);
	virtual void GetCHIndexBeforeBind(int*ipVoltage,int*ipCurrent,BOOL bUse);
	//���ͨ���Ĳ����������Сֵ
	virtual void GetCHSampMaxMiVal(float &fMaxVal,float &fMinVal);

protected:
	float *m_ppfCalValue[ANALOG_CAL_VALUE_MAX_COUNT];   //ͨ������ֵ������

	void InitCalValueBuffer();
	void FreeCalValueBuffer();
	void FreeCalValueBuffer(long nIndex);

public:
	BOOL AllocCalValueBuffer(long nIndex, long nPoints);
	float* GetCalValueBuffer(long nIndex);
	//xupf
public:
//	virtual UINT GetClassID() {    return GLOBALCLASSID_CCOMTRADEANALOGDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CComtradeFileXmlRWKeys::CComtradeAnalogDataKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BOOL CopyOwn(CBaseObject* pDest);

public:
	//2021-1-18  lijunqing
	BOOL IsAnalogU();
	BOOL IsAnalogI();
	BOOL IsAnalogUData()	{	return IsAnalogU();	}
	BOOL IsAnalogIData()	{	return IsAnalogI();	}
	BOOL MatchType(const CString &strType);

	long GetCoefVal();

	void WriteAnalogDatas(const CString &strFileHeadName = _T(""));//zhouhj ��ӡͨ������

	//2021-2-19 lijunqing
	double CalValue(short vValue)
	{
		return vValue * m_dCoefValue + m_dZeroValue;
	}
	void CalValue(short vValue, double &dValue)
	{
		dValue = vValue * m_dCoefValue + m_dZeroValue;
	}
};

#endif // !defined(AFX_COMTRADEANALOGDATA_H__E0AA22A6_09FD_4AF5_A855_D7E0CFBEE215__INCLUDED_)

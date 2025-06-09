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
	long m_nMax;				//10	  zhouhj  20201016 short 改为long  会包含65535 在此显示为-1
	double m_dPrimaryValue;		//11	
	double m_dSecondaryValue;	//12
	char    m_cPSType;				//13???
	CString m_strPSType;//13
	
	short m_nMinCal;				//9
	short m_nMaxCal;				//10	

//	CString m_strAlgDataFile;//该通道对应的data文件中的值

	double m_dBeginAng_SpecialSmpRate;//特殊采样频率下的开始点相位  对于一个周波1个点或2个点的采样频率，需要根据前一个采样频率算出当前采样频率开始点相位zhouhj 20201007
	                                 //对于大波形故障回放的情况，被切割为多个波形时，如该段波形的起始点就是此种采样频率，需要事先计算出第一个点的起始相位
	BOOL m_bInPhase_SpecialSmpRate;//对于一个周波2个点的情况，需要考虑，是否与开始点相差180°的情况，为true代表与开始点同相位，否则相差180°

	virtual void GetChanInfor(CString* pstrParse,long nOffSet = 0);
	virtual void SaveChanInfo(CString& strInfor);
	virtual BOOL IsAnalogData()		{	return TRUE;	}
	virtual void InitBuffer_Circle(long nDataFileType,long nTotalPoints);//zhouhj 20210918 大数据回放,循环缓存时进行初始化
	double GetRange();
	void CalMinMaxValue(long nPoints);
	void AdjustZeroValue(long nPoints, double dCoefCal);
	void AdjustCoefValue(long nPoints, double dNewCoefCal);//zhouhj 20201216 根据新的Coef,重新计算前nPoints个点的值
	void CalMinMaxValue2(long nPoints);
	double GetUnitRadio();//zhouhj获取mA、kA、mV、kV都转换为V、A
	BOOL IsChU0();//判断是否为零序电压通道
	BOOL IsChI0();//判断是否为零序电流通道
	BOOL GetMaxMinValue(long nPtBeginIndex, long nPointNum, double &dMaxValue, double &dMinValue);//从开始点起始,总计nPointNum个点数,获取其中的最大值、最小值
	void UpdateCoef_SpecialSmpRate(double dMaxValue);//对于包含每周波1个点或2个点的数据对象,防止从有效值转换为最大值时,越限,调整对应的系数值

	//zhouhj 2023.9.11 获取当前通道在电压或者电流通道里的单独顺序,从1开始编号
	long GetChCurrVolIndex();

	long GetValues_Double(double *pdFftCalPoint,long nPointNum,long nBeginPos);//获取当前通道中的数据double值
	double GetUShortPointValueDouble(long nPointIndex);
	BOOL Copy_AddSlowlyRising(float fSmpRate,long nAddRisingPoints,long nAddStartSteadyPoints,CComtradeDataBase *pDstData,
		BOOL bDealStartCircle = FALSE);//拷贝当前通道的内容到pDstData数据中,并添加缓慢上升波形,在缓慢上升波形后,添加的稳态波形,最后一个参数标识是否处理当前波形开始几个周波的波形稳态波形
	BOOL SetSteadySineWave(float fSmpRate,long nStartPointIndex,long nSetSteadyPoints);//将波形中的某一段设置为正弦波,正弦波的起始点相位、正弦波的幅值,从设置的起始点往后计算得出
	virtual long InsertBySampleRate(float* pdSrcSamRate,long* pnSrcDataPoints,long nSrcSamAmount, double dDstSmpRate,CComtradeDataBase *pDstData,const double &dDstBeginOffsetTime/* = 0*/);//zhouhj 20200914
	long InsertBySampleRate_DoubleBuff(CMemBuffer_Double &oDoubleBuff,float* pdSrcSamRate,long* pnSrcDataPoints,long nSrcSamAmount, double dDstSmpRate,const double &dDstBeginOffsetTime/* = 0*/);//zhouhj 20200914
	double GetCurPointAng(float* pdSrcSamRate,long* pnSrcDataPoints,long nSrcSamAmount,const double &dCurFreq,const long &nCurPointIndex);
	BOOL GetWaveCircleAmpAng(const long &nStartPointIndex,const double &dSmpRate,//获取波形中，某个周波的幅值相位,直流值
		const double &dCurFreq,double &dAmp,double &dAng ,double &dDC_Value);//参数1为起始周波点号,从0开始编号

	//zhouhj 2024.2.4 增加用于插入稳态波形
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

	long GetAttachBuffer_long(long nDataFileType,long nIndex);//zhouhj 20210918 获取指定点有符号数据Buffer值,不是数据点的值,参数1为文件类型

public:
	virtual UINT GetClassID() {    return CMTRDCLASSID_ANALOG;   }

	//定义获得通道显示个数的函数
	virtual void GetCountBeforeBind(int*ipBind);
	virtual void GetCHIndexBeforeBind(int*ipVoltage,int*ipCurrent,BOOL bUse);
	//获得通道的采样的最大、最小值
	virtual void GetCHSampMaxMiVal(float &fMaxVal,float &fMinVal);

protected:
	float *m_ppfCalValue[ANALOG_CAL_VALUE_MAX_COUNT];   //通道计算值缓冲区

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

	void WriteAnalogDatas(const CString &strFileHeadName = _T(""));//zhouhj 打印通道数据

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

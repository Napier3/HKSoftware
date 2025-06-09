// ComtradeMngr.h: interface for the CComtradeMngr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMTRADEMNGR_H__FEA5281F_FBA6_408F_A8DA_A390A05F2F0A__INCLUDED_)
#define AFX_COMTRADEMNGR_H__FEA5281F_FBA6_408F_A8DA_A390A05F2F0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ComtradeAnalogData.h"
#include "ComtradeBinaryData.h"
// #include "../../../MODULE/BASECLASS/LinkList.h"
#include "../RecordGlobalDefine.h"

// typedef CTLinkListEx<CComtradeDataBase> CComtradeList;

// #define ANALOG_DRAW_MIN_HEIGHT  160
// #define BINARY_DRAW_HEIGHT          12

#include "ComtradeFileGlobal.h"

#define PARSE_PART_AMOUNT 13

#define CMTRD_RDF_READALL    0X000000F
#define CMTRD_RDF_CLEARBUFF  0X0000001
#define CMTRD_RDF_READCFG    0X0000002
#define CMTRD_RDF_READDATA   0X0000004

#define COMTRADE_DATAFILE_TYPE_ASCII                  0
#define COMTRADE_DATAFILE_TYPE_BINARY                 1


class CRcdComtradeFile  : public CExBaseList
{
public:
    CRcdComtradeFile(BOOL bCreateBuffer = true);
	virtual ~CRcdComtradeFile();

	CString m_strComtradeFile;
	CExBaseList* GetAnalogs()	{	return &m_listAnalog;	}
	CExBaseList* GetBinarys()	{	return &m_listBinary;	}
	CExBaseList* GetRates()	{	return &m_listRates;	}
//	CComtradeAnalogData* GetAnalogData(long nCh_Index, const CString &strUnit);//根据Index获取电压、电流通道  index从1开始编号，电压、电流独立编号
	CComtradeAnalogData* GetAnalogDataByChIndex(long nCh_Index,BOOL bTypeU);
	CComtradeAnalogData* GetAnalogDataByChIndex(long nCh_Index);
	CComtradeAnalogData* GetAnalogDataByIndex(long nIndex);
	CComtradeAnalogData* FindAnalogDataByChID(const CString &strID);
	CComtradeAnalogData* FindAnalogDataByChType(const CString &strChType, long nIndex=-1); //2021-2-18  liunqing

	//2024-2-28 wuxinyi 
	CComtradeBinaryData* GetBinaryDataByIndex(long nIndex);
	CComtradeBinaryData *FindBinaryDataByChID(const CString &strID);

	long GetUCount();
	long GetICount();
	long GetChCount(const CString &strUnit);
	long GetUOrder();
	long GetIOrder();
	long GetChOrder(const CString &strUnit);
	long GetCurrPosByTime(double dTime);

protected:
	CExBaseList m_listAnalog;
	CExBaseList m_listBinary;
	CExBaseList m_listRates;

public:
	//选择起始点结束点相对时间以及插入点位置,插入循环数据波形
	BOOL InsertCyclePointsByRelTime(double dBeginTime, double dEndTime, double dInsertTime, int nCycleIndex);
	//选择起始点结束点相对时间以及插入点位置,插入循环数据波形
	BOOL InsertCyclePointsByPoint( long nBeginPoint, long nEndPoint, long nInserPoint, int nCycleIndex );
	//根据起始点结束点相对时间删除点
	BOOL DeletePointsByRelTime(double dBeginTime, double dEndTime);
	//在波形起始位置增加常态输出电压电流值[参数1:电压值,参数2:电流值,参数3:持续的时间(单位:s)]
	BOOL InsertNormalCyclePoints(double dVolValue,double dCurrentValue,double dTime_Second);

public:
	//关键字
	static const char* g_pszKeyBinary;
	static const char* g_pszKeyASCII;
	static const char* g_pszKeyCfg;
	static const char* g_pszKeyDat;

	CString m_strBasicInfo;//CFG文件的第一行信息，包含站名，站号和Comtrade版本
	float* m_pdSamRate; //不同的采样率
	long* m_pnDataPoints;//不同采样率下的采样点数
	RTTIME m_oTrigPointTime	;//启动时间
	RTTIME m_oFirstPointTime;//保存数据的第一个点的时间	
	//缓存位置索引
	long m_nBufBeginPos1;
	long m_nBufBeginPos2;
	long m_nBufLength1;
	long m_nBufLength2;
	long m_nBufferLen;
	long m_nTotalPoints;
// 	CComtradeList m_listChild;//管理通道,模拟和开关
	COMTRADEFILE m_oComtradeFile;

	//基本参数
public:
	//Comtrade版本类型
	long m_nComtradeVersion;//Comtrade版本值，如1991，1999等
	//站名和记录设备标识
	CString m_strStationName;
//	long m_nRecordingDeviceID;
	CString m_strRecordingDeviceID;
	long m_nAllChs;//所有通道数，模拟+状态
	long m_nAnalogs;//模拟通道数量
	long m_nBinarys;//状态通道数量
	double m_dFreq;//频率
	long m_nSamAmount;//采样率的数量
	CString m_strTrigPointTime;
	CString m_strFirstPointTime;
	double m_dTimeCoef	;
	long m_nDataFileType;//文件版本类型 0- ASCII , 1 - BIANRY

public:
	void Init();
	long ReadComtradeFile(const CString& strFilePath, UINT nReadMask = CMTRD_RDF_READALL);
	BOOL ReadCFGFile(const CString& strFilePath);//zhouhj 单独读取CFG文件,将其开放为public
	void SaveComtradeFile(const CString& strFilePath);
	void SaveDatFile(const CString& strFilePath);
	long GetTotalPoints();	//得到总的点数
	long GetChannelBuffferCount();
	double CalCyclesBeforeStart();
	double GetSampleRate(long nIndex=0);
	double CalComtradeFileSumTime();//zhouhj 20200914 获取不同采样率下,整个录波的总时间 （单位s） 
	long GetBinarySinglePointLength();//zhouhj 20200921 获取在Binary模式下，所有通道单个点在data文件中占用的字节长度

	void SetInPhase_SpecialSmpRate(BOOL bInPhase_SpecialSmpRate);//对于一个周波2个点的情况，需要考虑，是否与开始点相差180°的情况，为true代表与开始点同相位，否则相差180°
	void InitBeginAng_SpecialSmpRate(long nPointIndex,double dOffsetTime,double dFreq);

	DWORD GetCurPointTimeStamp(long nPointIndex);
	void UpdateAllChsTotalPointsNum();

	//20234-01-19 wuxinyi 更新采样信息
	long FindPointIndexByRelTime( double dTime ,double *pdTime ,long nSamAmount);
	void UpdateSamDateAfterDelete(int nBeginPos, int nEndPos);
	void UpdateSamDateAfterInsert(int nBeginPos, int nEndPos, int nInsertPos, int nCycNum);
	int FindPointIndexByDataPoints(int nPos, long *pdDataPoints, int &nDistance);//通过传入的点数，在m_pnDataPoints中找到位置,并返回当前与当前段数起点的距离

	//write
	void DeleteAllSmpRates();
	void SetSamAmount(long nSamAmount);
	void SetSamValue(long nSamIndex, long nDataPoints, float fSampleRate);
	void SetSamPoints(long nSamIndex, long nDataPoints);
	void SetSamReate(long nSamIndex, float fSampleRate);

	void BufferClear();//释放缓存
	void SetCreateBuffer(BOOL bCreate)	{m_bCreateBuffer = bCreate;}
	void ResetDataBuffer();//数据清0重新初始化
	void UpdateSmpRatesList();
	void ReadDataAsASIIMode(char *pString, long nIndex);

	void GetSmpRateString(CString &strSmpRateString);

	//2024-11-18 wuxinyi 新增接口
	void SaveAsciiDatDataFile(const CString& strFilePath);//保存ascii码时计算前通道数据
	void SaveBinaryDatDataFile(const CString& strFilePath);//保存Binary码时计算前通道数据

protected:
	//具体的设置
	void ClearDataBuffer();	
	void SetSaveGap(int nGap)	{	m_nSaveGap = nGap;	}
	int	 GetSaveGap()			{	return m_nSaveGap;	}
	void SaveCFGFile(const CString& strFilePath);
	void SaveMrttFile(const CString& strFilePath);//保存Mrtt文件暂时为空，确保录波文件的完整性
	void SaveDataAsBINARYMode(const CString& strFilePath);
	void SaveDataAsASIIMode(const CString& strFilePath);

	void ReadCfg_SampRate(char *pString, float &fRampRate, long &nTotalPoints);	
	long ReadDataFile(const CString& strFilePath);
	long ReadDataAsBINARYMode(const CString& strFilePath);
	long ReadDataAsASIIMode(const CString& strFilePath);

	void ReadDataAsBINARYMode(unsigned short* pnBuffer, long nIndex);

	//获得保存文件数据的范围
	void GetSaveTimeRange(long nBeginPos1,long nLen1,long nBeginPos2,long nLen2);
	long CalDataPoints(const CString &strPath);
	BOOL ValidTotalPoints(const CString &strCfgFilePath);//zhouhj 20211106 在读取完Cfg文件后

	//wuxinyi 2024.1.19 更新采样率数量
	void UpdateSampleRaes(long nSamAmount,const double* pdSamRate,const long* pnDataPoints);

private:
	
	int m_nSaveGap;	//实际采样率和保存采样率的比值
	void GetChannelAmount();
	//void CalMinMaxValue();
	void ParseString(const CString& strIn, CString* pstrOut);
	void ParseString(const CString& strIn, CStringArray &straOut);
	void ParseString_Char(char *pString, CStringArray &straOut);//zhouhj 20211105 Qt下解析ASCII数据时会报错,修改解析方法
	unsigned short CtringToUShort(const CString &strValue);
	long GetDataFilePoints(const CString &strDataFilePath);
	void SetDataFileTypeByString(char *sString);

 	BOOL m_bCreateBuffer;

public:
	void CalMinMaxValue();//2021-9-20  lijunqing
	void ResetCoefZeroValue();//20230519 zhouhj  恢复模拟量通道系数及零值
	void UpdateCoef_SpecialSmpRate();//对于包含每周波1个点或2个点的数据对象,防止从有效值转换为最大值时,越限,调整对应的系数值

//创建Comtrade文件
public:
	CRcdComtradeFile* CloneComtradeWithSingleSmpRate(double dSmpRate ,const double &dDstBeginOffsetTime = 0);//通过插值算法，按固定采样率，生成新的ComtrdeFile
	CRcdComtradeFile* CloneComtrade_AddSlowlyRising(double dSecondTime = 5,long nAddCircleStartNum = 0,long nAddCircleEndNum = 0);//在第一段波形前，添加一个缓慢上升的波形,参数2为缓慢上升的时间
	long CalTotalPoints_InsertWithSingleSmpRate(double dSmpRate ,const double &dDstBeginOffsetTime = 0);//计算按固定采样率插值，生成的插值后总点数
	void InitAnalogChsIncreaseValue(long nMaxValue);//zhouhj将录波文件中所有通道的值从1开始递增，递增的最大值为参数设定值
	void CreateComtradeFile(long nAnalogChs, long nBinaryChs, long nTotalPoints);
	BOOL SetAnalogAttr(long nAnalog, const CString &strName, const CString &strChID, const CString &strUnit
		, float fZero, float fCoef, float fPrimary, float fSecondary
		, unsigned short** ppnAttachBuffer);
	BOOL SetAnalogData(long nAnalog, const CString &strName, const CString &strChID, const CString &strUnit
		, float fZero, float fCoef, float fPrimary, float fSecondary
		, double *pdBuffer);

	void InitAfterCreate(float fFreq, long nSampRate, long nTotolPoints);
	void BigComtrade_InitChsAllocBufferNext();//zhouhj  初始化下一段读取前各通道的大小，特别是将前一段的最后一个点移到下一段的第一个点, 用于BigComtrade模式
	//xupf 增加xml读写
public:
	virtual UINT GetClassID() {    return GLOBALCLASSID_CRCDCOMTRADEFILE;   }
	virtual BSTR GetXmlElementKey()  {      return CComtradeFileXmlRWKeys::CRcdComtradeFileKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual BOOL CopyOwn(CBaseObject* pDest);

	//xxy20200908
public:
//	double CalComtradeFileSumTime();
	void CalUIMax(double &fUMax,double &fIMax);

//2021-2-17  lijunqing  同一个文件被多个地方访问、释放，避免删除导致其他的引用异常
public:
	void AddRef();
	void Release();
	long GetRefCount()	{	return m_nRefCount;		}

protected:
	long m_nRefCount; //被引用的次数
};


class CRcdComtradeFileMngr : CExBaseList
{
private:
	CRcdComtradeFileMngr();
	virtual ~CRcdComtradeFileMngr();

public:
	static long g_nComtradeMngrRef;
	static CRcdComtradeFileMngr *g_pCComtradeMngr;
	static const CString g_strComtradeFileFilter;

public:
	//静态对象
	static CRcdComtradeFileMngr* Create();
	static void Release();
	static BOOL PopOpenComtradeFile(CString &strFile);
	static CRcdComtradeFile* NewComtradeFile();
	static void AddNewComtradeFileChild(CRcdComtradeFile *pChild);
	static CRcdComtradeFile* OpenComtradeFile();
	static CRcdComtradeFile* OpenComtradeFile(const CString &strFile);
	static CRcdComtradeFile* FindComtradeFile(const CString &strFile);
	static CRcdComtradeFile* GetComtradeFile(long nIndex);
	static BOOL CloseComtradeFile(const CString &strFile);
	static BOOL CloseComtradeFile(CRcdComtradeFile *pComtradeFile);
	static long GetComtradeFileCount();
	//xupf
	void SaveThisXml(CString &strPath);
	CExBaseObject *FindByPath(CString strPath);
};

#endif // !defined(AFX_COMTRADEMNGR_H__FEA5281F_FBA6_408F_A8DA_A390A05F2F0A__INCLUDED_)

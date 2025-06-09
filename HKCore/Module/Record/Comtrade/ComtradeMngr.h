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
//	CComtradeAnalogData* GetAnalogData(long nCh_Index, const CString &strUnit);//����Index��ȡ��ѹ������ͨ��  index��1��ʼ��ţ���ѹ�������������
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
	//ѡ����ʼ����������ʱ���Լ������λ��,����ѭ�����ݲ���
	BOOL InsertCyclePointsByRelTime(double dBeginTime, double dEndTime, double dInsertTime, int nCycleIndex);
	//ѡ����ʼ����������ʱ���Լ������λ��,����ѭ�����ݲ���
	BOOL InsertCyclePointsByPoint( long nBeginPoint, long nEndPoint, long nInserPoint, int nCycleIndex );
	//������ʼ����������ʱ��ɾ����
	BOOL DeletePointsByRelTime(double dBeginTime, double dEndTime);
	//�ڲ�����ʼλ�����ӳ�̬�����ѹ����ֵ[����1:��ѹֵ,����2:����ֵ,����3:������ʱ��(��λ:s)]
	BOOL InsertNormalCyclePoints(double dVolValue,double dCurrentValue,double dTime_Second);

public:
	//�ؼ���
	static const char* g_pszKeyBinary;
	static const char* g_pszKeyASCII;
	static const char* g_pszKeyCfg;
	static const char* g_pszKeyDat;

	CString m_strBasicInfo;//CFG�ļ��ĵ�һ����Ϣ������վ����վ�ź�Comtrade�汾
	float* m_pdSamRate; //��ͬ�Ĳ�����
	long* m_pnDataPoints;//��ͬ�������µĲ�������
	RTTIME m_oTrigPointTime	;//����ʱ��
	RTTIME m_oFirstPointTime;//�������ݵĵ�һ�����ʱ��	
	//����λ������
	long m_nBufBeginPos1;
	long m_nBufBeginPos2;
	long m_nBufLength1;
	long m_nBufLength2;
	long m_nBufferLen;
	long m_nTotalPoints;
// 	CComtradeList m_listChild;//����ͨ��,ģ��Ϳ���
	COMTRADEFILE m_oComtradeFile;

	//��������
public:
	//Comtrade�汾����
	long m_nComtradeVersion;//Comtrade�汾ֵ����1991��1999��
	//վ���ͼ�¼�豸��ʶ
	CString m_strStationName;
//	long m_nRecordingDeviceID;
	CString m_strRecordingDeviceID;
	long m_nAllChs;//����ͨ������ģ��+״̬
	long m_nAnalogs;//ģ��ͨ������
	long m_nBinarys;//״̬ͨ������
	double m_dFreq;//Ƶ��
	long m_nSamAmount;//�����ʵ�����
	CString m_strTrigPointTime;
	CString m_strFirstPointTime;
	double m_dTimeCoef	;
	long m_nDataFileType;//�ļ��汾���� 0- ASCII , 1 - BIANRY

public:
	void Init();
	long ReadComtradeFile(const CString& strFilePath, UINT nReadMask = CMTRD_RDF_READALL);
	BOOL ReadCFGFile(const CString& strFilePath);//zhouhj ������ȡCFG�ļ�,���俪��Ϊpublic
	void SaveComtradeFile(const CString& strFilePath);
	void SaveDatFile(const CString& strFilePath);
	long GetTotalPoints();	//�õ��ܵĵ���
	long GetChannelBuffferCount();
	double CalCyclesBeforeStart();
	double GetSampleRate(long nIndex=0);
	double CalComtradeFileSumTime();//zhouhj 20200914 ��ȡ��ͬ��������,����¼������ʱ�� ����λs�� 
	long GetBinarySinglePointLength();//zhouhj 20200921 ��ȡ��Binaryģʽ�£�����ͨ����������data�ļ���ռ�õ��ֽڳ���

	void SetInPhase_SpecialSmpRate(BOOL bInPhase_SpecialSmpRate);//����һ���ܲ�2������������Ҫ���ǣ��Ƿ��뿪ʼ�����180��������Ϊtrue�����뿪ʼ��ͬ��λ���������180��
	void InitBeginAng_SpecialSmpRate(long nPointIndex,double dOffsetTime,double dFreq);

	DWORD GetCurPointTimeStamp(long nPointIndex);
	void UpdateAllChsTotalPointsNum();

	//20234-01-19 wuxinyi ���²�����Ϣ
	long FindPointIndexByRelTime( double dTime ,double *pdTime ,long nSamAmount);
	void UpdateSamDateAfterDelete(int nBeginPos, int nEndPos);
	void UpdateSamDateAfterInsert(int nBeginPos, int nEndPos, int nInsertPos, int nCycNum);
	int FindPointIndexByDataPoints(int nPos, long *pdDataPoints, int &nDistance);//ͨ������ĵ�������m_pnDataPoints���ҵ�λ��,�����ص�ǰ�뵱ǰ�������ľ���

	//write
	void DeleteAllSmpRates();
	void SetSamAmount(long nSamAmount);
	void SetSamValue(long nSamIndex, long nDataPoints, float fSampleRate);
	void SetSamPoints(long nSamIndex, long nDataPoints);
	void SetSamReate(long nSamIndex, float fSampleRate);

	void BufferClear();//�ͷŻ���
	void SetCreateBuffer(BOOL bCreate)	{m_bCreateBuffer = bCreate;}
	void ResetDataBuffer();//������0���³�ʼ��
	void UpdateSmpRatesList();
	void ReadDataAsASIIMode(char *pString, long nIndex);

	void GetSmpRateString(CString &strSmpRateString);

	//2024-11-18 wuxinyi �����ӿ�
	void SaveAsciiDatDataFile(const CString& strFilePath);//����ascii��ʱ����ǰͨ������
	void SaveBinaryDatDataFile(const CString& strFilePath);//����Binary��ʱ����ǰͨ������

protected:
	//���������
	void ClearDataBuffer();	
	void SetSaveGap(int nGap)	{	m_nSaveGap = nGap;	}
	int	 GetSaveGap()			{	return m_nSaveGap;	}
	void SaveCFGFile(const CString& strFilePath);
	void SaveMrttFile(const CString& strFilePath);//����Mrtt�ļ���ʱΪ�գ�ȷ��¼���ļ���������
	void SaveDataAsBINARYMode(const CString& strFilePath);
	void SaveDataAsASIIMode(const CString& strFilePath);

	void ReadCfg_SampRate(char *pString, float &fRampRate, long &nTotalPoints);	
	long ReadDataFile(const CString& strFilePath);
	long ReadDataAsBINARYMode(const CString& strFilePath);
	long ReadDataAsASIIMode(const CString& strFilePath);

	void ReadDataAsBINARYMode(unsigned short* pnBuffer, long nIndex);

	//��ñ����ļ����ݵķ�Χ
	void GetSaveTimeRange(long nBeginPos1,long nLen1,long nBeginPos2,long nLen2);
	long CalDataPoints(const CString &strPath);
	BOOL ValidTotalPoints(const CString &strCfgFilePath);//zhouhj 20211106 �ڶ�ȡ��Cfg�ļ���

	//wuxinyi 2024.1.19 ���²���������
	void UpdateSampleRaes(long nSamAmount,const double* pdSamRate,const long* pnDataPoints);

private:
	
	int m_nSaveGap;	//ʵ�ʲ����ʺͱ�������ʵı�ֵ
	void GetChannelAmount();
	//void CalMinMaxValue();
	void ParseString(const CString& strIn, CString* pstrOut);
	void ParseString(const CString& strIn, CStringArray &straOut);
	void ParseString_Char(char *pString, CStringArray &straOut);//zhouhj 20211105 Qt�½���ASCII����ʱ�ᱨ��,�޸Ľ�������
	unsigned short CtringToUShort(const CString &strValue);
	long GetDataFilePoints(const CString &strDataFilePath);
	void SetDataFileTypeByString(char *sString);

 	BOOL m_bCreateBuffer;

public:
	void CalMinMaxValue();//2021-9-20  lijunqing
	void ResetCoefZeroValue();//20230519 zhouhj  �ָ�ģ����ͨ��ϵ������ֵ
	void UpdateCoef_SpecialSmpRate();//���ڰ���ÿ�ܲ�1�����2��������ݶ���,��ֹ����Чֵת��Ϊ���ֵʱ,Խ��,������Ӧ��ϵ��ֵ

//����Comtrade�ļ�
public:
	CRcdComtradeFile* CloneComtradeWithSingleSmpRate(double dSmpRate ,const double &dDstBeginOffsetTime = 0);//ͨ����ֵ�㷨�����̶������ʣ������µ�ComtrdeFile
	CRcdComtradeFile* CloneComtrade_AddSlowlyRising(double dSecondTime = 5,long nAddCircleStartNum = 0,long nAddCircleEndNum = 0);//�ڵ�һ�β���ǰ�����һ�����������Ĳ���,����2Ϊ����������ʱ��
	long CalTotalPoints_InsertWithSingleSmpRate(double dSmpRate ,const double &dDstBeginOffsetTime = 0);//���㰴�̶������ʲ�ֵ�����ɵĲ�ֵ���ܵ���
	void InitAnalogChsIncreaseValue(long nMaxValue);//zhouhj��¼���ļ�������ͨ����ֵ��1��ʼ���������������ֵΪ�����趨ֵ
	void CreateComtradeFile(long nAnalogChs, long nBinaryChs, long nTotalPoints);
	BOOL SetAnalogAttr(long nAnalog, const CString &strName, const CString &strChID, const CString &strUnit
		, float fZero, float fCoef, float fPrimary, float fSecondary
		, unsigned short** ppnAttachBuffer);
	BOOL SetAnalogData(long nAnalog, const CString &strName, const CString &strChID, const CString &strUnit
		, float fZero, float fCoef, float fPrimary, float fSecondary
		, double *pdBuffer);

	void InitAfterCreate(float fFreq, long nSampRate, long nTotolPoints);
	void BigComtrade_InitChsAllocBufferNext();//zhouhj  ��ʼ����һ�ζ�ȡǰ��ͨ���Ĵ�С���ر��ǽ�ǰһ�ε����һ�����Ƶ���һ�εĵ�һ����, ����BigComtradeģʽ
	//xupf ����xml��д
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

//2021-2-17  lijunqing  ͬһ���ļ�������ط����ʡ��ͷţ�����ɾ�����������������쳣
public:
	void AddRef();
	void Release();
	long GetRefCount()	{	return m_nRefCount;		}

protected:
	long m_nRefCount; //�����õĴ���
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
	//��̬����
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

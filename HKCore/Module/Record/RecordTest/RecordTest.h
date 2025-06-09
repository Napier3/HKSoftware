// RecordTest.h: interface for the CRecordTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECORDTEST_H__1527A7D0_AC6C_4264_8C0B_76CD4699FA26__INCLUDED_)
#define AFX_RECORDTEST_H__1527A7D0_AC6C_4264_8C0B_76CD4699FA26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RtStartup.h"
#include "RtBufferConfig.h"
#include "RtVariables.h"
#include "RtFileWrite.h"
#include "RtSpy.h"
#include "RtAttrSpyConfigs.h"
#include "../RtMemBuffer/RtMemBufferMngr.h"
#include "SystemSetsConfig.h"
#include "../RecordSysMsgDef.h"

#define RecordTest_Mode_NoneWithOnlineRecord	 0
#define RecordTest_Mode_TestUseOnlineRecord		 1
#define RecordTest_Mode_CommonOnlineRecord		 2
#define RecordTest_Mode_OscillographOnlineRecord 3

class CRecordTest : public CExBaseList  
{
public:
	CRecordTest();
	virtual ~CRecordTest();

	//系统用到的修正系数
	double  g_pZeroValue[MAX_MR1200_CHANNELS];
	double g_pCoefValue[MAX_MR1200_CHANNELS];

	unsigned short g_nSampleGap;
	DWORD g_nSampleRate;

	long Analyse_Cal_Length;// = 2000;

	long USE_RT_FILTER_BUFFER_LEN;// =  81;
	long RT_FILTER_DATA_LEN_PREV;// = 40;
	long RT_FILTER_DATA_LEN_NEXT;// = 40;
	long RTATTRIBUTECAL_MIN_BUFFER_LEN;//   =    (7000+RT_FILTER_BUFFER_LEN); //20000
	long MR1200_DFT_CAL_LEN;
	long MR1200_SAMPLE_RATE;  //2020-06-22

	RECORD_CAL_LEN_PARA m_oRECORD_CAL_LEN_PARA;

	MR1200SYSANALYSEMNGR m_oMR1200SysAnalyseMngr;

	//2020-06-12  lijunqing  是否逐点计算
	BOOL m_bCalPointByPoint;

public:
	void Get_RECORD_CAL_LEN_PARA(RECORD_CAL_LEN_PARA *pCalLenPara);
	void init_RTATTRIBUTECAL_MIN_BUFFER_LEN();
	void init_RTATTRIBUTECAL_MIN_BUFFER_LEN(long nSamRate);
	long FindCoefAndZero(CExBaseObject *pRtVariable, double &dCoef, double &dZero);
	long FindCoefAndZero(CExBaseObject *pRtVariable, double **ppdCoef, double **ppdZero);

	BOOL CalCurrValuesFromPos(long nBeginPos);
	void CalValues_PeakVellay(long nBeginPos, long nUseLength);

	void SetCalPointByPoint(BOOL b = TRUE)	{	m_bCalPointByPoint = b;	}
	void InitAttrsBuffer(long nPoints)	{	m_pVariables->InitAttrsBuffer(nPoints);	}
	void SetAttrUse(UINT nAttrID, long nUse)	{	m_pVariables->SetAttrUse(nAttrID, nUse);	}

//属性
public:
	//关键字属性
// 	static const char *g_pszKeyRecordTest;
// 	static const char *g_pszKeyUI;
// 	static const char *g_pszKeyUseGps;
// 	static const char *g_pszKeyType;
// 	static const char *g_pszKeyTypeConfig;
// 	static const char *g_pszKeyTypeAuto;
// 	static const char *g_pszKeyOnlineRecordMode;
// 	static const char *g_pszKeySets;
// 	static const char *g_pszKeyRTOnline;
// 	static const char *g_pszKeyRTOscillograph;

	//自身属性
	CString m_strUI;//试验对应的功能配置文件
	long    m_nUseGps;
	CString m_strType;//Config/Auto
	long m_nOnlineRecordMode;//0表示没有在线录波，1表示试验用在线录波，2表示通用在线录波, 3表示示波试验的在线录波
	BOOL m_bTestUseOnlineRecord;//试验在线录波模式下，在线录波是否使用

	//子对象
	CRtVariables		*m_pVariables;        //变量定义
	CRtStartup			*m_pStartup;          //启动设置
	CRtBufferConfig		*m_pMemBuffer;        //内存配置
	CRtFileWrite		*m_pRtFileWrite;      //数据文件写模式配置
	CRtSpy				*m_pSpy;              //监视配置
	CRtMemBufferMngr	m_oRtMemBufferMngr;  //分配的内存管理对象
	CRtAttrSpyConfigs	*m_pRtAttrSpyConfigs; //属性监视管理对象
	//外部关联的数据缓冲区
	CRtMemBufferChannel *m_pGpsBuffer;
	
	CRecordTest* m_pClone; //克隆的RecordTest,在保持的时候使用
	CExBaseObject *m_pWaveAnalyseViewRef;
//方法
public:
	//重载的方法
	virtual UINT GetClassID(){		return RTCLASSID_RECORDTEST;	}
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild()					{    return NULL;	}
// 	virtual CExBaseObject* CreateNewChild(long nClassID)   	{    return NULL;	}
// 	virtual const char* GetXmlElementKey();
// 	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);

	//定值读写
// 	BOOL ReadSetsValueXml(MSXML::IXMLDOMNodeListPtr &oNodes);
// 	BOOL WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);

	//用于脚本的函数
	void CalValues();
	void CalValuesEx();  //每个通道都独立计算
	BOOL IsRecordFinished()                                          {     return m_pStartup->IsRecordFinished();                 }

	//根据ID查找属性，返回属性值的地址或定值的地址，详细参见CRtDataAttribute::GetValueRefByID(const CString &strID)
	virtual double* GetValueRefByID(const CString &strID)            {     return m_pVariables->GetValueRefByID(strID);           }
	virtual double* GetAttrValueRefByID(const CString &strID)        {     return m_pVariables->GetAttrValueRefByID(strID);       }
	virtual double* GetMutationValueRefByID(const CString &strID)    {     return m_pVariables->GetMutationValueRefByID(strID);   }
	
	//与文件相关的方法
// 	BOOL ReadRecordTestFromFile(const CString &strFile);
// 	BOOL ReadRecordTestFromFile();
// 	BOOL WriteRecordTestToFile(const CString &strFile);
// 	BOOL WriteRecordTestToFile();

	//初始化各数据属性对象数值计算参数,构建定值判启动表达式
	void InitDataAttributeCalFunc(BOOL bCalUseRecordBuffer);
	
	//获取SpyBuffer==>>RecordBuffer的取数间隔
	long GetRecordGap()   {    return m_pMemBuffer->GetRecordGap();   }

	//是否是自适应
	BOOL IsRecordTestAutofit();

	//自适应创建MultiVariable
	void AutofitCreateMultiVariable();

	//自适应创建file-write
	void AutofitCreateFileWrite();

	//是否使用在线录波的判断
	BOOL IsNoneWithOnlineRecord()   {	return (m_nOnlineRecordMode == RecordTest_Mode_NoneWithOnlineRecord);	}
	BOOL IsTestUseOnlineRecord()		{	return ((m_nOnlineRecordMode == RecordTest_Mode_TestUseOnlineRecord) && (m_bTestUseOnlineRecord == TRUE));	}
	BOOL IsCommonOnlineRecord()		{	return (m_nOnlineRecordMode == RecordTest_Mode_CommonOnlineRecord);	}
	
	//判断示波功能使用在线录波
	BOOL IsOscillographOnlineRecord() {		return (m_nOnlineRecordMode == RecordTest_Mode_OscillographOnlineRecord);		}

	void SetTestUseOnlineRecord(BOOL bTestUseOnlineRecord)	{	m_bTestUseOnlineRecord = bTestUseOnlineRecord;	}
	//是否是校准试验
	BOOL IsRtAdjust()
	{
		BOOL bTrue = FALSE;

		if (_stricmp(m_strID.GetString() , "RtAdjust") == 0)
		{
			bTrue = TRUE;
		}
		else
		{
		}

		return bTrue;
	}

	//调整RefVariable
	void AdjustRefVariable()	
	{
		if (IsRecordTestAutofit())
		{
			m_pVariables->AdjustRefVariable(m_oMR1200SysAnalyseMngr);	
		}
	}	

	//是否是在线录波试验
// 	BOOL IsRTOnline()		{	return(_stricmp(m_strID, g_pszKeyRTOnline) == 0);	}
// 	
// 	//是否是示波试验
// 	BOOL IsRTOscillograph()	{	return(_stricmp(m_strID, g_pszKeyRTOscillograph) == 0);	}

	void ValidateAttrCal();

	//克隆RecordTest
	void CloneRecordTest(CMemBuffer_UShort** pAttachBuffer, BOOL bCalUseRecordBuffer);
	void CloneRecordTest(CRecordTest* pSrc,CMemBuffer_UShort** pAttachBuffer, BOOL bCalUseRecordBuffer);

	//恢复默认定值设置
	void ResetSets(CSystemSetsConfig* pSetsConfig);
	void ResetSets(CRtSingleVariable* pVariable,CSystemSetsConfig* pSetsConfig);
	void ResetSets(CRtBinaryVariable* pVariable,CSystemSetsConfig* pSetsConfig);
	void ResetSets(CRtComplexVariable* pVariable,CSystemSetsConfig* pSetsConfig);
	void ResetSets(CRtMultiVariable* pVariable,CSystemSetsConfig* pSetsConfig);
 
	void ResetAnalogAttrsSets(CRtDataAttributes* pAttrs,double dRange,CSystemSetsConfig* pSetsConfig);
	void ResetAnalogAttrSets(CRtDataAttribute* pAttr,double dRange,CSystemSetAttr* pConfig);

public:
	//lijq 2020-4-21
	void InitDrawControl();
	void InitBufferMngr();

public:
//初始化故障计算
	void ResetValueCal();
};


#endif // !defined(AFX_RECORDTEST_H__1527A7D0_AC6C_4264_8C0B_76CD4699FA26__INCLUDED_)

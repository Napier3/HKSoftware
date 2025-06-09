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

	//ϵͳ�õ�������ϵ��
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

	//2020-06-12  lijunqing  �Ƿ�������
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

//����
public:
	//�ؼ�������
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

	//��������
	CString m_strUI;//�����Ӧ�Ĺ��������ļ�
	long    m_nUseGps;
	CString m_strType;//Config/Auto
	long m_nOnlineRecordMode;//0��ʾû������¼����1��ʾ����������¼����2��ʾͨ������¼��, 3��ʾʾ�����������¼��
	BOOL m_bTestUseOnlineRecord;//��������¼��ģʽ�£�����¼���Ƿ�ʹ��

	//�Ӷ���
	CRtVariables		*m_pVariables;        //��������
	CRtStartup			*m_pStartup;          //��������
	CRtBufferConfig		*m_pMemBuffer;        //�ڴ�����
	CRtFileWrite		*m_pRtFileWrite;      //�����ļ�дģʽ����
	CRtSpy				*m_pSpy;              //��������
	CRtMemBufferMngr	m_oRtMemBufferMngr;  //������ڴ�������
	CRtAttrSpyConfigs	*m_pRtAttrSpyConfigs; //���Լ��ӹ������
	//�ⲿ���������ݻ�����
	CRtMemBufferChannel *m_pGpsBuffer;
	
	CRecordTest* m_pClone; //��¡��RecordTest,�ڱ��ֵ�ʱ��ʹ��
	CExBaseObject *m_pWaveAnalyseViewRef;
//����
public:
	//���صķ���
	virtual UINT GetClassID(){		return RTCLASSID_RECORDTEST;	}
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild()					{    return NULL;	}
// 	virtual CExBaseObject* CreateNewChild(long nClassID)   	{    return NULL;	}
// 	virtual const char* GetXmlElementKey();
// 	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);

	//��ֵ��д
// 	BOOL ReadSetsValueXml(MSXML::IXMLDOMNodeListPtr &oNodes);
// 	BOOL WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);

	//���ڽű��ĺ���
	void CalValues();
	void CalValuesEx();  //ÿ��ͨ������������
	BOOL IsRecordFinished()                                          {     return m_pStartup->IsRecordFinished();                 }

	//����ID�������ԣ���������ֵ�ĵ�ַ��ֵ�ĵ�ַ����ϸ�μ�CRtDataAttribute::GetValueRefByID(const CString &strID)
	virtual double* GetValueRefByID(const CString &strID)            {     return m_pVariables->GetValueRefByID(strID);           }
	virtual double* GetAttrValueRefByID(const CString &strID)        {     return m_pVariables->GetAttrValueRefByID(strID);       }
	virtual double* GetMutationValueRefByID(const CString &strID)    {     return m_pVariables->GetMutationValueRefByID(strID);   }
	
	//���ļ���صķ���
// 	BOOL ReadRecordTestFromFile(const CString &strFile);
// 	BOOL ReadRecordTestFromFile();
// 	BOOL WriteRecordTestToFile(const CString &strFile);
// 	BOOL WriteRecordTestToFile();

	//��ʼ�����������Զ�����ֵ�������,������ֵ���������ʽ
	void InitDataAttributeCalFunc(BOOL bCalUseRecordBuffer);
	
	//��ȡSpyBuffer==>>RecordBuffer��ȡ�����
	long GetRecordGap()   {    return m_pMemBuffer->GetRecordGap();   }

	//�Ƿ�������Ӧ
	BOOL IsRecordTestAutofit();

	//����Ӧ����MultiVariable
	void AutofitCreateMultiVariable();

	//����Ӧ����file-write
	void AutofitCreateFileWrite();

	//�Ƿ�ʹ������¼�����ж�
	BOOL IsNoneWithOnlineRecord()   {	return (m_nOnlineRecordMode == RecordTest_Mode_NoneWithOnlineRecord);	}
	BOOL IsTestUseOnlineRecord()		{	return ((m_nOnlineRecordMode == RecordTest_Mode_TestUseOnlineRecord) && (m_bTestUseOnlineRecord == TRUE));	}
	BOOL IsCommonOnlineRecord()		{	return (m_nOnlineRecordMode == RecordTest_Mode_CommonOnlineRecord);	}
	
	//�ж�ʾ������ʹ������¼��
	BOOL IsOscillographOnlineRecord() {		return (m_nOnlineRecordMode == RecordTest_Mode_OscillographOnlineRecord);		}

	void SetTestUseOnlineRecord(BOOL bTestUseOnlineRecord)	{	m_bTestUseOnlineRecord = bTestUseOnlineRecord;	}
	//�Ƿ���У׼����
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

	//����RefVariable
	void AdjustRefVariable()	
	{
		if (IsRecordTestAutofit())
		{
			m_pVariables->AdjustRefVariable(m_oMR1200SysAnalyseMngr);	
		}
	}	

	//�Ƿ�������¼������
// 	BOOL IsRTOnline()		{	return(_stricmp(m_strID, g_pszKeyRTOnline) == 0);	}
// 	
// 	//�Ƿ���ʾ������
// 	BOOL IsRTOscillograph()	{	return(_stricmp(m_strID, g_pszKeyRTOscillograph) == 0);	}

	void ValidateAttrCal();

	//��¡RecordTest
	void CloneRecordTest(CMemBuffer_UShort** pAttachBuffer, BOOL bCalUseRecordBuffer);
	void CloneRecordTest(CRecordTest* pSrc,CMemBuffer_UShort** pAttachBuffer, BOOL bCalUseRecordBuffer);

	//�ָ�Ĭ�϶�ֵ����
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
//��ʼ�����ϼ���
	void ResetValueCal();
};


#endif // !defined(AFX_RECORDTEST_H__1527A7D0_AC6C_4264_8C0B_76CD4699FA26__INCLUDED_)

// RtVariables.h: interface for the CRtVariables class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTVARIABLES_H__C0F945B6_69F9_4670_B757_9D8A74B3638D__INCLUDED_)
#define AFX_RTVARIABLES_H__C0F945B6_69F9_4670_B757_9D8A74B3638D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExBaseList.h"
#include "RtMultiVariable.h"
#include "RtSingleVariable.h"
#include "RtBinaryVariable.h"
#include "RtComplexVariable.h"

// #define _CAL_USE_REF_VARIABLE_

class CRtVariables : public CExBaseList  
{
public:
	CRtVariables();
	virtual ~CRtVariables();

//����
public:
	//�ؼ�������
// 	static const char *g_pszKeyVariables;
// 	static const char *g_pszKeyRefVariable;

	CString m_strRefVariable;//��׼ͨ��

	//���������������
	CMemBuffer_UShort *m_pAttrTimeBuffer;   //ʱ�仺����

	//�Ͳ������㻺��λ���йصı�����fdp add 2010.4.15
	__int64 m_n64AttrReadBeginPos;
	DWORD  m_dwReadBeginPos;
	DWORD m_dwReadEndPos;
	DWORD m_dwTimeReadBeginPos;
	DWORD m_dwTimeReadEndPos;
	
	//����Ӧ���ܵ�ͨ��Դ
	CRtSingleVariable *m_pUSourceVariable;
	CRtSingleVariable *m_pISourceVariable;
	CRtSingleVariable *m_pUdcSourceVariable;
	CRtSingleVariable *m_pIdcSourceVariable;
	CRtBinaryVariable *m_pBSourceVariable;

	//����Ӧ��������multi��channal����
	char *m_pszAutoMultiChsName[AUTO_MULTI_CH_NAME_COUNT];
	
	//�ж�����������
	CExBaseList m_listAnalogInstAttrs;//ģ����˲ʱֵ��������
	CExBaseList m_listBinaryInstAttrs;//������˲ʱֵ����
	CExBaseList m_listAnalogAttrs;//ģ������˲ʱֵ����

	//�����е�ģ�ⵥͨ��������������
	CExBaseList m_oListAnologVariable;
	CExBaseList m_oListBinaryVariable;
	
	//�����е�ģ�⽻����ѹͨ������
	CExBaseList m_oListACVariable_U;

	//�����е�ģ�⽻������ͨ������
	CExBaseList m_oListACVariable_I;

	//��¡��CRtVariables
	CRtVariables* m_pClone;

//����
public:
	//���صķ���
	virtual UINT GetClassID();
#ifdef _record_use_all_mode_
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);	
	virtual const char* GetXmlElementKey();
	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
	BOOL ReadSetsValueXml(MSXML::IXMLDOMNodeListPtr &oNodes);
	BOOL WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);
#endif
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild()					{	return NULL;    }
// 	virtual CExBaseObject* CreateNewChild(long nClassID)	{	return NULL;    }

	CRtSingleVariable* FindVariable(const CString &strID);
	CRtVariable* FindByRefRecordData(CExBaseObject *pRefRecordData);
	long GetCountByPhaseID(const CString &strPhaseID, const CString &strType);

	double CalAngleOffset(long nRefPos, long nCurrPos, long nBuffLen, long nSampleRate);

	//��������
	void CalValuesRealTime(PRECORD_CAL_LEN_PARA pCalLenPara, DWORD nSampleGap, DWORD dwSampleRate, BOOL bCalPointByPoint=TRUE);
	void CalValuesRealTimeEx(PRECORD_CAL_LEN_PARA pCalLenPara, DWORD nSampleGap, DWORD dwSampleRate, BOOL bCalPointByPoint=TRUE);
	void CalValuesRealTimeEx(CRtVariable * pdVariable, PRECORD_CAL_LEN_PARA pCalLenPara, DWORD nSampleGap, DWORD dwSampleRate, BOOL bCalPointByPoint=TRUE);

	//û���õ���������
	BOOL AttrCalPosInFrequencyCalRage(DWORD dwAttrCalBeginPos, DWORD dwAttrCalPoints);

	//��������������
	BOOL AttrCalPosInFrequencyCalRage2(DWORD dwAttrCalBeginPos, DWORD dwAttrCalEndPos);

	//��ü���Ƶ�ʵ����ݷ�Χ������ֵ����óɹ�ΪTRUE,��֮FALSE
	//BOOL GetFrequencyCalPos(PRECORD_CAL_LEN_PARA pCalLenPara, long &nCalBuffer1Pos, long &nCalBuffer1Len , long &nCalBuffer2Pos, long &nCalBuffer2Len, BOOL bCalUseRecordBuffer);
	//BOOL GetFrequencyCalPos(CRtVariable *pRtVariable,PRECORD_CAL_LEN_PARA pCalLenPara, long &nCalBuffer1Pos, long &nCalBuffer1Len , long &nCalBuffer2Pos, long &nCalBuffer2Len, BOOL bCalUseRecordBuffer);
	//���������ҵ�ǰƵ�ʼ���ķ�Χ
	BOOL GetFrequencyCalPos2(PRECORD_CAL_LEN_PARA pCalLenPara, long &nCalBuffer1Pos, long &nCalBuffer1Len , long &nCalBuffer2Pos, long &nCalBuffer2Len,long nBegin = 0);
	
	//��������
	void CalInstValue(long nBegin,BOOL bCalUseRecordBuffer);//fdp add 2010.10.8,�����ݲ�����������������ʱ�����˲ʱֵ
	BOOL CalValues(PRECORD_CAL_LEN_PARA pCalLenPara, long nBeginPos, DWORD dwSampleRate,BOOL bCalUseRecordBuffer, BOOL bCalOtherValues);//fdp add 2010.6.3,��������������
	BOOL CalValuesFnom(PRECORD_CAL_LEN_PARA pCalLenPara, long nBeginPos, DWORD dwSampleRate,BOOL bCalUseRecordBuffer, BOOL bCalOtherValues);//fdp add 2010.6.3,��������������
	BOOL CalValuesFnom_Quick(PRECORD_CAL_LEN_PARA pCalLenPara, long nBeginPos, DWORD dwSampleRate,BOOL bCalUseRecordBuffer, BOOL bCalOtherValues);//fdp add 2010.6.3,��������������
	BOOL CalValues_PeakVellay(PRECORD_CAL_LEN_PARA pCalLenPara, long nBeginPos, long nUseLength, DWORD dwSampleRate,BOOL bCalUseRecordBuffer, BOOL bCalOtherValues);//fdp add 2010.6.3,��������������
	void CalOtherValues(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCalUseRecordBuffer);
	void CalStaticValues(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer);//���㾲̬���Բ���
	void CalStaticValues_Quick(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer);//���㾲̬���Բ���
	void CalValues_PeakVellay(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer);//���㾲̬���Բ���
	void CalFrequncy(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCalUseRecordBuffer);//����Ƶ��	
	void CalFrequncy(CRtVariable * pdVariable, PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCalUseRecordBuffer);//����Ƶ��	
	void AddAttrValue();//������õ������Բ�����ӵ����Ի�����
	void CalFaultValues(long nBeginPos, long nLen, long nCyclePoints);

	//�ж�����
	BOOL JudgeStartupAnalogInst(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, long &nStartup);//¼��ģ����˲ʱֵ�����ж�
	BOOL JudgeStartupBinaryInst(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, long &nStartup);//¼��������˲ʱֵ�����ж�
	BOOL JudgeStartupAnalog(long &nStartup);//��˲ʱֵ���¼�������ж�

	CRtVariables* GetSingleAndBinaryVariables();
	virtual double* GetValueRefByID(const CString &strID);
	virtual double* GetMutationValueRefByID(const CString &strID);	
	virtual double* GetAttrValueRefByID(const CString &strID);

	void AdjustStaticAttrs();//������̬����:����Ƶ�ʡ���Чֵ����λ��������Чֵ��������λ
	BOOL BuildExpression();//�����ű����ʽ�����������жϽű��͸���ͨ������ű�
	void InitBufferMngr(CRtMemBufferMngr *pRtMemBufferMngr);//���ͨ�����桢����ʱ�仺��
	void InitAttrsBuffer(long nPoints);
	BOOL InitDataAttributeCalFunc(BOOL bCalUseRecordBuffer);
	void InitVariablesFIFOIndex();
	void ResetCalPos();
	CRtVariable* FindByVariableID(const char* pstrAttrID);
	CRtVariable* FindByAttrBufferID(const char* pstrAttrBufferID);
	CRtVariable* FindByRecordBufferID(const char* pstrRecordBufferID);
	CRtVariable* FindByBufferID(const char* pstrBufferID);
	CRtVariable* FindByHDChIndex(int nHDChIndex);
	long GetSingleVariableCountUsed();
	long GetBinaryVariableCountUsed();
	long GetVariableCountUsed();
	//��ֹͣ���ø��ֻ���Ķ�ȡ��Χ,fdp add 2010.4.15
	void SetFinalDataPos();
	BOOL SetFinalDataRange(unsigned short* pTimeBuffer,long nBegin,long nEnd,__int64 n64AtttrFirst,__int64 n64RecordFirst,DWORD& dwTimeBufferBegin);
	void ResetUseAndSpy();
	void ResetAttrSpyState();
	
	BOOL IsChannelInUse(const CString &strChID);

	//��ʼ��ģ�⡢����ͨ������
	void InitAnologBinaryVariableList();

	//��ʼ������ģ���ѹ������ģ���������,������ʵ��ר��
	void InitACAnologVariableList();
	
	//��ֵ����и���Ӳ���任����ͨ��������ȡ��Ӧ����ͨ��
	CRtSingleVariable* GetSingleVariableByTranChannelIndex(int nAttachedTranCHIndex);

	//����HD-CHIndex��ȡ��Ӧ�ĵ�ͨ��
	CRtSingleVariable* GetSingleVariableByHDIndex(int nHDIndex);
	
	//��ȡ��һ��ʹ�õ�SingleVariable��������ΪĬ�ϴ���ͨ��
	CRtSingleVariable* GetFirstSingleWithUseState();

public:
	//����ͨ����������RefVariable
	void SetRefVariableByVariableName(const CString& strName);

	long GetACUSingleVariableCount();
	long GetACISingleVariableCount();
	long GetSingleVariableCount();
	long GetBinaryVariableCount();
	long GetComplexVariableCount();
	long GetMultiVariableCount();
	long GetVariableCountWithRecordBuffer();
	CRtVariable * GetRefVariable()   {    return m_pRefVariable;    }
	void SetRefVariable(CRtVariable* pVariable)	;	
	CMemBufferInterface* GetRefBuffer()   {    return m_pRefBuffer;   }
	void SetVariable(CRtVariable* pVariable,long nIndex);

	//����ͨ����ȡ��ͨ���ڵ�ͨ��������ͨ���е�����
	long GetAnalogIndex(CRtSingleVariable* pVar);
	long GetBinaryIndex(CRtBinaryVariable* pVar);

	//����Ӧ���ܣ�
	//���ݿ�¡ͨ��Դ
	void BackCloneSources();
	virtual long RTUpdateOwnByAutofit(HDINFO &oHDInfo);

	//����Ӧ����MultiVariable
	void AutofitCreateMultiVariable();
	void AutofitCreateMultiVariable_3U();
	void AutofitCreateMultiVariable_3I();
	void AutofitCreateMultiVariable_UI();

	//��ʼ������Ӧ����MultiVariable��channal������
	void InitAutofitMultiVariable_ChName(const CString &strName);
	void InitAutoMultiVariable_3U_ChName();
	void InitAutoMultiVariable_3I_ChName();
	void InitAutoMultiVariable_UI_ChName();
	
	//�����׼ͨ��(��ȡ�궨ֵ)
	void UpdateRefVariableByVariableUse();
	void InitRefVariable();

	//���ڸ�������¼�����ӱ���������Լ���״̬
	void SetAttrSpyStateByVariableSpyConfig(const CString & strAttrID, long nAttrSpyState);

	//�ж��Ƿ�������ͨ������ͬ��
	BOOL IsHaveSameNameVariable(CRtVariable* pVariable);

	//��ʼ���ο�ͨ��
	void ValidateRefVariable(BOOL bCalUseRecordBuffer);

	//��¡Variables
	void CloneVariables(CRtVariables* pSrc,CMemBuffer_UShort** pAttachBuffer = NULL);
	void AdjustRefVariable(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr);

	//����������λ��
	void SetStartupPos(long nPos)	{	m_nStartupPos = nPos;	}

	//����������λ�ü����һ����λ��
	void CalBeginPosByStartupPos(long nStartupPos, DWORD nSampleGap, DWORD dwSampleRate);
	void CalBeginPosByStartupPos(DWORD nSampleGap, DWORD dwSampleRate)
	{
		ASSERT (m_pRefBuffer != NULL);

		if (m_pRefBuffer != NULL)
		{
			CalBeginPosByStartupPos(m_pRefBuffer->GetDataFillBeginPosition(), nSampleGap, dwSampleRate);
		}
	}

	//�õ���һ����λ�ú������㵽��һ����ľ���
	void GetFirstDataPos_StartuptoFirstData(__int64& nPos,__int64& nLen)	{nPos = m_nFirstDataPos; nLen = m_nDataLenStartuptoFirstData;}
	
	//�ж�����ģ��ͨ���Ƿ񶼲�ʹ��
	BOOL IsAllSingleVariableNoUse();

#ifdef _CAL_USE_REF_VARIABLE_
	long GetRefBufDataLen()	{	return m_nXRefBufDataLen;	}
#endif

private:
	CRtMemBufferMngr *m_pRtMemBufferMngr;
	CRtVariable *m_pRefVariable;
	__int64 m_nFirstDataPos;
	long m_nStartupPos;
	long m_nDataLenStartuptoFirstData;
	//fdp add 2010.5.12 ������Ϊ�̴߳�����Buffer�ķ�Χ�ı䣬����ԭ�м���λ��
#ifdef _CAL_USE_REF_VARIABLE_
	DWORD m_nXRefBufLen;
	DWORD m_nXRefBufFillBeginPos;
	DWORD m_nXRefBufDataLen;
	DWORD m_nXFrequencyCalBeginPos;          //Ƶ�ʼ������ʼλ��
	DWORD m_nXAttrCalBeginPos;               //���Լ������ʼλ��
#endif

	CMemBufferInterface *m_pRefBuffer;
	DWORD m_pdwAttrCalPosition[MAX_FREQ_ZERO_POS_BUFFER];
	BOOL m_bRefVariableChanged;

	long GetLenFromCurrPosToFillPos(long nCurrPos, long nDataFillPos, long nDataLen, long nBufferLen);
	
	BOOL IsPosInRange(long nPos, long nBegin, long nEnd);
	BOOL IsPosInRange(CRtVariable * pdVariable, long nPos, long nBegin, long nEnd);
//	BOOL IsPosInRange(long nPos, long nBegin, long nEnd);
	//fdp add 2010.4.15
	//���ó���Ƶ��֮������Լ���ķ�Χ
	DWORD GetAttrCalPosition2 (DWORD *pdwAttrCalPosition,PRTATTRIBUTECALFUNCPARA pCalPara);
	DWORD GetAttrCalPosition2 (CRtVariable * pdVariable,PRTATTRIBUTECALFUNCPARA pCalPara);
	//���û����ȡ�����
	long SetReadBeginPos(/*CMemBuffer_UnsignedShort *pBuffer*/);
	long SetReadBeginPos(CRtVariable * pdVariable/*CMemBuffer_UnsignedShort *pBuffer*/);
	//�жϱ��β������������Ƿ���һ�������
	BOOL IsAttrCalBeginPosInRefZeroPos(DWORD** pBegin,DWORD* pEnd,long& nOffSet);
	BOOL IsAttrCalBeginPosInRefZeroPos(CRtVariable * pdVariable, DWORD** pBegin,DWORD* pEnd,long& nOffSet);
	//������ʱ�Ĳ�������ķ�Χ����
	long GetExceptionalAttrCalPos(DWORD* pdwAttrCalPos/*,DWORD dwFillBeginPos*/);
	long GetExceptionalAttrCalPos(CRtVariable * pdVariable,DWORD* pdwAttrCalPos/*,DWORD dwFillBeginPos*/);
	//����ʱ�Ĳ�������ķ�Χ����
	///long GetNormalAttrCalPos(DWORD* pBegin,DWORD* pEnd,DWORD* pdwAttrCalPos,double dFreqValue);
	long GetNormalAttrCalPos(DWORD* pBegin,DWORD* pEnd,DWORD* pdwAttrCalPos,double dFreqValue, PRTATTRIBUTECALFUNCPARA pCalPara);
	long GetNormalAttrCalPos(CRtVariable * pdVariable,DWORD* pBegin,DWORD* pEnd,DWORD* pdwAttrCalPos,double dFreqValue, PRTATTRIBUTECALFUNCPARA pCalPara);
	
	//��Ӳ�����ʱ�Ĳ���ֵ
// 	long AddAbNormalValue(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos);
// 	long AddAbNormalValue(CRtVariable* pRtVarible,PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos);
// 	long AddAbNormalValue(CRtDataAttribute* pRtDataAttr,PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos);
// 	void AddAbNormalValue(CMemBuffer_Float* pAttrBuffer); 
	//��ӵ�һ�����Ի�������fdp add 2010.4.23
	void AddFirstAttrData();
	void AddFirstAttrData(CRtVariable* pRtVarible);
	void AddFirstAttrData(CRtDataAttribute* pRtDataAttr);
	//���ʱ�����ݵ�����
	void AddTimeValue(RTATTRIBUTECALBUFFERPOS& oRtAttrCalBufPos);
	
	CRtVariable* FindByIDForRdSets(const CString& strID, const CString& strTanModel);	
	DWORD m_paVariables[MAX_RTVARIABLES];
	
	BOOL ValidateVariableRecordBuffer(BOOL bCalUseRecordBuffer);
	//////////////////////////////////////////////////////////////////////////
	//ϵͳ��������
public:
	void InitByAttrSpy(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr);
	void InitByAttrDedfault(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr);
	void SaveAttrSpy(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr);
	void InitByHarmAttrSpy(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr);

	void SetAttrUse(UINT nAttrID, long nUse);


	void ResetValueCal();
	DWORD* GetVariablesAddr()	{	return m_paVariables;	}
	void ResetValuesByHdIndex(long nHdIndex);
	void InitRtCalVariables();
	void InitCalFuncPara(long nChIndex);
	long GetChIndexByID(const CString &strChID);
};

//������ʼλ�úͼ�������ݳ��ȣ���ȡ�����е����ݷ�Χ��������ͨ�����DFT����
BOOL GetAttrCalPos(long nBeginPos, long nEndPos, long nBufferLen, long nDataLen, long nDataFillBeginPos, PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos);	
BOOL GetAttrCalPos(long nBeginPos, long nEndPos, long nBufferDataLen, long &nCalBuffer1Pos, long &nCalBuffer1Len , long &nCalBuffer2Pos, long &nCalBuffer2Len);
BOOL GetAttrCalPos(long nBeginPos, long nBufferLen, long nDataLen, PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, double dFrequency);	

extern CString g_strWriteRecordData_VariableID;

//2022-4-23  lijunqing �������ݻ��壬������̷߳��ʼ�������������
#define XCYCLE_VARS_COUNT  128
#define XCYCLE_MAX_COUNT  16

typedef struct sttVariablesRtValues
{
	long nCount;
	RTCHANNELATTRVALUE oRtValues[XCYCLE_VARS_COUNT];
}STTVARIABLESRTVALUES, *PSTTVARIABLESRTVALUES;

class CStttVariablesRtValueBuffer
{
public:
	CStttVariablesRtValueBuffer();
	virtual ~CStttVariablesRtValueBuffer();

private:
	long m_nBufferCount;
	long m_nWritePos;

	STTVARIABLESRTVALUES m_oSttVarsVals[XCYCLE_MAX_COUNT];

public:
	PSTTVARIABLESRTVALUES GetNextForWrite();
	PSTTVARIABLESRTVALUES GetCurrForWrite();
	void NextForWrite();
	PSTTVARIABLESRTVALUES GetLast();
	void GetLast(STTVARIABLESRTVALUES &oSttValues);
	void ResetAllValues();
};

extern CStttVariablesRtValueBuffer g_oStttVariablesRtValueBuffer;

#endif // !defined(AFX_RTVARIABLES_H__C0F945B6_69F9_4670_B757_9D8A74B3638D__INCLUDED_)

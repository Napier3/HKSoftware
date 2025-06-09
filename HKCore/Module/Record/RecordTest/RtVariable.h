// RtVariable.h: interface for the CRtVariable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTVARIABLE_H__77DAD0CF_EC2A_4A1F_A4F9_4B856F1D95C9__INCLUDED_)
#define AFX_RTVARIABLE_H__77DAD0CF_EC2A_4A1F_A4F9_4B856F1D95C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "RtChannels.h"
#include "RtDataAttributes.h"
#include "CalFunctions.h"
#include "../RtMemBuffer/MemBuffer.h"
//#include "../RtMemBuffer/MemBuffer_UnsignedShort.h"
#include "../RtMemBuffer/RtMemBufferChannel.h"
//#include "../RtMemBuffer/MemBuffer_Float.h"
//#include "../RtMemBuffer/MemBuffer_Double.h"
#include "RtAllocBuffer.h"

#define  RTVARIABLE_ATTRBUFFER_MAX_COUNT   8

extern long g_nRecordStartup;

class CRtVariable : public CExBaseList  
{
public:
	CRtVariable();
	virtual ~CRtVariable();

//����
public:
	//¼�����桢���ӻ�������
	CString m_strRecordBufferID;
	long     m_nRecordBufferUse;
	CString m_strSpyBufferID;
	long     m_nSpyBufferUse;
	CString  m_strTranModel;
	BOOL     m_bReadSets;
	
	//��������
	COLORREF m_crColor;
	long     m_nType;
	CRtChannels       *m_pChannels;   //������ͨ����ֻ��multi��complex����
	CRtDataAttributes *m_pDataAttrs;

	long m_nVariableUse;//ͨ���Ƿ�ʹ��
	long     m_nSpyState;    //���ӵ�״̬�����ڱ��ͨ���ļ���

	//Ϊ����������ݶ����ٵĻ�����
	CRtAllocBuffer  *m_pAllocBuffer;

	//2020-4-15  
	CExBaseObject *m_pRefRecordData;

	//�ⲿ���������ݻ�����
	CRtMemBufferChannel *m_pChannelBuffer;
	CMemBufferInterface   *m_pAttachRecordBuffer;		//������¼�����ݻ���������Ҫ��������¼�����ݷ�����

	RTCHANNELATTRVALUE m_oCurrValue;//��ǰ����ֵ
	RTCHANNELATTRVALUE m_oPrevValue;//��һ�εļ���ֵ
	RTCHANNELATTRVALUE m_oMutationValue;//ͻ����
	double m_dAngleOffset;

	//�����Ŀ�¡����
	CRtVariable* m_pClone;
	BOOL m_bChannelBufferCreatedByClone;//ͨ��������Ҫ�ͷ�
	CRtVariable* m_pRefRtVariable;//20221214 zhouhj  �ο�ͨ��
//����
public:
	//����
	virtual long GetRtVariableClassID()		{	return 0;	}

	//���صķ���
	virtual UINT GetClassID()     {		return RTCLASSID_VARIABLE;	}
#ifdef _record_use_all_mode_
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
	virtual const char* GetXmlElementKey()					{	 return NULL;    }
	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);    
	virtual BOOL ReadSetsValueXml(MSXML::IXMLDOMNodePtr &oNode);
	virtual BOOL WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);
#endif
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild()					{	 return NULL;	 }
// 	virtual CExBaseObject* CreateNewChild(long nClassID)	{	 return NULL;	 }

	//������ط���
	BOOL CanCal();
	virtual void CalValues(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCalUseRecordBuffer);
	virtual void CalStaticValues(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer);
	virtual void CalStaticValues_Quick(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer);
	virtual void CalValues_PeakVellay(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer);
	virtual void InitCalFuncPara();
	virtual void CalFrequncy(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCalUseRecordBuffer);
	void AddAttrValue();
	virtual BOOL JudgeStartup(long &nStartup);
	void CalFaultValues(long nBeginPos, long nLen, long nCyclePoints);
	void CalThd();

	//��������ID������������Եĺ����ĵ�ַ
	virtual BOOL GetCalFuncByAttrID(const CString &strAttrID, double **ppdValue, double **ppdMutationValue, UINT &nAttrID, CALFUNC **ppCalFunc, RTCALFUNCPARA &oRtCalFuncPara, BOOL bCalUseRecordBuffer);

	virtual double* GetValueRefByID(const CString &strID);
	virtual double* GetMutationValueRefByID(const CString &strID);	
	virtual double* GetAttrValueRefByID(const CString &strID);

	virtual double* GetValueByAttrID(const CString &strID);
	virtual double* GetCloneValueByAttrID(const CString &strID);
	virtual double* GetCalValueByAttrID(const CString &strID);
	virtual CString GetUnitString();//�������Ի�ȡ��λ
	void AdjustStaticAttrs();
	BOOL BuildExpression();
	virtual void InitBufferMngr(CRtMemBufferMngr *pRtMemBufferMngr);	
	void InitAttrsBuffer(long nPoints);

	virtual BOOL InitDataAttributeCalFunc(BOOL bCalUseRecordBuffer);

	//��������ID����ȡ���Լ��㺯���Ĳ������ݶ������ݶ�����ϸ���ݼ��ṹ��PRTATTRIBUTECALFUNCPARA
	PRTATTRIBUTECALFUNCPARA GetAttrCalFuncPara(UINT nAttrID);
	
	CString GetAttrBufferIDByAttrID(LPCTSTR pszAttrID);

	//���οؼ���صĲ���
	//virtual void InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, BOOL bParentExpand, HTREEITEM hAfter = TVI_LAST);
	void InitAfterClone();
	void ResetUseAndSpy()
	{
		m_pDataAttrs->ResetUseAndSpy();
	}
	
	void ResetAttrSpyState()
	{
		m_pDataAttrs->ResetAttrSpyState();
	}
	
	BOOL IsRecordBufferNull(BOOL bCalUseRecordBuffer);

	void CalInstValue(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos,BOOL bCalUseRecordBuffer);//˲ʱֵ���㣬fdp add 2010.10.8
	
public:
	void SetVariableType(long nType)	{	m_nType = nType;				   }
	BOOL IsVariableType_U()    {     return (m_nType == RTVARIABLE_TYPE_U);    }
	BOOL IsVariableType_I()    {     return (m_nType == RTVARIABLE_TYPE_I);    }
	BOOL IsVariableType_NONE() {     return (m_nType == RTVARIABLE_TYPE_NONE); }

	BOOL IsRtSingleVariable()  {     return GetClassID() == RTCLASSID_SINGLEVARIABLE;   }
	BOOL IsRtBinaryVariable()  {     return GetClassID() == RTCLASSID_BINARYVARIABLE;   }
	BOOL IsRtComplexVariable() {     return GetClassID() == RTCLASSID_COMPLEXVARIABLE;  }
	BOOL IsRtMultiVariable()   {     return GetClassID() == RTCLASSID_MULTIVARIABLE;    }

	long GetVariableUseState() {	 return m_nVariableUse;  }
	void SetVariableUseState(long nVariableUse) {	m_nVariableUse = nVariableUse;  }
	
	BOOL IsUserecordBuffer()   {	 return (m_nRecordBufferUse == 1);		   }
	BOOL IsVariableUse()	   {	 return (m_nVariableUse == 1);			   }
	long Get_ChIndex();
	void Set_ChIndex(long nIndex);
	long Get_HdIndex();
	void Set_HdIndex(long nIndex);

	//��¡Variable
	void CloneVariable(CRtVariable* pSrc,CMemBuffer_UShort* pAttachBuffer = NULL);
	void SetAttrUse(UINT nAttrID, long nUse);
private:
	BOOL GetCalFuncByAttrIDByChannel(const CString &strAttrID, double **ppdValue, double **ppdMutationValue, UINT &nAttrID, CALFUNC **ppCalFunc, RTCALFUNCPARA &oRtCalFuncPara);
	BOOL GetCalFuncByAttrIDByAttach(const CString &strAttrID, double **ppdValue, double **ppdMutationValue, UINT &nAttrID, CALFUNC **ppCalFunc, RTCALFUNCPARA &oRtCalFuncPara);


public:
	//��ͨ����������  2020-6-17  lijunqing
	__int64 m_n64AttrReadBeginPos;
	DWORD m_nFrequencyCalBeginPos;          //Ƶ�ʼ������ʼλ��
	DWORD m_nAttrCalBeginPos;               //���Լ������ʼλ��
	DWORD m_nRefBufLen;
	DWORD m_nRefBufFillBeginPos;
	DWORD m_nRefBufDataLen;
	DWORD m_dwAttrCalPosition[MAX_FREQ_ZERO_POS_BUFFER];

	void ZeroCalValues();
	void ZeroAllCalValues();
	void InitCalPos();
	void InitCalPos(long nRefBufLen, long nRefBufFillBeginPos, long RefBufDataLen);
	void ResetValueCal();

	BOOL HasChannelBuffer()
	{
		return (m_pChannelBuffer != NULL || m_pAttachRecordBuffer != NULL);
	}

	CMemBufferInterface* GetChannelBuffer()
	{
		if (m_pChannelBuffer != NULL)
		{
#ifdef _USE_RECORD_BUFFER_TO_CAL
			return m_pChannelBuffer->GetRecordMemBuffer();
#else
			return  m_pChannelBuffer->GetSpyMemBuffer();
#endif
		}

		return m_pAttachRecordBuffer;
	}
};

#endif // !defined(AFX_RTVARIABLE_H__77DAD0CF_EC2A_4A1F_A4F9_4B856F1D95C9__INCLUDED_)

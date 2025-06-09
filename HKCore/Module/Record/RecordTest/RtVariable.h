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

//属性
public:
	//录波缓存、监视缓存设置
	CString m_strRecordBufferID;
	long     m_nRecordBufferUse;
	CString m_strSpyBufferID;
	long     m_nSpyBufferUse;
	CString  m_strTranModel;
	BOOL     m_bReadSets;
	
	//自身属性
	COLORREF m_crColor;
	long     m_nType;
	CRtChannels       *m_pChannels;   //关联的通道，只有multi、complex才有
	CRtDataAttributes *m_pDataAttrs;

	long m_nVariableUse;//通道是否使用
	long     m_nSpyState;    //监视的状态，用于表格通道的监视

	//为自身保存的数据而开辟的缓冲区
	CRtAllocBuffer  *m_pAllocBuffer;

	//2020-4-15  
	CExBaseObject *m_pRefRecordData;

	//外部关联的数据缓冲区
	CRtMemBufferChannel *m_pChannelBuffer;
	CMemBufferInterface   *m_pAttachRecordBuffer;		//关联的录波数据缓冲区，主要用于在线录波数据分析用

	RTCHANNELATTRVALUE m_oCurrValue;//当前计算值
	RTCHANNELATTRVALUE m_oPrevValue;//上一次的计算值
	RTCHANNELATTRVALUE m_oMutationValue;//突变量
	double m_dAngleOffset;

	//关联的克隆对象
	CRtVariable* m_pClone;
	BOOL m_bChannelBufferCreatedByClone;//通道缓存需要释放
	CRtVariable* m_pRefRtVariable;//20221214 zhouhj  参考通道
//方法
public:
	//个性
	virtual long GetRtVariableClassID()		{	return 0;	}

	//重载的方法
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

	//试验相关方法
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

	//根据属性ID关联计算该属性的函数的地址
	virtual BOOL GetCalFuncByAttrID(const CString &strAttrID, double **ppdValue, double **ppdMutationValue, UINT &nAttrID, CALFUNC **ppCalFunc, RTCALFUNCPARA &oRtCalFuncPara, BOOL bCalUseRecordBuffer);

	virtual double* GetValueRefByID(const CString &strID);
	virtual double* GetMutationValueRefByID(const CString &strID);	
	virtual double* GetAttrValueRefByID(const CString &strID);

	virtual double* GetValueByAttrID(const CString &strID);
	virtual double* GetCloneValueByAttrID(const CString &strID);
	virtual double* GetCalValueByAttrID(const CString &strID);
	virtual CString GetUnitString();//根据属性获取单位
	void AdjustStaticAttrs();
	BOOL BuildExpression();
	virtual void InitBufferMngr(CRtMemBufferMngr *pRtMemBufferMngr);	
	void InitAttrsBuffer(long nPoints);

	virtual BOOL InitDataAttributeCalFunc(BOOL bCalUseRecordBuffer);

	//根据属性ID，获取属性计算函数的参数数据对象，数据对象详细内容见结构体PRTATTRIBUTECALFUNCPARA
	PRTATTRIBUTECALFUNCPARA GetAttrCalFuncPara(UINT nAttrID);
	
	CString GetAttrBufferIDByAttrID(LPCTSTR pszAttrID);

	//树形控件相关的操作
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

	void CalInstValue(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos,BOOL bCalUseRecordBuffer);//瞬时值计算，fdp add 2010.10.8
	
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

	//克隆Variable
	void CloneVariable(CRtVariable* pSrc,CMemBuffer_UShort* pAttachBuffer = NULL);
	void SetAttrUse(UINT nAttrID, long nUse);
private:
	BOOL GetCalFuncByAttrIDByChannel(const CString &strAttrID, double **ppdValue, double **ppdMutationValue, UINT &nAttrID, CALFUNC **ppCalFunc, RTCALFUNCPARA &oRtCalFuncPara);
	BOOL GetCalFuncByAttrIDByAttach(const CString &strAttrID, double **ppdValue, double **ppdMutationValue, UINT &nAttrID, CALFUNC **ppCalFunc, RTCALFUNCPARA &oRtCalFuncPara);


public:
	//各通道独立计算  2020-6-17  lijunqing
	__int64 m_n64AttrReadBeginPos;
	DWORD m_nFrequencyCalBeginPos;          //频率计算的起始位置
	DWORD m_nAttrCalBeginPos;               //属性计算的起始位置
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

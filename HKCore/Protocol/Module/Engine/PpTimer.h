#pragma once
#include "ExBaseObject.h"
#include "PpNode.h"

class CPpNode;

class CPpTimer :	public CExBaseList
{
public:
	CPpTimer(void);
	virtual ~CPpTimer(void);

//属性
public:
	CString m_strType;//add by whq
	long m_nType;
	long m_nTimeLong;
	CString m_strJumpTo;
	CPpNode* m_pJumpToNode;
private:
	CPpScript* m_pScript;

public:
	virtual UINT GetClassID(){ return PPCLASSID_PPTIMER; };
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPpTimerKey;     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

public:
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

public:
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	CPpScript* GetScript();
	
//////////////////////////////////////////////////////////////////////////
//timer时钟执行代码
private:
	DWORD m_dwTimerBegin;
	BOOL m_bTimerBegin;

public:
	void BeginTimer(DWORD dwCurrTick);
	void ResetTimer(DWORD dwCurrTick);
	void KillTimer();
	BOOL IsTimeOut(DWORD dwCurrTick);
};

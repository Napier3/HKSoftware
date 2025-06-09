//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PpCfgOptr.h  CPpCfgOptr

#pragma once

#include "ClassProcotolProjectGlobal.h"


#include "PpCfgOptrBatch.h"
#include "PpCfgOptrDevice.h"
#include "../Engine/PpScript.h"
#include "../../../Module/System/TickCount32.h"

class CPpCfgOptr : public CExBaseList
{
public:
	CPpCfgOptr();
	virtual ~CPpCfgOptr();

	long m_nIsRunning;
	long  m_nTDelay;
	CString  m_strRunProcedure;
	CString m_strPachageID;

	CPpCfgOptrBatch *m_pPpCfgOptrBatch;
	CPpScript *m_pPpScript;
//���غ���
public:
	virtual UINT GetClassID() {    return POCLASSID_CPPCFGOPTR;   }
	virtual BSTR GetXmlElementKey()  {      return CClassProcotolProjectXmlRWKeys::CPpCfgOptrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:
	CTickCount32 m_oTickCount32;

//˽�г�Ա�������ʷ���
public:
	CPpScript* GetPpScript();
	virtual void SerializeTrigerScript(long &nScriptIndex, CExBaseList &listTrigerScript, const CString &strID);
	
	BOOL CanRun();
	void EnterRun();
};


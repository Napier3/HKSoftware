//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PpCfgOptrsMngr.h  CPpCfgOptrsMngr

#pragma once

#include "ClassProcotolProjectGlobal.h"


#include "PpCfgOptrs.h"

class CPpCfgOptrsMngr : public CExBaseList
{
public:
	CPpCfgOptrsMngr();
	virtual ~CPpCfgOptrsMngr();


//���غ���
public:
	virtual UINT GetClassID() {    return POCLASSID_CPPCFGOPTRSMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CClassProcotolProjectXmlRWKeys::CPpCfgOptrsMngrKey();     }
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

//˽�г�Ա�������ʷ���
public:
	virtual void SerializeTrigerScript(long &nScriptIndex, CExBaseList &listTrigerScript, const CString &strID);

};


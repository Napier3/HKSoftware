//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PpCfgOptrs.h  CPpCfgOptrs

#pragma once

#include "ClassProcotolProjectGlobal.h"


#include "PpCfgOptr.h"

class CPpCfgOptrs : public CExBaseList
{
public:
	CPpCfgOptrs();
	virtual ~CPpCfgOptrs();


	CString  m_strProcedure;


//���غ���
public:
	virtual UINT GetClassID() {    return POCLASSID_CPPCFGOPTRS;   }
	virtual BSTR GetXmlElementKey()  {      return CClassProcotolProjectXmlRWKeys::CPpCfgOptrsKey();     }
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


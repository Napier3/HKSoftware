//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CommCmdStrcutAttrs.h  CCommCmdStrcutAttrs

#pragma once

#include "ReportTemplateConfigGlobal.h"


#include "CommCmdStrcutAttr.h"

class CCommCmdStrcutAttrs : public CExBaseList
{
public:
	CCommCmdStrcutAttrs();
	virtual ~CCommCmdStrcutAttrs();


//���غ���
public:
	virtual UINT GetClassID() {    return RPTCFGCLASSID_CCOMMCMDSTRCUTATTRS;   }
	virtual BSTR GetXmlElementKey()  {      return CReportTemplateConfigXmlRWKeys::CCommCmdStrcutAttrsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};


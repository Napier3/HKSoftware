//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CommCmdStrcutAttr.h  CCommCmdStrcutAttr

#pragma once

#include "ReportTemplateConfigGlobal.h"



class CCommCmdStrcutAttr : public CExBaseObject
{
public:
	CCommCmdStrcutAttr();
	virtual ~CCommCmdStrcutAttr();


//���غ���
public:
	virtual UINT GetClassID() {    return RPTCFGCLASSID_CCOMMCMDSTRCUTATTR;   }
	virtual BSTR GetXmlElementKey()  {      return CReportTemplateConfigXmlRWKeys::CCommCmdStrcutAttrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};


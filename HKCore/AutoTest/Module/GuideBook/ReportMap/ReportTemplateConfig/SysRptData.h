//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SysRptData.h  CSysRptData

#pragma once

#include "ReportTemplateConfigGlobal.h"



class CSysRptData : public CExBaseObject
{
public:
	CSysRptData();
	virtual ~CSysRptData();


//���غ���
public:
	virtual UINT GetClassID() {    return RPTCFGCLASSID_CSYSRPTDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CReportTemplateConfigXmlRWKeys::CSysRptDataKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};


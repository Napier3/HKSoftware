//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ReportTemplateConfig.h  CReportTemplateConfig

#pragma once

#include "ReportTemplateConfigGlobal.h"


#include "BkmkDataProcessMngr.h"
#include "CommCmdStrcutAttrs.h"
#include "SysRptDataMngr.h"

class CReportTemplateConfig : public CExBaseList
{
public:
	CReportTemplateConfig();
	virtual ~CReportTemplateConfig();


//���غ���
public:
	virtual UINT GetClassID() {    return RPTCFGCLASSID_CREPORTTEMPLATECONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CReportTemplateConfigXmlRWKeys::CReportTemplateConfigKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InitAfterRead();

	BOOL OpenReportTemplateConfigFile();

//˽�г�Ա����
private:
	CBkmkDataProcessMngr *m_pBkmkDataProcessMngr;
	CSysRptDataMngr *m_pSysRptDataMngr;
	CCommCmdStrcutAttrs *m_pCommCmdStrcutAttrs;
	CMgrpCmbnDataMngr *m_pMgrpCmbn;

//˽�г�Ա�������ʷ���
public:
	CCommCmdStrcutAttrs* GetCommCmdStrcutAttrs()		{	return m_pCommCmdStrcutAttrs;	}
	CBkmkDataProcessMngr* GetBkmkDataProcessMngr()		{	return m_pBkmkDataProcessMngr;	}
	CMgrpCmbnDataMngr* GetMgrpCmbnDataMngr()		{	return m_pMgrpCmbn;	}
};


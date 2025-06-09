//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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


//重载函数
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

//私有成员变量
private:
	CBkmkDataProcessMngr *m_pBkmkDataProcessMngr;
	CSysRptDataMngr *m_pSysRptDataMngr;
	CCommCmdStrcutAttrs *m_pCommCmdStrcutAttrs;
	CMgrpCmbnDataMngr *m_pMgrpCmbn;

//私有成员变量访问方法
public:
	CCommCmdStrcutAttrs* GetCommCmdStrcutAttrs()		{	return m_pCommCmdStrcutAttrs;	}
	CBkmkDataProcessMngr* GetBkmkDataProcessMngr()		{	return m_pBkmkDataProcessMngr;	}
	CMgrpCmbnDataMngr* GetMgrpCmbnDataMngr()		{	return m_pMgrpCmbn;	}
};


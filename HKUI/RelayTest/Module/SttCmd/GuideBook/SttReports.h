#pragma once

#include "../SttCmdDefineGlobal.h"
#include "SttReport.h"

class CSttReports : public CExBaseList
{
public:
	CSttReports();
	virtual ~CSttReports();


//重写父类方法
public:
	virtual UINT GetClassID(){    return STTCMDCLASSID_REPORTS;   }
	virtual BSTR GetXmlElementKey(){return CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strCSttReportsKey;}

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	void AddReport(CDataGroup *pDataGroup);
};

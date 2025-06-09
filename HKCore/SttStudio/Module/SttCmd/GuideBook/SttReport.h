#pragma once

#include "../SttCmdDefineGlobal.h"
#include "../../../../Module/DataMngr/DvmValues.h"
#include "../../../../Module/DataMngr/DvmDataset.h"
#include "../../../../Module/DataMngr/DataGroup.h"

class CSttReport : public CExBaseList
{
public:
	CSttReport();
	virtual ~CSttReport();

	CString m_strBeginTime;
	CString m_strEndTime;
	//属性
public:
	CDvmValues *m_pValues;//20230103 zhouhj 从CValues改为CDvmValues
	CDvmDataset *m_pRptDvmDataset; 

	//重写父类方法
public:
	virtual UINT GetClassID()		{    return STTCMDCLASSID_REPORT;   }
	virtual BSTR GetXmlElementKey(){return CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strCSttReportKey;}

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

public:
    void InitValues(CValues *pSrc);
    void InitRptDvmDataset(CDvmDataset *pSrc);
	void InitReport(CDataGroup *pDataGroup);
	CDvmValue* FindValueByID(const CString &strID);

	//报告中，增加几个固定的结果值，用于绑定误差判断的计算值
	BOOL AddRptValues_ErrorCal(); 
};

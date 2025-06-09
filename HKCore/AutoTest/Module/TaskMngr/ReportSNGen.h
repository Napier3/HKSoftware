#pragma once

#include "../../../Module/DataMngr/DvmDataset.h"

class CTestRrptSnGenInterface;

class CReportSNGen : public CExBaseObject
{
public:
	CReportSNGen(void);
	virtual ~CReportSNGen(void);

public:
	long m_nReportSNGenIndex;
	long m_nReportIndex;
	CString m_strLastDate;
	SYSTEMTIME m_tmCurrReport;
	CDvmDataset *m_pDataset;
	CTestRrptSnGenInterface *m_pCurrTestProject;

public:
	//´®ÐÐ»¯
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey();

public:
	BOOL OpenConfigFile();
	BOOL SaveConfigFile();

	void ReportSNGen(CExBaseList &listProjects, CDvmDataset *pRptSnGen, const CString &strMacroFileID);

protected:
	BOOL m_bUseReportSNGenIndex;
	CString m_strMacroFileID;
	CString GetReportSnGenFile();

	void ReportSNGen(CExBaseList &listProjects, CDvmDataset *pRptSnGen);
	void InitGenIndex();

public:
	void ReportSNGen(CDvmDataset *pRptSnGen, CString &strReportSN);
	void ReportSNGen(CDvmData *pDvmData, CString &strReportSN);
};

#ifndef _CSttXHtmlRptGenInterface_H
#define _CSttXHtmlRptGenInterface_H

#include "../UI/Interface/SttHtmlReportVIewInterface.h"
#include "../../../Module/MemBuffer/ExpandMemBuf.h"
#include "../../../Module/DataMngr/DataTypes.h"

#define HTML_BUFFER_SIZE_INIT 1048576



class CSttXHtmlRptGenInterface
{
public:
    CSttXHtmlRptGenInterface();
    virtual ~CSttXHtmlRptGenInterface();


public:	
	void SetDataTypes(CDataTypes *pDataTypes);
	void SetHtmlReportView(CSttHtmlReportVIewInterface *pView)	{	m_pReportView = pView;	}
	void SetHtmlBuffer(CExpandMemBuf *pBuffer)	{	m_pHtmlBuffer = pBuffer;	}
	CSttHtmlReportVIewInterface* GetHtmlReportView(){return m_pReportView;}
	
protected:
	CDataTypes *m_pDataTypes;
	CSttHtmlReportVIewInterface *m_pReportView; //��ʾ��ҳ
	CExpandMemBuf  *m_pHtmlBuffer;

public:
	virtual void FillReport();		 	 		//����Ա���HTML�ı�������Բ���
	virtual void FillReportData(const CString &strParentItemsPath, const CString &strItemID, const CString &strState, char *pszReport);

	virtual void OpenHead();							//�򿪱���ͷReportHeader.html
	virtual void FillHead();							//ʹ��ReportHead_Paras.xml��䱨��ͷhtml

	virtual void GenHtml();			 					//���ɲ��Ա���HTML�ı�
	virtual void InsertRptHtml();
	virtual void UpdateRptHtml();

	virtual void GenModule_RootDiv(const CString &strModuleID);
	virtual void GenModule_Table_th(const CString &strModuleID);
	virtual void GenModule_RootDiv(const char *strModuleID);
	virtual void GenModule_Table_th(const char *strModuleID);
	virtual void GenModule_Table_th(CDataGroup *pColsTitle, BOOL bUseIndex);
	virtual void GenModule_Table_th(const char *strModuleID, CDataGroup *pColsTitle, BOOL bUseIndex);
	virtual void GenModule_Table_th(const CString &strModuleID, CDataGroup *pColsTitle, BOOL bUseIndex);

	virtual void GenModule_Table_te();

	virtual void Gen_Table_th(const char *pszColTitle);
	virtual void Gen_Table_td(const char *pszColTitle);
	virtual void Gen_Table_td(float fValue, long ndecimal);
	virtual void Gen_Table_td(CString strValue, long ndecimal);
	virtual void Gen_Table_td(long nValue);
public:
	void FormatDataValue(CDvmData *pData, long nDecimal);
	void FormatDataValue(CDataGroup *pDatas, const CString &strDataID, long nDecimal);
	
	void FormatDataValue(CDvmData *pData, const CString &strDataTypeID);
	void FormatDataValue(CDataGroup *pDatas, const CString &strDataID, const CString &strDataTypeID);

	CString GetDataValueString(CDvmData *pData, const CString &strDataTypeID);
	CString GetDataValueString(CDvmValue *pValue, const CString &strDataTypeID);
	void ShowData_td_ByDataType(long nIndex ,const CString &strDataType);
	void ShowData_td_ByDataType(CDvmData *pData, const CString &strChildID,const CString &strDataType);
	void ShowData_td_ByDataType(CDvmData *pData, const CString &strChildID1, const CString &strChildID2,
		const CString &strDataType);
};


#endif // _CSttXHtmlRptGenInterface_H

#ifndef _CSttHtmlRptGen_MUAccuracy_H
#define _CSttHtmlRptGen_MUAccuracy_H

#include "../SttXmacroHtmlRptGenBase.h"

class CSttHtmlRptGen_MUAccuracy : public CSttXmacroHtmlRptGenBase
{
public:
    CSttHtmlRptGen_MUAccuracy();
    virtual ~CSttHtmlRptGen_MUAccuracy();

	static CSttXmacroHtmlRptGenBase* New()
	{
		return new CSttHtmlRptGen_MUAccuracy();
	}

	//CDvmDataset *m_pDvmDataset;
	//void InitDataset();

public:

	virtual void GenHtml();			 					//生成测试报告HTML文本
	virtual void GenRootDiv();
	virtual void GenRootDiv_H1();
	virtual void GenMUAccuracy();					
	virtual void GenRootDiv_End();

	virtual void GenMUAccuracy_RootDiv(const CString &strTypeID);          //生成子表根节点
	virtual void GenMUAccuracy_h2(const CString &strName);	             //生成子表标题
	//virtual void GenMUAccuracy_Table(const CString &strTypeID);	         //生成子表的<table>部分
	//virtual void GenMUAccuracy_Table_th(const CString &strTypeID);         //生成子表头

	void GenMUAccuracy_Table_th_RatError(const CString &strTypeID);
	void GenMUAccuracy_Table_th_AngError(const CString &strTypeID);
	void GenMUAccuracy_Table_th_CompError(const CString &strTypeID);
	void GenMUAccuracy_Table_th_ChDelay(const CString &strTypeID);

	//virtual void GenMUAccuracy_Table_te();				 //生成子表尾
	virtual void GenMUAccuracy_Point_RatError(const CString &strTypeID);
	virtual void GenMUAccuracy_Point_AngError(const CString &strTypeID);
	virtual void GenMUAccuracy_Point_CompError(const CString &strTypeID);
	virtual void GenMUAccuracy_Point_ChDelay();

	virtual void ShowData_td(CDvmData *pData, CString strTypeID, CString strAttrID);
	void Gen_Data_td_AngError(int nIndex, CDvmData *pData,  CString strTypeID);
	void Gen_Data_td_RatError(int nIndex, CDvmData *pData,  CString strTypeID);
	void Gen_Data_td_CompError(int nIndex, CDvmData *pData,  CString strTypeID);
	void ShowData_td_ChDelay(CDvmData *pData, CString strAttrID);
	void Gen_Data_td_ChDelay(const CString &strCBName,CDvmData *pData);

//	virtual void ShowData_td_Results(CDvmData *pData, CString strTypeID, CString strAttrID);
//	void ShowData_td_ChDelay_Result(CDvmData *pData, CString strAttrID);

};


#endif // _CSttHtmlRptGen_MUAccuracy_H

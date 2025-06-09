//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestMacro.h  CTestMacro

#pragma once

#include "TestMacroGlobal.h"


#include "TmFaultParas.h"
#include "TmSysParas.h"
#include "TmResultParas.h"
#include "TmFaultParasEx.h"
#include "TmResultParasEx.h"

class CTestMacro : public CExBaseList
{
public:
	CTestMacro();
	virtual ~CTestMacro();


	CString  m_strVersion;
	CString  m_strType;
	CString  m_strRemark;

	CString m_strFile;   //shaolei 20210706

//重载函数
public:
	virtual UINT GetClassID() {    return TMCLASSID_CTESTMACRO;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroXmlRWKeys::CTestMacroKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);   //shaolei 20210708
    virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

    virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	CTmFaultParas *m_pFaultParas;
	CTmSysParas *m_pSysParas;
	CTmResultParas *m_pResults;
	CTmSearchResultParas *m_pSearchResults;
	CTmFaultParasEx *m_pFaultParasEx;
	CTmResultParasEx *m_pResultsEx;

	//2021-8-15  lijunqing批注：参数按照remark进行分类管理，老版本需求
	CExBaseList m_listFaultParasGroup;
	CExBaseList m_listSysParasGroup;

	//统一成DvmDataGroup  2020-10-06
	CDataGroup *m_pFaultParas_Dvm;
	CDataGroup *m_pResults_Dvm;

public:
	//2023-1-6  shaolei  扩展故障参数和扩展结果参数，分别整理成单独的链表
	CExBaseList m_list_FaultParasEx;
	CExBaseList m_list_ResultParasEx;

//私有成员变量访问方法
public:
	CShortDatas* GetFaultParas()	{	return m_pFaultParas;	}
	CShortDatas* GetSearchResults()	{	return m_pSearchResults;	}
	CShortDatas* GetSysParas()		{	return m_pSysParas;		}
	CShortDatas* GetResults()		{	return m_pResults;		}
	CShortData* FindDataByID(const CString &strID);
	CTmFaultParasEx* GetFaultParasEx()	{	return m_pFaultParasEx;	}
	CTmResultParasEx* GetResultsEx()		{	return m_pResultsEx;	}

	virtual void OnSetParaValue(CShortData *pPara, CExBaseList &listNew, CExBaseList &listDelete);
	virtual void OnSetParaValue(const CString &sttrIDPath, const CString &strValue, CExBaseList &listNew, CExBaseList &listDelete, CExBaseList &listChanged);

	//lijunqing 2021-8-15  
	CDataGroup* GetFaultParas_Dvm()	{	return m_pFaultParas_Dvm;	}
	CDataGroup* GetResults_Dvm()	{	return m_pResults_Dvm;	}

//////////////////////////////////////////////////////////////////////////
//参数分组功能
public:
	CExBaseList* GetFaultParasGroups()	{	return &m_listFaultParasGroup;	}
	CExBaseList* GetSysParasGroups()	{	return &m_listSysParasGroup;	}
	void InitParasGroup();
	void ResetDatas(CExBaseList &listDatas);
	void ResetDatas();

	void GetParasValues(CValues *pValues);

	//2020-10-06  lijunqing
	void GetTestMacroParas(CDataGroup *pParas, CDataGroup *pResults);
	void GetTestMacroParas_Fault(CDataGroup *pParas);
	void GetTestMacroParas_Result(CDataGroup *pResults);
	void InitParas_Dvm();
	void GetTestMacroParas_Fault_CloneEx(CDataGroup *pParas);
	void GetTestMacroParas_Result_CloneEx(CDataGroup *pResults);

	//以下四个函数，分别将扩展故障参数和扩展结果参数，整理成一个链表
	void InitFaultParasEx();
	void InitResultParasEx();
	void InitFaultParasEx(CExBaseList &oList, long nStateCount=-1);
	void InitResultParasEx(CExBaseList &oList, long nStateCount=-1);
	long GetStateNum(const CString &strDataID);  //状态序列特殊处理，从参数ID中获取状态号

	void GetParaIDPath(CString &strPath, CShortData *pPara);
	CString GetParaIDPath(CShortData *pPara);
	void GetParaNamePath(CString &strPath, CShortData *pPara);
	CString GetParaNamePath(CShortData *pPara);

private:
	CShortDatas* FindGroupByID(CExBaseList *pListGroup, const CString &strID);
	CShortDatas* AddGroupByID(CExBaseList *pListGroup, const CString &strID, POS &posFirst);
	void AddParaToGroup(CShortData *pData, CExBaseList *pListGroup, POS &posFirst);
	void AddParasToGroup(CShortDatas *pDatas, CExBaseList *pListGroup, POS &posFirst);

	void FreeParasGroup(CExBaseList *pListGroup);
	void AppendValues(CExBaseList *pList, CValues *pValues);

	//shaolei 20210706
public:
	BOOL SaveFile();   
	void SetParasToDefault(); // shaolei  2021119 将所有参数设置回默认值
	void SetParasToDefault(CShortDatas *pDatas);

};


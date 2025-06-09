//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttItemBase.h  CSttItemBase

#pragma once

#include "../SttCmdDefineGlobal.h"


#include "SttReportMap.h"
#include "SttReports.h"
#include "SttItemRsltExpr.h"

class CSttItemBase : public CExBaseList
{
public:
	CSttItemBase();
	virtual ~CSttItemBase();


	long  m_nTkID;
	long  m_nShow;
	long  m_nEnable;
	long  m_nExecType;
	long  m_nBatchItem;
	long  m_nMdvTestEach;
	long  m_nState;
	long  m_nSelect;
//重载函数
public:
	virtual UINT GetClassID() {    return STTGBXMLCLASSID_CSTTITEMBASE;   }
	virtual BSTR GetXmlElementKey();//  {      return CSttCmdDefineXmlRWKeys::CSttItemBaseKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	

	virtual long GetGbItemCount();
	virtual void GetItemsCountByItemsType(long &nTotalCount, long &nEligibleCount, long &nInlegibleCount);
	virtual void GetFirstTwoItemsByItemsType(CString &strFirst, CString &strSecond);
	virtual void GetAllItemsByItemsType(CExBaseList &oList);

	virtual BOOL IsChildItemExist(CSttItemBase *pChildItem);
	//shaolei 20221020
	virtual CSttItemBase* GetPrevItem(CSttItemBase *pCurrItem);
	virtual CSttItemBase* GetNextItem(CSttItemBase *pCurrItem);

public:
	//shaolei 2023-3-1
	CSttItemRsltExpr *m_pRsltExpr;
//私有成员变量
private:
	CSttReports *m_pSttReports;
	CSttReportMap *m_pSttReportMap;

//私有成员变量访问方法
public:
	void UpdateParentState(); //sf 20220223 更新父节点状态
//属性变量访问方法
public:
	CSttReports* SetReports(CSttReports *pSttReports);
	CSttReports* GetSttReports()	{	return m_pSttReports;	}
	CSttReport* GetReport(long nIndex);	
	void GetAllItemsByID(const CString &strItemID, CExBaseList &oItemList);
	long IsTestFinish();

	CSttReportMap* GetReportMap(BOOL bCreate);
	long GetReportsCount();
	CSttItemRsltExpr* GetRsltExpr();
	void GetRsltExprValues(CExBaseList *pRlstExprValues, CExBaseList *pReportValues, CExBaseList *pListXExprValues);

	//根据项目的相对路径，查找对应的项目
	long SelectItems(const CString &strPath, CExBaseList &oListDest);
	//根据类型，查找第一个CSttItems项目
	virtual CSttItemBase* FindFirstItems(const CString &strType, BOOL bCheckType = TRUE);
	//获取项目的测试次数。
	virtual long GetItemTestCount()	{	return 1;	}
	virtual void SetState(long nState);
	virtual void ClearReport();
	virtual void DeleteChildItem_Commcmd(BOOL bRecursion = TRUE);
protected:
    virtual long SelectChildrenItems(const CString &strPath, CExBaseList &oListDest)
    {
#ifdef _PSX_IDE_QT_
        (void)strPath;
        (void)oListDest;
#endif
        return 0;
    };

	virtual long SelectItemsLeft_Var(const CString &strPath, const CString &strPathLeft, const CString &strPathRight, CExBaseList &oListDest);

};

//测试结束，返回1，正在测试返回2，未开始，返回0
long Stt_IsItemsTestFinished(CExBaseList *pList);
//判断该项目下，是否所有子项目都测试合格
BOOL Stt_Stt_IsAllChildItemTestELIGIBLE(CExBaseList *pList);
BOOL Stt_IsGbItemClassID(UINT nClassID);
BOOL Stt_IsItemsBaseClassID(UINT nClassID);
//获取最近的,为功能类节点的CSttItems父节点  shaolei   20220404
//默认形参为非功能类节点
class CSttItems;
CSttItems* Stt_GetFirstParentItems(CExBaseObject *pObj, const CString &strType, BOOL bType = FALSE);

//清空报告数据
void Stt_EmptyReportDatas(CExBaseList *pList, BOOL bOnlySelect=FALSE);

BOOL stt_IsItemsAin(const CString &strItemsID);  //判断是否是遥测项目
BOOL stt_IsItemAin(CExBaseObject *pItemBase);  //判断是否是遥测项目
BOOL stt_IsItemHasAin(CSttItemBase *pItemBase);  //判断该项目下，是否有遥测项目

//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
//���غ���
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
//˽�г�Ա����
private:
	CSttReports *m_pSttReports;
	CSttReportMap *m_pSttReportMap;

//˽�г�Ա�������ʷ���
public:
	void UpdateParentState(); //sf 20220223 ���¸��ڵ�״̬
//���Ա������ʷ���
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

	//������Ŀ�����·�������Ҷ�Ӧ����Ŀ
	long SelectItems(const CString &strPath, CExBaseList &oListDest);
	//�������ͣ����ҵ�һ��CSttItems��Ŀ
	virtual CSttItemBase* FindFirstItems(const CString &strType, BOOL bCheckType = TRUE);
	//��ȡ��Ŀ�Ĳ��Դ�����
	virtual long GetItemTestCount()	{	return 1;	}
	virtual void SetState(long nState);
	virtual void ClearReport();
	virtual void DeleteChildItem_Commcmd(BOOL bRecursion = TRUE);
protected:
	virtual long SelectChildrenItems(const CString &strPath, CExBaseList &oListDest)		{		return 0;		};
	virtual long SelectItemsLeft_Var(const CString &strPath, const CString &strPathLeft, const CString &strPathRight, CExBaseList &oListDest);

};

//���Խ���������1�����ڲ��Է���2��δ��ʼ������0
long Stt_IsItemsTestFinished(CExBaseList *pList);
//�жϸ���Ŀ�£��Ƿ���������Ŀ�����Ժϸ�
BOOL Stt_Stt_IsAllChildItemTestELIGIBLE(CExBaseList *pList);
BOOL Stt_IsGbItemClassID(UINT nClassID);
BOOL Stt_IsItemsBaseClassID(UINT nClassID);
//��ȡ�����,Ϊ������ڵ��CSttItems���ڵ�  shaolei   20220404
//Ĭ���β�Ϊ�ǹ�����ڵ�
class CSttItems;
CSttItems* Stt_GetFirstParentItems(CExBaseObject *pObj, const CString &strType, BOOL bType = FALSE);

//��ձ�������
void Stt_EmptyReportDatas(CExBaseList *pList, BOOL bOnlySelect=FALSE);

BOOL stt_IsItemsAin(const CString &strItemsID);  //�ж��Ƿ���ң����Ŀ
BOOL stt_IsItemAin(CExBaseObject *pItemBase);  //�ж��Ƿ���ң����Ŀ
BOOL stt_IsItemHasAin(CSttItemBase *pItemBase);  //�жϸ���Ŀ�£��Ƿ���ң����Ŀ

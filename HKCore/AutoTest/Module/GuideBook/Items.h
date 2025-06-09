#pragma once
#include "GbItemBase.h"
#include "GuideBookDefine.h"
#include "CommCmd.h"
#include "TestMacroUiParas.h"
#include "TestMacroCharParas.h"
#include "MacroTest.h"

// #define GBID_BeforeTest_ (_T("_BeforeTest_"))
// #define GBID_AfterTest_  (_T("_AfterTest_") )
#define GBNAME_BeforeTest_ (g_sLangTxt_TestReady/*_T("����׼��")*/)
#define GBNAME_AfterTest_  (g_sLangTxt_TestWork/*_T("���Թ����ָ�")*/ )

// #define GBID_ItemPrefix_BeforeTest (_T("_BFT_"))
// #define GBID_ItemPrefix_AfterTest  (_T("_AFT_"))
// 
// #define  GBITEMS_NODETYPE_NONE       (_T("none"))
// #define  GBITEMS_NODETYPE_ROOTNODE   (_T("rootnode"))

class CItems :public CGbItemBase
{
public:
	CItems(void);
	virtual ~CItems(void);

	static CItems* _New(CBaseObject *pParent=NULL)
	{
		CItems *pNew = new CItems();
		return pNew;
	}

	static CItems* _NewForExport()
	{
		CItems *pNew = new CItems();
		pNew->m_strName = g_strExportID;
		pNew->m_strID = g_strExportID;
		return pNew;
	}

	static const CString g_strExportID;

	BOOL IsTypeRootNode();
	void SetTypeRootNode(BOOL bRoot=TRUE);
	CItems* FindFirstRootTypeItem();

	//2022-11-04  lijuniqng  �������ã��ز���������Ŀģʽ����ģʽ��ֻҪһ������Ŀ���ϸ񣬾��ز���������Ŀ
	//����ֻ��ѡ���ϸ�����Ŀ�Լ���ص�ǰ���ͺ�����Ŀ
	BOOL IsReTestAllChildMode();
public:
	//attribute
	CString m_strType;                    //������ڵ㣺����ѡ������Ŀ������в���
	CString m_strCharacteristicID;
	//��Ŀ����󶨵��߼�ͼҳ�� shaolei 20210310
	CString m_strActLogic;

	//�Ƿ������ģ�����ʵ�����õ��ĸ��ڵ�  20150305
	CString m_strStxmlFile;
	CString m_strWzdMapFile;
	//�ظ�������shaolei 20230317
	long m_nTestTimes;   //���Դ���

	CItemsRsltExprScript *m_pItemsRsltExprScript;

	//shaolei  2023-6-20 
	long m_nRptTitle;  //�Ƿ���Ϊword�������
	long m_nTitleLevel;  //��ΪWORD�������ʱ������ȼ�

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_ITEMS;			}
	virtual BSTR GetXmlElementKey()  {      return CGbXMLKeys::g_pGbXMLKeys->m_strItemsKey;     }

	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(CExBaseObject *pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual void InitAfterRead();

	CItemsRsltExprScript* GetItemsRsltExprScript(BOOL bCreate);
	BOOL HasItemsRsltExprScript();

protected:
	//shaolei 2022-01-05
	CTestMacroUiParas* m_pUiParas;
	//shaolei 2023-3-22
	CTestMacroCharParas* m_pCharParas;

	virtual long SelectChildrenItems(const CString &strPath, CGbItemBaseList &oListDest);
	virtual long XmlWriteChildren_FinalReport(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	

public:
	//2020-02-03  lijq update items paras
// 	virtual BOOL Update(CBaseObject* pDest);
// 	virtual BOOL UpdateOwn(CBaseObject* pDest);
	virtual BOOL UpdateChildren(CBaseObject* pDest);

	void UpdateItems(CItems *pDestItems, CGbItemBase *pNewItem);
	void GetItemsCountByType(long &nTotalCount, long &nEligibleCount, long &nInlegibleCount);

	//shaolei 2022-01-05
	CTestMacroUiParas* GetTestMacroUiParas()	{	return m_pUiParas;	}
	CTestMacroUiParas* CreateTestMacroUiParas();
	void SetTestMacroUiParas(CTestMacroUiParas *pUiParas);
	//shaolei 2023-03-22
	CTestMacroCharParas* GetTestMacroCharParas()	{	return m_pCharParas;	}
	CTestMacroCharParas* CreateTestMacroCharParas();
	void SetTestMacroCharParas(CTestMacroCharParas *pCharParas);
	//shaolei 20220607
	virtual void SetItemState(long nShow, long nEnable, long nSelect, BOOL bSetShow, BOOL bSetEnable, BOOL bSetSelect);
	virtual long GetItemTestCount();
	CMacroTest* GetFirstMacroTest();  //��ȡ��һ����������Ŀ
};


CExBaseObject* GbItems_CreateNewChild(long nClassID);
CExBaseObject* GbItems_CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
void Gb_UpdateMacroTestParaData(CExBaseList *pList, const CShortData  *pData, const CString &strMacroID, BOOL bOnlySubItem=TRUE, BOOL bShowLog = TRUE);
BOOL GbItems_HasItem(CExBaseList *pItems, UINT nClassID);
void Gb_UpdateCmmCmdParaData(CExBaseList *pList, CCmd *pCmd,UINT nParaID, BOOL bOnlySubItem=TRUE, BOOL bShowLog = TRUE);

void Gb_SetTestItemSelectedState(CGbItemBase *pItem,long nSelect, BOOL bUpdateParent=TRUE);
void Gb_UpdateItemSelectedState(CGbItemBase* pItem);

//ͨѶ������Ŀ����
void Gb_DeleteAllItem(CExBaseObject* pItem, CTreeCtrl *pTreeCtrl, CExBaseList *pListDelete);
void Gb_DeleteValueFromAllCommCmd(CCommCmd *pCommCmd, CExBaseList *pListValue);
void Gb_AddValuesToAllCmd(CExBaseObject *pObj, CCommCmd *pCommCmd);
CValue* Gb_FindValueByIDPath(const CString &strID, CValues *pValues);
CValue* Gb_AddValuesToCmd(CCommCmd *pCommCmd, CExBaseObject *pObj);

void Gb_EditAllCmdValue(CValue *pValue, CCommCmd *pCommCmd);
BOOL Gb_IsCommCmdTheSameType(CCommCmd *pSrc, CCommCmd *pDest, BOOL bUseID=FALSE);
void Gb_PasteAllCommCmd(CCommCmd *pSrcCommCmd, CCommCmd *pCurrCommCmd);

//��ձ�������
void Gb_EmptyReportDatas(CExBaseList *pList, BOOL bOnlySelect = FALSE);

//׼����Ŀ�ͻָ���Ŀ����
long Gb_QueryBftAftItem(CExBaseList *pGuideBook, CExBaseObject *pCurrItem, CExBaseList &listQuery);
long Gb_QueryBftItem(CExBaseList &listQuery, CExBaseList &listDest);

CItemsRsltExprScriptMngr* Gb_GetExprScriptMngr(CExBaseObject *pGbObj);

//2021-8-9  lijunqing  
void Gb_QueryItems_SafetyDataTypes(CGbItemBase *pItemRoot, CDataTypes *pDataTypes);

//2023-9-18 lijunqing ���ò�����Ŀ����ı�������
void Gb_SetItemsReport(CItems *pDestItems, CItems *pSrcItems);
void Gb_SetItemReport(CGbItemBase *pDestItem, CGbItemBase *pSrcItem);

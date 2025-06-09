// ExBaseList.h: interface for the CExBaseList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EXBASELIST_H__)
#define _EXBASELIST_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExBaseObject.h"
#include "TLinkList.h"

class CExBaseList : public CExBaseObject , public CTLinkListEx<CExBaseObject> 
{
public:
	CExBaseList();
	virtual ~CExBaseList();

public:
//属性定义

//方法
public:
	virtual void Append(CExBaseList &oListSrc, unsigned int nClassID);
	virtual void Append(CExBaseList &oListSrc);
	virtual void AppendEx(CExBaseList &oListSrc, BOOL bSetParent=TRUE);
	virtual void AppendClone(CExBaseList &oListSrc);
	virtual void AppendClone(CExBaseList &oListSrc, BOOL bAddSame);
	virtual void AppendCloneEx(CExBaseList &oListSrc, BOOL bSetParent=TRUE);
	virtual void AppendCloneEx2(CExBaseList &oListSrc, BOOL bSetParent=TRUE, BOOL bCopyOwn=TRUE, BOOL bCopyChildren=TRUE);
	virtual void Append(CExBaseList *pListSrc)			{	Append(*pListSrc);			}
	virtual void AppendClone(CExBaseList *pListSrc)		{	AppendClone(*pListSrc);		}
	virtual void Append(CExBaseList &oListSrc, long nBegin, long nCount, BOOL bSetParent=TRUE);
	virtual void AppendClone(CExBaseList &oListSrc, long nBegin, long nCount);

	virtual CExBaseObject* CreateNewChild(CXmlRWNodeBase &oNode, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
	{
		CString strNodeName;
		strNodeName = oNode.GetNodeName();
		return CreateNewChild(strNodeName, bAddToTail, pXmlRWKeys);
	}
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual CExBaseObject* AddNew(long nClassID);

	virtual UINT GetClassID()                             {      return CLASSID_EXLISTCLASS;                 }
	
	//ReadXml
	virtual long XmlReadChildren(CXmlRWNodeListBase &oNodes, CXmlRWKeys *pXmlRWKeys);

	//WriteXml
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	

	//缓冲区串行化
	virtual long SerializeChildren(CBinarySerialBuffer &oBinaryBuffer);
	
    //文件树形控件相关的操作
	virtual long InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);
	
	//列表控件操作
	virtual long InsertChildToListCtrl(CListCtrl *pListCtrl, long nBeginIndex=0); 	//将子对象插入到列表视图中
	virtual long UpdateChildListCtrl(CListCtrl *pListCtrl, long nBeginIndex=0); 	//将子对象插入到列表视图中
	virtual long UpdateChildListCtrlIndex(CListCtrl *pListCtrl, long nBeginIndex=0); 	//将子对象插入到列表视图中

	virtual long InsertChildreComboBox(CComboBox *pComboBox); 
	virtual long InsertChildreListBox(CListBox *pListBox);

#ifndef NO_XDbBaseLib
    //Mysql相关  begin
	//从数据库中查找合适的数据集
	virtual BOOL DB_SelectChildren(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask);
	virtual BOOL DB_Select(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask);
	virtual BOOL DB_DeleteChildren(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL DB_Insert_Children(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask);
	//插入后更新主键，更新子对象外键
	virtual BOOL DB_Update_Children(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL DB_Update_Children_Cmd(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL DB_SetForeignKeyValue_Children(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);
	virtual BOOL DB_SelectEx(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString strFK=_T(""), CString strFKVal=_T(""));
	virtual BOOL DB_InsertEx(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);
	virtual BOOL DB_UpdateEx(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL DB_SelectSqlEx(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString &strSql);

	virtual CExBaseObject* FindByPkValue(__int64 &n64FindPKVal);
	virtual CExBaseObject* FindByPkValue(long &nFindPKVal);
	virtual CExBaseObject* FindByPkValue(const CString &strFindPKVal);
	virtual CExBaseObject* FindByPkValue(CXDb_PKeyValue &oPkValue);

	virtual void DB_InitNameAttrs();
	//end
#endif

public:
	virtual BOOL CopyChildren(CBaseObject* pDest)	;
	virtual BOOL IsEqualChildren(CBaseObject* pObj);

	virtual BOOL UpdateChildren(CBaseObject* pDest)	;
	virtual CBaseObject* FindSame(CBaseObject* pObj);
	//删除子对象，并清空成员指针
	virtual void DeleteChildren();

	virtual BOOL CanPaste(UINT nClassID);
	virtual BOOL CanPaste(CExBaseObject *pObj);
	virtual BOOL CanPaste(CExBaseList *pList);
	virtual CExBaseObject* Paste(CExBaseObject *pObj);
	virtual CExBaseObject* Paste(CExBaseList *pList);

	CExBaseObject* AddNew(const CString &strName, const CString &strID);
	virtual CBaseObject* Clone();

	virtual void InitNameAndIDForPaste(CExBaseObject *pObj);
	virtual CExBaseObject* AddNewChild(CExBaseObject *pNew, BOOL bInitNameAndId=FALSE);
	virtual CExBaseObject* FindByClassID(DWORD dwClassID);
	virtual CExBaseObject* FindByClassID(DWORD dwClassID, long nIndex);  //2023-3-28  lijunqing
	virtual BOOL AddChildren(UINT nChildClassID, long nCount);

	virtual DWORD FilterChildren(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD FilterChildren_ID(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	//shaolei 20200204 id、name同时过滤，id优先
	virtual DWORD FilterChildren_ID_Name(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	//shaolei 20200228 id、name同时过滤，id优先，不区分大小写
	virtual DWORD FilterChildren_ID_Name_NoCase(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual void RemoveTail(UINT nRemoveClassID, long nCountRemove, CExBaseList &oListRemove);

	virtual void InitReserved(DWORD dwReserved=0x0FFFFFFF);
	virtual void InitItemData(DWORD dwItemData=0x0FFFFFFF);

public:
	//根据路径查找节点
	//long SelectEx(CString &strPath, CExBaseList &oListDest);
    virtual long SelectDatas(const CString &strIDPath, CExBaseList &oListDest, const CString &strSeperator=_T("$"));
    virtual CExBaseObject* SelectData(const CString &strIDPath, const CString &strSeperator=_T("$"));
	virtual CExBaseObject* FindChildByID(const CString &strID)	{	return FindByID(strID);	}
	virtual CExBaseObject* FindChildByIDEx(const CString &strID);
	virtual CExBaseObject* FindByIDPathEx(UINT nRootClassID, BOOL bHasRoot, const CString &strIDPath);
	virtual long SelectChildrenByClassID(CExBaseList &listChild, UINT nChildClassID);
	virtual long SelectChildrenByClassIDEx(CExBaseList &listChild, UINT nChildClassID);

	virtual long QueryByID(const CString &strID, CExBaseList &oList);
	virtual void DeleteByID(const CString &strID);
protected:
	virtual long SelectChildren(CString &strPath, CExBaseList &oListDest, TCHAR chSeperator);

public:
	virtual long FindByPathChildren(CString &strPath, CExBaseList &oListDest, TCHAR chSeperator);
	//通过Name形成的路径，查找子对象  shaolei 20220527
	virtual long FindByPathChildren_Name(CString &strPath, CExBaseList &oListDest, TCHAR chSeperator);
	void SortByID();

////多语言相关
public:
	virtual CString GetXLangID(CExBaseObject *pChildObj);
	virtual void GetXLangID(CExBaseObject *pChildObj, CString &strLangID);

//2019-4-17  lijunqing,用于编辑的时候，验证数据是否有效
public:
	virtual BOOL ValidateForNew(CExBaseObject* pNewObj);
	virtual BOOL ValidateForNew(CExBaseObject* pNewObj, BOOL bValidateName, BOOL bValidateID);
	virtual BOOL ValidateForEdit(CExBaseObject* pEditRef, CExBaseObject *pEditTempData);
	virtual BOOL ValidateForEdit(CExBaseObject* pEditRef, CExBaseObject *pEditTempData, BOOL bValidateName, BOOL bValidateID);
	virtual BOOL ValidateForEdit(CExBaseObject *pEditTempData, BOOL bValidateName, BOOL bValidateID);

public:
	virtual void CalChildrenSize(BOOL bCalChild, long &nObjCount, long &nTotalSize, CFile *pFile);

	//2019-08-25
	virtual void Sort(BOOL bAscending);
	virtual void Sort(DWORD dwAttrID, BOOL bAscending);
	virtual void Sort(const CString &strAttrID, BOOL bAscending);

};

BOOL ValidateExBaseObjectName(CExBaseObject *pObj, CString &strName);
BOOL ValidateExBaseObjectID(CExBaseObject *pObj, CString &strID);
BOOL ValidateExBaseObjectNameAndID(CExBaseObject *pObj, CString &strName, CString &strID);

#ifndef NO_XDbBaseLib
//2019-5-11  lijunqing
BOOL DB_ValidateExBaseObjectNameAndPk_New(CExBaseObject *pObj, const CString &strName, CString &strMsg);
BOOL DB_ValidateExBaseObjectNameAndPk_Edit(CExBaseObject *pObj, CExBaseObject *pRefObj, const CString &strName, CString &strMsg);
#endif

#endif // !defined(_EXBASELIST_H__)

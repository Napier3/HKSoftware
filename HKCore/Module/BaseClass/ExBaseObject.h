// ExBaseObject.h: interface for the CExBaseObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EXBASEOBJECT_H__)
#define _EXBASEOBJECT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseObject.h"

#ifndef NO_XDbBaseLib
#include "XDbBaseLib.h"
#endif

typedef long PFuc_InitListCtrlColumns(CListCtrl *pListCtrl);

#define FILTERMODE_CLEAR   0
#define FILTERMODE_HAS     1
#define FILTERMODE_EQUAL   2

class CExBaseList;

class CExBaseObject : public CBaseObject
{
public:
	CExBaseObject();
	virtual ~CExBaseObject();

//属性定义
public:
	CString m_strName;
	CString m_strID;
	//CString m_strLangID;   //多语言字符串资源，只限于XML文件使用  2016-12-30

	DWORD  m_dwItemData;
#ifndef exbase_not_use_m_dwReserved
	DWORD  m_dwReserved;    //保留用
#endif

//方法
public:
	//ReadXML
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	//WriteXML
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	//缓冲区串行化
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

    //树形控件相关的操作
	virtual void InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);
	virtual void InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);
	virtual long InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);
	
	//列表控件相关操作
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);//   {	return 0;  }//初始化ListCtrlColumns
	virtual long InsertChildToListCtrl(CListCtrl *pListCtrl, long nBeginIndex=0);	//将子对象插入到列表视图中
	virtual long InsertToListCtrl(CListCtrl *pListCtrl, long lItemIndex=0);	// 将对象插入到列表视图中
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);	// 将对象插入到列表视图中
	virtual PFuc_InitListCtrlColumns* GetInitListCtrlColumnsFunc()	{	return NULL;	}

	//ComboBox相关
	virtual long InsertComboBox(CComboBox *pComboBox);
	virtual long InsertChildreComboBox(CComboBox *pComboBox);

	//ListBox相关
	virtual long InsertListBox(CListBox *pListBox);
	virtual long InsertChildreListBox(CListBox *pListBox);

	virtual DWORD Filter(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD FilterOwn(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD FilterChildren(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD Filter_ID(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD FilterOwn_ID(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD FilterChildren_ID(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	//shaolei 20200204 id、name同时过滤，id优先
	virtual DWORD Filter_ID_Name(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD FilterOwn_ID_Name(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD FilterChildren_ID_Name(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	//shaolei 20200228 id、name同时过滤，id优先,不区分大小写
	virtual DWORD Filter_ID_Name_NoCase(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD FilterOwn_ID_Name_NoCase(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD FilterChildren_ID_Name_NoCase(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);

#ifndef NO_XDbBaseLib
//////////////////////////////////////////////////////////////////////////
//数据库定义部分  begin
public:
	virtual BSTR DB_GetTableName(CXmlRWKeys *pXmlRWKeys);
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)	;
	virtual BSTR DB_GetChildTableName(CXmlRWKeys *pXmlRWKeys);
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys);
	virtual CString DB_GetPrimaryKeyValue();//		{	return _T("");		}

	virtual BSTR DB_GetForeignKey(CXmlRWKeys *pXmlRWKeys);
	virtual CString DB_GetForeignKeyValue();

	virtual BOOL DB_Select(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask);
	virtual CXDbRecordsetBase* DB_Select_Own(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL DB_SelectChildren(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask);

	//读数据
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	//写数据
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);

	//创建子对象
	virtual CExBaseObject* DB_CreateNewChild()		{	return NULL;		}

	//更新数据库中的值，把BaseObject中的字段组成sql语句写入数据库中
	virtual BOOL DB_Update(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys) ;
	virtual BOOL DB_Update_Children(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL DB_Update_Cmd(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys) ;
	
	//从数据库中删除一条记录,此时BaseList中delete一个子对象
	virtual BOOL DB_Delete(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL DB_Delete_Own(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL DB_DeleteChildren(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys);

	//把BaseObject中的字段组成sql语句写入数据库中
	virtual BOOL DB_Insert(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask) ;
	virtual BOOL DB_Insert_Cmd(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys) ;
	virtual BOOL DB_Insert_Own(CXDbBaseLib *pXDbLib, CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask) ;
	virtual BOOL DB_Insert_Children(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask);
	 
	//获得SQL语句
	virtual BOOL DB_GetSQL_Select_Own(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString &strSQL);
	virtual BOOL DB_GetSQL_Select_Childrenren(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString &strSQL);
	virtual BOOL DB_GetSQL_Select_Childrenren_ForeignKey(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString &strSQL);
	
	virtual BOOL DB_GetSQL_Insert(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString &strSQL);

	//没找到插入数据库，返回FALSE,找到，更新对象，返回TRUE
	virtual BOOL DB_UpdateOrInsert(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys
									,BOOL bInsert=TRUE, CString strSQL=_T("")
									,BOOL bUpdateSelf=TRUE);

	virtual BOOL DB_Select_OwnEx(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys
									, CString strQuerySql=_T(""));
	//没找到插入数据库，找到更新数据库，返回操作结果
	virtual BOOL DB_Insert(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys
								, CString strQuerySql=_T(""));
	//数据库定义部分  end

public:
	virtual long DB_WriteFields_BlobBinary(CXDbRecordsetBase *pRecordset, BSTR bstrKey);
	virtual long DB_WriteFields_BlobXML(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys, BSTR bstrKey);

	//约定：如果传入的pTempList指针不为空，则表示BLOB存储的为对象的子对象，否则为自身对象
	virtual long DB_ReadFields_BlobBinary(CXDbRecordsetBase *pRecordset, BSTR bstrKey);
	virtual long DB_ReadFields_BlobXML(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys, 
		BSTR bstrKey, CExBaseList *pTempList);

	//插入后更新主键，有自动编号的表需要重载此函数
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset);
	//插入后更新主键，更新子对象外键
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue);
	virtual void Db_SetPkeyValue(CXDb_PKeyValue &oPKeyValue);
	virtual void Db_SetPkeyValue(CExBaseObject *pRefObj);
	virtual BOOL DB_SetForeignKeyValue(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);
	virtual BOOL DB_SetForeignKeyValue_Children(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);

	virtual BOOL DB_SelectEx(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString strFK=_T(""), CString strFKVal=_T(""));
	virtual BOOL DB_InsertEx(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);
	virtual BOOL DB_UpdateEx(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL DB_SelectSqlEx(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString &strSql);
	virtual void DB_InitNameAttrs();
#endif

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE,BOOL bCopyChildren=FALSE);
	//删除子对象，并清空成员指针
	virtual void DeleteChildren(){}

	virtual BOOL IsSame(CBaseObject* pObj);
	virtual void InitReserved(DWORD dwReserved=0x0FFFFFFF);
	virtual void InitItemData(DWORD dwItemData=0x0FFFFFFF);

public:
	long GetAllAncestor(CExBaseList *pList);
	long GetAllAncestor(CExBaseList *pList, UINT nClassID);
	long GetAllAncestorEqClassID(CExBaseList *pList, UINT nClassID);
	virtual BOOL GetRefObjPath(CExBaseObject *pRefObj, CString &strPath);
	virtual CString GetPath();
	virtual long Select(CString &strPath, CExBaseList &oListDest, TCHAR chSeperator='\\');
	virtual long FindByPath(CString &strPath, CExBaseList &oListDest, TCHAR chSeperator='\\');
	virtual long FindByPathChildren(CString &strPath, CExBaseList &oListDest, TCHAR chSeperator='\\');

	//通过Name形成的路径，查找子对象  shaolei 20220527
	virtual long FindByPath_Name(CString &strPath, CExBaseList &oListDest, TCHAR chSeperator='\\');
	virtual long FindByPathChildren_Name(CString &strPath, CExBaseList &oListDest, TCHAR chSeperator='\\');

protected:
	virtual long SelectChildren(CString &strPath, CExBaseList &oListDest, TCHAR chSeperator);
	virtual long SelectLeft_Var(CString &strPath, CString &strPathLeft, CString &strPathRight, CExBaseList &oListDest, TCHAR chSeperator);


public:
	virtual CString GetIDPathEx(UINT nRootClassID, BOOL bHasRoot=TRUE, const CString &strSeperator=_T("$"));
	virtual CString GetNamePathEx(UINT nRootClassID, BOOL bHasRoot=TRUE, const CString &strSeperator=_T("$"));

	CString GetIDPathEx(CExBaseObject *pRoot, BOOL bHasRoot=TRUE, const CString &strSeperator=_T("$"));   //2022-9-17  lijunqing
	CString GetNamePathEx(CExBaseObject *pRoot, BOOL bHasRoot=TRUE, const CString &strSeperator=_T("$"));   //2023-9-1 shaolei
	
////多语言相关
public:
	virtual CString GetXLangID();
	virtual void GetXLangID(CString &strLangID);

public:
	virtual void CalObjSize(BOOL bCalChild, long &nObjCount, long &nTotalSize, CFile *pFile);
	virtual void CalChildrenSize(BOOL bCalChild, long &nObjCount, long &nTotalSize, CFile *pFile);
};


#endif // !defined(_EXBASEOBJECT_H__)

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

//���Զ���
public:
	CString m_strName;
	CString m_strID;
	//CString m_strLangID;   //�������ַ�����Դ��ֻ����XML�ļ�ʹ��  2016-12-30

	DWORD  m_dwItemData;
#ifndef exbase_not_use_m_dwReserved
	DWORD  m_dwReserved;    //������
#endif

//����
public:
	//ReadXML
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	//WriteXML
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	//���������л�
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

    //���οؼ���صĲ���
	virtual void InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);
	virtual void InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);
	virtual long InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);
	
	//�б�ؼ���ز���
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);//   {	return 0;  }//��ʼ��ListCtrlColumns
	virtual long InsertChildToListCtrl(CListCtrl *pListCtrl, long nBeginIndex=0);	//���Ӷ�����뵽�б���ͼ��
	virtual long InsertToListCtrl(CListCtrl *pListCtrl, long lItemIndex=0);	// ��������뵽�б���ͼ��
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);	// ��������뵽�б���ͼ��
	virtual PFuc_InitListCtrlColumns* GetInitListCtrlColumnsFunc()	{	return NULL;	}

	//ComboBox���
	virtual long InsertComboBox(CComboBox *pComboBox);
	virtual long InsertChildreComboBox(CComboBox *pComboBox);

	//ListBox���
	virtual long InsertListBox(CListBox *pListBox);
	virtual long InsertChildreListBox(CListBox *pListBox);

	virtual DWORD Filter(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD FilterOwn(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD FilterChildren(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD Filter_ID(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD FilterOwn_ID(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD FilterChildren_ID(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	//shaolei 20200204 id��nameͬʱ���ˣ�id����
	virtual DWORD Filter_ID_Name(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD FilterOwn_ID_Name(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD FilterChildren_ID_Name(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	//shaolei 20200228 id��nameͬʱ���ˣ�id����,�����ִ�Сд
	virtual DWORD Filter_ID_Name_NoCase(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD FilterOwn_ID_Name_NoCase(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD FilterChildren_ID_Name_NoCase(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);

#ifndef NO_XDbBaseLib
//////////////////////////////////////////////////////////////////////////
//���ݿⶨ�岿��  begin
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

	//������
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	//д����
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);

	//�����Ӷ���
	virtual CExBaseObject* DB_CreateNewChild()		{	return NULL;		}

	//�������ݿ��е�ֵ����BaseObject�е��ֶ����sql���д�����ݿ���
	virtual BOOL DB_Update(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys) ;
	virtual BOOL DB_Update_Children(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL DB_Update_Cmd(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys) ;
	
	//�����ݿ���ɾ��һ����¼,��ʱBaseList��deleteһ���Ӷ���
	virtual BOOL DB_Delete(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL DB_Delete_Own(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL DB_DeleteChildren(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys);

	//��BaseObject�е��ֶ����sql���д�����ݿ���
	virtual BOOL DB_Insert(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask) ;
	virtual BOOL DB_Insert_Cmd(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys) ;
	virtual BOOL DB_Insert_Own(CXDbBaseLib *pXDbLib, CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask) ;
	virtual BOOL DB_Insert_Children(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask);
	 
	//���SQL���
	virtual BOOL DB_GetSQL_Select_Own(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString &strSQL);
	virtual BOOL DB_GetSQL_Select_Childrenren(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString &strSQL);
	virtual BOOL DB_GetSQL_Select_Childrenren_ForeignKey(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString &strSQL);
	
	virtual BOOL DB_GetSQL_Insert(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CString &strSQL);

	//û�ҵ��������ݿ⣬����FALSE,�ҵ������¶��󣬷���TRUE
	virtual BOOL DB_UpdateOrInsert(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys
									,BOOL bInsert=TRUE, CString strSQL=_T("")
									,BOOL bUpdateSelf=TRUE);

	virtual BOOL DB_Select_OwnEx(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys
									, CString strQuerySql=_T(""));
	//û�ҵ��������ݿ⣬�ҵ��������ݿ⣬���ز������
	virtual BOOL DB_Insert(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys
								, CString strQuerySql=_T(""));
	//���ݿⶨ�岿��  end

public:
	virtual long DB_WriteFields_BlobBinary(CXDbRecordsetBase *pRecordset, BSTR bstrKey);
	virtual long DB_WriteFields_BlobXML(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys, BSTR bstrKey);

	//Լ������������pTempListָ�벻Ϊ�գ����ʾBLOB�洢��Ϊ������Ӷ��󣬷���Ϊ�������
	virtual long DB_ReadFields_BlobBinary(CXDbRecordsetBase *pRecordset, BSTR bstrKey);
	virtual long DB_ReadFields_BlobXML(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys, 
		BSTR bstrKey, CExBaseList *pTempList);

	//�����������������Զ���ŵı���Ҫ���ش˺���
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset);
	//�������������������Ӷ������
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
	//ɾ���Ӷ��󣬲���ճ�Աָ��
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

	//ͨ��Name�γɵ�·���������Ӷ���  shaolei 20220527
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
	
////���������
public:
	virtual CString GetXLangID();
	virtual void GetXLangID(CString &strLangID);

public:
	virtual void CalObjSize(BOOL bCalChild, long &nObjCount, long &nTotalSize, CFile *pFile);
	virtual void CalChildrenSize(BOOL bCalChild, long &nObjCount, long &nTotalSize, CFile *pFile);
};


#endif // !defined(_EXBASEOBJECT_H__)

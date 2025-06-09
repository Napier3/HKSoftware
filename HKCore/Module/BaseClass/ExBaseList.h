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
//���Զ���

//����
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

	//���������л�
	virtual long SerializeChildren(CBinarySerialBuffer &oBinaryBuffer);
	
    //�ļ����οؼ���صĲ���
	virtual long InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);
	
	//�б�ؼ�����
	virtual long InsertChildToListCtrl(CListCtrl *pListCtrl, long nBeginIndex=0); 	//���Ӷ�����뵽�б���ͼ��
	virtual long UpdateChildListCtrl(CListCtrl *pListCtrl, long nBeginIndex=0); 	//���Ӷ�����뵽�б���ͼ��
	virtual long UpdateChildListCtrlIndex(CListCtrl *pListCtrl, long nBeginIndex=0); 	//���Ӷ�����뵽�б���ͼ��

	virtual long InsertChildreComboBox(CComboBox *pComboBox); 
	virtual long InsertChildreListBox(CListBox *pListBox);

#ifndef NO_XDbBaseLib
    //Mysql���  begin
	//�����ݿ��в��Һ��ʵ����ݼ�
	virtual BOOL DB_SelectChildren(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask);
	virtual BOOL DB_Select(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask);
	virtual BOOL DB_DeleteChildren(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL DB_Insert_Children(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys, CXDbQueryChildrenMask *pXdbQueryMask);
	//�������������������Ӷ������
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
	//ɾ���Ӷ��󣬲���ճ�Աָ��
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
	//shaolei 20200204 id��nameͬʱ���ˣ�id����
	virtual DWORD FilterChildren_ID_Name(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	//shaolei 20200228 id��nameͬʱ���ˣ�id���ȣ������ִ�Сд
	virtual DWORD FilterChildren_ID_Name_NoCase(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual void RemoveTail(UINT nRemoveClassID, long nCountRemove, CExBaseList &oListRemove);

	virtual void InitReserved(DWORD dwReserved=0x0FFFFFFF);
	virtual void InitItemData(DWORD dwItemData=0x0FFFFFFF);

public:
	//����·�����ҽڵ�
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
	//ͨ��Name�γɵ�·���������Ӷ���  shaolei 20220527
	virtual long FindByPathChildren_Name(CString &strPath, CExBaseList &oListDest, TCHAR chSeperator);
	void SortByID();

////���������
public:
	virtual CString GetXLangID(CExBaseObject *pChildObj);
	virtual void GetXLangID(CExBaseObject *pChildObj, CString &strLangID);

//2019-4-17  lijunqing,���ڱ༭��ʱ����֤�����Ƿ���Ч
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

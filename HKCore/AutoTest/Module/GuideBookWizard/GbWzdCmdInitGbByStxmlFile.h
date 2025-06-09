#pragma once

#include "GbWzdCmd.h"
#include "GbInsertStxmlFileTool.h"

//m_strName： 子模板的文件名
//m_strID：   子模板的路径（相对路径）
class CGbWzdCmdInitGbByStxmlFile : public CGbWzdCmdList
{
public:
	CGbWzdCmdInitGbByStxmlFile();
	virtual ~CGbWzdCmdInitGbByStxmlFile();

	virtual UINT GetClassID()			{		return GBWZDCLASSID_INITGBBYSTXML;	} 
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey() ;

	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();
	virtual void InitAfterRead();

	void SelectRootItems();

public:
	CExBaseList *m_pRootItems;

	//父项目的，名称路径、ID路径
	CString     m_strRootItemsNamePath;
	CString     m_strRootItemsIDPath;
	CExBaseObject *m_pWzdAutoTemplateRef;

public:
	virtual BOOL Execute(DWORD dwExecMode);
	virtual void GetCmdInfor(CString &strText);
	void InitGbItemEditCmds();
	BOOL SetRootItems(CExBaseList *pRootItems);
	CExBaseList* GetRootItems()	{	return m_pRootItems;	}
	BOOL OnGbNodeSelChange(CExBaseObject *pGbNode);
	//CGbInsertStxmlFileTool* GetGbInsertStxmlFileTool()	{	return &m_oGbInsertStxmlTool;	}
	CGbInsertStxmlFileTool* GetGbInsertStxmlFileTool();

	void InitGbInsertStxmlFileToolOwn();

protected:
	//CGbInsertStxmlFileTool m_oGbInsertStxmlTool;
	CGbInsertStxmlFileTool *m_pReadStxmlTool;
	CGbInsertStxmlFileTool *m_pGbInsertStxmlTool;
	void InitCmd();
	BOOL IsNeedEditItems(CExBaseObject *pItem);
	BOOL IsNeedEditItem(CExBaseObject *pItem);
	void InsertEditItemsGbCmd(CExBaseList *pList);

	void FreeStxmlTool()
	{
		if (m_pReadStxmlTool != NULL)
		{
			Delete(m_pReadStxmlTool);
			m_pReadStxmlTool = NULL;
		}
	}
};

CXKeyDB* GbWzd_GetXKeyDB();

#pragma once

#include "FileToolInterface.h"

static const CString g_strSetsFileFilter = _T("");


class CFileToolCreator : public CExBaseObject
{
public:
	CFileToolCreator(const CString &strName,const CString &strFilePostFix, PFILETOOLCREATE* pFunCreate)
	{
		m_strName = strName;
		m_strID = strFilePostFix;
		m_pFunCreate = pFunCreate;
	}
	
	virtual ~CFileToolCreator(void){};

	CFileToolInterface* Create()
	{
		CFileToolInterface *pFileTool = m_pFunCreate();
		pFileTool->m_strName = m_strName;
		pFileTool->m_strID = m_strID;
		return pFileTool;
	}

private:
	//m_strID, 文件后缀
	//m_strName, 文件描述，说明
	PFILETOOLCREATE* m_pFunCreate;

};


class CFileToolsFactory : public CExBaseList
{
public:
	CFileToolsFactory(void);
	~CFileToolsFactory(void);

	virtual BOOL ExportFile(CExBaseObject *pObject, CWnd *pParentWnd, const CString &strPath, LPDISPATCH lpDispatch=NULL);
	virtual BOOL ImportFile(CExBaseObject *pObject, CWnd *pParentWnd, const CString &strPath, LPDISPATCH lpDispatch=NULL);

	virtual BOOL ExportFile(CExBaseObject *pObject, const CString &strFile, LPDISPATCH lpDispatch=NULL);
	virtual BOOL ImportFile(CExBaseObject *pObject, const CString &strFile, LPDISPATCH lpDispatch=NULL);

protected:
	virtual CFileToolCreator* RegisterCreator(const CString &strName,const CString &strFilePostFix, PFILETOOLCREATE* pFunCreate); 
	CFileToolInterface* CreateTool(const CString &strFile);
	void GetAllFilters(CString &strFilter);

	virtual void AfterImportFile(CExBaseObject *pRefObject, CExBaseObject *pNewObject) = 0;

protected:
	CExBaseList m_listFileTool;
};


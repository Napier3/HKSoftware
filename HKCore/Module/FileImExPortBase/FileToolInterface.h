#pragma once

#include "../BaseClass/ExBaseList.h"

//	szFilter.Format(_T("%s(*%s)|*%s||"),m_strPostFixDes,m_strFilePostfix,m_strFilePostfix);

class CFileToolInterface : public CExBaseList
{
public:
	CFileToolInterface(void)	
	{	
		m_pNewObject = NULL;
		m_pRefObject = NULL;	
	};

	virtual ~CFileToolInterface(void)	
	{
		if(m_pNewObject != NULL)
		{
			delete m_pNewObject;
			m_pNewObject = NULL;
		}
	};

	virtual BOOL ExportFile(const CString &strFile, LPDISPATCH lpDispatch=NULL) = 0;
	virtual BOOL ImportFile(const CString &strFile, LPDISPATCH lpDispatch=NULL) = 0;

protected:
	//m_strID, 文件后缀
	//m_strName, 文件描述，说明
	CExBaseObject *m_pRefObject;
	CExBaseObject *m_pNewObject;

public:
	void SetRefObject(CExBaseObject *pObj)
	{
		m_pRefObject = pObj;
	}

	CExBaseObject* GetRefObject()
	{
		return m_pRefObject;
	}

	CExBaseObject* GetNewObject()
	{
		return m_pNewObject;
	}
};

typedef CFileToolInterface* (PFILETOOLCREATE)();

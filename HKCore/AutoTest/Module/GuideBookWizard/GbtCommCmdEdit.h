#pragma once

#include "GbInsertStxmlFileToolDefine.h"

class CGbInsertStxmlFileTool;

//////////////////////////////////////////////////////////////////////////
//通讯命令的处理
class CGbtCommCmdItemEditExpand : public CExBaseObject
{
public:
	CGbtCommCmdItemEditExpand();
	virtual ~CGbtCommCmdItemEditExpand();
	long m_bSelect;

public:
	virtual CBaseObject* Clone();
	virtual UINT GetClassID() {    return GBTWZDCLASSID_COMMCMDEDITEXPAND;   }
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbtCommCmdItemEditExpandKey();     }

public:
	void InitByCopy(CGbtCommCmdItemEditExpand *pSrc);

};

//////////////////////////////////////////////////////////////////////////
//CGbtCommCmdItemEdit
class CGbtCommCmdItemEdit : public CExBaseList
{
public:
	CGbtCommCmdItemEdit();
	virtual ~CGbtCommCmdItemEdit();
	CExBaseObject *m_pCommCmdRef;
	CString m_strCommCmdItemPath;
	CString m_strDatasetPath;

	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_COMMCMDEDIT;   }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbtCommCmdItemEditKey();     }
	CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

public:
	void InitByCopy(CGbtCommCmdItemEdit *pSrc);
	CGbtCommCmdItemEditExpand* AddNewEdit(const CString &strDatasetPath);
	void EditCommCmdItem();
};


class CGbtCommCmdItemEditMngr : public CExBaseList
{
public:
	CGbtCommCmdItemEditMngr();
	virtual ~CGbtCommCmdItemEditMngr();

	CGuideBook *m_pGuideBookDest;
	CExBaseList m_listDataset;

public:
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_COMMCMDEDITMNGR;   }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbtCommCmdItemEditMngrKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

public:
	void InitGuideBookDest(CGuideBook *pGuideBook);
	void InitGbtCommCmdItemEdit(CGuideBook *pGuideBook);
	void InitGbtCommCmdItemEdit(CExBaseList *pList);
	CGbtCommCmdItemEdit* GbtCommCmdItemEdit(CCommCmd *pCommCmd);

	void InitByCopy(CGbtCommCmdItemEditMngr *pSrc);
	CGbtCommCmdItemEdit* FindGbtCommCmdItemEdit(const CString &strPath);
	CDataSet* FindDatasetByDsID(const CString &strDsID, CExBaseList &listDataset);

	void EditCommCmdItems();
};

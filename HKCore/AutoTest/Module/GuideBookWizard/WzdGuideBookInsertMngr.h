#pragma once

#include "GbInsertStxmlFileToolDefine.h"

//////////////////////////////////////////////////////////////////////////
//

class CWzdGuideBookItemsRef : public CExBaseObject
{
public:
	CWzdGuideBookItemsRef();
	virtual ~CWzdGuideBookItemsRef();
	long m_nUse;
	CString m_strValue;

	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_BATCHITEMREFVALUE;   }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CValueKey();     }
};


class CWzdInsertItemsLevel : public CExBaseList
{
public:
	CWzdInsertItemsLevel();
	virtual ~CWzdInsertItemsLevel();
	UINT m_nRefItemClassID;
	CString m_strDatasetPath;

	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_BATCHITEMREF;   }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CWzdInsertItemsLevelKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	void InitByCopy(CWzdInsertItemsLevel *pSrc);

	long GetUsedBatchItemRefValues(CExBaseList &oListValue);
	void InitBatchItemRef(CValues *pValues);
};

//测试项目的一个序列，一个组别，循环添加（枚举）的一个环节
class CWzdGuideBookInsertMngr : public CExBaseList
{
public:
	CWzdGuideBookInsertMngr();
	virtual ~CWzdGuideBookInsertMngr();

	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_BTACHITEMGROUP;   }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CWzdGuideBookInsertMngrKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	void InitByCopy(CWzdGuideBookInsertMngr *pSrc);

public:
	CWzdInsertItemsLevel* NewBatchItemRef(CExBaseObject *pItem);

	BOOL HasBatchItems();
	BOOL IsAllCommCmdItems();
	BOOL IsAllMacroTestItems();
	long GetValuesCount();
	void SetBatchItemRefDatasetPath(long nItemRefIndex, const CString &strDatasetPath);
	BOOL ValidateBatchItemsGroup(CString &strErrorMsg);
	long GetUsedBatchItemRefValues(CExBaseList &oListValue);
	void ChangeBatchItemRefValueSel(long nItemRefIndex, CWzdGuideBookItemsRef *pValue);

protected:
	CWzdInsertItemsLevel* NewBatchItemRef_CommCmd(CExBaseObject *pItem);


};


//管理对象，实现对CWzdGuideBookInsertMngr的管理
class CGbInsertGbxmlFileTool : public CExBaseList
{
public:
	CGbInsertGbxmlFileTool();
	virtual ~CGbInsertGbxmlFileTool();
	long m_nBatchVariableMode;
	long m_nBatchItemsMode;


	virtual UINT GetClassID() {    return GBTWZDCLASSID_BTACHITEMGROUPS;   }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbInsertGbxmlFileToolKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();

	void InitByCopy(CGbInsertGbxmlFileTool *pSrc);

	CWzdGuideBookInsertMngr *m_pGbtBatchItemGroupRef;

public:
	void InitListBatchItem(CGuideBook *pGuideBook);
	CWzdGuideBookInsertMngr* NewBatchItemGroup();
	BOOL HasBatchItems();
	BOOL IsAllCommCmdItems();
	BOOL IsAllMacroTestItems();
	void SetBatchItemRefDatasetPath(long nItemRefIndex, const CString &strDatasetPath);
	BOOL ValidateBatchItemsGroups(CString &strErrorMsg);
	void ChangeBatchItemRefValueSel(long nItemRefIndex, CWzdGuideBookItemsRef *pValue);

private:
	void InitListBatchItemRef(CExBaseList *pList);
};

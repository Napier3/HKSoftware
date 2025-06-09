#pragma once

#include "GbInsertStxmlFileToolDefine.h"

class CGbInsertStxmlFileTool;

#define BATCHMODE_ITEM         0
#define BATCHMODE_GBTDATA      1

//////////////////////////////////////////////////////////////////////////
//批量添加
//拥有m_nBatchItem==1的测试项目的引用

class CGbtBatchItemRefValue : public CExBaseObject
{
public:
	CGbtBatchItemRefValue();
	virtual ~CGbtBatchItemRefValue();
	long m_nUse;
	CString m_strValue;
	CString m_strRelValue;

	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_BATCHITEMREFVALUE;   }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CValueKey();     }

	void InitReplace()	{	m_strRelValue = m_strValue;	}
};


class CGbtBatchItemRef : public CExBaseList
{
public:
	CGbtBatchItemRef();
	virtual ~CGbtBatchItemRef();
	UINT m_nRefItemClassID;
	CString m_strDatasetPath;

	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_BATCHITEMREF;   }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbtBatchItemRefKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	void InitByCopy(CGbtBatchItemRef *pSrc);

	long GetUsedBatchItemRefValues(CExBaseList &oListValue);
	void InitBatchItemRef(CValues *pValues);
	void InitReplace();
};

//测试项目的一个序列，一个组别，循环添加（枚举）的一个环节
class CGbtBatchItemGroup : public CExBaseList
{
public:
	CGbtBatchItemGroup();
	virtual ~CGbtBatchItemGroup();

	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_BATCHITEMGROUP;   }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbtBatchItemGroupKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	virtual void InitByCopy(CGbtBatchItemGroup *pSrc);

public:
	virtual long GetValuesCount();
	virtual BOOL ValidateBatchItemsGroup(CString &strErrorMsg);

public:
	CGbtBatchItemRef* NewBatchItemRef(CExBaseObject *pItem);

	BOOL HasBatchItems();
	BOOL IsAllCommCmdItems();
	BOOL IsAllMacroTestItems();
	void SetBatchItemRefDatasetPath(long nItemRefIndex, const CString &strDatasetPath);
	long GetUsedBatchItemRefValues(CExBaseList &oListValue);
	void ChangeBatchItemRefValueSel(long nItemRefIndex, CGbtBatchItemRefValue *pValue);

	void InitReplace();

protected:
	CGbtBatchItemRef* NewBatchItemRef_CommCmd(CExBaseObject *pItem);


};


class CGbtBatchGbtDataRef : public CExBaseObject
{
public:
	CGbtBatchGbtDataRef();
	virtual ~CGbtBatchGbtDataRef();
	CString m_strGbtDataValue;

	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_BATCHGBTDATA;   }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbtBatchGbtDataRefKey();     }

	void InitByCopy(CGbtBatchGbtDataRef *pSrc);
	void InitBatchItemRef(CGbtData *pGbtData);
	void InitReplace();
};


class CGbtBatchGbtDataGroup : public CGbtBatchItemGroup
{
public:
	CGbtBatchGbtDataGroup();
	virtual ~CGbtBatchGbtDataGroup();

public:
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_BATCHGBTDATAGROUP;   }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbtBatchGbtDataGroupKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	virtual void InitByCopy(CGbtBatchItemGroup *pSrc);

public:
	virtual long GetValuesCount();
	virtual BOOL ValidateBatchItemsGroup(CString &strErrorMsg);

public:
	CGbtBatchGbtDataRef* NewBatchGbtDataRef(CExBaseObject *pData);

	BOOL HasBatchItems();
	BOOL IsAllCommCmdItems();
	BOOL IsAllMacroTestItems();
	void SetBatchItemRefDatasetPath(long nItemRefIndex, const CString &strDatasetPath);
	long GetUsedBatchItemRefValues(CExBaseList &oListValue);
	void ChangeBatchItemRefValueSel(long nItemRefIndex, CGbtBatchItemRefValue *pValue);

	void InitReplace();
	void InitByGbtDatas(CGbtDatas *pGbtDatas);
};

#define BATCH_ITEMS_MODE_EXTERNER   0
#define BATCH_ITEMS_MODE_INTERNAL   1


//管理对象，实现对CGbtBatchItemGroup的管理
class CGbtBatchItemGroups : public CExBaseList
{
public:
	CGbtBatchItemGroups();
	virtual ~CGbtBatchItemGroups();
	long m_nBatchVariableMode;     //批量处理的模式：项目模式、接口数据模式
	long m_nBatchItemsMode;        //批量项目插入的位置方式


	virtual UINT GetClassID() {    return GBTWZDCLASSID_BATCHITEMGROUPS;   }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbtBatchItemGroupsKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();

	void InitByCopy(CGbtBatchItemGroups *pSrc);

	CGbtBatchItemGroup *m_pGbtBatchItemGroupRef;

public:
	void InitListBatchItem(CGuideBook *pGuideBook);
	CGbtBatchItemGroup* NewBatchItemGroup();
	void SetBatchItemGroupCount(long nCount);
	BOOL HasBatchItems();
	BOOL IsAllCommCmdItems();
	BOOL IsAllMacroTestItems();
	void SetBatchItemRefDatasetPath(long nItemRefIndex, const CString &strDatasetPath);
	BOOL ValidateBatchItemsGroups(CString &strErrorMsg);
	void ChangeBatchItemRefValueSel(long nItemRefIndex, CGbtBatchItemRefValue *pValue);

	BOOL IsBatchGbtDataMode();
	BOOL IsBatchItemMode();
private:
	void InitListBatchItemRef(CExBaseList *pList);

	void FreeBatchItemGroupRef()
	{
		if (m_pGbtBatchItemGroupRef != NULL)
		{
			delete m_pGbtBatchItemGroupRef;
			m_pGbtBatchItemGroupRef = NULL;
		}
	}
};

#pragma once

#include "SysParaEdit.h"
#include "Cpus.h"
#include "Device.h"

class CSysParaEditGroup : public CExBaseList
{
public:
	CSysParaEditGroup();
	virtual ~CSysParaEditGroup();
	CExBaseObject *m_pObjectRef;  //指向具体的数据管理对象
	UINT m_nClassID;
	//子对象为数据对象

public:
	virtual UINT GetClassID()			{		return GBCLASSID_SYSPARAEDITGROUP;		}
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{		return CGbXMLKeys::g_pGbXMLKeys->m_strSysParaEditGroupKey;	}

	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

public:
	void Release(BOOL bDatasIsRef);
	void AddToValues(CValues *pValues);
	void InitValues(CSysParaEditGroup *pSrcGroup);

private:
	void AddToValues_Sets(CValues *pValues);
	void AddToValues_Datas(CValues *pValues);

	void InitValues_Sets(CSysParaEditGroup *pSrcGroup);
	void InitValues_Datas(CSysParaEditGroup *pSrcGroup);
};

class CSysParaEditGroups : public CExBaseList
{
public:
	CSysParaEditGroups();
	virtual ~CSysParaEditGroups();

	CSysParaEdit *m_pSysParaEdit;
	CValues *m_pValues;

public:
	virtual UINT GetClassID()			{		return GBCLASSID_SYSPARAEDITGROUPS;		}
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{		return CGbXMLKeys::g_pGbXMLKeys->m_strSysParaEditGroupsKey;	}

	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

public:
	void InitSysParaEditGroups(CSysParaEdit *pSysParaEdit);
	void Release(BOOL bDatasIsRef);
	CValues* GetReportValues();
	void InitValues(CSysParaEditGroups *pSrcGroups);

private:
	void InitMngr();
	void InitMngrDatas_Sets(const CString &strType);
	void InitMngrDatas_ShortDatas(const CString &strType);
	CSet* SelectSet(const CString &strType, CCpus *pCpus, const CString &strPath, CExBaseList *pList);
	CSysParaEditGroup* AddNewGroup(const CString &strName, const CString &strID, UINT nClassID);
};

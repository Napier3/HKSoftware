#pragma once

#include "GbItemBase.h"
#include "GuideBookDefine.h"
#include "ValParas.h"
#include "Msg.h"
#include "CommCmd.h"

class CSysParaEdit : public CGbItemBase
{
public:
	CSysParaEdit();
	virtual ~CSysParaEdit();
	virtual CGbItemBase* CloneForTempFile();

	static CSysParaEdit* _New(CBaseObject *pParent=NULL)
	{
		CSysParaEdit *pNew = new CSysParaEdit();
		pNew->InitAfterRead();
		return pNew;
	}

	//属性
public:
	CString m_strDatasetPath;
	CValues* m_pParas;
	CExBaseList m_oListMsgs;
	CExBaseList m_oListCommCmds;

public:
	//测试时临时数据链表
	//数据链表，保存需要编辑的数据
	CExBaseList m_oListDataTotal;
	CExBaseList m_oListDataEdit;

	CString InitDataList(long &nDatasCount);
	CValues* GetReportValues();
	CExBaseList* GetSysParaEditDataObjList()	{	return &m_oListDataEdit;	}
	CExBaseList* GetDatasetRef();

private:
	CExBaseList *m_pSysParaEditGroups;

	//公共接口
public:
	CExBaseList* GetSysParaEditGroup();
	CExBaseList* GetMsgs();
	CValues* GetParas();
	CExBaseList* GetCommCmds();
	virtual BOOL GetItemParaValue(const CString &strValueID, double &dValue);
	long SetItemParaValue(const CString & strValueID, const CString & strValue, BOOL bAddNew=FALSE);
	BOOL IsDeviceIndexPara(const CString &strID);

	void SetDatasetPath(const CString &strPath)							{		m_strDatasetPath = strPath;		}
	CString GetDatasetPath()										{		return m_strDatasetPath;		}


	//重写父类方法
public:
	virtual UINT GetClassID()			{		return GBCLASSID_SYSPARAEDIT;		}

	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{		return CGbXMLKeys::g_pGbXMLKeys->m_strSysParaEditKey;	}

	virtual void InitAfterRead();

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();

	virtual long CalTestTimeLong();

	//shaolei 20220607
	virtual void SetItemState(long nShow, long nEnable, long nSelect, BOOL bSetShow, BOOL bSetEnable, BOOL bSetSelect);

	virtual long GetItemTestCount();
	virtual void ClearReport(BOOL bBack=TRUE);
};
#pragma once

#include "GuideBookDefine.h"
#include "../../../Module/DataMngr/ShortData.h"
#include "../../../Module/DataMngr/DvmDataset.h"

class CDataObjValue :public CExBaseList
{
public:
	CDataObjValue(void);
	virtual ~CDataObjValue(void);

	static CDataObjValue* _New(CBaseObject *pParent=NULL)
	{
		CDataObjValue *pNew = new CDataObjValue();
		pNew->SetParent(pParent);
		return pNew;
	}

	CString  m_strDataTypeID;
	CString  m_strValue;

	//2021-10-13 lijunqing
	CString GetIDPath_Root_Dataset(const CString &strPathSp = _T("$"));

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_DATAOBJ_VALUE;		}
	virtual BSTR GetXmlElementKey() 	{		return CGbXMLKeys::g_pGbXMLKeys->m_strValueKey;     	}

	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

public:
	void GetIDForPath(CString &strID, const CString &strPathSp = _T("$"));
	CString GetIDForPath(const CString &strPathSp = _T("$"));

	void SetDataObjValue(CValues* pValues);
	void InitValueByData(CShortData *pData);
	void WriteToData(CValue *pData);

	void InitValueByData(CDvmValue *pData);
	void WriteToData(CDvmValue *pData);

	void AddToDvm(CDvmValue *pData);
	CString GetText()
	{
		if (m_strName.GetLength() > 1)
		{
			return m_strName;
		}
		else
		{
			return m_strID;
		}
	}

	void AddToValues(CValues *pValues);  //2021-10-18  lijunqing;
	void InitByValues(CValues *pValues, BOOL bUseReserved); //2021-10-18  lijunqing

	//模型更新  shaolei 20220716
	void UpdateDataObjValue(CDataObjValue *pSrcParentValue, BOOL bNewNotExist = TRUE);
	//shaolei 2022-12-06   CDataObjValue对象转换成CDvmValue对象
	void Data_Gb_to_Dvm(CDvmValue *pDestDvm);
};

BOOL DS_InStringDataPath(const CString &strText);


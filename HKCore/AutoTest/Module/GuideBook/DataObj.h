#pragma once

#include "GuideBookDefine.h"
#include "DataObjValue.h"
#include "../../../Module/DataMngr/DataGroup.h"
extern long g_nLog_TestControl_Msg;
extern CDataGroup *g_pGlobalDatas_Gb_CalParaExp;

class CDataObj :public CExBaseList
{
public:
	CDataObj(void);
	virtual ~CDataObj(void);

	static CDataObj* _New(CBaseObject *pParent=NULL)
	{
		CDataObj *pNew = new CDataObj();
		pNew->SetParent(pParent);
		return pNew;
	}

	CString  m_strDataType;
	CString  m_strUnit;
	CString  m_strValue;
	CString  m_strDefaultValue;
// 	CString m_strMinVal;
// 	CString m_strMaxVal;
	long    m_nDataIndex;
	
	double m_dMinVal;
	double m_dMaxVal;
	double m_dStepVal;

public:
	//Serialize mathods
	virtual long SerializeChildren(CBinarySerialBuffer &oBinaryBuffer);

	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_DATAOBJ;		}
	virtual BSTR GetXmlElementKey() 	{		return CGbXMLKeys::g_pGbXMLKeys->m_strDataKey;     	}
	virtual void InitAfterRead();

	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn,BOOL bCopyChildren);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

public:
	void GetIDForPath(CString &strID, const CString &strPathSp = _T("$"));
	CString GetIDForPath(const CString &strPathSp = _T("$"));

	//2021-10-13 lijunqing
	CString GetIDPath_Root_Dataset(const CString &strPathSp = _T("$"));

	void SetValue(const CString &strValue);
	void SetDataObjValue(CValues* pValues);
	void InitValueByData(CShortData *pData);
	void WriteToData(CShortData *pData);

	void InitValueByData(CDvmData *pData, BOOL bSetMinMax);
	void WriteToData(CDvmData *pData);
	
	void InitValueByData(CDataObj *pSrcData);

	void  AddToDvm(CDvmData *pData);
	CDataObjValue* FindValue(const CString &strIDHas);

	CDataTypes* GetDataTypes();
	CDataType*  GetDataType();
	BOOL GetValueByID(const CString &strValueID, CString &strValue);

	void ResetDvmValue();

	CDataObjValue* FindDataObjValueByID_Has(const CString &strIDPath);
	virtual long SelectDatas(const CString &strIDPath, CExBaseList &oListDest, const CString &strSeperator=_T("$"));

	BOOL CmpDataType(CDvmData *pDataSrc);
	BOOL CmpDataType(const CString &strDataType);
	CExBaseObject* FindValueObject(CExBaseList *pList);

	//2021-3-28  lijunqing   属性是否全部匹配
	BOOL IsAttrsMatch(CValues *pAttrs);

	CString GetDataObjPath();	//2021-10-13  lijunqing
	void AddToValues(CValues *pValues);//2021-10-18  lijunqing
	void InitByValues(CValues *pValues, BOOL bUseReserved);//2021-10-18  lijunqing
	//模型更新  shaolei 20220716
	void UpdateDataObjValue(CDataObj *pSrcDataObj, BOOL bNewNotExist = TRUE);

	//shaolei 2022-12-06   CDataObj对象转换成CDvmData对象
	void Data_Gb_to_Dvm(CDvmData *pDestDvm);
};

BOOL DS_InStringDataPath(const CString &strText);

//2021-10-14  lijunqing 从GbItemBase移到此处
BOOL Gb_CalParaExpression(const CString &strExpress, CExBaseList *pObjDevice, double &dValue, BOOL bLogError, CValues *pValues=NULL);
BOOL Gb_CalParaExpressionEx(const CString &strExpress, CExBaseList *pObjDevice, double &dValue, BOOL bLogError, CString &strValue);
CString Gb_CalValue(CExBaseObject *pDevice, CValue *pValue);
CString Gb_CalValue_MinMax(CExBaseObject *pDevice, CValue *pValue, double dValue);

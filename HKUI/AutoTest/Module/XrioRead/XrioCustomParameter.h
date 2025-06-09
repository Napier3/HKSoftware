#pragma once

#include "XrioCfgMngrGlobal.h"

// CXrioCustomParameter
class CXrioCustomParameter : public CExBaseList
{
public:
	CXrioCustomParameter();
	virtual ~CXrioCustomParameter();

	//CString m_strID; 
	CString m_strEnabled;
	CString m_strDescription;
	CString m_strForeignId;
	CString m_strDataType;
	CString m_strValue;
	CString m_strValueFormula;
	CString m_strMaxValue;
	CString m_strMinValue;
    CString m_strUnit;
//增加小数点位数属性，此变量应该在CXrioUnit类中，但是这个类不应作为CreateNewChild的一个子对象。现在暂时这样处理
//    <Parameter Id="ID_10_10">
//        <Name>Fault Freq Time</Name>
//        <Description>Fault Freq Time</Description>
//        <ForeignId>ID_10_10</ForeignId>
//        <DataType>Real</DataType>
//        <Value>3600</Value>
//        <MinValue>0</MinValue>
//        <MaxValue>9999</MaxValue>
//        <Unit DecimalPlaces="0">s</Unit>
//    </Parameter>
    CString m_strDecimalPlaces;

	//重载函数
public:
	virtual UINT GetClassID() {    return XRIOCLASSID_CUSTOMPARAMETER;   }
	virtual BSTR GetXmlElementKey()  {      return CXrioCfgMngrXmlRWKeys::CustomParameterKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual void InitAfterRead();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);

	BOOL GetParameterFullPath(CString &strValue);
	BOOL GetParameterValue(CString &strValue);
};


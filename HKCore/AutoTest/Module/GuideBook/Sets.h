#pragma once

#include "GuideBookDefine.h"
#include "Set.h"
#include "DataSet.h"

class CSets :public CExBaseList
{
public:
	CSets(void);
	virtual ~CSets(void);

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_SETS;		}
	virtual BSTR GetXmlElementKey()  ;

	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);

public:
	void SetSetsValue(CValues* pValues);

	void InitValueByDatas(CShortDatas *pDatas);
	void WriteToDatas(CShortDatas *pDatas);

public:
	void InitDataSet(CDataSet *pDataSet);
	void InitByDataSet(CDataSet *pDataSet, BOOL bAppend=FALSE);
};
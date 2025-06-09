#pragma once
#include "ResultRec.h"

class CResultsRec : public CExBaseList
{
public:
	CResultsRec();
	virtual ~CResultsRec();

	long m_nAllTipIndex;
	long m_nAllWarningIndex;
	long m_nAllErrorIndex;
	long m_nAllFatalErrorIndex;
	BOOL m_bExportRpt;

//÷ÿ‘ÿ∫Ø ˝
public:
	virtual UINT GetClassID() {    return SCLCLASSID_CHECK_DATA;   }
	void ResetRec();
	void Statis_AllResults();
//	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CRptCtrlsKey();     }

// #ifdef XML_USE_TINYXML
// 
// 	virtual long XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys);
// 	virtual long XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys);
// 	virtual long XmlWriteChildren(TiXmlElement *oElement, CXmlRWKeys *pXmlRWKeys);
// 
// #else
// 
// 	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
// 	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
// 	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
// 
// #endif
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BOOL CanPaste(UINT nClassID);

};


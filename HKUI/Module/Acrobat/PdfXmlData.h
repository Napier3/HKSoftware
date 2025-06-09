#pragma once

#include <math.h>
#include "ReadXmlData.h"
#include "PdfXmlParseGlobal.h"

#define		COL_SP		_T("SP")
#define		COL_DATA	_T("String")

class CPdfXmlData :	public CExBaseObject
{
public:
	CPdfXmlData(void);
	virtual ~CPdfXmlData(void);

	void AnalysisXmlData(CReadXmlData* pStringData, float fPageVpos);

	float CalWordWith();

public:
	float m_fHpos;
	float m_fVpos;
	float m_fWidth;
	float m_fHeight;

	float m_fHpos2;
	float m_fVpos2;

	CString m_sfont;

	long m_nCol; //2023-7-19  lijunqing 当前data所属于的col
	bool m_bSetCol;

public:
	virtual UINT GetClassID() {    return PDFPCLASSID_XML_STRING;   }
	virtual BSTR GetXmlElementKey()  {      return CPdfParseXmlRWKeys::StringDataKey();     }
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual long ValCmp(CBaseObject* pRightObj);
	virtual long ValCmp(CBaseObject* pRightObj, DWORD dwAttrID);

	virtual BOOL Copy(CBaseObject* pDest);

	BOOL AddColDataH(CBaseObject* pDest, const CString &strSP);
	void AddColDataMaxH(CBaseObject* pDest, CExBaseObject *pSatrt);
	void AddColDataV(CBaseObject* pDest);

};

#pragma once
#include "TXmlDatabase.h"
#include "XmlDatabase.h"
#include "TXmlDbTag.h"
#include "XmlDbData.h"

class CXmlDbMngr
{
public:
	CXmlDbMngr(void);
	~CXmlDbMngr(void);

	CTXmlDatabase *m_pTXmlDatabase;
	CXmlDatabase  *m_pXmlDatabase;
	CString m_strTDbFile;
	CString m_strDbFile;

	//查找自身的属性值
	CTXmlDbTag *GetTDbTag(const CString &strTTableID, const CString &strTTagID);
	BOOL GetAttrValue(CXmlDbData *pData, const CString &strAttrID, CString &strAttrData);

	//查找子对象
	CXmlDbData *FindChild(CXmlDbData *pParent, const CString &strAttrID, const CString &strAttrData);
};

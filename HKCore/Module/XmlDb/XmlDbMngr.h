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

	//�������������ֵ
	CTXmlDbTag *GetTDbTag(const CString &strTTableID, const CString &strTTagID);
	BOOL GetAttrValue(CXmlDbData *pData, const CString &strAttrID, CString &strAttrData);

	//�����Ӷ���
	CXmlDbData *FindChild(CXmlDbData *pParent, const CString &strAttrID, const CString &strAttrData);
};

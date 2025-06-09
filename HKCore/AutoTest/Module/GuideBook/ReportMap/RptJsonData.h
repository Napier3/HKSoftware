#pragma once

#include "../../Module/xml/json/CJSON.h"


class CRptJsonData : public CExBaseList
{
public:
	CRptJsonData(void);
	~CRptJsonData(void);

	CJSON* m_node;	//名称：m_node->string；值：m_node->valuestring；

private:
	CJSON* m_root;			//根节点

	char* ReadFile(const CString &strFile);
	void ReadItem(CJSON* Fitem, CRptJsonData* pParent);

public:
	virtual BOOL OpenXmlFile(const CString &strFile, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType = _PUGI_XML_TYPE_);	

	virtual BOOL SaveXmlFile(const CString &strFile, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType = _PUGI_XML_TYPE_);
};

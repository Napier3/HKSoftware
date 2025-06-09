#pragma once

#include "../../../AutoTest/ReportTemplateDev/resource.h"
#include "../GuideBookDefine.h"
#include "../GbDataTypeMngr.h"
#include "../../Module/xml/XmlRW_Pugi.h"
#include <map>
#include <vector>
#include "rpteditinterface.h"

using namespace std; 

typedef		pugi::xml_node					BDNode;
typedef		pugi::xml_attribute				BDAttB;
typedef		pugi::xml_attribute_struct		BDAttr;



class CXmlData : public CExBaseList
{
public:
	CXmlData();
	virtual ~CXmlData();

public:
	BDNode *m_xmlNode;

	vector<BDAttr*> m_vecAttri;
	void ReadNode(BDNode *xmlNode, map<CString, BDAttr*> *_mapBkmk);

	DWORD GetSelectBkmk(const CString &sSelectBkmk);
	BDAttr* GetBkmk(const CString &sSelectBkmk);

private:
	void ReadNodeAttribte(map<CString, BDAttr*> *_mapBkmk);
	void AddBkmk(BDAttr *attrTmp, map<CString, BDAttr*> *_mapBkmk);
	CImageList m_imageList;
};

class CXmlProssData : public CTLinkList<CXmlData> 
{
public:
	CXmlProssData(void);
	virtual ~CXmlProssData(void);

public:
	map<CString, BDAttr*> m_MapBkmks;

private:
	pugi::xml_document m_oXmlDoc;

public:
	BOOL OpenXmlFile(const CString &strFile);	
	BOOL SaveXmlFile(const CString &strFile);

	BOOL AddBkmk(BDAttr *cAttri, const CString &sBkmk);

	//Ìæ»»Ô­±êÇ©
	BOOL Replacekmk(const CString &sSelectBkmk, const CString &sNewBkmk);

	BOOL Deletekmk(const CString &sSelectBkmk);

	DWORD GetSelectBkmk(const CString &sSelectBkmk);

public:
	BOOL DataReplacekmk(const CString &sSelectBkmk, const CString &sData);

};

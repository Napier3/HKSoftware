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
	static int g_iXml_Find_ItemData;

	vector<BDAttr*> m_vecAttri;
	void ReadNode(BDNode *xmlNode, map<BDAttr*,CString> *_mapBkmk);

	DWORD GetSelectBkmk(const CString &sSelectBkmk,int iIndex = 0);
	BDAttr* GetBkmk(const CString &sSelectBkmk);

private:
	void ReadNodeAttribte(map<BDAttr*,CString> *_mapBkmk);
	void AddBkmk(BDAttr *attrTmp, map<BDAttr*,CString> *_mapBkmk);
	CImageList m_imageList;
};

class CXmlPathData: public CTLinkList<CXmlData> 
{
public:
	CXmlPathData(void);
	virtual ~CXmlPathData(void);
public:
	map<BDAttr*,CString> m_MapBkmks;

private:
	pugi::xml_document m_oXmlDoc;

public:
	BOOL OpenXmlFile(const CString &strFile);	
	BOOL SaveXmlFile(const CString &strFile);

	BOOL AddBkmk(BDAttr *cAttri, const CString &sBkmk);

	//Ìæ»»Ô­±êÇ©
	BOOL Replacekmk(BDAttr *cAttri, const CString &sNewBkmk);

	BOOL Deletekmk(BDAttr *cAttri);

	DWORD GetSelectBkmk(const CString &sSelectBkmk,int iIndex = 0);

public:
	BOOL DataReplacekmk(const CString &sSelectBkmk, const CString &sData);
};

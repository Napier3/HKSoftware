#pragma once

#include "../GuideBookDefine.h"
#include "../GbDataTypeMngr.h"
#include "../../Module/xml/json/CJSON.h"
#include "../../Module/xml/JsonRW.h"
#include <map>
#include "rpteditinterface.h"

using namespace std; 

class CJsonData : public CExBaseList
{
public:
	CJsonData();
	virtual ~CJsonData();

public:
	CJSON* m_node;
	static int g_iJson_Find_ItemData;

	void ReadNode(CJSON *jNode,map<CJSON*, CString> *_mapBkmk);

	DWORD GetSelectBkmk(const CString &sSelectBkmk, int iIndex = 0);

private:
	void AddBkmk(CJSON *jNode,map<CJSON*, CString> *_mapBkmk);
	bool is_str_utf8(const char* str);

	bool IsChinese(char *strutf8);
};

class CJsonPathData : public CTLinkList<CJsonData>
{
public:
	CJsonPathData(void);
	virtual ~CJsonPathData(void);

public:
	map<CJSON*, CString> m_MapBkmks;

public:
	BOOL OpenXmlFile(const CString &strFile);	
	BOOL SaveXmlFile(const CString &strFile);

	BOOL AddBkmk(CJSON *jNode, const CString &sBkmk);

	//替换原标签
	BOOL Replacekmk(CJSON *jNode, const CString &sNewBkmk);

	BOOL Deletekmk(CJSON *jNode);

	DWORD GetSelectBkmk(const CString &sSelectBkmk, int iIndex);
	void SetBkmk(CJSON *jNode, const CString &sBkmk);

private:
	CJSON* m_root;			//根节点
	char* ReadFile(const CString &strFile);

public:
	BOOL DataReplacekmk(const CString &sSelectBkmk, const CString &sData);
};

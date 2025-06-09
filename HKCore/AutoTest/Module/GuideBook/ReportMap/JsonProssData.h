#pragma once

#include "../GuideBookDefine.h"
#include "../GbDataTypeMngr.h"
#include "../../Module/xml/json/CJSON.h"
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

	void ReadNode(CJSON *jNode, map<CString, CJSON*> *_mapBkmk);

	DWORD GetSelectBkmk(const CString &sSelectBkmk);

private:
	void AddBkmk(CJSON *jNode, map<CString, CJSON*> *_mapBkmk);
	bool is_str_utf8(const char* str);

	bool IsChinese(char *strutf8);
	char * CJsonData::UTF8toANSI(char *strutf8);
};

class CJsonProssData : public CTLinkList<CJsonData>
{
public:
	CJsonProssData(void);
	virtual ~CJsonProssData(void);

public:
	map<CString, CJSON*> m_MapBkmks;

public:
	BOOL OpenXmlFile(const CString &strFile);	
	BOOL SaveXmlFile(const CString &strFile);

	BOOL AddBkmk(CJSON *jNode, const CString &sBkmk);

	//替换原标签
	BOOL Replacekmk(const CString &sSelectBkmk, const CString &sNewBkmk);

	BOOL Deletekmk(const CString &sSelectBkmk);

	DWORD GetSelectBkmk(const CString &sSelectBkmk);
	void SetBkmk(CJSON *jNode, const CString &sBkmk);

private:
	CJSON* m_root;			//根节点
	char* ReadFile(const CString &strFile);

public:
	BOOL DataReplacekmk(const CString &sSelectBkmk, const CString &sData);

};

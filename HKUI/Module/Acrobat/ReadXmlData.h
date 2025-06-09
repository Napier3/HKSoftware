#pragma once

#include "../../Module/xml/XmlRW_Pugi.h"
#include <vector>

using namespace std; 

typedef		pugi::xml_node					BDNode;
typedef		pugi::xml_attribute				BDAttB;
typedef		pugi::xml_attribute_struct		BDAttr;


class CPdfStringDatas : public CExBaseList
{
public:
	CPdfStringDatas();
	virtual ~CPdfStringDatas();

public:
	float m_fPageVpos;		//当前页面开始高度
	bool m_bAddString;		//是否由SP分割的合并

	float m_fBlockHeight;	//Block的高度
	int m_iBlockCount;		//Block计数

	float m_iMinHpos;		//首列最小Hpos

public:
	void ProssTextLine(CExBaseList *pData);

private:
	BOOL FindSameHposData(CExBaseObject *pParameter1);

	BOOL CheckXmlData(CExBaseObject *pParameter1, CExBaseObject *pParameter2);
	BOOL CheckContainData(CExBaseObject *pParameter1, CExBaseObject *pParameter2);
	BOOL CheckMergeData(CExBaseObject *pParameter1, CExBaseObject *pParameter2);
	BOOL CheckIntersectData(CExBaseObject *pParameter1, CExBaseObject *pParameter2);

	void AddXmlData(CExBaseObject *pParameter1);

	BOOL CheckDataChangeAfter();
	BOOL CheckEnterLine();

};


class CReadXmlData : public CExBaseList
{
public:
	CReadXmlData(void);
	~CReadXmlData(void);

	BOOL OpenXmlFile(const CString &strFile);

	void FindAllTextLine(CExBaseList* pTextLineList);

	vector<BDAttr*> m_vecAttri;

private:
	pugi::xml_document m_oXmlDoc;
	BDNode *m_xmlNode;	

	void ReadNode(BDNode *xmlNode);
	void ReadNodeAttribte();
	
};


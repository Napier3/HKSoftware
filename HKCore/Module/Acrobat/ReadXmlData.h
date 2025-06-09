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
	float m_fPageVpos;		//��ǰҳ�濪ʼ�߶�
	bool m_bAddString;		//�Ƿ���SP�ָ�ĺϲ�

	float m_fBlockHeight;	//Block�ĸ߶�
	int m_iBlockCount;		//Block����

	float m_iMinHpos;		//������СHpos

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


#include "StdAfx.h"
#include "XmlProssData.h"
CXmlData::CXmlData()
{
	m_xmlNode = NULL;
}
CXmlData::~CXmlData()
{
}

void CXmlData::ReadNode(BDNode *xmlNode, map<CString, BDAttr*> *_mapBkmk)
{
	m_xmlNode = xmlNode;
	if(m_xmlNode == NULL)
		return ;

	m_strName = m_xmlNode->name();

	ReadNodeAttribte(_mapBkmk);

	BDNode cur = m_xmlNode->first_child();			
	while (cur && cur != *m_xmlNode)
	{
		CXmlData* pObj = new CXmlData();
		pObj->SetParent(this);		
		AddTail(pObj);

		pObj->ReadNode(&cur, _mapBkmk);

		cur = cur.next_sibling();
	}
}

void CXmlData::ReadNodeAttribte(map<CString, BDAttr*> *_mapBkmk)
{
	if(m_xmlNode == NULL)
		return;

	m_vecAttri.clear();

	BDAttr *atttr = NULL;
	BDAttB attrTmp = m_xmlNode->first_attribute();
	for (; attrTmp; attrTmp = attrTmp.next_attribute())
	{
		atttr = attrTmp.internal_object();
		m_vecAttri.push_back(atttr);
		AddBkmk(atttr, _mapBkmk);	//只查找属性中是否包含标签信息
	}
}
void CXmlData::AddBkmk(BDAttr *attrTmp, map<CString, BDAttr*> *_mapBkmk)
{
	if(attrTmp)
	{
		BDAttB attriB(attrTmp);
		CString strKey(attriB.value());

		if(xml_CheckBkmk(strKey) == BMK_NULL)
			return ;
		_mapBkmk->insert(pair<CString, BDAttr*>(strKey, attrTmp));
	}
}

DWORD CXmlData::GetSelectBkmk(const CString &sSelectBkmk)
{
	DWORD hItem = 0;

	//于属性中查找
	vector<BDAttr*>::iterator attr = m_vecAttri.begin();
	for ( ; attr != m_vecAttri.end(); ++attr )
	{
		BDAttB attriB(*attr);
		CString strName(attriB.name());
		CString strValue(attriB.value());

		if(sSelectBkmk == strValue)
		{
			return this->m_dwItemData;
		}
	}

	//于子节点中查找
	CXmlData* pObj = NULL;
	POS pos = GetHeadPosition();
	while (pos != NULL)
	{
		pObj = (CXmlData*)GetNext(pos);
		if(pObj == NULL)
			return 0;
		
		hItem = pObj->GetSelectBkmk(sSelectBkmk);
		if(hItem != 0)
		{
			return hItem;
		}
	}

	return 0;
}
BDAttr *CXmlData::GetBkmk(const CString &sSelectBkmk)
{
	vector<BDAttr*>::iterator attr = m_vecAttri.begin();
	for ( ; attr != m_vecAttri.end(); ++attr )
	{
		BDAttB attriB(*attr);
		CString strName(attriB.name());
		CString strValue(attriB.value());

		if(sSelectBkmk == strValue)
		{
			return *attr;
		}
	}
	return NULL;
}
/***************************************************/
CXmlProssData::CXmlProssData(void)
{
	m_oXmlDoc.reset();
}

CXmlProssData::~CXmlProssData(void)
{
	DeleteAll();
	m_oXmlDoc.reset();
}

BOOL CXmlProssData::OpenXmlFile(const CString &strFile)
{
	
	if (!IsFileExist(strFile))
	{
		//2022-11-25  lijunqing
#ifdef _DEBUG
		CString strMsg = _T("File error :") + strFile;
		CLogPrint::LogString(XLOGLEVEL_ERROR, strMsg);
#endif
		return FALSE;
	}

	DeleteAll();
	m_MapBkmks.clear();

	BOOL bRet = FALSE;
	bRet = m_oXmlDoc.load_file(strFile.GetString());
	if(!bRet)
		return FALSE;

	CXmlData* pObj = new CXmlData();
	AddTail(pObj);

	pObj->ReadNode(&m_oXmlDoc, &m_MapBkmks);	

	return TRUE;
}

BOOL CXmlProssData::SaveXmlFile(const CString &strFile)
{
	if (strFile.GetLength() < 3)
	{
		return FALSE;
	}

	try
	{
		ClearFileReadOnlyAttr(strFile);

		CString strPath = GetPathFromFilePathName(strFile);
		CreateAllDirectories(strPath);

		m_oXmlDoc.save_file(strFile.GetString());
	}
	catch (...)
	{
		return FALSE;
	}
	
	return TRUE;
}

BOOL CXmlProssData::AddBkmk(BDAttr *cAttri, const CString &sBkmk)
{
	if(xml_CheckBkmk(sBkmk) == BMK_NULL)
		return FALSE;

	BDAttB attriB(cAttri);
	wchar_t *pstr = sBkmk.AllocSysString();
	attriB.set_value(pstr);

	m_MapBkmks.insert(pair<CString, BDAttr*>(sBkmk, cAttri));
	return TRUE;
}

BOOL CXmlProssData::Replacekmk(const CString &sSelectBkmk, const CString &sNewBkmk)
{
	if(xml_CheckBkmk(sNewBkmk) == BMK_NULL)
		return FALSE;

	map<CString, BDAttr*>::iterator it;  
    it = m_MapBkmks.find(sSelectBkmk);  
	if(it != m_MapBkmks.end())
	{
		BDAttr *cAttri = it->second;
		if(cAttri != NULL)
		{
			BDAttB attriB(cAttri);
			wchar_t *pstr = sNewBkmk.AllocSysString();
			attriB.set_value(pstr);
		}

		m_MapBkmks.erase(it); 
		m_MapBkmks.insert(pair<CString, BDAttr*>(sNewBkmk, cAttri));
		return TRUE;
	}

	return FALSE;
}
BOOL CXmlProssData::Deletekmk(const CString &sSelectBkmk)
{
	CString sNewBkmk = _T("");
	map<CString, BDAttr*>::iterator it;  
    it = m_MapBkmks.find(sSelectBkmk);  
	if(it != m_MapBkmks.end())
	{
		BDAttr *cAttri = it->second;
		if(cAttri != NULL)
		{
			BDAttB attriB(cAttri);
			wchar_t *pstr = sNewBkmk.AllocSysString();
			attriB.set_value(pstr);
		}

		m_MapBkmks.erase(it); 
		return TRUE;
	}

	return FALSE;
}

DWORD CXmlProssData::GetSelectBkmk(const CString &sSelectBkmk)
{
	CXmlData* pObj = (CXmlData*)GetHead();
	if(pObj == NULL)
		return 0;
	return pObj->GetSelectBkmk(sSelectBkmk);
}

//一次性替换
BOOL CXmlProssData::DataReplacekmk(const CString &sSelectBkmk, const CString &sData)
{
	map<CString, BDAttr*>::iterator it;  
    it = m_MapBkmks.find(sSelectBkmk);  
	if(it != m_MapBkmks.end())
	{
		BDAttr *cAttri = it->second;
		if(cAttri != NULL)
		{
			BDAttB attriB(cAttri);
			wchar_t *pstr = sData.AllocSysString();
			attriB.set_value(pstr);
		}

		m_MapBkmks.erase(it); 
		return TRUE;
	}

	return FALSE;
}

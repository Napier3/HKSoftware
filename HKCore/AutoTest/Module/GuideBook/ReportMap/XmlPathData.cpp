#include "StdAfx.h"
#include "XmlPathData.h"
int CXmlData::g_iXml_Find_ItemData = 0;

CXmlData::CXmlData()
{
	m_xmlNode = NULL;
}
CXmlData::~CXmlData()
{
}

void CXmlData::ReadNode(BDNode *xmlNode, map<BDAttr*,CString> *_mapBkmk)
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
void CXmlData::ReadNodeAttribte(map<BDAttr*,CString> *_mapBkmk)
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
void CXmlData::AddBkmk(BDAttr *attrTmp, map<BDAttr*,CString> *_mapBkmk)
{
	if(attrTmp)
	{
		BDAttB attriB(attrTmp);
		CString strKey(attriB.value());

		if(xml_CheckBkmk(strKey) != BMK_PATH)
			return ;
		_mapBkmk->insert(pair<BDAttr*,CString>(attrTmp,strKey));
	}
}
DWORD CXmlData::GetSelectBkmk(const CString &sSelectBkmk,int iIndex)
{
	DWORD hItem = 0;
	CString Count;
	//于属性中查找
	vector<BDAttr*>::iterator attr = m_vecAttri.begin();
	for ( ; attr != m_vecAttri.end(); ++attr )
	{
		BDAttB attriB(*attr);
		CString strName(attriB.name());
		CString strValue(attriB.value());

		if(sSelectBkmk == strValue)
		{
// 			Count.Format(_T("%d"),SelBkmk->GetCount()+1);
// 			CExBaseObject*tmp = SelBkmk->AddNew(Count,strValue);
// 			tmp->m_dwItemData = this->m_dwItemData;
			if(CXmlData::g_iXml_Find_ItemData == iIndex)
			{
				return this->m_dwItemData;
			}
			else
			{
				CXmlData::g_iXml_Find_ItemData++;
			}
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

		hItem = pObj->GetSelectBkmk(sSelectBkmk,iIndex);
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
CXmlPathData::CXmlPathData(void)
{
	m_oXmlDoc.reset();
}

CXmlPathData::~CXmlPathData(void)
{
	DeleteAll();
	m_oXmlDoc.reset();
}
BOOL CXmlPathData::OpenXmlFile(const CString &strFile)
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
BOOL CXmlPathData::SaveXmlFile(const CString &strFile)
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
BOOL CXmlPathData::AddBkmk(BDAttr *cAttri, const CString &sBkmk)
{
	if(xml_CheckBkmk(sBkmk) != BMK_PATH)
		return FALSE;

	BDAttB attriB(cAttri);
	wchar_t *pstr = sBkmk.AllocSysString();
	attriB.set_value(pstr);

	m_MapBkmks.insert(pair<BDAttr*,CString>(cAttri,sBkmk));
	return TRUE;
}
BOOL CXmlPathData::Replacekmk(BDAttr *cAttri, const CString &sNewBkmk)
{
	if(xml_CheckBkmk(sNewBkmk) != BMK_PATH)
		return FALSE;

	map<BDAttr*,CString>::iterator it;  
	it =m_MapBkmks.find(cAttri);  
	if(it != m_MapBkmks.end())
	{
		BDAttB attriB(cAttri);
		wchar_t *pstr = sNewBkmk.AllocSysString();
		attriB.set_value(pstr);

		m_MapBkmks.erase(it); 
		m_MapBkmks.insert(pair<BDAttr*,CString>(cAttri,sNewBkmk));
		return TRUE;
	}

	return FALSE;
}
BOOL CXmlPathData::Deletekmk(BDAttr *cAttri)
{
	CString sNewBkmk = _T("");
	map<BDAttr*,CString>::iterator it;  
	it = m_MapBkmks.find(cAttri);  
	if(it != m_MapBkmks.end())
	{
		BDAttB attriB(cAttri);
		wchar_t *pstr = sNewBkmk.AllocSysString();
		attriB.set_value(pstr);

		m_MapBkmks.erase(it); 
		return TRUE;
	}

	return FALSE;
}
DWORD CXmlPathData::GetSelectBkmk(const CString &sSelectBkmk,int iIndex)
{
	CXmlData* pObj = (CXmlData*)GetHead();
	if(pObj == NULL)
		return 0;

	CXmlData::g_iXml_Find_ItemData = 0;
	return pObj->GetSelectBkmk(sSelectBkmk,iIndex);
}

//一次性替换
BOOL CXmlPathData::DataReplacekmk(const CString &sSelectBkmk, const CString &sData)
{
	map<BDAttr*,CString>::iterator it;
	for(it=m_MapBkmks.begin(); it!=m_MapBkmks.end(); it++)
	{
		if(it->second == sData)
		{
			BDAttr *cAttri = it->first;
			BDAttB attriB(cAttri);
			wchar_t *pstr = sData.AllocSysString();
			attriB.set_value(pstr);
			m_MapBkmks.erase(it); 
		}
	}

	return FALSE;
}

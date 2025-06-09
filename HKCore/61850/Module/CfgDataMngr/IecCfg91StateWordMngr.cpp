//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfg91StateWordMngr.cpp  CIecCfg91StateWordMngr


#include "stdafx.h"
#include "IecCfg91StateWordMngr.h"
#include "../globaldatamngr/IecGlobalDataMngrGlobal.h"
#include "../../../Module/API/GlobalConfigApi.h"

CIecCfg91StateWordMngr::CIecCfg91StateWordMngr()
{
	//初始化属性
	m_pStateWord = NULL;
	m_pStDataTypeMngr = NULL;

	//初始化成员变量
}

CIecCfg91StateWordMngr::~CIecCfg91StateWordMngr()
{
}

long CIecCfg91StateWordMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfg91StateWordMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CIecCfg91StateWordMngr::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		UINT nClassID = p->GetClassID();

		if (nClassID == CFGCLASSID_CIECCFG91STATEWORD)
		{
			m_pStateWord = (CIecCfg91StateWord *)p;
		}
		else if (nClassID == DTMCLASSID_CDATATYPES)
		{
			m_pStDataTypeMngr = (CDataTypes*)p;
		}
	}
}

BOOL CIecCfg91StateWordMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecCfg91StateWordMngr *p = (CIecCfg91StateWordMngr*)pObj;

	return TRUE;
}

BOOL CIecCfg91StateWordMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfg91StateWordMngr *p = (CIecCfg91StateWordMngr*)pDest;

	return TRUE;
}

CBaseObject* CIecCfg91StateWordMngr::Clone()
{
	CIecCfg91StateWordMngr *p = new CIecCfg91StateWordMngr();
	Copy(p);
	return p;
}

long CIecCfg91StateWordMngr::XmlReadChildren(CXmlRWNodeListBase &oNodes, CXmlRWKeys *pXmlRWKeys)
{
	long nCount = oNodes.GetNodeNum();
	long nIndex = 0;
	CExBaseObject *pNew = NULL;
	CXmlRWNodeBase *pNode = NULL;
	//MSXML2::IXMLDOMNodePtr oNode = NULL;
	CString strNodeName;
	BOOL bAddToTail = TRUE;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pNode = oNodes.GetChild(nIndex);
		pNew = CExBaseList::CreateNewChild(*pNode, bAddToTail, pXmlRWKeys);

		if (pNew != NULL && bAddToTail)
		{
			pNew->SetParent(this);
			AddTail(pNew);
		}

		if (pNew)
		{
			UINT nClassID = pNew->GetClassID();

			if (nClassID == CFGCLASSID_CIECCFG91STATEWORD)
			{
				pNew->XmlRead(*pNode, pXmlRWKeys);
			}
			else if (nClassID == DTMCLASSID_CDATATYPES)
			{
				pNew->XmlRead(*pNode, CIecGlobalDataMngrXmlRWKeys::g_pXmlKeys);
			}
		}

		bAddToTail = TRUE;
	}

	return 0;
}

CExBaseObject* CIecCfg91StateWordMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfg91StateWordKey)
	{
		pNew = new CIecCfg91StateWord();
	}
	else if (strClassID == CIecGlobalDataMngrXmlRWKeys::CDataTypeMngrKey())
	{
		pNew = new CDataTypes();
	}

	return pNew;
}

CExBaseObject* CIecCfg91StateWordMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == CFGCLASSID_CIECCFG91STATEWORD)
	{
		pNew = new CIecCfg91StateWord();
	}
	else if (nClassID == DTMCLASSID_CDATATYPES)
	{
		pNew = new CDataTypes();
	}

	return pNew;
}

CIecCfg91StateWord* CIecCfg91StateWordMngr::GetIecCfg91StateWord()
{
	if (m_pStateWord == NULL)
	{
		m_pStateWord = new CIecCfg91StateWord();
		AddNewChild(m_pStateWord);
	}

	return m_pStateWord;
}

CDataTypes* CIecCfg91StateWordMngr::GetStDataTypeMngr()
{
	if (m_pStateWord == NULL)
	{
		m_pStDataTypeMngr = new CDataTypes();
		AddNewChild(m_pStDataTypeMngr);
	}

	return m_pStDataTypeMngr;
}

BOOL CIecCfg91StateWordMngr::InitStateWordMngr()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("CfgStateWordConfig.xml");
	return OpenXmlFile(strFile, GetXmlElementKey(), CCfgDataMngrXmlRWKeys::g_pXmlKeys);
}


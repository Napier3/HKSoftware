//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Analogs.cpp  CAnalogs


#include "stdafx.h"
#include "Analogs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAnalogs::CAnalogs()
{
	//初始化属性

	//初始化成员变量
}

CAnalogs::~CAnalogs()
{
}

long CAnalogs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAnalogs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAnalogs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CAnalogs::InitAfterRead()
{
}

BOOL CAnalogs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAnalogs *p = (CAnalogs*)pObj;

	return TRUE;
}

BOOL CAnalogs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAnalogs *p = (CAnalogs*)pDest;

	return TRUE;
}

CBaseObject* CAnalogs::Clone()
{
	CAnalogs *p = new CAnalogs();
	Copy(p);
	return p;
}

CBaseObject* CAnalogs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAnalogs *p = new CAnalogs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAnalogs::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CANALOG)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAnalogs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAnalogKey)
	{
		pNew = new CAnalog();
	}

	return pNew;
}

CExBaseObject* CAnalogs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CANALOG)
	{
		pNew = new CAnalog();
	}

	return pNew;
}
CExBaseObject* CAnalogs::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAnalog();

	return pNew;
}

BOOL CAnalogs::SetAllChMaps(CIecCfg92Data *pIecCfg92Data)
{
	POS pos = GetHeadPosition();
	CAnalog *pAnalog = NULL;

	while (pos != NULL)
	{
		pAnalog = (CAnalog *)GetNext(pos);

		if (!pAnalog->SetChMap(pIecCfg92Data->m_pCfgChs))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("模拟量通道(%s)在指定IEC配置控制块中未查找到."),pAnalog->m_strID);
		}
	}

	return TRUE;
}

BOOL CAnalogs::SetAllChMaps(CIecCfgDatasSMV *pSmvMngr)
{
	POS pos_analog = GetHeadPosition();
	CAnalog *pAnalog = NULL;
	BOOL bHasFind = FALSE;

	while (pos_analog != NULL)
	{
		pAnalog = (CAnalog *)GetNext(pos_analog);

		POS pos_iecfg_data = pSmvMngr->GetHeadPosition();
		CIecCfgDataBase *pIecCfgDataBase = NULL;
		bHasFind = FALSE;

		while (pos_iecfg_data != NULL)
		{
			pIecCfgDataBase = (CIecCfgDataBase *)pSmvMngr->GetNext(pos_iecfg_data);

			if (pSmvMngr->IsCfgData(pIecCfgDataBase->GetClassID()))
			{
				if (pAnalog->SetChMap(pIecCfgDataBase->m_pCfgChs))
				{
					bHasFind = TRUE;
					break;
				}
			}
		}

		if (!bHasFind)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("模拟量通道(%s)在IEC配置文件中未查找到."),pAnalog->m_strID);
		}
	}

	return TRUE;
}
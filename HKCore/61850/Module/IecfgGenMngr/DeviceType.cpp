//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DeviceType.cpp  CDeviceType


#include "stdafx.h"
#include "DeviceType.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDeviceType::CDeviceType()
{
	//初始化属性

	//初始化成员变量
}

CDeviceType::~CDeviceType()
{
}

long CDeviceType::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDeviceType::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDeviceType::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CDeviceType::InitAfterRead()
{
}

BOOL CDeviceType::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDeviceType *p = (CDeviceType*)pObj;

	return TRUE;
}

BOOL CDeviceType::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDeviceType *p = (CDeviceType*)pDest;

	return TRUE;
}

CBaseObject* CDeviceType::Clone()
{
	CDeviceType *p = new CDeviceType();
	Copy(p);
	return p;
}

CBaseObject* CDeviceType::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CDeviceType *p = new CDeviceType();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CDeviceType::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CGENRULE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CDeviceType::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCGenRuleKey)
	{
		pNew = new CGenRule();
	}

	return pNew;
}

CExBaseObject* CDeviceType::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CGENRULE)
	{
		pNew = new CGenRule();
	}

	return pNew;
}
long CDeviceType::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	return 0;
}

long CDeviceType::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	return 0;
}

CExBaseObject* CDeviceType::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CGenRule();

	return pNew;
}

BOOL CDeviceType::GenerateIecfgDevice(CIecCfgDevice *pIecfgDevice)
{
	CIecCfgDatasMngr *pIecCfgDatasMngr = (CIecCfgDatasMngr*)pIecfgDevice->FindByClassID(CFGCLASSID_CIECCFGDATASMNGR);

	if (pIecCfgDatasMngr == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前CIecCfgDevice对象中,缺少缺省CIecCfgDatasMngr对象."));
		return FALSE;
	}

	if (GetCount() <= 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前设备(name=%s;ID=%s;)配置生成规则对象为空."),m_strName,m_strID);
		return FALSE;
	}

	CIecCfgDatasMngr *pTmpIecfgDataMngr = (CIecCfgDatasMngr*)pIecCfgDatasMngr->Clone();//创建零序对象,用于后期clone结果为初始状态的CIecCfgDatasMngr
	POS pos = GetHeadPosition();
	CGenRule *pCurGenRule = (CGenRule*)GetNext(pos);

	if (!pCurGenRule->GenarateIecCfgDatasMngr(pIecCfgDatasMngr))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前设备(name=%s;ID=%s;)生成第一个子配置(name=%s;ID=%s;)失败."),m_strName,m_strID,pCurGenRule->m_strName,pCurGenRule->m_strID);
	}

	CIecCfgDatasMngr *pNew = NULL;

	while(pos)
	{
		pCurGenRule = (CGenRule*)GetNext(pos);

		pNew  = (CIecCfgDatasMngr*)pTmpIecfgDataMngr->Clone();
		pIecfgDevice->AddNewChild(pNew, TRUE);
		pIecfgDevice->InitSclRef(pNew);

		if (!pCurGenRule->GenarateIecCfgDatasMngr(pIecCfgDatasMngr))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前设备(name=%s;ID=%s;)生成子配置(name=%s;ID=%s;)失败."),m_strName,m_strID,pCurGenRule->m_strName,pCurGenRule->m_strID);
		}
	}

//	iecfg_SetModified(pNew, TRUE);
	delete pTmpIecfgDataMngr;
	return TRUE;
}
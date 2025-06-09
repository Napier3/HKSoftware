//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeParas.cpp  CEdgeParas


#include "stdafx.h"
#include "EdgeParas.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeParas::CEdgeParas()
{
	//初始化属性

	//初始化成员变量
}

CEdgeParas::~CEdgeParas()
{
}

long CEdgeParas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return CEdgeGroup::XmlReadOwn(oNode,pXmlRWKeys);
}

long CEdgeParas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return CEdgeGroup::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
}

long CEdgeParas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEdgeParas::InitAfterRead()
{
}

BOOL CEdgeParas::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeParas *p = (CEdgeParas*)pObj;

	return TRUE;
}

BOOL CEdgeParas::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeParas *p = (CEdgeParas*)pDest;

	return TRUE;
}

CBaseObject* CEdgeParas::Clone()
{
	CEdgeParas *p = new CEdgeParas();
	Copy(p);
	return p;
}

CBaseObject* CEdgeParas::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeParas *p = new CEdgeParas();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeParas::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CEDGEDATA)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CEDGEDEV)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CEDGEDISK)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CEDGEDISKLMT)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CEDGEFILE)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CEDGELINKS)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CEDGEMEM)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CEDGEMEMLMT)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CEDGEOS)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CEDGESIGN)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CEDGECPU)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CEDGECPULMT)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CEDGEMEMUSED)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CEDGELINKSTATE)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CEDGETEMPERATURE)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CEDGEREPPERIOD)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CEDGEDEVICEINFOS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEdgeParas::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEdgeDataKey)
	{
		pNew = new CEdgeData();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeDevKey)
	{
		pNew = new CEdgeDev();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeDiskKey)
	{
		pNew = new CEdgeDisk();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeDiskLmtKey)
	{
		pNew = new CEdgeDiskLmt();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeFileKey)
	{
		pNew = new CEdgeFile();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeLinksKey)
	{
		pNew = new CEdgeLinks();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeMemKey)
	{
		pNew = new CEdgeMem();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeMemLmtKey)
	{
		pNew = new CEdgeMemLmt();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeOSKey)
	{
		pNew = new CEdgeOS();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeSignKey)
	{
		pNew = new CEdgeSign();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeCpuKey)
	{
		pNew = new CEdgeCpu();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeCpuLmtKey)
	{
		pNew = new CEdgeCpuLmt();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeMemUsedKey)
	{
		pNew = new CEdgeMemUsed();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeLinkStateKey)
	{
		pNew = new CEdgeLinkState();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeTemperatureKey)
	{
		pNew = new CEdgeTemperature();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeRepPeriodKey)
	{
		pNew = new CEdgeRepPeriod();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeDeviceInfosKey)
	{
		pNew = new CEdgeDeviceInfos();
	}

	return pNew;
}

CExBaseObject* CEdgeParas::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CEDGEDATA)
	{
		pNew = new CEdgeData();
	}
	else if (nClassID == MNGRCLASSID_CEDGEDEV)
	{
		pNew = new CEdgeDev();
	}
	else if (nClassID == MNGRCLASSID_CEDGEDISK)
	{
		pNew = new CEdgeDisk();
	}
	else if (nClassID == MNGRCLASSID_CEDGEDISKLMT)
	{
		pNew = new CEdgeDiskLmt();
	}
	else if (nClassID == MNGRCLASSID_CEDGEFILE)
	{
		pNew = new CEdgeFile();
	}
	else if (nClassID == MNGRCLASSID_CEDGELINKS)
	{
		pNew = new CEdgeLinks();
	}
	else if (nClassID == MNGRCLASSID_CEDGEMEM)
	{
		pNew = new CEdgeMem();
	}
	else if (nClassID == MNGRCLASSID_CEDGEMEMLMT)
	{
		pNew = new CEdgeMemLmt();
	}
	else if (nClassID == MNGRCLASSID_CEDGEOS)
	{
		pNew = new CEdgeOS();
	}
	else if (nClassID == MNGRCLASSID_CEDGESIGN)
	{
		pNew = new CEdgeSign();
	}
	else if (nClassID == MNGRCLASSID_CEDGECPU)
	{
		pNew = new CEdgeCpu();
	}
	else if (nClassID == MNGRCLASSID_CEDGECPULMT)
	{
		pNew = new CEdgeCpuLmt();
	}
	else if (nClassID == MNGRCLASSID_CEDGEMEMUSED)
	{
		pNew = new CEdgeMemUsed();
	}
	else if (nClassID == MNGRCLASSID_CEDGELINKSTATE)
	{
		pNew = new CEdgeLinkState();
	}
	else if (nClassID == MNGRCLASSID_CEDGETEMPERATURE)
	{
		pNew = new CEdgeTemperature();
	}
	else if (nClassID == MNGRCLASSID_CEDGEREPPERIOD)
	{
		pNew = new CEdgeRepPeriod();
	}
	else if (nClassID == MNGRCLASSID_CEDGEDEVICEINFOS)
	{
		pNew = new CEdgeDeviceInfos();
	}

	return pNew;
}

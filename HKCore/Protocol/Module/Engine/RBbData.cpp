#include "StdAfx.h"
#include "RBbData.h"
#include "PpTemplate.h"
#include "PpParsePackage.h"
#include "PpEngineDataMngrCntr.h"

#include "DataQueryBindStatck.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CRBbData::CRBbData(void)
{
	m_pInitScript = NULL;
}

CRBbData::~CRBbData(void)
{

}

CPpScript* CRBbData::GetInitScript()
{
	if (m_pInitScript == NULL)
	{
#ifdef UNICODE
		m_pInitScript = new CPpScript(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strInitScriptKey);
#else
		m_pInitScript = new CPpScript(CString(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strInitScriptKey));
#endif
		AddTail(m_pInitScript);
		m_pInitScript->SetParent(this);
		//m_pInitScript->m_strScript = L"--在此定义数据打包初始化脚本\r\n--当前绑定的数据满足打包条件,返回1，否则返回0\r\nreturn 1;";
	}

	return m_pInitScript;
}


long CRBbData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CBbData::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CRBbData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CBbData::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	
	return 0;
}

long CRBbData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{

	return 0;
}


CExBaseObject* CRBbData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataBlockKey)
	{//数据绑定
		//ASSERT (m_pDataByteBlock != NULL);
		m_pDataByteBlock = new CRDataByteBlock();
		return m_pDataByteBlock;
	}
	else if(strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strByteBlockKey)
	{
		return new CRByteBlock();
	}
	else if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strInitScriptKey)
	{
		ASSERT (m_pInitScript == NULL);

		if (m_pInitScript == NULL)
		{
			m_pInitScript = new CPpScript(strClassID);
			return m_pInitScript;
		}
		else
		{
			return NULL;
		}
	}
	return CBbData::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
}

CExBaseObject* CRBbData::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	
	return NULL;
}

void CRBbData::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == PPCLASSID_RDATABYTEBLOCK)
		{
			m_pDataByteBlock = (CRDataByteBlock*)p;
		}
		else if (p->GetClassID() == PPCLASSID_PPSCRIPT)
		{
			m_pInitScript = (CPpScript*)p;
		}
		else
		{
		}
	}

	CBbData::InitAfterRead();
}

DWORD CRBbData::RunInitScript()
{
	if (m_pInitScript != NULL)
	{
		m_pInitScript->Run();
		return m_pInitScript->m_dwReturn;
	}
	else
	{
		return 1;
	}
}

DWORD CRBbData::Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)
{// 数据解析
	if (m_pDataBinds == NULL)
	{
		return PPS_ERROR;
	}

// 	if (pDetail != NULL)
// 	{
// 		((CPpPackageDetail*)pDetail)->m_pPkgBufPos = &oPkgBufPos;
// 	}

	if (RunInitScript() == 0)
	{	//数据集解析结束
		return PPS_LOOP_BREAK;
	}

	m_pDataBinds->InitBindsDataType();

	POS pos = GetHeadPosition();
	CByteBlock *pByteBlock = NULL;

	DWORD nResult = 0;
	UINT nClassID = 0;

	// 遍历字节块
	while (pos != NULL)
	{
		pByteBlock = (CByteBlock*)GetNext(pos);
		nClassID = pByteBlock->GetClassID();

		if (nClassID == PPCLASSID_RBYTEBLOCK)
		{
			nResult = pByteBlock->Parse(oPkgBufPos, pDetail);
			if (IsPpParseError(nResult))
			{
				return nResult;
			}
		}
		else if (nClassID == PPCLASSID_RDATABYTEBLOCK)
		{
			nResult = pByteBlock->Parse(oPkgBufPos, pDetail);
			if (IsPpParseError(nResult))
			{
				return nResult;
			}

		} 			
	}	

	return nResult;

}
//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CRBbData::IsEqualOwn(CBaseObject* pObj)
{
	ASSERT (pObj == NULL);

	if (pObj == NULL)
	{
		return FALSE;
	}

	if (this == pObj)
	{
		return TRUE;
	}

	return CBbData::IsEqualOwn(pObj);
}

CBaseObject* CRBbData::Clone()
{
	CRBbData* pNew = new CRBbData();
	Copy(pNew);
	return pNew;
}

BOOL CRBbData::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	return CBbData::CopyOwn(pDest);
}

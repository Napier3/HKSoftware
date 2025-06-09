#include "StdAfx.h"
#include "PpProducePackage.h"
#include "ProtocolXmlRWKeys.h"
#include "PpScript.h"
#include "BbVariables.h"
#include "WBbDataSets.h"
#include "WByteBlock.h"
#include "PpPackageDetail.h"
#include "BbDataRange.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpProducePackage::CPpProducePackage(void)
{
	m_pOnBbPckScript = NULL;
}

CPpProducePackage::~CPpProducePackage(void)
{
	
}

long CPpProducePackage::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPpPackage::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;

}
long CPpProducePackage::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPpPackage::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	return 0;
}

CExBaseObject* CPpProducePackage::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strOnDataPakScriptKey)
	{
		m_pOnBbPckScript = new CPpScript(strClassID);
		return m_pOnBbPckScript;
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataSetsKey)
	{
		return new CWBbDataSets();
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strByteBlockKey)
	{
		return new CWByteBlock();
	}

	return CPpPackage::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
}

CExBaseObject* CPpProducePackage::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{

	return NULL;
}

DWORD CPpProducePackage::Produce(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)
{
	pDetail->m_strName = m_strName;
	pDetail->m_strID = m_strID;

	DWORD nResult = 0;
	//ASSERT (m_pTtPackage != NULL);

// 	if (m_pInitScript != NULL)
// 	{
// 		m_pInitScript->Run();
// 	}

	SetPkgLength(0);

	//����ͷ����
	if (m_pTtPackage != NULL && m_pTtPackage->m_pTtHead != NULL)
	{
		m_pTtPackage->m_pTtHead->Produce(oPkgBufPos, pDetail);
	}

	//����������
	POS pos = GetHeadPosition();
	CByteBlock *pByteBlock = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pByteBlock = (CByteBlock*)GetNext(pos);
		nClassID = pByteBlock->GetClassID();

		if (nClassID == PPCLASSID_WBYTEBLOCK || nClassID == PPCLASSID_WBBDATASETS)
		{
			nResult = pByteBlock->Produce(oPkgBufPos, pDetail);

			if (IsPpProduceError(nResult))
			{
				break;
			}
		}
	}
	
	if (m_pTtPackage != NULL && m_pTtPackage->m_pTtTail != NULL)
	{
		m_pTtPackage->m_pTtTail->Produce(oPkgBufPos, pDetail);
	}

	if (pDetail != NULL)
	{
		SetPkgLength(oPkgBufPos.nIndex);
	}

	// ������˳��Ϊ���İ�
	CByteBlock *pByteBlockSumCheck = NULL;

	CExBaseList oListByteBlocks;
	((CPpPackageDetail*)pDetail)->GetAllByteBlocks(&oListByteBlocks);
	pos = oListByteBlocks.GetHeadPosition();

	while (pos != NULL)
	{
		pByteBlock = (CByteBlock*)oListByteBlocks.GetNext(pos);

		if ( !PpIsByteBlock(pByteBlock->GetClassID()))
		{
			continue;
		}

		//if (pByteBlock->m_strDataType == g_strBbDataTypeSumCheck)
		if (pByteBlock->IsDataTypeCheck())
		{// У��ͣ�������
			pByteBlockSumCheck = pByteBlock;
			continue;
		}

		if (pByteBlock->m_nPackOrder == 1)
		{// �����������ģ������ڽű����и�ֵ
			nResult = pByteBlock->ProduceLastOrder();

			if (IsPpProduceError(nResult))
			{
				oListByteBlocks.RemoveAll();
				return nResult;
			}
		}
	}

	// �����У��ͣ�����
	Pp_Check(&oListByteBlocks, pByteBlockSumCheck);

	//ִ�д�������ű�
// 	if (m_pEndScript != NULL)
// 	{
// 		m_pEndScript->Run();
// 	}

	// �����������������������
	pos = oListByteBlocks.GetHeadPosition();
	long nIndex=0;

	while (pos != NULL)
	{
		pByteBlock = (CByteBlock*)oListByteBlocks.GetNext(pos);
		nResult = pByteBlock->AddBufferData(nIndex, oPkgBufPos.pBuffer);
	
		if (IsPpProduceError(nResult))
		{
			oListByteBlocks.RemoveAll();
			return nResult;
		}
	}

	oPkgBufPos.nIndex = nIndex;

	CPpPackageDetail *pPkgDetail = (CPpPackageDetail*)pDetail;
    ASSERT (pPkgDetail->m_pVariables != NULL);
	GetPackageVaraibles(*(pPkgDetail->m_pVariables));
	pPkgDetail->InitOwnAllVariables(TRUE);

	oListByteBlocks.RemoveAll();

	return nResult;
}

//////////////////////////////////////////////////////////////////////////
//���� ��¡ �Ա�
BOOL CPpProducePackage::IsEqualOwn(CBaseObject* pObj)
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

	return CPpPackage::IsEqualOwn(pObj);
}

CBaseObject* CPpProducePackage::Clone()
{
	CPpProducePackage* pNew = new CPpProducePackage();
	Copy(pNew);

	return pNew;
}

BOOL CPpProducePackage::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	return CPpPackage::CopyOwn(pDest);
}

void CPpProducePackage::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject*)GetNext(pos);

		UINT nClassID = p->GetClassID();

		switch (nClassID)
		{
		case PPCLASSID_BBVARIABLES:
			{
				CBbVariables *pVariables = (CBbVariables*)p;

				if (pVariables->m_strXmlKey == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataInterfaceKey)
				{
					m_pDataInterface = pVariables;
				}
				else if (pVariables->m_strXmlKey == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataInterfaceKey)
				{
					m_pVariables = pVariables;
				}
				else
				{

				}
			}

			break;

		case PPCLASSID_PPSCRIPT:
			{
				CPpScript *pScript = (CPpScript*)p;

				if (pScript->m_strXmlKey == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strEndScriptKey)
				{
					m_pEndScript = pScript;
				}
				else if(pScript->m_strXmlKey == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strInitScriptKey)
				{
					m_pInitScript = pScript;
				}
				else if(pScript->m_strXmlKey == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strOnDataPakScriptKey)
				{
					m_pOnBbPckScript = pScript;
				}
			}
			break;

		default:
			break;
		}
	}

	CPpPackage::InitAfterRead();
}

CWBbDataSets* CPpProducePackage::GetWBbDataSets()
{
	POS pos = GetHeadPosition();

	CExBaseObject* pObj = NULL;
	CWBbDataSets* pFind = NULL;
	while(pos != NULL)
	{
		pObj = (CExBaseObject*)GetNext(pos);
		if(pObj->GetClassID() == PPCLASSID_WBBDATASETS)
		{
			pFind = (CWBbDataSets*)pObj;
			break;
		}
	}

	return pFind;
}

CPpScript* CPpProducePackage::CreateOnBbPckScript()
{
	if (m_pOnBbPckScript == NULL)
	{
#ifdef UNICODE
		m_pOnBbPckScript = new CPpScript(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strOnDataPakScriptKey);
#else
		m_pOnBbPckScript = new CPpScript(CString(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strOnDataPakScriptKey));
#endif
		m_pOnBbPckScript->SetParent(this);
		AddTail(m_pOnBbPckScript);
		//m_pOnBbPckScript->m_strScript = L"--�����һ�����ݺ�ִ�еĽű��������жϱ����Ƿ񳬹�����ĳ���\r\n --���һ�����ݺ�������ȳ���������0���������ȡ����ǰ���ݵĴ��\r\n--����1���������";
	}

	return m_pOnBbPckScript;
}


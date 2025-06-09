#include "StdAfx.h"
#include "WBbData.h"
#include "WByteBlock.h"
#include "PpScript.h"
#include "WDataByteBlock.h"

#include "PpTemplate.h"
//#include "PpEngineDataMngrCntr.h"
#include "../XLanguageResourcePp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


const CString CWBbData::g_strLoopCountVariable = _T("LoopCount");
const CString CWBbData::g_strLoopIndexVariable = _T("LoopIndex");

CWBbData::CWBbData(void)
{
	m_pInitScript = NULL;
	m_nLoopCount = 0;
	m_nLoopIndex = -1;

	if (m_pVariables == NULL)
	{
		m_pVariables = new CBbVariables(_T(""));
		this->AddTail(m_pVariables);
		m_pVariables->SetParent(this);
	}

	m_strName = _T("���ݶ���");
	m_strID = _T("ID");

	m_pOldDataBind = NULL;
	m_pLoopIndexBind = new CPpDataBind();
	m_pDeviceBindData = NULL;

	m_nBindItemIndex = -1;
}

CWBbData::~CWBbData(void)
{
	delete m_pLoopIndexBind;
}

CPpScript* CWBbData::GetInitScript()
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
		//m_pInitScript->m_strScript = L"--�ڴ˶������ݴ����ʼ���ű�\r\n--��ǰ�󶨵���������������,����1�����򷵻�0\r\nreturn 1;";
	}

	return m_pInitScript;
}

long CWBbData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CBbData::XmlReadOwn(oNode, pXmlRWKeys);

	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pKeys->m_strLoopCountKey, oNode, m_strLoopCount);
	xml_GetAttibuteValue(pKeys->m_strLoopIndexKey,oNode,m_strLoopIndex);
	xml_GetAttibuteValue(pKeys->m_strDataCountKey,oNode,m_strDataCount);

	m_pLoopIndexBind->m_strDataType = g_strVariableDataTypeItemIndexID;
	m_pLoopIndexBind->m_strDataAttrID = m_strLoopIndex;

	return 0;
}

long CWBbData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CBbData::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pKeys->m_strLoopCountKey, oElement, m_strLoopCount);
	xml_SetAttributeValue(pKeys->m_strLoopIndexKey,oElement,m_strLoopIndex);
	xml_SetAttributeValue(pKeys->m_strDataCountKey,oElement,m_strDataCount);

	return 0;
}

long CWBbData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{

	return 0;
}


CExBaseObject* CWBbData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strInitScriptKey)
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
	else if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataBlockKey)
	{//���ݰ�
		ASSERT (m_pDataByteBlock == NULL);
		m_pDataByteBlock = new CWDataByteBlock();
		return m_pDataByteBlock;
	}
	else if(strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strByteBlockKey)
	{
		return new CWByteBlock();
	}

	return CBbData::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);

	//return NULL;
	//else if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strByteBlockKey)
	//{//���ݰ�
	//	return new CWByteBlock();
	//}
	//else
	//{
	//	return CBbData::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
	//}
}

CExBaseObject* CWBbData::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{

	return NULL;
}


void CWBbData::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == PPCLASSID_WDATABYTEBLOCK)
		{
			m_pDataByteBlock = (CWDataByteBlock*)p;
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

DWORD CWBbData::RunInitScript()
{
	if (m_pInitScript != NULL)
	{
		if (m_pInitScript->m_strScript.GetLength() <= 5)
		{
			return 1;
		}
		else
		{
			m_pInitScript->Run();
			return m_pInitScript->m_dwReturn;
		}
	}
	else
	{
		return 1;
	}
}

//�ֽڿ������
DWORD CWBbData::ProduceDeviceNode(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail, CExBaseObject *pNode)
{
	// ��ȡ��Ӧ�豸���ݺ������ָ��			
	CPpTemplate *pTemplate = (CPpTemplate*)GetAncestor(PPCLASSID_PPTEMPLATE);
	CPpProducePackage* pPkg = (CPpProducePackage*)GetAncestor(PPCLASSID_PPPRODUCEPACKGE);
	CDvmDataset* pDeviceNode  = (CDvmDataset*)pNode;
	long nCount = pDeviceNode->GetCount();
	long nIndex = 0;
	DWORD nResult = 0;
	CByteBlock *pByteBlock = NULL;
	UINT nClassID = 0;
	CDvmData *pNodeData = NULL;

	//####################################
	//��ȡWBbDataѭ������������
	//�ٸ���ѭ�����������ݻ�ȡ��ʼ��λ��
	//####################################
	long nLoopIndex = 0, nLoopCount = 0, nDataCount=0;

	//�������ݼ������ݵ�����
	nDataCount = pDeviceNode->GetCount();
	pPkg->SetVariableValue(m_strDataCount, nDataCount);

	//��ÿ�ʼѭ��ȡ���ݵ�λ��
	pPkg->GetVariableValue(m_strLoopIndex, nLoopIndex);

	//���δ���ĸ�������ʼ��Ϊ0
	pPkg->SetVariableValue(m_strLoopCount, nLoopCount);

	//���°󶨹�ϵ
	SetLoopIndexBind();

	while (TRUE)
	{
		m_nBindItemIndex = -1; //���ð�ģʽΪͨ��������ȡ��ģʽ

		if (nLoopIndex >= nDataCount)
		{
			int ii = 0;
		}

		if (nLoopIndex >= nDataCount)
		{
			nResult = PpProduceFinish();
			break;
		}

		if (RunInitScript() == 0)
		{	// �жϸ�Data�Ƿ���Ҫ����������ƻ�����
			//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"RunInitScript=0, nLoopIndex=%d", nLoopIndex);
			nLoopIndex++;
			pPkg->SetVariableValue(m_strLoopIndex, nLoopIndex);
			continue;
		}

		POS pos = GetHeadPosition();

		long nAddedBlock = 0;
		
		CWBbData *pDataDetail = new CWBbData();
		pDataDetail->m_strName = m_strName;
		pDataDetail->m_strID = m_strID;
		pDetail->AddNewChild(pDataDetail);

		while (pos != NULL)
		{
			pByteBlock = (CByteBlock*)GetNext(pos);
			nClassID = pByteBlock->GetClassID();

			if (nClassID == PPCLASSID_WBYTEBLOCK)
			{
				//nResult = pByteBlock->Produce(oPkgBufPos, pDetail);
				nResult = pByteBlock->Produce(oPkgBufPos, pDataDetail);

				if (IsPpProduceError(nResult))
				{
					ResetBinds();
					return nResult;
				}

				nAddedBlock += 1;
			}
			else if (nClassID == PPCLASSID_WDATABYTEBLOCK)
			{
				//�ȹ̶�����Ϊ��Value��
				nResult = pByteBlock->Produce(oPkgBufPos, pDataDetail);

				if (IsPpProduceError(nResult))
				{
					ResetBinds();
					return nResult;
				}

				nAddedBlock += 1;
			}
		}

		//���һ�����ݣ�����ѭ������
		nLoopIndex++;
		pPkg->SetVariableValue(m_strLoopIndex, nLoopIndex);
		nLoopCount++;
		pPkg->SetVariableValue(m_strLoopCount, nLoopCount);

		//����Package�ĳ���
		pPkg->SetPkgLength(oPkgBufPos.nIndex);

		// ����Data�Ƿ���ɻ��������
		if (RunOnBbPckScript(pPkg, nAddedBlock, pDetail, oPkgBufPos.nIndex) == 0)
		{
			//nLoopIndex--;
			//pPkg->SetVariableValue(m_strLoopIndex, nLoopIndex);
			//nLoopCount--;
			//pPkg->SetVariableValue(m_strLoopCount, nLoopCount);

			ResetBinds();
			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Counts=%d  Packs=%d  Index=%d  buff=%d"), nDataCount, nLoopCount, nLoopIndex, oPkgBufPos.nIndex);
			return PpProduceNotFinish();
		}
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Counts=%d  Packs=%d  Index=%d"), nDataCount, nLoopCount, nLoopIndex);
	ResetBinds();

	return 0;
}

DWORD CWBbData::ProduceDeviceNodeData(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail, CExBaseObject *pNodeData)
{
	// ��ȡ��Ӧ�豸���ݺ������ָ��			
	CPpTemplate *pTemplate = (CPpTemplate*)GetAncestor(PPCLASSID_PPTEMPLATE);
	CPpProducePackage* pPkg = (CPpProducePackage*)GetAncestor(PPCLASSID_PPPRODUCEPACKGE);
	DWORD nResult = 0;
	CByteBlock *pByteBlock = NULL;
	UINT nClassID = 0;
	CDvmData *pData = (CDvmData*)pNodeData;
	POS pos = GetHeadPosition();
	long nAddedBlock = 0;

	RunInitScript() ;
	
	while (pos != NULL)
	{
		pByteBlock = (CByteBlock*)GetNext(pos);
		nClassID = pByteBlock->GetClassID();

		if (nClassID == PPCLASSID_WBYTEBLOCK)
		{
			nResult = pByteBlock->Produce(oPkgBufPos, pDetail);

			if (IsPpProduceError(nResult))
			{
				return nResult;
			}

			nAddedBlock += 1;
		}
		else if (nClassID == PPCLASSID_WDATABYTEBLOCK)
		{
			nResult = pByteBlock->Produce(oPkgBufPos, pDetail);

			if (IsPpProduceError(nResult))
			{
				return nResult;
			}

			nAddedBlock += 1;
		}
	}

	return 0;
}

DWORD CWBbData::Produce(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)
{// ��������
	if (m_pDataBinds == NULL)
	{
		return PpProduceError();
	}

	m_pDataBinds->InitBindsDataType();

	DWORD nResult = 0;

	// ��ȡ��Ӧ�豸���ݺ������ָ��			
	CPpTemplate *pTemplate = (CPpTemplate*)GetAncestor(PPCLASSID_PPTEMPLATE);
	CPpProducePackage* pPkg = (CPpProducePackage*)GetAncestor(PPCLASSID_PPPRODUCEPACKGE);

	if (pTemplate == NULL || pPkg == NULL)
	{
		return PpProduceError();
	}

	// ���ݰ󶨹�ϵ��ȡ��������
	if (m_pDataBinds == NULL)
	{
		return nResult;
	}

	//��ȡ���ݰ󶨵Ľڵ�
	CExBaseObject *pData = CBbData::QueryByBind(FALSE);
	m_pDeviceBindData = pData;

	//û���ҵ��󶨵����ݡ����ݽڵ�
	if (pData == NULL)
	{
		if (g_bLogBindQueryErrorInfor)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("�������ݶ���\"%s\"���ݰ󶨴���"), m_strName.GetString());
		}

		return PpProduceError();
	}

	UINT nClassID = pData->GetClassID();

	if (nClassID == DVMCLASSID_CDVMDATASET)
	{//ͨ���󶨹�ϵ�ҵ����ǽڵ�
		CDvmDataset *pNode = (CDvmDataset*)pData;
		return ProduceDeviceNode(oPkgBufPos, pDetail, pData);

// 		if (pNode->IsDataNode())
// 		{//�ڵ��Ӷ���Ϊ:����
// 			return ProduceDeviceNode(oPkgBufPos, pDetail, pData);
// 		}
// 		else
// 		{//�ڵ��Ӷ���Ϊ:�ڵ�
// 			if (g_bLogBindQueryErrorInfor)
// 			{
// 				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"�������ݶ���\"%s\"���ݰ󶨴���", m_strName);
// 			}
// 
// 			return PpProduceError();
// 		}
	}
	else if (nClassID == DVMCLASSID_CDVMDATA)
	{
		return ProduceDeviceNodeData(oPkgBufPos, pDetail, pData);
	}
	else
	{
		return PpProduceError();
	}
}

DWORD CWBbData::RunOnBbPckScript(CBaseObject *pPkg, long &nAddedBlock, CExBaseList *pDetail, long &nPos)
{
	DWORD dwReturn = 1;
	CPpProducePackage *pProducePackage = (CPpProducePackage*)pPkg;
	CPpScript *pScript = pProducePackage->m_pOnBbPckScript;

	if (pScript != NULL)
	{
		pScript->Run();
		dwReturn = pScript->m_dwReturn;

		if (dwReturn == 0)
		{// ���
			//���ٳ����ݣ����Ǵ��ʱ����CrcPush�����ᵼ�¶����һ��CRC
			/*
			// ��pDetailɾ������
			CExBaseObject *pWData = (CByteBlock*)pDetail->GetTail();

			if (pWData->GetClassID() == PPCLASSID_WBBDATA)
			{
				CWBbData *pCWBbData = (CWBbData*)pWData;
				POS pos = pCWBbData->GetHeadPosition();
				CExBaseObject *p = NULL;

				while (pos != NULL)
				{
					p = (CByteBlock*)pCWBbData->GetNext(pos);
					UINT nClassID = p->GetClassID();

					if (nClassID == PPCLASSID_WDATABYTEBLOCK
						|| nClassID == PPCLASSID_WBYTEBLOCK)
					{	
						CByteBlock *pBb = (CByteBlock*)p;
						nPos -= pBb->GetByteBlockLength2();
					}
				}

				pDetail->DeleteTail();
			}
			*/

// 			while (nAddedBlock > 0)
// 			{
// 				nPos -= pBb->GetByteBlockLength2();
// 				pDetail->DeleteTail();
// 				nAddedBlock --;
// 			}		
		}
	}

	return dwReturn;
}

CExBaseObject* CWBbData::QueryByBind()
{
	if (m_pDeviceBindData == NULL)
	{
		return NULL;
	}

	UINT nClassID = m_pDeviceBindData->GetClassID();

	if (nClassID == DVMCLASSID_CDVMDATASET)
	{
		long nLoopIndex = 0;
		CPpProducePackage* pPkg = (CPpProducePackage*)GetAncestor(PPCLASSID_PPPRODUCEPACKGE);

		//��õ�ǰ�ı���������
		if (m_nBindItemIndex >= 0)
		{
			nLoopIndex = m_nBindItemIndex;
		}
		else
		{
			pPkg->GetVariableValue(m_strLoopIndex, nLoopIndex);
		}

		CDvmDataset *pNode = (CDvmDataset*)m_pDeviceBindData;
		CDvmData *pData = (CDvmData*)pNode->GetAt(nLoopIndex);
		return pData;
	}
	else if (nClassID == DVMCLASSID_CDVMDATA)
	{
		return m_pDeviceBindData;
	}

	return NULL;
}


CExBaseObject* CWBbData::BindItemIndex(long nItemIndex)
{
	m_nBindItemIndex = nItemIndex;  //����Ϊͨ�������ItemIndex���а󶨵�ģʽ
	return QueryByBind();
}

//////////////////////////////////////////////////////////////////////////
//���� ��¡ �Ա�
BOOL CWBbData::IsEqualOwn(CBaseObject* pObj)
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

	if (m_nLoopCount != ((CWBbData*)pObj)->m_nLoopCount)
	{
		return FALSE;
	}

	if (m_nLoopIndex != ((CWBbData*)pObj)->m_nLoopIndex)
	{
		return FALSE;
	}

	return CBbData::IsEqualOwn(pObj);
}

CBaseObject* CWBbData::Clone()
{
	CWBbData* pNew = new CWBbData();
	Copy(pNew);
	return pNew;
}

BOOL CWBbData::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CWBbData*)pDest)->m_nLoopCount = m_nLoopCount;
	((CWBbData*)pDest)->m_nLoopIndex = m_nLoopIndex;

	((CWBbData*)pDest)->m_strLoopCount = m_strLoopCount;
	((CWBbData*)pDest)->m_strLoopIndex = m_strLoopIndex;
	((CWBbData*)pDest)->m_strDataCount = m_strDataCount;

	return CBbData::CopyOwn(pDest);
}

CBbVariable* CWBbData::GetVariable(CString &strVariableID)
{
	CBbVariable* pVar = NULL;
	CPpProducePackage* pPkg = (CPpProducePackage*)GetAncestor(PPCLASSID_PPPRODUCEPACKGE);

	if (pPkg == NULL)
	{
		return NULL;
	}
	else
	{
		pVar = (CBbVariable*)pPkg->FindVariableByID(strVariableID);
		if (pVar == NULL)
		{
			if (pPkg->m_pTtPackage == NULL)
			{
				return NULL;
			}
			pVar = (CBbVariable*)pPkg->m_pTtPackage->FindVariableByID(strVariableID);
			if (pVar == NULL)
			{
				return NULL;
			}
		}
	}

	return pVar;
}

void  CWBbData::SetLoopIndexBind()
{
	POS pos = m_pDataBinds->GetTailPosition();
	m_pOldDataBind = (CPpDataBind*)m_pDataBinds->GetAt(pos);

	if (m_pOldDataBind != NULL)
	{
		if (g_strVariableDataTypeItemIndexID != m_pOldDataBind->m_strDataType)
		{
			if (m_pOldDataBind->m_strDataType.GetLength() > 0)
			{
				m_pOldDataBind = new CPpDataBind();
				m_pDataBinds->AddNewChild(m_pOldDataBind);
				pos = m_pDataBinds->GetTailPosition();
			}
		}
	}
	else
	{
		CString strNamePath;
		strNamePath = GetNamePathEx(PPCLASSID_PPPRODUCEPACKGE);
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                    , g_sLangTxt_DataRltnshipError3.GetString()/*_T("%s�����ݰ󶨹�ϵ����")*/
                    , strNamePath.GetString());
	}


	m_pDataBinds->SetAt(pos, m_pLoopIndexBind);
}

void  CWBbData::ResetBinds()
{
	POS pos = m_pDataBinds->GetTailPosition();
	m_pDataBinds->SetAt(pos, m_pOldDataBind);
}


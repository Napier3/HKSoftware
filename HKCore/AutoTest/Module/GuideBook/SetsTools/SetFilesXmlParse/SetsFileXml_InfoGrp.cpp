//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SetsFileXml_InfoGrp.cpp  CSetsFileXml_InfoGrp


#include "stdafx.h"
#include "SetsFileXml_InfoGrp.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSetsFileXml_InfoGrp::CSetsFileXml_InfoGrp()
{
	//��ʼ������
	m_nSetGrpNum = 0;
	m_nItemNum = 0;
	m_nRemote = 0;

	//��ʼ����Ա����
}

CSetsFileXml_InfoGrp::~CSetsFileXml_InfoGrp()
{
}

long CSetsFileXml_InfoGrp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDescKey, oNode, m_strDesc);
	xml_GetAttibuteValue(pXmlKeys->m_strSetGrpNumKey, oNode, m_nSetGrpNum);
	xml_GetAttibuteValue(pXmlKeys->m_strItemNumKey, oNode, m_nItemNum);
	xml_GetAttibuteValue(pXmlKeys->m_strRemoteKey, oNode, m_nRemote);
	return 0;
}

long CSetsFileXml_InfoGrp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDescKey, oElement, m_strDesc);
	xml_SetAttributeValue(pXmlKeys->m_strSetGrpNumKey, oElement, m_nSetGrpNum);
	xml_SetAttributeValue(pXmlKeys->m_strItemNumKey, oElement, m_nItemNum);
	xml_SetAttributeValue(pXmlKeys->m_strRemoteKey, oElement, m_nRemote);
	return 0;
}

long CSetsFileXml_InfoGrp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDesc);
		BinarySerializeCalLen(oBinaryBuffer, m_nSetGrpNum);
		BinarySerializeCalLen(oBinaryBuffer, m_nItemNum);
		BinarySerializeCalLen(oBinaryBuffer, m_nRemote);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDesc);
		BinarySerializeRead(oBinaryBuffer, m_nSetGrpNum);
		BinarySerializeRead(oBinaryBuffer, m_nItemNum);
		BinarySerializeRead(oBinaryBuffer, m_nRemote);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDesc);
		BinarySerializeWrite(oBinaryBuffer, m_nSetGrpNum);
		BinarySerializeWrite(oBinaryBuffer, m_nItemNum);
		BinarySerializeWrite(oBinaryBuffer, m_nRemote);
	}
	return 0;
}

void CSetsFileXml_InfoGrp::InitAfterRead()
{
}

BOOL CSetsFileXml_InfoGrp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSetsFileXml_InfoGrp *p = (CSetsFileXml_InfoGrp*)pObj;

	if(m_strDesc != p->m_strDesc)
	{
		return FALSE;
	}

	if(m_nSetGrpNum != p->m_nSetGrpNum)
	{
		return FALSE;
	}

	if(m_nItemNum != p->m_nItemNum)
	{
		return FALSE;
	}

	if(m_nRemote != p->m_nRemote)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSetsFileXml_InfoGrp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSetsFileXml_InfoGrp *p = (CSetsFileXml_InfoGrp*)pDest;

	p->m_strDesc = m_strDesc;
	p->m_nSetGrpNum = m_nSetGrpNum;
	p->m_nItemNum = m_nItemNum;
	p->m_nRemote = m_nRemote;
	return TRUE;
}

CBaseObject* CSetsFileXml_InfoGrp::Clone()
{
	CSetsFileXml_InfoGrp *p = new CSetsFileXml_InfoGrp();
	Copy(p);
	return p;
}

CBaseObject* CSetsFileXml_InfoGrp::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSetsFileXml_InfoGrp *p = new CSetsFileXml_InfoGrp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSetsFileXml_InfoGrp::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSETSFILEXML_SI)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSetsFileXml_InfoGrp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSetsFileXml_SIKey)
	{
		pNew = new CSetsFileXml_SI();
	}

	return pNew;
}

CExBaseObject* CSetsFileXml_InfoGrp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSETSFILEXML_SI)
	{
		pNew = new CSetsFileXml_SI();
	}

	return pNew;
}

void CSetsFileXml_InfoGrp::SetModifyedFlag(BOOL bFlag)
{
	m_dwReserved = bFlag;
	CSetsFileXml_SI *pSI = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pSI = (CSetsFileXml_SI *)GetNext(pos);
		pSI->SetModifyedFlag(bFlag);
	}
}

void CSetsFileXml_InfoGrp::UpdateVal(CSetsFileXml_InfoGrp *pSrcInfoGrp)
{
	if (pSrcInfoGrp == NULL)
	{
		return;
	}

	m_dwReserved = 1; //��ģ��༭Ԥ�õ�ֵ���¹�������Ϊ���༭
	CSetsFileXml_SI *pSI = NULL;
	POS pos = pSrcInfoGrp->GetHeadPosition();

	while (pos != NULL)
	{
		pSI = (CSetsFileXml_SI *)pSrcInfoGrp->GetNext(pos);
		CSetsFileXml_SI *pDest = FindSIByDesc(pSI->m_strDesc);

		if (pDest == NULL)
		{
			continue;
		}

		pDest->UpdateVal(pSI);
	}
}

//�β��Ǳ��༭�Ķ���ͨ��m_dwReserved��ǣ���ӱ��޸ĵĶ���thisָ��
void CSetsFileXml_InfoGrp::AppendByModify(CSetsFileXml_InfoGrp *pModifyInfoGrp)
{
	if (pModifyInfoGrp == NULL)
	{
		return;
	}

	CSetsFileXml_SI *pSI = NULL;
	POS pos = pModifyInfoGrp->GetHeadPosition();

	while (pos != NULL)
	{
		pSI = (CSetsFileXml_SI *)pModifyInfoGrp->GetNext(pos);

		if (pSI->m_dwReserved != 1)
		{
			continue;
		}

		CSetsFileXml_SI *pNew = (CSetsFileXml_SI *)pSI->CloneEx(); //����¡����
		AddNewChild(pNew);
		pNew->AppendByModify(pSI);
	}
}

CSetsFileXml_SI* CSetsFileXml_InfoGrp::FindSIByDesc(const CString &strDesc)
{
	CSetsFileXml_SI *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		CSetsFileXml_SI *pSI = (CSetsFileXml_SI *)GetNext(pos);

		if (pSI->m_strDesc == strDesc)
		{
			pFind = pSI;
			break;
		}
	}

	return pFind;
}

//ָ����ֵ������ֵ�����Ƿ񱻱༭
BOOL CSetsFileXml_InfoGrp::IsModifyed_Grp(long nGrp)
{
	if (m_dwReserved != 1)
	{
		return FALSE;
	}

	POS pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		CSetsFileXml_SI *pSI = (CSetsFileXml_SI *)GetNext(pos);

		if (pSI->IsModifyed_Grp(nGrp))
		{
			return TRUE;
		}
	}

	return FALSE;
}

CSetsFileXml_SI* CSetsFileXml_InfoGrp::FindSIByRef(const CString &strRef)
{
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		CSetsFileXml_SI *pSI = (CSetsFileXml_SI *)GetNext(pos);

		if (pSI->m_strRef == strRef)
		{
			return pSI;
		}
	}

	return NULL;
}

//nGrp����ֵ����
void CSetsFileXml_InfoGrp::ParseToDvm(CDvmDataset *pDataset, long nGrp)
{
	POS pos = GetHeadPosition();
	CSetsFileXml_SI *pSI = NULL;

	while (pos != NULL)
	{
		pSI = (CSetsFileXml_SI *)GetNext(pos);
		pSI->ParseToDvm(pDataset, nGrp);
	}
}

/*
configVersion����Ϊ1.00�汾ʱ��
�������Ϊ����ֵ�����ݣ���Val��ǩ����,ȥ���ո��Ʊ�����س���
���к�������ַ�����
*/
void CSetsFileXml_InfoGrp::GetValStringTotal(long nGrp, CString &strVal)
{
	strVal.Empty();
	CString str;
	POS pos = GetHeadPosition();
	CSetsFileXml_SI *pSI = NULL;

	while (pos != NULL)
	{
		pSI = (CSetsFileXml_SI *)GetNext(pos);
		str = pSI->GetValByGrp_String(nGrp);

		strVal.AppendFormat(_T("%s"), str);
	}
}

/*
��configVersion����Ϊ1.10�汾ʱ�������
������Ϊÿ����ֵ���������ֵ�����ݣ���desc��Val��ǩ����,ȥ��
�ո��Ʊ�����س������к�������ַ����ݣ���������ֵ�����ʹ
��Ӣ�Ķ��ţ�ASCII��ֵΪ0x2C����Ϊ�ָ������ָ���ͬ����Ϊ�������
*/
void CSetsFileXml_InfoGrp::GetValStringTotal_V110(long nGrp, CString &strVal)
{
	CString str;
	strVal.Empty();
	POS pos = GetHeadPosition();
	CSetsFileXml_SI *pSI = NULL;

	while (pos != NULL)
	{
		pSI = (CSetsFileXml_SI *)GetNext(pos);
		str = pSI->GetValByGrp_String(nGrp);

		strVal.AppendFormat(_T("%s,%s,"), pSI->m_strDesc, str);
	}
}

char* CSetsFileXml_InfoGrp::GetValStringTotal_V110(long nGrp)
{
	char *pszTotal = new char[10240];
	std::memset(pszTotal, 0, 10240 * sizeof(char));

	POS pos = GetHeadPosition();
	CSetsFileXml_SI *pSI = NULL;
	CString strVal;

	while (pos != NULL)
	{
		pSI = (CSetsFileXml_SI *)GetNext(pos);
		strVal = pSI->GetValByGrp_String(nGrp);
		char *pszApd = new char[128];
		std::memset(pszApd, 0, 128 * sizeof(char));
		sprintf(pszApd, "%s,%s,", pSI->m_strDesc, strVal);
		strcat(pszTotal, pszApd);
	}

	return pszTotal;
}

void CSetsFileXml_InfoGrp::GetValStringTotal_V110_Single(CString &strVal)
{
	CString str;
	POS pos = GetHeadPosition();
	CSetsFileXml_SI *pSI = NULL;

	while (pos != NULL)
	{
		pSI = (CSetsFileXml_SI *)GetNext(pos);
		str = pSI->GetVal_String();

		strVal.AppendFormat(_T("%s,%s,"), pSI->m_strDesc, str);
	}
}
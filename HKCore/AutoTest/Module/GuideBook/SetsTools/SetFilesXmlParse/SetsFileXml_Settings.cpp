//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SetsFileXml_Settings.cpp  CSetsFileXml_Settings


#include "stdafx.h"
#include "SetsFileXml_Settings.h"

#include "..\..\..\..\..\Module\API\Xmd5.h"
#include "..\..\..\..\..\Module\API\StringConvert\String_Gbk_To_Utf8.h"
#include "SetFilesXml_DSC.h"
#include "..\..\..\..\..\Module\xml\XmlRW_Pugi.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSetsFileXml_Settings::CSetsFileXml_Settings()
{
	//��ʼ������
	m_nInfoGrpNum = 0;
	//����װ�ò�����ѹ�����ݼ����ǵ�����ֵ��û�ж��嶨ֵ���ţ�
	//�˴���Ҫ����ֵ����Ĭ��Ϊ-1��
	m_nGrp = -1;

	m_pNode = NULL;
	//��ʼ����Ա����
}

CSetsFileXml_Settings::~CSetsFileXml_Settings()
{
}

long CSetsFileXml_Settings::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	CXmlRWNode_Pugi *pNode = (CXmlRWNode_Pugi *)&oNode;
	m_pNode = &(pNode->m_oPugiXmlNode);

	xml_GetAttibuteValue(pXmlKeys->m_strLdKey, oNode, m_strLd);
	xml_GetAttibuteValue(pXmlKeys->m_strClassKey, oNode, m_strClass);
	xml_GetAttibuteValue(pXmlKeys->m_strInfoGrpNumKey, oNode, m_nInfoGrpNum);
	xml_GetAttibuteValue(pXmlKeys->m_strGrpKey, oNode, m_nGrp);
	return 0;
}

long CSetsFileXml_Settings::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strLdKey, oElement, m_strLd);
	xml_SetAttributeValue(pXmlKeys->m_strClassKey, oElement, m_strClass);

	if (m_nGrp > 0)
	{//ֻ�ж�ֵ���е�ǰ������
		xml_SetAttributeValue(pXmlKeys->m_strGrpKey, oElement, m_nGrp);
	}

	xml_SetAttributeValue(pXmlKeys->m_strInfoGrpNumKey, oElement, m_nInfoGrpNum);

	return 0;
}

long CSetsFileXml_Settings::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strLd);
		BinarySerializeCalLen(oBinaryBuffer, m_strClass);
		BinarySerializeCalLen(oBinaryBuffer, m_nInfoGrpNum);
		BinarySerializeCalLen(oBinaryBuffer, m_nGrp);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strLd);
		BinarySerializeRead(oBinaryBuffer, m_strClass);
		BinarySerializeRead(oBinaryBuffer, m_nInfoGrpNum);
		BinarySerializeRead(oBinaryBuffer, m_nGrp);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strLd);
		BinarySerializeWrite(oBinaryBuffer, m_strClass);
		BinarySerializeWrite(oBinaryBuffer, m_nInfoGrpNum);
		BinarySerializeWrite(oBinaryBuffer, m_nGrp);
	}
	return 0;
}

void CSetsFileXml_Settings::InitAfterRead()
{
}

BOOL CSetsFileXml_Settings::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSetsFileXml_Settings *p = (CSetsFileXml_Settings*)pObj;

	if(m_strLd != p->m_strLd)
	{
		return FALSE;
	}

	if(m_strClass != p->m_strClass)
	{
		return FALSE;
	}

	if(m_nInfoGrpNum != p->m_nInfoGrpNum)
	{
		return FALSE;
	}

	if(m_nGrp != p->m_nGrp)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSetsFileXml_Settings::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSetsFileXml_Settings *p = (CSetsFileXml_Settings*)pDest;

	p->m_strLd = m_strLd;
	p->m_strClass = m_strClass;
	p->m_nInfoGrpNum = m_nInfoGrpNum;
	p->m_nGrp = m_nGrp;
	return TRUE;
}

CBaseObject* CSetsFileXml_Settings::Clone()
{
	CSetsFileXml_Settings *p = new CSetsFileXml_Settings();
	Copy(p);
	return p;
}

CBaseObject* CSetsFileXml_Settings::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSetsFileXml_Settings *p = new CSetsFileXml_Settings();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSetsFileXml_Settings::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSETSFILEXML_INFOGRP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSetsFileXml_Settings::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSetsFileXml_InfoGrpKey)
	{
		pNew = new CSetsFileXml_InfoGrp();
	}

	return pNew;
}

CExBaseObject* CSetsFileXml_Settings::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSETSFILEXML_INFOGRP)
	{
		pNew = new CSetsFileXml_InfoGrp();
	}

	return pNew;
}

BSTR CSetsFileXml_Settings::GetXml(CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType)
{
	return CBaseObject::GetXml(pXmlRWKeys, nXmlRWType);
// 	if (m_pNode != NULL)
// 	{
// 		char *pChar = NULL;
// 		CString strXml;
// 		pChar = m_pNode->get_xml_string();
// 		strXml.Format(_T("%s"), pChar);
// 		delete []pChar;
// 		return strXml.AllocSysString();
// 	}
// 	else
// 	{
// 		CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(nXmlRWType);
// 		CXmlRWElementBase *pRWElement = pRWDoc->GetDocElement();
// 		XmlWrite(*pRWDoc, *pRWElement,  pXmlRWKeys);
// 		CString strXML;
// 		pRWDoc->GetXml(strXML);
// 		delete pRWDoc;
// 		return strXML.AllocSysString();
// 	}
}

char* CSetsFileXml_Settings::GetXml_XmlNode()
{
	if (m_pNode == NULL)
	{
		return NULL;
	}

	return m_pNode->get_xml_string();
}

void CSetsFileXml_Settings::SetModifyedFlag(BOOL bFlag)
{
	m_dwReserved = bFlag;
	CSetsFileXml_InfoGrp *pInfoGrp = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pInfoGrp = (CSetsFileXml_InfoGrp *)GetNext(pos);
		pInfoGrp->SetModifyedFlag(bFlag);
	}
}

void CSetsFileXml_Settings::UpdateSettings(CSetsFileXml_Settings *pSrcSettings)
{
	if (pSrcSettings == NULL)
	{
		return;
	}

	m_dwReserved = 1; //��ģ��༭Ԥ�õ�ֵ���¹�������Ϊ���༭
	CSetsFileXml_InfoGrp *pInfoGrp = NULL;
	POS pos = pSrcSettings->GetHeadPosition();

	while (pos != NULL)
	{
		pInfoGrp = (CSetsFileXml_InfoGrp *)pSrcSettings->GetNext(pos);
		CSetsFileXml_InfoGrp *pDest = FindInforGrpByDesc(pInfoGrp->m_strDesc);

		if (pDest == NULL)
		{
			continue;
		}

		pDest->UpdateVal(pInfoGrp);
	}
}

//�β��Ǳ��༭�Ķ���ͨ��m_dwReserved��ǣ���ӱ��޸ĵĶ���thisָ��
void CSetsFileXml_Settings::AppendByModify(CSetsFileXml_Settings *pModifySettings)
{
	if (pModifySettings == NULL)
	{
		return;
	}

	CSetsFileXml_InfoGrp *pInfoGrp = NULL;
	POS pos = pModifySettings->GetHeadPosition();

	while (pos != NULL)
	{
		pInfoGrp = (CSetsFileXml_InfoGrp *)pModifySettings->GetNext(pos);
		
		if (pInfoGrp->m_dwReserved != 1)
		{
			continue;
		}

		CSetsFileXml_InfoGrp *pNew = (CSetsFileXml_InfoGrp *)pInfoGrp->CloneEx(); //����¡����
		AddNewChild(pNew);
		pNew->AppendByModify(pInfoGrp);
	}
}

CSetsFileXml_InfoGrp* CSetsFileXml_Settings::FindInforGrpByDesc(const CString &strDesc)
{
	CSetsFileXml_InfoGrp *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		CSetsFileXml_InfoGrp *pInfoGrp = (CSetsFileXml_InfoGrp *)GetNext(pos);

		if (pInfoGrp->m_strDesc == strDesc)
		{
			pFind = pInfoGrp;
			break;
		}
	}

	return pFind;
}

void CSetsFileXml_Settings::ParseToDvm(CDvmLogicDevice *pLDevice)
{
	if (pLDevice == NULL)
	{
		return;
	}

	//long nGrp = 1;   //��ֵ����
	CString strName;
 	if (m_strClass == SETTING_CLASS_SETTING)
 	{
 		strName = _T("������ֵ");
 	}
 
 	if (m_strClass == SETTING_CLASS_PARAMETER)
 	{
 		strName = _T("�豸����");
 	}
 
 	if (m_strClass == SETTING_CLASS_RELAYENA)
 	{
 		strName = _T("��ѹ��");
 	}
	
	//��ֵ���ݼ����Ƕ�����ֵ��װ�ò����͹�����ѹ�����ݼ����ǵ�����ֵ
	//������ֵ�������嶨ֵ����
	//��Ϊ�˺�������һ���ԣ����캯���У���������ֵ�Ķ�ֵ���ţ�Ĭ��Ϊ1
	CDvmDataset *pDataset = new CDvmDataset;
	pLDevice->AddNewChild(pDataset);
	pDataset->m_strID = m_strClass;
	pDataset->m_strName = strName;

	POS pos = GetHeadPosition();
	CSetsFileXml_InfoGrp *pInfoGrp = NULL;

	while (pos != NULL)
	{
		pInfoGrp = (CSetsFileXml_InfoGrp *)GetNext(pos);
		pInfoGrp->ParseToDvm(pDataset, m_nGrp);
	}
}

//����ֵ���ݣ�ƴ�ӳ�һ�����ַ������أ����ڼ���Md5ֵ
void CSetsFileXml_Settings::GetValStringTotal(CString &strValTotal, BOOL bReCalMd5)
{
	strValTotal.Empty();
	CString strVal;

	POS pos = GetHeadPosition();
	CSetsFileXml_InfoGrp *pInfoGrp = NULL;

	while (pos != NULL)
	{
		pInfoGrp = (CSetsFileXml_InfoGrp *)GetNext(pos);
		pInfoGrp->GetValStringTotal(m_nGrp, strVal);
		strValTotal.AppendFormat(_T("%s"), strVal);
	}

	CString strMd5;
	GetMd5_ForCal(strMd5, strValTotal, bReCalMd5);
}

void CSetsFileXml_Settings::GetValStringTotal_V110(CString &strValTotal, BOOL bReCalMd5)
{
	strValTotal.Empty();
	CString strVal;

	POS pos = GetHeadPosition();
	CSetsFileXml_InfoGrp *pInfoGrp = NULL;

	while (pos != NULL)
	{
		pInfoGrp = (CSetsFileXml_InfoGrp *)GetNext(pos);
		pInfoGrp->GetValStringTotal_V110(m_nGrp, strVal);
		strValTotal.AppendFormat(_T("%s"), strVal);
	}

	//ȥ���ո��Ʊ�����س��������з�
// 	strValTotal.Replace(_T(" "), _T(""));
// 	strValTotal.Replace(_T("\t"), _T(""));
// 	strValTotal.Replace(_T("\r"), _T(""));
// 	strValTotal.Replace(_T("\n"), _T(""));
	strValTotal = RemoveOffsetChars(strValTotal);

	CString strMd5;
	GetMd5_ForCal(strMd5, strValTotal, bReCalMd5);
}

//������ֵ����ȡ��ֵ���ݵĴ��ı�
void CSetsFileXml_Settings::GetValStringTotal_V110_Single(CString &strValTotal)
{
	strValTotal.Empty();
	CString strVal;

	POS pos = GetHeadPosition();
	CSetsFileXml_InfoGrp *pInfoGrp = NULL;

	while (pos != NULL)
	{
		strVal = "";
		pInfoGrp = (CSetsFileXml_InfoGrp *)GetNext(pos);
		pInfoGrp->GetValStringTotal_V110_Single(strVal);
		strValTotal.AppendFormat(_T("%s"), strVal);
	}

	//ȥ���ո��Ʊ�����س��������з�
// 	strValTotal.Replace(_T(" "), _T(""));
// 	strValTotal.Replace(_T("\t"), _T(""));
// 	strValTotal.Replace(_T("\r"), _T(""));
// 	strValTotal.Replace(_T("\n"), _T(""));
	strValTotal = RemoveOffsetChars(strValTotal);
}

//������ֵ����ȡָ����ֵ���Ķ�ֵ���ݵĴ��ı�
void CSetsFileXml_Settings::GetValStringToTal_V110_Multi(CString &strValTotal, long nGrp)
{
	strValTotal.Empty();
	CString strVal;

	POS pos = GetHeadPosition();
	CSetsFileXml_InfoGrp *pInfoGrp = NULL;

	while (pos != NULL)
	{
		strVal = "";
		pInfoGrp = (CSetsFileXml_InfoGrp *)GetNext(pos);
		pInfoGrp->GetValStringTotal_V110(nGrp, strVal);
		strValTotal.AppendFormat(_T("%s"), strVal);
	}

	//ȥ���ո��Ʊ�����س��������з�
	// 	strValTotal.Replace(_T(" "), _T(""));
	// 	strValTotal.Replace(_T("\t"), _T(""));
	// 	strValTotal.Replace(_T("\r"), _T(""));
	// 	strValTotal.Replace(_T("\n"), _T(""));
	strValTotal = RemoveOffsetChars(strValTotal);
}

//������ֵ����ȡָ����ֵ���Ķ�ֵ���ݵĴ��ı�
char* CSetsFileXml_Settings::GetValStringToTal_V110_Multi(long nGrp)
{
	char *pszTotal = new char[1024000];
	std::memset(pszTotal, 0, 1024000 * sizeof(char));

	POS pos = GetHeadPosition();
	CSetsFileXml_InfoGrp *pInfoGrp = NULL;

	while (pos != NULL)
	{
		pInfoGrp = (CSetsFileXml_InfoGrp *)GetNext(pos);
		char* pszApd = pInfoGrp->GetValStringTotal_V110(nGrp);
		strcat(pszTotal, pszApd);
		delete []pszApd;
	}

	return pszTotal;
}

void CSetsFileXml_Settings::GetMd5_ForCal(CString &strMd5, const CString &strValTotal, BOOL bReCalMd5)
{
	if (!bReCalMd5)
	{
		//����Ҫ�ظ�����ʱ���ж��Ѿ����������ֱ�ӷ���
		if (m_strMd5_Cal.GetLength() > 0)
		{
			strMd5 = m_strMd5_Cal;
			return;
		}
	}

	char *pchVal = NULL;
	char *pszUtf8 = NULL;
	int nSize = CString_to_char(strValTotal,&pchVal);
	int nDestLen = 0;
	gbk_to_utf8_r((unsigned char*)pchVal, nSize, (unsigned char**)&pszUtf8, &nDestLen, 0);

	CXMD5 oMD5;
	oMD5.update(pszUtf8, nDestLen);
	string str = oMD5.toString();
	strMd5 = str.c_str();
	m_strMd5_Cal = strMd5;

	delete []pchVal;
	delete []pszUtf8;
}

//��ȡ��ֵ��������
long CSetsFileXml_Settings::GetSetGrpNum()
{
	if (m_nGrp <= 0)
	{
		return 1;
	}

	//���ڶ�����ֵ�������ڲ�ͬ��ֵ���飬��ֵ��������һ�µ������������ȡһ����ֵ�������
	CSetsFileXml_InfoGrp *pInfoGrp = (CSetsFileXml_InfoGrp *)FindByClassID(MNGRCLASSID_CSETSFILEXML_INFOGRP);

	if (pInfoGrp == NULL)
	{
		return 1;
	}

	return pInfoGrp->m_nSetGrpNum;
}

BOOL CSetsFileXml_Settings::IsModifyed_Grp(long nGrp)
{
	if (m_dwReserved != 1)
	{
		return FALSE;
	}

	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		CSetsFileXml_InfoGrp *pInfoGrp = (CSetsFileXml_InfoGrp *)GetNext(pos);

		if (pInfoGrp->IsModifyed_Grp(nGrp))
		{
			return TRUE;
		}
	}

	return FALSE;
}

//��ʱֻ�����˶�ֵ�ļ�������Ķ�ֵ + ��ֵ��ֵ����ȷ
long CSetsFileXml_Settings::CmpDataset(CDvmDataset *pDataset, long nGrp, char**ppszRet)
{
	if (pDataset == NULL)
	{
		return 0;
	}

	BOOL bRet = TRUE;
	CString strErrorInfo;
	CDvmData *pData = NULL;
	CString strSIVal;
	CString strID;

	//��������Ϊ��ͨ����ֵ�ļ���װ�ķ�ʽ�޸�װ�ö�ֵ����ͨ��MMS/CMS����ֵ�ļ�������װ��ֵ���бȽ�
	//��ˣ��Զ�ֵ�ļ��Ķ�ֵ������Ϣ��Ϊ��׼������thisָ�롣
	POS pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		//���ڶ����ֵ������Ϣ����Ҫ����
		CSetsFileXml_InfoGrp *pInfoGrp = (CSetsFileXml_InfoGrp *)GetNext(pos);
		POS pos2 = pInfoGrp->GetHeadPosition();

		while (pos2 != NULL)
		{
			CSetsFileXml_SI *pSI = (CSetsFileXml_SI *)pInfoGrp->GetNext(pos2);
			//pData = (CDvmData *)pDataset->FindByName(pSI->m_strDesc);  //ͨ������ӳ��
			CString strLd = pSI->GetLd();
			pData = FindData(pDataset, pSI->m_strDesc, pSI->m_strType, strLd, pSI->m_strRef);

			if (pData == NULL)
			{
				bRet = FALSE;
				strErrorInfo.AppendFormat(_T("CMS/MMS��ȡ��ֵ��ȱ�ٶ�ֵ<%s>\r\n"), pSI->m_strDesc);
				continue;
			}

			strID = pData->m_strID;

		 	if (strLd.GetLength() > 0)
		 	{
		 		long nPos = pSI->m_strRef.Find(strLd);
		 
		 		if (nPos >= 0)
		 		{
		 			strID = pSI->m_strRef.Mid(nPos + strLd.GetLength() + 1);
		 		}
		 	}

			if (pData->m_strID != strID)
			{
				//������һ�£�ͬ�����Ϊ���ϸ�
				bRet = FALSE;

				if (nGrp <= 0)
				{
					strErrorInfo.AppendFormat(_T("��ֵ<%s>·����һ�£�CMS/MMS��ȡ��%s����ֵ�ļ��У�%s\r\n")
						, pSI->m_strDesc, pData->m_strID, strID);
				}
				else
				{
					strErrorInfo.AppendFormat(_T("<%d��>��ֵ<%s>·����һ�£�CMS/MMS��ȡ��%s����ֵ�ļ��У�%s\r\n")
						, nGrp, pSI->m_strDesc, pData->m_strID, strID); 
				}
			}
			
			if (nGrp > 0)
			{
				strSIVal = pSI->GetValByGrp_String(nGrp); //������ֵ��ֻȡָ����ֵ��
			}
			else
			{
				strSIVal = pSI->GetVal_String();  //˵���ǵ�����ֵ
			}

			CString strNewValue;
			if (! IsEqualValue(strSIVal, pSI->m_strUnit, pSI->m_strStep, pData, strNewValue, pSI->m_strType)/*strSIVal != pData->m_strValue*/)
			{
				//�˴�Ҫ��ģ���ļ��е�ֵ�����ղ������档���磺step=0.01��value����2λС��
				bRet = FALSE;

				if (nGrp <= 0)
				{
					strErrorInfo.AppendFormat(_T("��ֵ<%s>��ֵ��һ�£�CMS/MMS��ȡ��%s����ֵ�ļ��У�%s\r\n")
						, pSI->m_strDesc, strNewValue, strSIVal);
				}
				else
				{
					strErrorInfo.AppendFormat(_T("<%d��>��ֵ<%s>��ֵ��һ�£�CMS/MMS��ȡ��%s����ֵ�ļ��У�%s\r\n")
						, nGrp, pSI->m_strDesc, strNewValue, strSIVal); 
				}

				continue;
			}
		}
	}

	//sprintf(*ppszRet, "Rslt=%ld;ErrorInfo=%s;", bRet, strErrorInfo);
	sprintf(*ppszRet, "%s", strErrorInfo);

	return bRet;
}

long CSetsFileXml_Settings::CmpDatasets(CDvmDevice *pDvmDevice, CString &strErrorInfo)
{
	if (pDvmDevice == NULL)
	{
		return 0;
	}

	BOOL bRet = TRUE;
	//�ȸ���ld�����ҵ���Ӧ���߼��豸��LD0��PROT
	CDvmLogicDevice *pLDevice = pDvmDevice->FindByIDHas(m_strLd);

	if (pLDevice == NULL)
	{
		strErrorInfo.Format(_T("�豸ģ���ļ���û�ҵ��߼��豸 [%s]"), m_strLd);
		return FALSE;
	}

	CExBaseList oList;
	long nCount = pLDevice->GetDatasetList(m_strClass, oList);  //��ȡ���ݼ��б�

	if (m_nGrp <= 0)
	{
		//������ֵ
		ASSERT(nCount == 1);

		if (nCount != 1)
		{
			strErrorInfo.Format(_T("�豸ģ���ļ����ҵ� [%d] ��������ֵ���ݼ� [%s]"), nCount, m_strClass);
			oList.RemoveAll();
			return FALSE;
		}

		CDvmDataset *pDataset = (CDvmDataset *)oList.GetHead();
		char *pszRet = new char[1024000];
		std::memset(pszRet, 0, 1024000 * sizeof(char));
		bRet = CmpDataset(pDataset, -1, &pszRet);
		strErrorInfo.AppendFormat(_T("%s"), pszRet);
		delete []pszRet;
	}
	else
	{
		//������ֵ
		long nGrpNum = GetSetGrpNum();
		ASSERT(nCount == nGrpNum);

		if (nCount != nGrpNum)
		{
			strErrorInfo.Format(_T("������ֵ���ݼ� [%s]����ֵ��������ƥ�䣬ģ���ļ��У�[%d]������ֵ�ļ��У�[%d]����"), m_strClass, nCount, nGrpNum);
			oList.RemoveAll();
			return FALSE;
		}

		char *pszRet = new char[1024000];

		for (int n=1; n<=nCount; n++)
		{
			CDvmDataset *pDataset = (CDvmDataset *)oList.GetAtIndex(n-1);

			std::memset(pszRet, 0, 1024000 * sizeof(char));
			BOOL bRet2 = CmpDataset(pDataset, n, &pszRet);
			strErrorInfo.AppendFormat(_T("%s"), pszRet);

			if (!bRet2)
			{
				bRet = FALSE;
			}
		}

		delete []pszRet;
	}

	oList.RemoveAll();
	return bRet;
}

long CSetsFileXml_Settings::CmpSetsFile(CSetFilesXml_DSC *pDscUp, CString &strErrorInfo)
{
	if (pDscUp == NULL)
	{
		return 0;
	}

	BOOL bRet = TRUE;
	CSetsFileXml_Settings *pSettings = pDscUp->FindSettings(m_strClass, m_strLd);

	if (pSettings == NULL)
	{
		strErrorInfo.Format(_T("��ֵ�ļ�_���٣��Ҳ�����ֵ������Ϣ [class��%s, ld��%s]"), m_strClass, m_strLd);
		return FALSE;
	}

	long nSetNumUp = pSettings->GetSetGrpNum();
	long nSetNum = GetSetGrpNum();

	if (nSetNum != nSetNumUp)
	{
		strErrorInfo.Format(_T("��ֵ������Ϣ�� [class��%s, ld��%s]����ֵ��������һ�� [��ֵ�ļ�_���٣�%d����ֵ�ļ�_��װ��%d]")
			, m_strClass, m_strLd, nSetNumUp, nSetNum);
		return FALSE;
	}

	if (nSetNum == 1)
	{
		//������ֵ
		return CmpSetsFile(pSettings, -1, strErrorInfo);
	}
	else
	{
		for (int n=1; n<=nSetNum; n++)
		{
			if (!CmpSetsFile(pSettings, n, strErrorInfo))
			{
				bRet = FALSE;
			}
		}
	}

	return bRet;
}

long CSetsFileXml_Settings::CmpSetsFile(CSetsFileXml_Settings *pSettings, long nGrp, CString &strErrorInfo)
{
	if (pSettings == NULL)
	{
		return 0;
	}

	if (pSettings->m_nInfoGrpNum != m_nInfoGrpNum)
	{
		strErrorInfo.Format(_T("��ֵ������Ϣ�� [class��%s, ld��%s]����ֵ����������һ�� [��ֵ�ļ�_���٣�%d����ֵ�ļ�_��װ��%d]")
			, m_strClass, m_strLd, pSettings->m_nInfoGrpNum, m_nInfoGrpNum);
		return 0;
	}

	BOOL bRet = TRUE;
	CString strSIVal, strSIValUp;

	//��������Ϊ��ͨ����ֵ�ļ���װ�ķ�ʽ�޸�װ�ö�ֵ�������ٶ�ֵ�ļ�������װ��ֵ���бȽ�
	//��ˣ�����װ��ֵ�ļ��Ķ�ֵ������Ϣ��Ϊ��׼������thisָ�롣
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		//���ڶ����ֵ������Ϣ����Ҫ����
		CSetsFileXml_InfoGrp *pInfoGrp = (CSetsFileXml_InfoGrp *)GetNext(pos);
		POS pos2 = pInfoGrp->GetHeadPosition();
		CSetsFileXml_InfoGrp *pInfoGrpUp = pSettings->FindInforGrpByDesc(pInfoGrp->m_strDesc);

		if (pInfoGrpUp == NULL)
		{
			strErrorInfo.AppendFormat(_T("��ֵ�ļ�_������ȱ�ٶ�ֵ����<%s>"), pInfoGrp->m_strDesc);
			bRet = FALSE;
			continue;
		}

		while (pos2 != NULL)
		{
			CSetsFileXml_SI *pSI = (CSetsFileXml_SI *)pInfoGrp->GetNext(pos2);
			CSetsFileXml_SI *pSIUp = pInfoGrpUp->FindSIByRef(pSI->m_strRef);

			if (pSIUp == NULL)
			{
				strErrorInfo.AppendFormat(_T("��ֵ�ļ�_������ȱ�ٶ�ֵ��<ref��%s>   "), pSI->m_strRef);
				bRet = FALSE;
				continue;
			}

			if (nGrp > 0)
			{
				strSIVal = pSI->GetValByGrp_String(nGrp); //������ֵ��ֻȡָ����ֵ��
				strSIValUp = pSIUp->GetValByGrp_String(nGrp); 
			}
			else
			{
				strSIVal = pSI->GetVal_String();  //˵���ǵ�����ֵ
				strSIValUp = pSIUp->GetVal_String(); 
			}

			if (strSIVal != strSIValUp)
			{
				//�˴�Ҫ��ģ���ļ��е�ֵ�����ղ������档���磺step=0.01��value����2λС��
				bRet = FALSE;

				if (nGrp <= 0)
				{
					strErrorInfo.AppendFormat(_T("��ֵ<%s>��ֵ��һ�£���ֵ�ļ�_���٣�%s����ֵ�ļ�_��װ��%s��   ")
						, pSI->m_strDesc, strSIValUp, strSIVal); 
				}
				else
				{
					strErrorInfo.AppendFormat(_T("<%d��>��ֵ<%s>��ֵ��һ�£���ֵ�ļ�_���٣�%s����ֵ�ļ�_��װ��%s��   ")
						, nGrp, pSI->m_strDesc, strSIValUp, strSIVal); 
				}
				
				continue;
			}
		}
	}

	return bRet;
}

//INT32  FLOAT32  STRING  BOOLEAN  HEX16
CDvmData* CSetsFileXml_Settings::FindData(CDvmDataset *pDataset, const CString &strName, const CString &strDataType
										  , const CString &strLD, const CString &strRef)
{
	if (pDataset == NULL)
	{
		return NULL;
	}

	if (pDataset->GetCount() == 0)
	{
		return NULL;
	}

	//2024-12-17 ���ִ����������������װ���У�ͨ��ģ���ļ���ȡ������ֵ�ļ��д���������ֵ��·��Ū�������
	//���ͻ���ͨ��������ƥ��Ϊ׼��
	//��������������������£���ͨ�����ƺ��������Ͳ��ң�
	CDvmData *pFind = NULL;
	CString strName2 = strName;
	//���Ե��ļ��������ǡ�������ֵ��***�����������֣�***��
	strName2.Replace(_T("������ֵ��"), _T(""));
	strName2.Replace(_T("�����֣�"), _T(""));

	POS pos = pDataset->GetHeadPosition();
	CString strMapDataType = GetDataTypeMap(strDataType);

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pDataset->GetNext(pos);

		if (pData->m_strName != strName2)
		{
			continue;
		}

		if (strMapDataType != GetDataType(pData))
		{
			continue;
		}

		pFind = pData;
		break;
	}

 	if (pFind != NULL)
 	{
 		return pFind;
 	}

	//��ͨ��·������
	//��ͨ�����ƺ����������Ҳ���ʱ����ͨ��·�����ң�ʱ�䶨ֵ��ģ���ļ��е�λΪms����������ΪINT����ֵ�ļ��е�λΪs����������ΪFLOAT32
 	if (strLD.GetLength() > 0)
 	{
 		CString strID;
 		long nPos = strRef.Find(strLD);
 
 		if (nPos >= 0)
 		{
 			strID = strRef.Mid(nPos + strLD.GetLength() + 1);
 			pFind = (CDvmData *)pDataset->FindByID(strID);
 		}
 	}

	return pFind;
}

//INT32  INT32U  FLOAT32  STRING  BOOLEAN  HEX16  HEX32   IPSTR
//�β�ΪSI���������ͣ����ص���ģ���е���������
//���У�IPSTR��ʱδ����
CString CSetsFileXml_Settings::GetDataTypeMap(const CString &strDataType)
{
	if (strDataType == _T("INT32")
		|| strDataType == _T("INT32U"))
	{
		return _T("INT");
	}
	else if (strDataType == _T("FLOAT32"))
	{
		return _T("FLOAT");
	}
	else if (strDataType == _T("STRING"))
	{
		return _T("UTF8_STR");
	}
	else if (strDataType == _T("BOOLEAN"))
	{
		return _T("BOOL");
	}
	else if (strDataType == _T("HEX16"))
	{
		return _T("HEX16");
	}
	else if (strDataType == _T("HEX32"))
	{
		return _T("HEX32");
	}
	else
	{
		return _T("UTF8_STR");//Ĭ���ַ���
	}
}

CString CSetsFileXml_Settings::GetDataType(CDvmData *pData)
{
	if (m_strID == SETTING_CLASS_MATRIX
		&& pData->m_strID.Find(_T("MATR")) >= 0)
	{
		//��բ����
		return _T("HEX16");
	}

	if (pData->m_strDataType == _T("INT")
		|| pData->m_strDataType == _T("FLOAT")
		|| pData->m_strDataType == _T("UTF8_STR")
		|| pData->m_strDataType == _T("BOOL") )
	{
		return pData->m_strDataType;
	}

	CDvmValue *pFind = pData->GetDataValue();   //���س�$t  $q֮��ĵ�һ��pDvmData�Ӷ���

	if (pFind == NULL)
	{
		return pData->m_strDataType;
	}

	return pFind->m_strDataType;
}

BOOL CSetsFileXml_Settings::IsEqualValue(const CString &strSIVal, const CString &strSIUnit, const CString &strStep, CDvmData *pData, CString &strNewValue, const CString &strSIDataType)
{
	CString strDataType;

	if (strSIDataType.GetLength() > 0)
	{
		strDataType = GetDataTypeMap(strSIDataType);; //�Զ�ֵ�ļ��е���������Ϊ׼
	}
	else
	{
		strDataType = GetDataType(pData);
	}

	CString strUnit1, strUnit2;
	strUnit1 = strSIUnit;
	strUnit2 = pData->m_strUnit;
	strUnit2.MakeLower();
	strUnit1.MakeLower();

	if (strUnit1 == _T("s") 
		/*&& strUnit2 == _T("ms") && strDataType == _T("INT")*/)
	{
		//˵����ʱ�䶨ֵ��˫�ߵ�λ��һ�£���ֵ�ļ���s��MMS��ms
		//Ŀǰ�������������ģ���ļ��еĵ�λΪ�գ����������strUnit2
		double fSIVal = CString_To_double(strSIVal);
		long nValue1 = (fSIVal * 1000);
		long nValue2 = CString_To_long(pData->m_strValue);

		return (nValue2 == nValue1);
	}

	if (strDataType == _T("HEX16"))
	{
		//HEX16��0x0000~0xFFFF��
		long nVal = CString_To_ulong(pData->m_strValue);
		CString strFormat,strTextValue;
		strFormat.Format(_T("0x%%0%dx"), 4);
		strTextValue.Format(strFormat.GetString(), nVal);

		CString strValue = strSIVal;
		strValue.MakeLower();
		strNewValue = strTextValue;
		return (strValue == strTextValue);
	}
	else if (strDataType == _T("HEX32"))
	{
		//HEX32��0x00000000~0xFFFFFFFF
		long nVal = CString_To_ulong(pData->m_strValue);
		CString strFormat,strTextValue;
		strFormat.Format(_T("0x%%0%dx"), 8);
		strTextValue.Format(strFormat.GetString(), nVal);

		CString strValue = strSIVal;
		strValue.MakeLower();
		strNewValue = strTextValue;
		return (strValue == strTextValue);
	}
	else if (strDataType == _T("INT")
		|| strDataType == _T("BOOL"))
	{
		long nValue1 = CString_To_long(strSIVal);
		long nValue2 = CString_To_long(pData->m_strValue);
		strNewValue.Format(_T("%d"), nValue2);
		return (nValue2 == nValue1);
	}
	else if (strDataType == _T("FLOAT"))
	{
		strNewValue = GetValDealStep(strStep, pData->m_strValue);
		return (strSIVal == strNewValue);
	}
	else
	{
		strNewValue = pData->m_strValue;
		return (pData->m_strValue == strSIVal);
	}
}

CString CSetsFileXml_Settings::GetValDealStep(const CString &strStep, const CString &strValue)
{
	CString strNewValue;
	int nPos = strStep.Find(".");
	int nXS = -1;
	if (nPos > 0)
	{
		nPos += 1;
		int nLen = strStep.GetLength();
		nXS = nLen - nPos;
	}

	CString strFormat;

	if (nXS == -1)
	{
		//ĳЩװ�ã�CT���ζֵ��min=1��step=4��max=5
		//��������������FLOAT����ֵ�ļ��е�ֵ��1��5��û��С����
		nXS = 0;  
	}
	strFormat.Format(_T("%%.%df"), nXS);

	double fCurrValTemp = atof(strValue);
	CString strNewTextTemp = "";
	strNewValue.Format(strFormat, fCurrValTemp);
	return strNewValue;
}
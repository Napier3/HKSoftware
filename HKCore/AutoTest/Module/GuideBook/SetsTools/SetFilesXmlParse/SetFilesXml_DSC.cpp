//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SetFilesXml_DSC.cpp  CSetFilesXml_DSC


#include "stdafx.h"
#include "SetFilesXml_DSC.h"
#include "..\..\..\..\..\Module\API\Xmd5.h"
#include "..\..\..\..\..\Module\API\StringConvert\String_Gbk_To_Utf8.h"
#include "..\..\..\..\..\Module\DataMngr\DvmDevice.h"


using namespace pugi;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSetFilesXml_DSC::CSetFilesXml_DSC()
{
	//��ʼ������

	//��ʼ����Ա����
	m_pHeader = NULL;
	m_pHashInfo = NULL;
	m_pDevInfo = NULL;
	m_pFileInfo = NULL;
	m_nSetsZone = 1;
	m_pLDevice = NULL;
	m_pUpdateInfo = NULL;

	m_pRWDoc = NULL;
	m_pNode = NULL;
	m_pRemark = NULL;

	m_pNodeHashInfoBk = NULL;

	m_strMd5_Cal_Parameter = "";   
	m_strMd5_Cal_Setting = "";  
	m_strMd5_Cal_Ena = "";
	m_strMd5_Cal_MatrixSet = "";
	m_strMd5_Cal_VtcParameter = "";

	m_strSettingFilePath = "";
	m_strSettingFileName = "";
}

CSetFilesXml_DSC::~CSetFilesXml_DSC()
{
	if (m_pRWDoc != NULL)
	{
		delete m_pRWDoc;
		m_pRWDoc = NULL;
	}
}

long CSetFilesXml_DSC::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	CXmlRWNode_Pugi *pNode = (CXmlRWNode_Pugi *)&oNode;
	m_pNode = &(pNode->m_oPugiXmlNode);

	xml_GetAttibuteValue(pXmlKeys->m_strConfigVersionKey, oNode, m_strConfigVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strFileKey, oNode, m_strFile);

	return 0;
}

long CSetFilesXml_DSC::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strConfigVersionKey, oElement, m_strConfigVersion);

	if (m_strFile.GetLength() > 10)
	{
		xml_SetAttributeValue(pXmlKeys->m_strFileKey, oElement, m_strFile);
	}

	return 0;
}

long CSetFilesXml_DSC::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strConfigVersion);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strConfigVersion);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strConfigVersion);
	}
	return 0;
}

void CSetFilesXml_DSC::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CSETSFILEXML_HEADER)
		{
			m_pHeader = (CSetsFileXml_Header*)p;
		}
		else if (nClassID == MNGRCLASSID_CSETSFILEXML_HASHINFO)
		{
			m_pHashInfo = (CSetsFileXml_HashInfo*)p;
		}
		else if (nClassID == MNGRCLASSID_CSETSFILEXML_DEVINFO)
		{
			m_pDevInfo = (CSetsFileXml_DevInfo*)p;
		}
		else if (nClassID == MNGRCLASSID_CSETSFILEXML_FILEINFO)
		{
			m_pFileInfo = (CSetsFileXml_FileInfo*)p;
		}
		else if (nClassID == MNGRCLASSID_CSETSFILEXML_UPDATE)
		{
			m_pUpdateInfo = (CSetsFileXml_Update*)p;
		}
		else if (nClassID == MNGRCLASSID_CSETSFILEXML_REMARK)
		{
			m_pRemark = (CSetsFileXml_Remark*)p;
		}
	}

	if (m_pHeader == NULL)
	{
		m_pHeader = (CSetsFileXml_Header*)AddNewChild(new CSetsFileXml_Header());
	}

	if (m_pHashInfo == NULL)
	{
		m_pHashInfo = (CSetsFileXml_HashInfo*)AddNewChild(new CSetsFileXml_HashInfo());
	}

	if (m_pDevInfo == NULL)
	{
		m_pDevInfo = (CSetsFileXml_DevInfo*)AddNewChild(new CSetsFileXml_DevInfo());
	}

	if (m_pFileInfo == NULL)
	{
		m_pFileInfo = (CSetsFileXml_FileInfo*)AddNewChild(new CSetsFileXml_FileInfo());
	}

	if (m_pUpdateInfo == NULL)
	{
		m_pUpdateInfo = (CSetsFileXml_Update*)AddNewChild(new CSetsFileXml_Update());
	}

	if (m_pRemark == NULL)
	{
		m_pRemark = (CSetsFileXml_Remark *)AddNewChild(new CSetsFileXml_Remark());
	}

	BringToTail(m_pRemark);
	ParseToDvm();

	/*

	#define SETTING_CLASS_PARAMETER   _T("dsParameter")
	#define SETTING_CLASS_SETTING     _T("dsSetting")
	#define SETTING_CLASS_RELAYENA    _T("dsRelayEna")
	#define SETTING_CLASS_CTRL        _T("dsCtrl")
	#define SETTING_CLASS_MATRIX      _T("dsMatrix")
	*/
	//for debug
	// 	CString strMd5;
	// 	GetMd5_FromCal(SETTING_CLASS_PARAMETER, strMd5);
	// 	GetMd5_FromCal(SETTING_CLASS_SETTING, strMd5);
	// 	GetMd5_FromCal(SETTING_CLASS_RELAYENA, strMd5);
	// 	GetMd5_FromCal(SETTING_CLASS_VTCPARAMETER, strMd5);
}

BOOL CSetFilesXml_DSC::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSetFilesXml_DSC *p = (CSetFilesXml_DSC*)pObj;

	if(m_strConfigVersion != p->m_strConfigVersion)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSetFilesXml_DSC::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSetFilesXml_DSC *p = (CSetFilesXml_DSC*)pDest;

	p->m_strConfigVersion = m_strConfigVersion;
	return TRUE;
}

CBaseObject* CSetFilesXml_DSC::Clone()
{
	CSetFilesXml_DSC *p = new CSetFilesXml_DSC();
	Copy(p);
	return p;
}

CBaseObject* CSetFilesXml_DSC::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSetFilesXml_DSC *p = new CSetFilesXml_DSC();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSetFilesXml_DSC::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSETSFILEXML_HEADER)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSETSFILEXML_HASHINFO)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSETSFILEXML_DEVINFO)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSETSFILEXML_FILEINFO)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSETSFILEXML_SETTINGS)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSETSFILEXML_REMARK)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSETSFILEXML_UPDATE)
	{
		return TRUE;
	}


	return FALSE;
}

CExBaseObject* CSetFilesXml_DSC::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSetsFileXml_HeaderKey)
	{
		pNew = new CSetsFileXml_Header();
	}
	else if (strClassID == pXmlKeys->m_strCSetsFileXml_HashInfoKey)
	{
		pNew = new CSetsFileXml_HashInfo();
	}
	else if (strClassID == pXmlKeys->m_strCSetsFileXml_DevInfoKey)
	{
		pNew = new CSetsFileXml_DevInfo();
	}
	else if (strClassID == pXmlKeys->m_strCSetsFileXml_FileInfoKey)
	{
		pNew = new CSetsFileXml_FileInfo();
	}
	else if (strClassID == pXmlKeys->m_strCSetsFileXml_SettingsKey)
	{
		pNew = new CSetsFileXml_Settings();
	}
	else if (strClassID == pXmlKeys->m_strCSetsFileXml_RemarkKey)
	{
		pNew = new CSetsFileXml_Remark();
	}
	else if (strClassID == pXmlKeys->m_strUpdateKey)
	{
		pNew = new CSetsFileXml_Update();
	}

	return pNew;
}

CExBaseObject* CSetFilesXml_DSC::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSETSFILEXML_HEADER)
	{
		pNew = new CSetsFileXml_Header();
	}
	else if (nClassID == MNGRCLASSID_CSETSFILEXML_HASHINFO)
	{
		pNew = new CSetsFileXml_HashInfo();
	}
	else if (nClassID == MNGRCLASSID_CSETSFILEXML_DEVINFO)
	{
		pNew = new CSetsFileXml_DevInfo();
	}
	else if (nClassID == MNGRCLASSID_CSETSFILEXML_FILEINFO)
	{
		pNew = new CSetsFileXml_FileInfo();
	}
	else if (nClassID == MNGRCLASSID_CSETSFILEXML_SETTINGS)
	{
		pNew = new CSetsFileXml_Settings();
	}
	else if (nClassID == MNGRCLASSID_CSETSFILEXML_REMARK)
	{
		pNew = new CSetsFileXml_Remark();
	}
	else if (nClassID == MNGRCLASSID_CSETSFILEXML_UPDATE)
	{
		pNew = new CSetsFileXml_Update();
	}

	return pNew;
}

BOOL CSetFilesXml_DSC::OpenXmlFile(const CString &strFile, BSTR bstrElementKey, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType)
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

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(nXmlRWType);

	try
	{
		if ( !xml_OpenFile(pRWDoc, strFile) )//����XMLInterface.h�е�ȫ�ֺ�����������Դ����ڷ��ظ�oDoc��
		{
			delete pRWDoc;
			return FALSE;
		}
	}
	catch (...)
	{
		delete pRWDoc;
		return FALSE;
	}

	CXmlRWNodeBase *pDocRoot = pRWDoc->GetDocNode();

	if (bstrElementKey != NULL)
	{
		pDocRoot = pDocRoot->GetChildNode(bstrElementKey);
	}
	else
	{
		delete pRWDoc;
		return FALSE;
		//pDocRoot = pRWDoc->GetDocNode();
	}

	if (pDocRoot == NULL)
	{
		delete pRWDoc;
		return FALSE;
	}

	if(!pDocRoot->IsValid())
	{
		delete pRWDoc;
		return FALSE;
	}

	XmlRead(*pDocRoot, pXmlRWKeys);
	m_pRWDoc = pRWDoc;
	//delete pRWDoc;

	return TRUE;
}

BOOL CSetFilesXml_DSC::OpenXmlFile(const CString &strFile, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType)
{
	BSTR bstrElementKey = GetXmlElementKey();//�麯�������ö�ֱ̬�ӵ�������Ĵ˺��������ؾ�̬��Ա������ֵ��ʵ�ʲ���Ϊ{      return CXLanguageXmlRWKeys::CXLanguageMngrKey();     }
	return OpenXmlFile(strFile, bstrElementKey, pXmlRWKeys,nXmlRWType);//�м����Ϊ�ո������Թؼ����ﾲ̬����ָ��ָ��Ķ����Ա������ֵ�����Ӧ�˸��ڵ�����ƣ�
}

void CSetFilesXml_DSC::ParseToDvm()
{
	if (m_pLDevice == NULL)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CSETSFILEXML_SETTINGS)
		{
			continue;
		}

		CSetsFileXml_Settings *pSettings = (CSetsFileXml_Settings *)pObj;
		pSettings->ParseToDvm(m_pLDevice);
	}
}

CSetsFileXml_Settings* CSetFilesXml_DSC::FindSettingsByClass(const CString &strClass)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CSetsFileXml_Settings *pSettings = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CSETSFILEXML_SETTINGS)
		{
			continue;
		}

		pSettings = (CSetsFileXml_Settings *)pObj;

		if (pSettings->m_strClass == strClass)
		{
			break;
		}
	}

	return pSettings;
}

CSetsFileXml_Settings* CSetFilesXml_DSC::FindSettings(const CString &strClass, const CString &strLD)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CSetsFileXml_Settings *pSettings = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CSETSFILEXML_SETTINGS)
		{
			continue;
		}

		pSettings = (CSetsFileXml_Settings *)pObj;

		if (pSettings->m_strClass == strClass
			&& pSettings->m_strLd == strLD)
		{
			break;
		}
	}

	return pSettings;
}

void CSetFilesXml_DSC::GetSettingsValTotl(CString &strValTotal)
{
	CString strVal;
	strValTotal.Empty();
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CSetsFileXml_Settings *pSettings = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CSETSFILEXML_SETTINGS)
		{
			continue;
		}

		pSettings = (CSetsFileXml_Settings *)pObj;
		pSettings->GetValStringTotal(strVal);
		strValTotal.AppendFormat(_T("%s"), strVal);
	}
}

void CSetFilesXml_DSC::GetSettingsValTotal_ByVersion(const CString &strClass, CString &strValTotal, BOOL bReCalMd5)
{
	if (m_strConfigVersion.Find(_T("1.00")) >= 0)
	{
		//V1.00�汾
		GetSettingsValTotl(strClass, strValTotal);
	}
	else if (m_strConfigVersion.Find(_T("1.10")) >= 0)
	{
		//V1.10�汾
		GetSettingsValTotl_V110(strClass, strValTotal, bReCalMd5);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("��ǰ�汾���ݲ�֧�ּ���md5ֵ��configVersion=%s"), m_strConfigVersion.GetString());
	}
}

void CSetFilesXml_DSC::GetSettingsValTotl(const CString &strClass, CString &strValTotal)
{
	strValTotal.Empty();
	CSetsFileXml_Settings *pSettings = FindSettingsByClass(strClass);

	if (pSettings == NULL)
	{
		GetSettingsValTotl(strValTotal);
		return;
	}

	pSettings->GetValStringTotal(strValTotal);
}

void CSetFilesXml_DSC::GetSettingsValTotl_V110(const CString &strClass, CString &strValTotal, BOOL bReCalMd5)
{
	strValTotal.Empty();
	CSetsFileXml_Settings *pSettings = FindSettingsByClass(strClass);

	if (pSettings == NULL)
	{
		//GetSettingsValTotl_V110(strValTotal);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("û�ҵ���Ӧ�Ķ�ֵ������Ϣ�Σ�class=%s"), strClass.GetString());
		return;
	}

	pSettings->GetValStringTotal_V110(strValTotal, bReCalMd5);
}

//���ض�ֵ���ļ��еĹ�ϣֵ
void CSetFilesXml_DSC::GetMd5_FromFile(const CString &strClass, CString &strMd5)
{
	if (strClass == _T(""))
	{
		//Ϊ��  �����ܵĹ�ϣֵ
		if (m_pHeader == NULL)
		{
			return ;
		}

		strMd5 = m_pHeader->m_strmd5;
		return;
	}

	if (m_pHashInfo == NULL)
	{
		return ;
	}

	m_pHashInfo->GetMd5_FromFile(strClass, strMd5);
}

void CSetFilesXml_DSC::GetMd5_FromCal(const CString &strClass, CString &strMd5)
{
	if (strClass == SETTING_CLASS_PARAMETER)
	{
		if (m_strMd5_Cal_Parameter.GetLength() > 0)
		{
			strMd5 = m_strMd5_Cal_Parameter;
			return;
		}
	}
	else if (strClass == SETTING_CLASS_SETTING)
	{
		if (m_strMd5_Cal_Setting.GetLength() > 0)
		{
			strMd5 = m_strMd5_Cal_Setting;
			return;
		}
	}
	else if (strClass == SETTING_CLASS_RELAYENA)
	{
		if (m_strMd5_Cal_Ena.GetLength() > 0)
		{
			strMd5 = m_strMd5_Cal_Ena;
			return;
		}
	}
	else if (strClass == SETTING_CLASS_MATRIX)
	{
		if (m_strMd5_Cal_MatrixSet.GetLength() > 0)
		{
			strMd5 = m_strMd5_Cal_MatrixSet;
			return;
		}
	}

	CString strValTotal;
	GetSettingsValTotal_ByVersion(strClass, strValTotal, TRUE);
	char *pchVal = NULL;
	char *pszUtf8 = NULL;
	int nSize = CString_to_char(strValTotal,&pchVal);
	int nDestLen = 0;
	gbk_to_utf8_r((unsigned char*)pchVal, nSize, (unsigned char**)&pszUtf8, &nDestLen, 0);

	CXMD5 oMD5;
	oMD5.update(pszUtf8, nDestLen);
	string str = oMD5.toString();
	strMd5 = str.c_str();
	delete []pchVal;
	delete []pszUtf8;

	if (strClass == SETTING_CLASS_PARAMETER)
	{
		m_strMd5_Cal_Parameter = strMd5;
	}
	else if (strClass == SETTING_CLASS_SETTING)
	{
		m_strMd5_Cal_Setting = strMd5;
	}
	else if (strClass == SETTING_CLASS_RELAYENA)
	{
		m_strMd5_Cal_Ena = strMd5;
	}
	else if (strClass == SETTING_CLASS_MATRIX)
	{
		m_strMd5_Cal_MatrixSet = strMd5;
	}
}

void CSetFilesXml_DSC::ClearUpdateInfo(BOOL bDeleteUpdate)
{
	if (m_pUpdateInfo == NULL)
	{
		return;
	}
	//ASSERT(m_pUpdateInfo != NULL);

	m_pUpdateInfo->ClearAllXmlNode();
	m_pUpdateInfo->DeleteAll();

	if (bDeleteUpdate)
	{
		if (m_pNode != NULL)
		{
			pugi::xml_node oUpdate = m_pNode->child(CSetFileXmlParseXmlRWKeys::CSetsFileXml_UpdateKey());

			if (! oUpdate.empty())
			{
				m_pNode->remove_child(oUpdate);
			}
		}

		Delete(m_pUpdateInfo);
		m_pUpdateInfo = NULL;
		return;
	}

	//xml ��node ͬʱ����Ϊ0
	m_pUpdateInfo->SetItemNum(0);
}

/*
md5ֵ�ļ��㣬�Ƿ�������ġ������ڶ�����ֵ���ԣ��Ǹ��ݶ�ֵ���ż����
���ڶ�����ֵ����װ��ֵʱ����ͬʱ�޸Ĺ�������Ķ�ֵ��Update��Ϣ���У��Ǹ��ݶ�ֵ���Ž������ֵ�
��HashInfo���У��޷����ֶ������������װ��ֵ�ļ�ǰ����HI��Ŀȫ�����
*/
void CSetFilesXml_DSC::ClearHashInfo(BOOL bBk)
{
	ASSERT(m_pHashInfo != NULL);

	if (bBk)
	{
		m_oListHashInfoBk.Append(*m_pHashInfo);
		m_pHashInfo->RemoveAll();
	}
	else
	{
		m_pHashInfo->DeleteAll();
	}

	//�Ƴ�/ɾ��pNode     node�Ƴ��ӽڵ㣬��ɾ���ڴ�  �����������
	m_pHashInfo->ClearAllXmlNode();
	m_pHashInfo->SetItemNum(0);

}

void CSetFilesXml_DSC::AppendHashInfoFromBk()
{
	ASSERT(m_pHashInfo != NULL);
	long nCount = m_oListHashInfoBk.GetCount();

	if (nCount > 0)
	{
		m_pHashInfo->AppendEx(m_oListHashInfoBk);
		//m_pHashInfo->m_nItemNum = m_pHashInfo->GetCount();
		m_oListHashInfoBk.RemoveAll();

		//��� pNode�����HI
		char* psz = NULL;
		wchar_t *pW = NULL;
		CSetsFileXml_HI *pHI = NULL;
		POS posHI = m_pHashInfo->GetHeadPosition();
		while (posHI != NULL)
		{
			pHI = (CSetsFileXml_HI *)m_pHashInfo->GetNext(posHI);
			if(pHI != NULL)
			{
				pugi::xml_node oHI = m_pHashInfo->m_pNode->append_child(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strCSetsFileXml_HIKey);
				pugi::xml_attribute attr1 = oHI.append_attribute(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strClassKey);
				psz = NULL;
				pW = NULL;
				CString_to_char(pHI->m_strClass, &psz);
				Char_to_WChart(psz, &pW);
				attr1.set_value(pW);
				delete []psz;
				delete []pW;

				pugi::xml_attribute attr2 = oHI.append_attribute(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strMd5Key);
				psz = NULL;
				pW = NULL;
				CString_to_char(pHI->m_strmd5, &psz);
				Char_to_WChart(psz, &pW);
				attr2.set_value(pW);
				delete []psz;
				delete []pW;
			}
		}
	}
	m_pHashInfo->SetItemNum(nCount);
}

//��װǰ�����ݱ༭�����㶨ֵ��md5�����浽Update��Ϣ��
void CSetFilesXml_DSC::CalSettingsMd5ByModify()
{
	//TODO��YUANTING���˴�Ҫ�����ж�m_pUpdateInfo�Ƿ�Ϊ�գ���Ϊ����ģ����쳣1��
	//��m_pUpdateInfoΪ�գ�����Ҫ��m_pUpdateInfo  new��������ͬʱ����m_pNode�ĵط���this�����
	if(m_pUpdateInfo == NULL)
	{
		AddNewUpdate();
	}

	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pObj = (CExBaseObject *)GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CSETSFILEXML_SETTINGS)
		{
			continue;
		}

		CSetsFileXml_Settings *pSettings = (CSetsFileXml_Settings *)pObj;

		if (pSettings->m_dwReserved != 1)
		{
			continue;
		}

		if (pSettings->m_nGrp > 0)
		{
			//������ֵ����Ҫ�����ж�ÿ�������Ƿ񱻱༭��ֻ���㱻�༭������md5
			CalSettingsMd5ByModify_Multi(pSettings);
		}
		else
		{
			//������ֵ��grp�����塣�����ʼ��ֵΪ0��-1��
			//������ֵ��ֱ�Ӽ��㼴��
			CString strTotalText, strMd5;
			pSettings->GetValStringTotal_V110_Single(strTotalText);
			pSettings->GetMd5_ForCal(strMd5, strTotalText, TRUE);
			m_pUpdateInfo->AddNewUI(pSettings->m_strLd, pSettings->m_strClass, 0, strMd5);//��ֵ���� = 0����ʾ������ֵ
		}
	}
}

//������ֵ�����ݱ༭������md5�����浽Update��Ϣ��
void CSetFilesXml_DSC::CalSettingsMd5ByModify_Multi(CSetsFileXml_Settings *pSettings)
{
	if (pSettings == NULL)
	{
		return;
	}

	if (pSettings->m_nGrp <= 0)
	{
		//˵���ǵ�����ֵ
		return;
	}

	long nSetGrpNum = pSettings->GetSetGrpNum(); //��ֵ��������

	for (long i=1; i<=nSetGrpNum; i++)
	{
		if (!pSettings->IsModifyed_Grp(i))
		{
			continue;
		}

		CString strTotalText, strMd5;
		pSettings->GetValStringToTal_V110_Multi(strTotalText, i);
		pSettings->GetMd5_ForCal(strMd5, strTotalText, TRUE);
		m_pUpdateInfo->AddNewUI(pSettings->m_strLd, pSettings->m_strClass, i, strMd5);
	}
}

void CSetFilesXml_DSC::SetModifyedFlag(BOOL bFlag)
{
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pObj = (CExBaseObject *)GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CSETSFILEXML_SETTINGS)
		{
			continue;
		}

		CSetsFileXml_Settings *pSettings = (CSetsFileXml_Settings *)pObj;
		pSettings->SetModifyedFlag(bFlag);
	}
}

//�β�ΪԴ�����µ�thisָ���У�ֻ����Setting����
void CSetFilesXml_DSC::UpdateSettings(CSetFilesXml_DSC *pSrcDevice)
{
	if (pSrcDevice == NULL)
	{
		return;
	}

	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	POS pos = pSrcDevice->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = (CExBaseObject *)pSrcDevice->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CSETSFILEXML_SETTINGS)
		{
			continue;
		}

		CSetsFileXml_Settings *pSettings = (CSetsFileXml_Settings *)pObj;
		CSetsFileXml_Settings *pDest = FindSettings(pSettings->m_strClass, pSettings->m_strLd);

		if (pSettings == NULL || pDest == NULL)
		{
			continue;
		}

		pDest->UpdateSettings(pSettings);
	}
}

//�β��Ǳ��༭�Ķ���ͨ��m_dwReserved��ǣ���ӱ��޸ĵĶ���thisָ��
void CSetFilesXml_DSC::AppendByModify(CSetFilesXml_DSC *pDeviceModify)
{
	if (pDeviceModify == NULL)
	{
		return;
	}

	m_strFile = pDeviceModify->m_strFileTemp;

	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	POS pos = pDeviceModify->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = (CExBaseObject *)pDeviceModify->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CSETSFILEXML_SETTINGS)
		{
			continue;
		}

		CSetsFileXml_Settings *pSettings = (CSetsFileXml_Settings *)pObj;

		if (pSettings->m_dwReserved != 1)
		{
			continue;
		}

		CSetsFileXml_Settings *pNew = (CSetsFileXml_Settings *)pSettings->CloneEx(); //����¡����
		AddNewChild(pNew);
		pNew->AppendByModify(pSettings);
	}
}

//����ͷ����Ϣ���ļ��޸�ʱ�䡢�ļ���MD5��
void CSetFilesXml_DSC::UpdateHeader()
{
	if (m_pHeader == NULL)
	{
		return;
	}

	SYSTEMTIME oTime;
	::GetLocalTime(&oTime);
	CString strTime;
	strTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d")
		, oTime.wYear, oTime.wMonth, oTime.wDay, oTime.wHour, oTime.wMinute, oTime.wSecond);
	m_pHeader->SetUpdateTime(strTime);

	if (m_pNode == NULL)
	{
		CalTotalSettingsMd5();
	}
	else
	{
		CalTotalSettingsMd5_XmlNode();
	}
}	

/*
У�˷�ΧΪ����<Settings>����
������</Settings>����ĩ��֮�䣨�������к�ĩ�У�ȥ���ո��Ʊ����
�س������к�������ַ����ݣ�ʮ�������ַ����ô�д������ΪHEX
*/
CString CSetFilesXml_DSC::CalTotalSettingsMd5(bool bIsUpdateHeader)
{
	if (m_pHeader == NULL)
	{
		return "";
	}

	POS pos = GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;
	CString strSettings, strTotal;

	while (pos != NULL)
	{
		pObj = (CExBaseObject *)GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CSETSFILEXML_SETTINGS)
		{
			continue;
		}

		CSetsFileXml_Settings *pSettings = (CSetsFileXml_Settings *)pObj;
		strSettings = pSettings->GetXml(CSetFileXmlParseXmlRWKeys::g_pXmlKeys);
		strTotal += strSettings;
	}

	//ȥ���ո��Ʊ�����س��������з�
	// 	strTotal.Replace(_T(" "), _T(""));
	// 	strTotal.Replace(_T("\t"), _T(""));
	// 	strTotal.Replace(_T("\r"), _T(""));
	// 	strTotal.Replace(_T("\n"), _T(""));
	strTotal = RemoveOffsetChars(strTotal);

	char *pchVal = NULL;
	char *pszUtf8 = NULL;
	int nSize = CString_to_char(strTotal,&pchVal);
	int nDestLen = 0;
	gbk_to_utf8_r((unsigned char*)pchVal, nSize, (unsigned char**)&pszUtf8, &nDestLen, 0);

	CXMD5 oMD5;
	oMD5.update(pszUtf8, nDestLen);
	string str = oMD5.toString();
	CString strMd5 = str.c_str();
	//m_pHeader->m_strmd5 = strMd5;

	//m_pHeader->SetMd5(strMd5);
	if(bIsUpdateHeader)
	{
		m_pHeader->SetMd5(strMd5);
	}

	// 	CFile oFile;
	// 	CString strFile = _T("D:\\0\\SetsFileTest\\FileAfterCalMd5.txt");
	// 	if (oFile.Open(strFile, CFile::modeWrite|CFile::modeCreate))
	//	{
	//		oFile.Write(pchVal, strlen(pchVal));
	//		oFile.Close();
	// 	}

	delete []pchVal;
	delete []pszUtf8;

	return strMd5;
}

CString CSetFilesXml_DSC::CalTotalSettingsMd5_XmlNode(bool bIsUpdateHeader)
{
	if (m_pHeader == NULL)
	{
		return "";
	}

	POS pos = GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;
	char *pszSettings = NULL;
	char *pszTotal = new char[1024000];
	std::memset(pszTotal, 0, 1024000 * sizeof(char));

	while (pos != NULL)
	{
		pObj = (CExBaseObject *)GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CSETSFILEXML_SETTINGS)
		{
			continue;
		}

		CSetsFileXml_Settings *pSettings = (CSetsFileXml_Settings *)pObj;
		pszSettings = pSettings->GetXml_XmlNode();
		strcat(pszTotal, pszSettings);
		delete []pszSettings;
	}

	char *pchVal = removeSpacesNewlinesTabs(pszTotal);

	CXMD5 oMD5;
	oMD5.update(pchVal, strlen(pchVal));
	string str = oMD5.toString();
	CString strMd5 = str.c_str();
	//m_pHeader->m_strmd5 = strMd5;
	//m_pHeader->SetMd5(strMd5);
	if(bIsUpdateHeader)
	{
		m_pHeader->SetMd5(strMd5);
	}

	m_pHeader->m_strHeaderMD5_Cal = strMd5;
	// 	CFile oFile;
	// 	CString strFile = _T("D:\\0\\SetsFileTest\\FileAfterCalMd5.txt");
	// 	if (oFile.Open(strFile, CFile::modeWrite|CFile::modeCreate))
	//	{
	//		oFile.Write(pchVal, strlen(pchVal));
	//		oFile.Close();
	// 	}

	delete []pszTotal;
	free(pchVal);

	return strMd5;
}

//////////////////////////////////////////////////////////////////////////
//
/*
ʵ�����ݼ��Ͷ�ֵ�ļ�����ֵ�Ƚϡ�
����1(Path)���ļ�·����GBRPTPATH����ʾ���Լ�¼�������ļ�·��
����2(SetsFile)����ֵ�����ļ���
����3(DsFile)����ʾ���ݼ��ļ����������CdvmDataset����
����4(Grp)����ֵ���ţ���1��ʼ��������ֵ����Ч����
���ؽ�����Ƿ���ͬ���쳣��Ϣ�ı�������1������2�����3ƴ�ӵõ�����·����
˵����
A��	���ص��쳣��Ϣ���������£���***��ֵ��ֵ��һ�£�MMS=***����ֵ�ļ�=***��
B��	��ֵ���ݵĶ�Ӧ��ͨ�����ƽ��в���
C��	���ڶ�����ֵ�����ݼ��ļ�Ҳ��Ҫ�����������Ķ�ֵ����һ����ֵ��һ����ֵ��ȥ�ȡ�
*/
long CSetFilesXml_DSC::CmpDataset(const CString &strPath, const CString &strFile, const CString &strDsFile, long nGrp, char**ppszRet)
{
	CString strSetsFile, strRight, strDatasetFile;
	strSetsFile = strPath;
	strDatasetFile = strPath;
	strRight = strPath.Right(1);

	if (strRight != _T("/") && strRight != _T("\\") )
	{
		strSetsFile += _T("/");
		strDatasetFile += _T("/");
	}

	strSetsFile += strFile;
	strDatasetFile += strDsFile;

	if (!IsFileExist(strSetsFile))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=��ֵ�ļ�������<%s>;", strSetsFile);
		return -1;
	}

	if (!IsFileExist(strDatasetFile))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=���ݼ��ļ�������<%s>;", strDatasetFile);
		return -1;
	}

	CDvmDataset oDataset;
	CSetFilesXml_DSC oDsc;

	if (! oDataset.OpenXmlFile(strDatasetFile, CDataMngrXmlRWKeys::g_pXmlKeys))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=���ݼ��ļ���ʧ��;");
		return -1;
	}

	if (! oDsc.OpenXmlFile(strSetsFile, CSetFileXmlParseXmlRWKeys::g_pXmlKeys))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=��ֵ�ļ���ʧ��;");
		return -1;
	}

	return oDsc.CmpDataset(&oDataset, nGrp, ppszRet);
}

long CSetFilesXml_DSC::CmpDataset(CDvmDataset *pDataset, long nGrp, char**ppszRet)
{
	if (pDataset == NULL)
	{
		return -1;
	}

	CString strClass;

	//�ȶ�λ���ݼ�
	if (pDataset->m_strID.Find(SETTING_CLASS_PARAMETER) >= 0)
	{
		strClass = SETTING_CLASS_PARAMETER;  //װ�ò���
	}
	else if(pDataset->m_strID.Find(SETTING_CLASS_SETTING) >= 0)
	{
		strClass = SETTING_CLASS_SETTING;  //������ֵ
	}
	else if(pDataset->m_strID.Find(SETTING_CLASS_RELAYENA) >= 0)
	{
		strClass = SETTING_CLASS_RELAYENA;  //����ѹ��
	}
	else if(pDataset->m_strID.Find(SETTING_CLASS_CTRL) >= 0)
	{
		strClass = SETTING_CLASS_CTRL;  //������
	}
	else if(pDataset->m_strID.Find(SETTING_CLASS_MATRIX) >= 0)
	{
		strClass = SETTING_CLASS_SETTING;  //��բ������ģ����û��ר�ŵ����ݼ����Ǹ���ֵ���ݼ���һ���
	}
	else if (pDataset->m_strID.Find(SETTING_CLASS_PARAMETER) >= 0)
	{
		strClass = SETTING_CLASS_PARAMETER;  //�����ò���
	}
	else
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=��֧�ֵ����ݼ�;");
		return -1;
	}

	CSetsFileXml_Settings *pSettings = FindSettingsByClass(strClass);

	if (pSettings == NULL)
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=��ֵ�ļ��У�û�к����ݼ��ļ�ͬ���͵Ķ�ֵ������Ϣ��;");
		return -1;
	}

	BOOL bRet = pSettings->CmpDataset(pDataset, nGrp, ppszRet);
	sprintf(*ppszRet, "Rslt=%d;ErrorInfo=%s;", bRet, *ppszRet);
	return bRet;
}

/*��ֵ�ļ���ֵ�Ƚ�
1����ֵ�ļ��Ͷ�����ݼ��Ƚϣ�����Ϊ�豸ģ���ļ��Ͷ�ֵ�ļ������ж�����ֵͬʱ�Ƚ�
2�����ز�����CmpDataset��һ�£�
3�����ڶ�����ֵ�����籣����ֵ���ݼ���ͨ�����߼��豸�´���dataset�ķ�ʽʵ�֣����磺dsSetting_1��dsSetting_2������
4������ģ���б�����ж�����ݼ��ģ������ѹ��������һ����dsSetting1��dsSetting2����������Ὣһ�����Ķ�ֵ�ϲ���һ�����ݼ������磺dsSetting1_1��dsSetting1_2������
5�����ڶ�����ֵ�����Ը������ݼ����߼��豸�µ������ţ�ȷ��������ֵ���š������һ��dsSetting_*����ʾ1����ֵ����ʱ��*=1
*/
long CSetFilesXml_DSC::CmpDatasets(const CString &strPath, const CString &strFile, const CString &strDvmFile,char**ppszRet,const CString &strDeviceModel,bool bIsDeviceModel)
{
	CString strSetsFile, strRight, strDvmFilePath;
	strSetsFile = strPath;
	strDvmFilePath = strPath;
	strRight = strPath.Right(1);

	if (strRight != _T("/") && strRight != _T("\\") )
	{
		strSetsFile += _T("/");
		strDvmFilePath += _T("/");
	}

	strSetsFile += strFile;
	strDvmFilePath += strDvmFile;

	if (!IsFileExist(strSetsFile))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=��ֵ�ļ�������<%s>;", strSetsFile);
		return -1;
	}

	if (!IsFileExist(strDvmFilePath))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=�豸ģ���ļ�������<%s>;", strDvmFilePath);
		return -1;
	}

	CDvmDevice oDvmDevice;
	CSetFilesXml_DSC oDsc;

	if (! oDvmDevice.OpenXmlFile(strDvmFilePath, CDataMngrXmlRWKeys::g_pXmlKeys))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=���ݼ��ļ���ʧ��;");
		return -1;
	}

	if (! oDsc.OpenXmlFile(strSetsFile, CSetFileXmlParseXmlRWKeys::g_pXmlKeys))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=��ֵ�ļ���ʧ��;");
		return -1;
	}

	//return oDsc.CmpDatasets(&oDvmDevice, ppszRet);
	CString strErrorInfo  = "";
	int nRet1 = 1,nRet2 = 1;
	if(!oDsc.CmpDatasets(&oDvmDevice, strErrorInfo))  //���Ƚ϶�ֵ����ֵ���Ƿ�һ��
	{
		nRet1 = 0;
	}

	//2024-12-16 yuanting �Աȶ����ļ��е�װ���ͺš�Ψһ�Ա��롢IEDname��ģ���ļ��е��Ƿ�һ��
	nRet2 = oDsc.CmpDatasets(&oDvmDevice,strErrorInfo,strDeviceModel,bIsDeviceModel);
	//nRet2==200���������ϸ񣬽�װ���ͺ�Ϊ��
	//nRet2==100��װ���ͺ�Ϊ�գ�������Ҳ���ڲ��ϸ�
	//nRet2==0��װ���ͺŲ�Ϊ�գ������������ϸ�
	//nRet2==1��ȫ���ϸ�

	//1��ȷ��װ���ͺŲ����ڣ�����ȱʧ���ж�Ϊ�쳣��
	//2��ȷ��װ���ͺŴ��ڣ�����ȱʧ�ж�Ϊ�쳣��
	if(nRet2 == 100 || nRet2 == 200)
	{
		int nRet = MessageBox(NULL,_T("ģ���ļ��У�װ���ͺ�Ϊ�գ���ȷ���Ƿ��ж�Ϊ�쳣\r\n\r\nѡ���ǣ�ȷ��װ���ͺŴ��ڣ�����ȱʧ�ж�Ϊ�쳣��\r\nѡ���ȷ��װ���ͺŲ����ڣ�����ȱʧ���ж�Ϊ�쳣��"),_T("��ʾ"),MB_YESNO|MB_ICONQUESTION);
		if (nRet == IDNO)
		{
			if(nRet2 == 200)
			{
				//nRet2==200���������ϸ񣬽�װ���ͺ�Ϊ��
				//�˹�ѡ������ж����Ϊ����
				nRet2 = 1;
			}
			else
			{
				//nRet2==100��װ���ͺ�Ϊ�գ�������Ҳ���ڲ��ϸ�
				//�˹�ѡ��������������ڲ��ϸ񣬽��ж����ϸ񣬲�׷���쳣ԭ��
				nRet2 = 0;
			}
		}
		else
		{
			//�˹�ѡ���ǣ����ж�Ϊ�쳣����׷���쳣ԭ��
			nRet2 = 0;
			strErrorInfo.AppendFormat(_T("�豸ģ���ļ��У�װ���ͺ�Ϊ��\r\n"));
		}
	}

	if(nRet2 == 0 || nRet1 == 0)
	{
		RemoveTrailingCRLF(strErrorInfo);
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=%s;", strErrorInfo);
		return -1;
	}
	else/* if(nRet2 == 1 && nRet1 == 1)*/
	{
		sprintf(*ppszRet, "Rslt=1;ErrorInfo=--;");
		return 1;
	}
}

long CSetFilesXml_DSC::CmpDatasets(CDvmDevice *pDvmDevice, CString& strErrorInfo)
{
	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();
	UINT nClassID = 0;
	BOOL bRet = TRUE;
	//CString strErrorInfo;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CSETSFILEXML_SETTINGS)
		{
			continue;
		}

		CSetsFileXml_Settings *pSettings = (CSetsFileXml_Settings *)pObj;

		if (! pSettings->CmpDatasets(pDvmDevice, strErrorInfo))
		{
			bRet = FALSE;
		}
	}

	/*if (bRet)
	{
	sprintf(*ppszRet, "Rslt=1;ErrorInfo=--;");
	}
	else
	{
	sprintf(*ppszRet, "Rslt=0;ErrorInfo=%s;", strErrorInfo);
	}*/

	return bRet;
}

long CSetFilesXml_DSC::CmpDatasets(CDvmDevice *pDvmDevice,CString& strErrorInfo,const CString &strDeviceModel,bool bIsDeviceModel)
{
	int nRet = 1,nRetType = 1;
	CString strDevID = "LD0",strDataSetID = "LLN0$dsDevStdMsg";
	CDvmLogicDevice *pLDevice = pDvmDevice->FindByIDHas(strDevID);
	if (pLDevice == NULL)
	{
		//strErrorInfo.Format(_T("��ģ���ļ���û�ҵ��߼��豸 [%s]"), strDevID);
		strErrorInfo.AppendFormat(_T("��ģ���ļ���û�ҵ��߼��豸 [%s]"), strDevID);
		return 0;
	}

	CDvmDataset *pDataset = NULL;
	pDataset = (CDvmDataset *)pLDevice->FindByID(strDataSetID);
	if (pDataset == NULL)
	{
		strErrorInfo.AppendFormat(_T("�豸ģ���ļ���û�ҵ����ݼ� [%s]"), strDataSetID);
		return 0;
	}

	CString strZZID = "LPHD1$DC$PhyNam$serNum"; //װ��ʶ�����
	CDvmData *pZZData = NULL;
	pZZData = (CDvmData *)pDataset->FindByID(strZZID);
	if (pZZData == NULL)
	{
		strErrorInfo.AppendFormat(_T("�豸ģ���ļ�û���ҵ�װ��ʶ��������� [%s]"), strZZID);
		return 0;
	}
	else if(pZZData->m_strValue != m_pHeader->m_strDevID)
	{
		strErrorInfo.AppendFormat(_T("װ��ʶ���벻һ�£��豸ģ���ļ���[%s]����ֵ�ļ���[%s]\r\n"), pZZData->m_strValue, m_pHeader->m_strDevID);
		nRet = 0;
	}

	CString strZZTypeID = "IEDModel"; //װ���ͺ�
	CDvmData* pZZTypeData = (CDvmData *)pDataset->FindByID(strZZTypeID);
	if (pZZTypeData == NULL)
	{
		strErrorInfo.AppendFormat(_T("�豸ģ���ļ�û���ҵ�װ���ͺ����� [%s]"), strZZTypeID);
		return 0;
	}
	else 
	{
		//���滻װ���ͺ�  strDeviceModel �ⲿ����
		if(bIsDeviceModel)
		{
			pZZTypeData->m_strValue = strDeviceModel;
		}

		//�ж�װ���ͺ��Ƿ�Ϊ��
		//��ģ���ļ���װ���ͺŵ�ֵΪ�գ��򵯴��˹�ѡ���Ƿ�����쳣
		if(pZZTypeData->m_strValue == "")
		{
			//strErrorInfo.AppendFormat(_T("�豸ģ���ļ��е�װ���ͺ�Ϊ��;"));	
			nRetType = 100; //���Ϊ�գ����غ󵯴��˹��ж��Ƿ�ϸ�
			//return 100;
		}
		else
		{
			if(pZZTypeData->m_strValue != m_pHeader->m_strDevType)
			{
				strErrorInfo.AppendFormat(_T("װ���ͺŲ�һ�£��豸ģ���ļ���[%s]����ֵ�ļ���[%s]\r\n"),pZZTypeData->m_strValue, m_pHeader->m_strDevType);	
				nRet = 0;
			}
		}
	}

	CString strIedNameID = "IEDName"; //IedName
	CDvmData *pIedNameData = NULL;
	pIedNameData = (CDvmData *)pDataset->FindByID(strIedNameID);
	if (pIedNameData == NULL)
	{
		strErrorInfo.AppendFormat(_T("�豸ģ���ļ���û���ҵ�IEDName���� [%s]"),strIedNameID);	
		return 0;
	}
	else if(pIedNameData->m_strValue != m_pHeader->m_strIedName)
	{
		strErrorInfo.AppendFormat(_T("IedName��һ�£��豸ģ���ļ���[%s]����ֵ�ļ���[%s]\r\n"),pIedNameData->m_strValue, m_pHeader->m_strIedName);
		nRet = 0;
		//return 0;
	}

	//��֤MD5
	CString strMD5ID = "";
	CDvmData *pMD5Data = NULL;
	POS nHPos = m_pHashInfo->GetHeadPosition();
	while(nHPos != NULL)
	{
		CSetsFileXml_HI* pHiTemp = (CSetsFileXml_HI*)m_pHashInfo->GetNext(nHPos);
		if(pHiTemp->m_strClass == "dsParameter")
		{
			strMD5ID = "LPHD1$SP$SysParaMd5$setVal"; //ϵͳ����
		}
		else if(pHiTemp->m_strClass == "dsSetting")
		{
			strMD5ID = "LPHD1$SP$SettingMd5$setVal"; //������ֵ
		}
		else if(pHiTemp->m_strClass == "dsRelayEna")
		{
			strMD5ID = "LPHD1$SP$RelEnaMd5$setVal"; //��ѹ��
		}
		else if(pHiTemp->m_strClass == "dsMatrixSet")
		{
			strMD5ID = "LPHD1$SP$MatrixMd5$setVal"; //���ڶ�ֵ
		}
		else if(pHiTemp->m_strClass == "dsVtcParameter")
		{
			strMD5ID = "LPHD1$SP$VtcParaMd5$setVal"; //�����ò���
		}
		else if (pHiTemp->m_strClass == "dsRemark")  //��ע��Ϣ
		{
			strMD5ID = "LPHD1$SP$RemarkMd5$setVal";
		}

		pMD5Data = (CDvmData *)pDataset->FindByID(strMD5ID);
		if (pMD5Data == NULL)
		{
			strErrorInfo.AppendFormat(_T("�豸ģ���ļ�û���ҵ� [%s] ��MD5����"),pHiTemp->m_strClass);
			return 0;
		}
		else if(pMD5Data->m_strValue != pHiTemp->m_strmd5)
		{
			strErrorInfo.AppendFormat(_T("[%s]��MD5�벻һ�£��豸ģ���ļ���[%s]����ֵ�ļ���[%s]\r\n"),pHiTemp->m_strClass, pMD5Data->m_strValue, pHiTemp->m_strmd5);
			nRet = 0;
			//return 0;
		}
	}

	//��֤Remark��MD5
	strMD5ID = "LPHD1$SP$RemarkMd5$setVal"; //��ע��Ϣ
	pMD5Data = (CDvmData *)pDataset->FindByID(strMD5ID);
	if (pMD5Data == NULL)
	{
		strErrorInfo.AppendFormat(_T("�豸ģ���ļ���û���ҵ�Remark��MD5����"));
		return 0;
	}
	else if(pMD5Data->m_strValue != m_pRemark->m_strmd5)
	{
		strErrorInfo.AppendFormat(_T("��ע��Ϣ��Remark��MD5�벻һ�£��豸ģ���ļ���[%s]����ֵ�ļ���[%s]\r\n"),pMD5Data->m_strValue, m_pRemark->m_strmd5);
		nRet = 0;
		//return 0;
	}

	if(nRet == 1 && nRetType == 100)
	{
		//�������ϸ񣬽�װ���ͺ�Ϊ��
		return 200;
	}
	else if(nRet == 0 && nRetType == 100)
	{
		//�������ڲ��ϸ���װ���ͺ�Ϊ��
		return 100;
	}
	return nRet;
	//return 1;
}

/*��ֵ�ļ���ֵ�Ƚ�
1��������ֵ�ļ��Ƚϡ�
<paras>
<value name="��ֵ�ļ���_����" id="SetsFileUp" data-type="string" value=""/>
<value name="��ֵ�ļ���_��װ" id="SetsFileDown" data-type="string" value=""/>
<value name="�ļ�·��" id="Path" data-type="string" value="GBRPTDATAPATH"/>
<value name="װ�ñ��" id="DeviceSN" data-type="string" value="GBRPTNAME"/>
</paras>
2�����ز��������ؽ�����Ƿ���ͬ���쳣��Ϣ�ı���
3����ֵ�ļ��Ƚϣ���У�鶨ֵ��װ���������٣������װ��ֵ�Ƿ���Ч�����������װ�Ķ�ֵΪ��׼��
*/
long CSetFilesXml_DSC::CmpSetsFile(const CString &strPath, const CString &strFileUp, const CString &strFileDown, char**ppszRet)
{
	CString strSetsFileUp, strRight, strSetsFileDown;
	strSetsFileUp = strPath;
	strSetsFileDown = strPath;
	strRight = strPath.Right(1);

	if (strRight != _T("/") && strRight != _T("\\") )
	{
		strSetsFileUp += _T("/");
		strSetsFileDown += _T("/");
	}

	strSetsFileUp += strFileUp;
	strSetsFileDown += strFileDown;

	if (!IsFileExist(strSetsFileUp))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=��ֵ�ļ�_���ٲ�����<%s>;", strSetsFileUp);
		return -1;
	}

	if (!IsFileExist(strSetsFileDown))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=��ֵ�ļ�_��װ������<%s>;", strSetsFileDown);
		return -1;
	}

	CSetFilesXml_DSC oDscUp;
	CSetFilesXml_DSC oDscDown;

	if (! oDscUp.OpenXmlFile(strSetsFileUp, CSetFileXmlParseXmlRWKeys::g_pXmlKeys))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=��ֵ�ļ�_���ٴ�ʧ��;");
		return -1;
	}

	if (! oDscDown.OpenXmlFile(strSetsFileDown, CSetFileXmlParseXmlRWKeys::g_pXmlKeys))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=��ֵ�ļ�_��װ��ʧ��;");
		return -1;
	}

	//return oDscDown.CmpSetsFile(&oDscUp, ppszRet);
	//return 0;
	CString strErrorInfo  = "";
	int nRet = 1;
	if(!oDscDown.CmpSetsFile(&oDscUp, strErrorInfo))
	{
		nRet = 0;
	}
	//2024-12-16 yuanting �ȶԱ� ��װ�ļ��е�װ���ͺš�Ψһ�Ա��롢IEDname�������ļ��е��Ƿ�һ��
	if(!oDscDown.CmpSetsFile2(&oDscUp, strErrorInfo))
	{
		nRet = 0;
	}
	if (nRet)
	{
		sprintf(*ppszRet, "Rslt=1;ErrorInfo=--;");
	}
	else
	{
		RemoveTrailingCRLF(strErrorInfo);
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=%s;", strErrorInfo);
	}

	return nRet;

}

long CSetFilesXml_DSC::CmpSetsFile(CSetFilesXml_DSC *pSrcUp,  CString& strErrorInfo)
{
	CExBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();
	UINT nClassID = 0;
	BOOL bRet = TRUE;
	//CString strErrorInfo;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CSETSFILEXML_SETTINGS)
		{
			continue;
		}

		CSetsFileXml_Settings *pSettings = (CSetsFileXml_Settings *)pObj;

		if (! pSettings->CmpSetsFile(pSrcUp, strErrorInfo))
		{
			bRet = FALSE;
		}
	}

	/*if (bRet)
	{
	sprintf(*ppszRet, "Rslt=1;ErrorInfo=--;");
	}
	else
	{
	sprintf(*ppszRet, "Rslt=0;ErrorInfo=%s;", strErrorInfo);
	}*/

	return bRet;
}

long CSetFilesXml_DSC::CmpSetsFile2(CSetFilesXml_DSC *pSrcUp, CString& strErrorInfo)
{
	int nRet = 1;
	if(pSrcUp->m_pHeader == NULL)
	{
		strErrorInfo += _T("�����ļ�ȱʧHeader�ڵ�");
		return 0;
	}
	if(m_pHeader == NULL)
	{
		strErrorInfo += _T("��װ���ļ�ȱʧHeader�ڵ�");
		return 0;
	}

	//װ��ʶ�����
	if (pSrcUp->m_pHeader->m_strDevID != m_pHeader->m_strDevID)
	{
		strErrorInfo.AppendFormat(_T("��������װ��װ��ʶ����벻һ�� ����[%s] ��װ[%s]\r\n"),pSrcUp->m_pHeader->m_strDevID,m_pHeader->m_strDevID);
		nRet = 0;
	}
	//װ���ͺ�
	if(pSrcUp->m_pHeader->m_strDevType != m_pHeader->m_strDevType)
	{
		strErrorInfo.AppendFormat(_T("��������װ��װ���ͺŲ�һ�� ����[%s] ��װ[%s]\r\n"),pSrcUp->m_pHeader->m_strDevType,m_pHeader->m_strDevType);
		nRet = 0;
	}
	////IedName
	if(pSrcUp->m_pHeader->m_strIedName != m_pHeader->m_strIedName)
	{
		strErrorInfo.AppendFormat(_T("��������װ��IedName��һ�� ����[%s] ��װ[%s]\r\n"), pSrcUp->m_pHeader->m_strIedName,m_pHeader->m_strIedName);
		nRet = 0;
	}

	if(pSrcUp->m_pHashInfo == NULL)
	{
		strErrorInfo += _T("��װ���ļ�ȱʧHashInfo�ڵ�");
		return 0;
	}

	if(m_pHashInfo == NULL)
	{
		strErrorInfo += _T("��װ���ļ�ȱʧHashInfo�ڵ�");
		return 0;
	}

	//��֤MD5
	POS nHPosUp = pSrcUp->m_pHashInfo->GetHeadPosition();
	while(nHPosUp != NULL)
	{
		CSetsFileXml_HI* pHiTempUp = (CSetsFileXml_HI*)pSrcUp->m_pHashInfo->GetNext(nHPosUp);

		POS nHPosDown = m_pHashInfo->GetHeadPosition();
		while(nHPosDown != NULL)
		{
			CSetsFileXml_HI* pHiTempDown = (CSetsFileXml_HI*)m_pHashInfo->GetNext(nHPosDown);
			if(pHiTempUp->m_strClass == pHiTempDown->m_strClass)
			{
				if(pHiTempUp->m_strmd5 != pHiTempDown->m_strmd5)
				{
					strErrorInfo.AppendFormat(_T("��������װ[%s]��MD5��һ�� ����[%s] ��װ[%s]\r\n"), pHiTempDown->m_strClass,pHiTempUp->m_strmd5,pHiTempDown->m_strmd5);
					nRet = 0;
				}
				break;
			}
		}
	}

	if(pSrcUp->m_pRemark == NULL)
	{
		strErrorInfo += _T("��װ���ļ�ȱʧRemark�ڵ�");
		return 0;
	}

	if(m_pRemark == NULL)
	{
		strErrorInfo += _T("��װ���ļ�ȱʧRemark�ڵ�");
		return 0;
	}

	//��֤Remark��MD5
	if(pSrcUp->m_pRemark->m_strmd5 != m_pRemark->m_strmd5)
	{
		//strErrorInfo.Format(_T("�����ļ�����װ�ļ��е�Remark��MD5��һ�£�����[%s] ��װ[%s]"), pSrcUp->m_pRemark->m_strmd5,m_pRemark->m_strmd5);
		strErrorInfo.AppendFormat(_T("��������װ��Remark��MD5��һ�� ����[%s] ��װ[%s]\r\n"), pSrcUp->m_pRemark->m_strmd5,m_pRemark->m_strmd5);
		nRet = 0;
	}

	return nRet;
}

/*
�༭�޸Ķ�ֵ�ļ�������
����ģ��༭���Զ������ ��ѡ�����ݶ�����ʾ���������ݣ����û��ֶ��༭�����غͼ�¼��Ҫ�޸ĵĶ�ֵ���ݣ�XML����JSON��ʽ��
�Զ�����ִ�У�������Ҫ�޸ĵĶ�ֵ���ݣ��޸Ķ�ֵ�ļ�����
*/
long CSetFilesXml_DSC::EditSettings(char* strPara, char**ppszRet)
{
	return 0;
}

/*
���涨ֵ�����ļ���
����1(Path)���ļ�·����ΪGBRPTPATH����ʾ���Լ�¼�������ļ�·��
����2(SetsFile)������Ķ�ֵ�����ļ����ơ�
���Ӵ˺�����Ŀ�ģ������ܹ���¼��װ�Ķ�ֵ�ļ�����Ϊ���Թ����п��ܲ�ֹһ����Ҫ��װ��ֵ�����ļ���
*/
long CSetFilesXml_DSC::SaveSettingsFile(CString &strPath, CString &strFile, char **ppszRet)
{
	CString strSetsFile, strRight;
	strSetsFile = strPath;
	strRight = strPath.Right(1);
	CString strErrorInfo;
	strErrorInfo = _T("--");

	if (strRight != _T("/") && strRight != _T("\\") )
	{
		strSetsFile += _T("/");
	}

	strSetsFile += strFile;
	BOOL bRet = FALSE;

	if (m_pNode != NULL)
	{
		char* pHead = new char[1024000];
		std::memset(pHead, 0, 1024000 * sizeof(char));
		strcat(pHead, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
		char *pChar;
		pChar = m_pNode->get_xml_string(1024000);
		CFile oFile;

		if (oFile.Open(strSetsFile, CFile::modeWrite|CFile::modeCreate))
		{
			strcat(pHead, pChar);
			oFile.Write(pHead, strlen(pHead));
			oFile.Close();
			bRet = TRUE;
		}
		else
		{
			bRet = FALSE;
		}

		delete []pHead;
		delete []pChar;
	}
	else
	{
		bRet = SaveXmlFile(strSetsFile, CSetFileXmlParseXmlRWKeys::g_pXmlKeys);
	}

	if (! bRet)
	{
		strErrorInfo = _T("�ļ�����ʧ��");
	}

	sprintf(*ppszRet, "Rslt=%ld;ErrorInfo=%s;", bRet, strErrorInfo);

	return 0;
}

/*
��ȡ��ֵ�����ļ���
����1(Path)���ļ�·����ΪGBRPTPATH����ʾ���Լ�¼�������ļ�·��
����2(SetsFile)������Ķ�ֵ�����ļ����ơ�
���Ӵ˺�����Ŀ�ģ������ܹ�����ȡ���Ķ�ֵ�ļ�����SetsFileTest.dll����Ϊ���Թ����е�һ�δ�װ�ö�ȡ��ֵ�ļ�����Ҫ���ص��ڴ��У��Ӷ����ڴ��ļ����ݽ��б༭�޸ġ�
*/
long CSetFilesXml_DSC::OpenSettingsFile(CString &strPath, CString &strFile, char **ppszRet)
{
	CString strSetsFile, strRight;
	strSetsFile = strPath;
	strRight = strPath.Right(1);
	long nRet = 0;
	CString strErrorInfo;

	if (strRight != _T("/") && strRight != _T("\\") )
	{
		strSetsFile += _T("/");
	}

	strSetsFile += strFile;

	if (!IsFileExist(strSetsFile))
	{
		strErrorInfo.Format(_T("��ֵ�ļ�������[%s]"), strSetsFile);
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=%s;", strErrorInfo);
		return -1;
	}

	DeleteAll();

	if (! OpenXmlFile(strSetsFile, CSetFileXmlParseXmlRWKeys::g_pXmlKeys))
	{
		strErrorInfo.Format(_T("��ֵ�ļ���ʧ��[%s]"), strSetsFile);
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=%s;", strErrorInfo);
		return 0;
	}

	// 	//�ȴ���һ���µĶ���򿪣�����ɹ����滻�������򱣳�ԭ��������
	// 	CSetFilesXml_DSC *pNew = new CSetFilesXml_DSC();
	// 
	// 	if (! pNew->OpenXmlFile(strSetsFile, CSetFileXmlParseXmlRWKeys::g_pXmlKeys))
	// 	{
	// 		strErrorInfo = _T("��ֵ�ļ���ʧ��");
	// 		sprintf(*ppszRet, "Rslt=0;ErrorInfo=%s;", strErrorInfo);
	// 		delete pNew;
	// 		return 0;
	// 	}
	// 
	// 	DeleteAll();
	// 	//InitDevice();
	// 	AppendEx(*pNew, TRUE);
	// 	InitAfterRead();
	// 	pNew->CopyOwn(this);
	// 	pNew->RemoveAll();
	// 	delete pNew;

	sprintf(*ppszRet, "Rslt=1;ErrorInfo=--;");
	return 1;
}

long CSetFilesXml_DSC::OpenSettingsFile(CString &strFilePath)
{
	if (!IsFileExist(strFilePath))
	{
		//�ļ�������
		return -1;
	}

	//�ȴ���һ���µĶ���򿪣�����ɹ����滻�������򱣳�ԭ��������
	CSetFilesXml_DSC *pNew = new CSetFilesXml_DSC();

	if (! pNew->OpenXmlFile(strFilePath, CSetFileXmlParseXmlRWKeys::g_pXmlKeys))
	{
		delete pNew;
		return 0;
	}

	DeleteAll();
	//InitDevice();
	AppendEx(*pNew, TRUE);
	InitAfterRead();
	pNew->CopyOwn(this);
	pNew->RemoveAll();
	delete pNew;
	return 1;
}

long CSetFilesXml_DSC::SaveSettingsFile(CString &strPathName)
{
	BOOL bRet = FALSE;
	if (m_pNode != NULL)
	{
		char* pHead = new char[1024000];
		std::memset(pHead, 0, 1024000 * sizeof(char));
		strcat(pHead, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
		char *pChar;
		pChar = m_pNode->get_xml_string();
		CFile oFile;

		if (oFile.Open(strPathName, CFile::modeWrite|CFile::modeCreate))
		{
			strcat(pHead, pChar);
			oFile.Write(pHead, strlen(pHead));
			oFile.Close();
			bRet = TRUE;
		}
		else
		{
			bRet = FALSE;
		}

		delete []pHead;
		delete []pChar;
	}
	return bRet;
}

void CSetFilesXml_DSC::AddNewUpdate()
{
	if(m_pUpdateInfo != NULL)
	{
		return;
	}
	//��xml �����
	POS HashInfPos;
	POS nPos = GetHeadPosition();
	while(nPos != NULL)
	{
		CExBaseObject *pObj = GetNext(nPos);
		if(pObj->GetClassID() == MNGRCLASSID_CSETSFILEXML_HASHINFO)
		{
			HashInfPos = nPos;
			break;
		}
	}

	m_pUpdateInfo = new CSetsFileXml_Update();
	m_pUpdateInfo->SetParent(this);
	InsertAfter(HashInfPos,m_pUpdateInfo);

	//��node�����
	if(m_pNode != NULL)
	{
		/*pugi::xml_node *pUpdate = new pugi::xml_node();
		pUpdate->set_name(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strUpdateKey);
		pUpdate->append_attribute(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strItemNumKey);*/

		pugi::xml_node oUpdate = m_pNode->insert_child_after(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strUpdateKey,*(m_pHashInfo->m_pNode));
		//oUpdate.set_name(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strUpdateKey);
		pugi::xml_attribute attr1 = oUpdate.append_attribute(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strItemNumKey);
		//m_pUpdateInfo->m_pNode = &oUpdate;
		m_pUpdateInfo->m_pNode = &(m_pNode->child(CSetFileXmlParseXmlRWKeys::CSetsFileXml_UpdateKey()));

		/*pugi::xml_node oUpdate = m_pNode->append_child(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strUpdateKey);
		pugi::xml_attribute attr1 = oUpdate.append_attribute(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strItemNumKey);
		m_pUpdateInfo->m_pNode = &oUpdate;*/
	}

	m_pUpdateInfo->SetItemNum(0);

}

//��֤�����ļ��ĸ�ʽ�Ƿ���ȷ
long CSetFilesXml_DSC::FileFormatCheck(CString& strErrorInfo)
{
	int nRet = 0;// 0 ����ȷ 1 �Ǵ���  ԭ������ֵ
	InitAttributeName();//��ʼ����������

	if(m_pNode == NULL)
	{
		strErrorInfo = "Rslt=0;ErrorInfo=�ļ�Ϊ��";
		return 1;
	}
	//��֤DSC��Ԫ�ص���������������
	if(CheckDSC(m_pNode,strErrorInfo))
		nRet = 1;

	//��֤DSC�����ӽڵ��������˳������
	bool bIsDSCChildFlag = true;
	if(FindChildNodeName(m_pNode,strErrorInfo))
	{
		bIsDSCChildFlag = false;
		nRet = 1;
	}
	if(ChildNodeIsLack(m_pNode,strErrorInfo))
	{
		bIsDSCChildFlag = false;
		nRet = 1;
	}
	//û�зǷ����ӽڵ�  ��ȱ���ӽڵ� ��֤˳��
	pugi::xml_node nodeTemp1 = m_pNode->first_child();
	if(bIsDSCChildFlag)
	{
		if(!nodeTemp1.empty())
		{
			if(CheckNode(nodeTemp1,(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HeaderKey(),(CString)CSetFileXmlParseXmlRWKeys::CSetFilesXml_DSCKey(),strErrorInfo))
				nRet = 1;
		}

		nodeTemp1 = nodeTemp1.next_sibling();
		if(!nodeTemp1.empty())
		{
			if(CheckNode(nodeTemp1,(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HashInfoKey(),(CString)CSetFileXmlParseXmlRWKeys::CSetFilesXml_DSCKey(),strErrorInfo))
				nRet = 1;
		}
	
		nodeTemp1 = nodeTemp1.next_sibling();
		if(!nodeTemp1.empty())
		{
			if(CheckNode(nodeTemp1,(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_UpdateKey(),(CString)CSetFileXmlParseXmlRWKeys::CSetFilesXml_DSCKey(),strErrorInfo))
				nRet = 1;
		}

		nodeTemp1 = nodeTemp1.next_sibling();
		if(!nodeTemp1.empty())
		{
			if(CheckNode(nodeTemp1,(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_DevInfoKey(),(CString)CSetFileXmlParseXmlRWKeys::CSetFilesXml_DSCKey(),strErrorInfo))
				nRet = 1;
		}

		nodeTemp1 = nodeTemp1.next_sibling();
		if(!nodeTemp1.empty())
		{
			if(CheckNode(nodeTemp1,(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_FileInfoKey(),(CString)CSetFileXmlParseXmlRWKeys::CSetFilesXml_DSCKey(),strErrorInfo))
				nRet = 1;
		}
		//�м�Settings �����ж����������֤˳��
		//���һ����Remark
		nodeTemp1 = m_pNode->last_child();
		if(!nodeTemp1.empty())
		{
			if(CheckNode(nodeTemp1,(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_RemarkKey(),(CString)CSetFileXmlParseXmlRWKeys::CSetFilesXml_DSCKey(),strErrorInfo))
				nRet = 1;
		}
	}
	
	//��֤DSC�ӽڵ�Ĺ���
		pugi::xml_node nodeTemp = m_pNode->first_child();
		while (! nodeTemp.empty())
		{
			char_t* cNodeName = (char_t*)nodeTemp.name();
			CString strNodeName(cNodeName);

		//��֤�Ƿ��ǺϷ��ӽڵ㣬���Ƿ���ֱ������	
		if(strNodeName != (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HeaderKey() &&
			strNodeName != (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HashInfoKey() &&
			strNodeName != (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_UpdateKey() &&
			strNodeName != (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_DevInfoKey() &&
			strNodeName != (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_FileInfoKey() &&
			strNodeName != (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_RemarkKey() &&
			strNodeName != (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_SettingsKey())
		{
			nodeTemp = nodeTemp.next_sibling();
			continue;
		}
	
		//��֤��ǰ�ڵ��Ƿ��зǷ����ӽڵ�
		if(FindChildNodeName(&nodeTemp,strErrorInfo))
		{
			nRet = 1;
		}
		/*if(ChildNodeIsLack(&nodeTemp,strErrorInfo))
		{
			nRet = 1;
		}*/


		//��֤�ӽڵ�
			if(strNodeName == (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HeaderKey())
			{
				if(CheckHeader(&nodeTemp,strErrorInfo))
					nRet = 1;
			}
			else if(strNodeName == (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HashInfoKey())
			{
				if(CheckHashInfo(&nodeTemp,strErrorInfo))
					nRet = 1;
			}
			else if(strNodeName == (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_UpdateKey())
			{
				if(CheckUpdate(&nodeTemp,strErrorInfo))
					nRet = 1;
			}
			else if(strNodeName == (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_DevInfoKey())
			{
				if(CheckDevInfo(&nodeTemp,strErrorInfo))
					nRet = 1;
			}
			else if(strNodeName == (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_FileInfoKey())
			{
				if(CheckFileInfo(&nodeTemp,strErrorInfo))
					nRet = 1;
			}
			else if(strNodeName == (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_RemarkKey())
			{
				if(CheckRemark(&nodeTemp,strErrorInfo))
					nRet = 1;
			}
			else if(strNodeName == (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_SettingsKey())
			{
				if(CheckSetting(&nodeTemp,strErrorInfo))
					nRet = 1;
			}

			nodeTemp = nodeTemp.next_sibling();
		}

	return nRet;
	//return 0;
}

long CSetFilesXml_DSC::CheckDSC(pugi::xml_node *pNode,CString& strErrorInfo)
{
	int nRet = 0;
	CString strDesc = "";
	if(FindAttributeName(pNode,strErrorInfo,strDesc))
	{
		//���������д��󣬲�������֤����ǰ�ڵ�ֱ�ӷ��ش���
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 1)
		{
			//strErrorInfo += _T("HashInfo�ڵ�������������\r\n");
			nRet = 1;
			//return 1;
		}

		if(AttributeIsLack(pNode,strErrorInfo,strDesc))
		{
			//����������ȱ�٣���������֤����ǰ�ڵ�ֱ�ӷ��ش���
			nRet = 1;
			//return nRet;
		}
		else
		{
			char_t* cNodeName = (char_t*)pNode->name();
			CString strNodeName(cNodeName);
			xml_attribute xmlAtt = pNode->first_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::ConfigVersionKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;
		}
	}
	return nRet;
}

long CSetFilesXml_DSC::CheckHeader(pugi::xml_node *pNode,CString& strErrorInfo)
{
	int nRet = 0;
	CString strDesc = "";
	if(FindAttributeName(pNode,strErrorInfo,strDesc))
	{
		//���������д��󣬲�������֤����ǰ�ڵ�ֱ�ӷ��ش���
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 4 && nAttCount != 5)
		{
			//strErrorInfo += _T("Header�ڵ�������������\r\n");
			nRet = 1;
		}

		CString strOtherAttName = "";
		if(nAttCount <= 4)
		{
			strOtherAttName = (CString)CSetFileXmlParseXmlRWKeys::DevIdKey();
		}

		if(AttributeIsLack(pNode,strErrorInfo,strDesc,strOtherAttName))
		{
			//����������ȱ�٣���������֤����ǰ�ڵ�ֱ�ӷ��ش���
			nRet = 1;
			//return nRet;
		}
		else
		{
			//���Ե���4����5 �����Բ�ȱ�ٵ���� û�зǷ�����ǰ���� ��֤���Ե�˳��
#ifdef CHECK_XML_ATTRIBUTE_ORDER
			char_t* cNodeName = (char_t*)pNode->name();
			CString strNodeName(cNodeName);

			xml_attribute xmlAtt = pNode->first_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::DevTypeKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;
			if(nAttCount == 5)
			{
				xmlAtt = xmlAtt.next_attribute();
				if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::DevIdKey(),strNodeName,strDesc,strErrorInfo))
					nRet = 1;
			}

			xmlAtt = xmlAtt.next_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::IedNameKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;
			xmlAtt = xmlAtt.next_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::UpdateTimeKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;
			xmlAtt = xmlAtt.next_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::Md5Key(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;	
#else
		nRet = 0;
#endif
			
		}
	}

	return nRet;
	//return 0;
}

long CSetFilesXml_DSC::CheckHashInfo(pugi::xml_node *pNode,CString& strErrorInfo)
{
	int nRet = 0;
	CString strDesc = "";
	if(FindAttributeName(pNode,strErrorInfo,strDesc))
	{
		//���������д��󣬲�������֤����ǰ�ڵ�ֱ�ӷ��ش���
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 1)
		{
			//strErrorInfo += _T("HashInfo�ڵ�������������\r\n");
			nRet = 1;
			//return 1;
		}

		if(AttributeIsLack(pNode,strErrorInfo,strDesc))
		{
			//����������ȱ�٣���������֤����ǰ�ڵ�ֱ�ӷ��ش���
			nRet = 1;
			//return nRet;
		}
		else
		{
#ifdef CHECK_XML_ATTRIBUTE_ORDER
			char_t* cNodeName = (char_t*)pNode->name();
			CString strNodeName(cNodeName);
			xml_attribute xmlAtt = pNode->first_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::ItemNumKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;
#else
			nRet = 0;
#endif

		}
	}
	//Ĭ�������ļ�HI �ڵ���ڵ��� 1��
	int nChildCount = pNode->child_number();
	if(pNode->child_number() < 1)
	{
		strErrorInfo += _T("�ڵ�HashInfo,�ӽڵ�HI������С��1 \r\n");
		nRet = 1;
	}

	for(pugi::xml_node nodeTemp = pNode->first_child();nodeTemp;nodeTemp = nodeTemp.next_sibling())
	{
		char_t* cNodeName = (char_t*)nodeTemp.name();
		CString strNodeName(cNodeName);
		if(strNodeName != (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HIKey())
		{
			continue;
		}
		
		if(FindChildNodeName(&nodeTemp,strErrorInfo))
		{
			nRet = 1;
		}
		if(CheckNode(nodeTemp,(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HIKey(),(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HashInfoKey(),strErrorInfo))
			nRet = 1;

		if(CheckHI(&nodeTemp,strErrorInfo))
		{
			nRet = 1;
		}
	}
	return nRet;
	//return 0;
}

long CSetFilesXml_DSC::CheckHI(pugi::xml_node *pNode,CString& strErrorInfo)
{
	int nRet = 0;
	CString strDesc = "";
	xml_attribute xmlAttDesc = pNode->attribute(L"class");
	if(!xmlAttDesc.empty())
	{
		char_t* cClassValue = (char_t*)xmlAttDesc.value();
		CString strClassValue(cClassValue);
		strDesc = strClassValue;
	}
	if(FindAttributeName(pNode,strErrorInfo,strDesc))
	{
		//���������д��󣬲�������֤����ǰ�ڵ�ֱ�ӷ��ش���
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 2)
		{
			//strErrorInfo += _T("HI�ڵ�������������\r\n");
			nRet = 1;
			//return 1;
		}

		if(AttributeIsLack(pNode,strErrorInfo,strDesc))
		{
			//����������ȱ�٣���������֤����ǰ�ڵ�ֱ�ӷ��ش���
			nRet = 1;
			//return nRet;
		}
		else
		{
#ifdef CHECK_XML_ATTRIBUTE_ORDER
			char_t* cNodeName = (char_t*)pNode->name();
			CString strNodeName(cNodeName);
			xml_attribute xmlAtt = pNode->first_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::ClassKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;

			xmlAtt = xmlAtt.next_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::Md5Key(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;
#else
			nRet = 0;
#endif

		}
	}
	return nRet;
	//return 0;
}

long CSetFilesXml_DSC::CheckUpdate(pugi::xml_node *pNode,CString& strErrorInfo)
{
	//Ĭ�������ļ� Update
	int nRet = 0;
	CString strDesc = "";
	if(FindAttributeName(pNode,strErrorInfo,strDesc))
	{
		//���������д��󣬲�������֤����ǰ�ڵ�ֱ�ӷ��ش���
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 1)
		{
			//strErrorInfo += _T("Update�ڵ�������������\r\n");
			nRet = 1;
			//return 1;
		}

		if(AttributeIsLack(pNode,strErrorInfo,strDesc))
		{
			//����������ȱ�٣���������֤����ǰ�ڵ�ֱ�ӷ��ش���
			nRet = 1;
			//return nRet;
		}
		else
		{
#ifdef CHECK_XML_ATTRIBUTE_ORDER
			char_t* cNodeName = (char_t*)pNode->name();
			CString strNodeName(cNodeName);
			xml_attribute xmlAtt = pNode->first_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::ItemNumKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;
#else
			nRet = 0;
#endif

		}
	}
	//Ĭ�������ļ�UI �ڵ���ڵ��� 0��
	//�����ļ�������һ��
	/*int nChildCount = pNode->child_number();
	if(pNode->child_number() < 1)
	{
	nRet = 1;
	}*/
	for(pugi::xml_node nodeTemp = pNode->first_child();nodeTemp;nodeTemp = nodeTemp.next_sibling())
	{
		char_t* cNodeName = (char_t*)nodeTemp.name();
		CString strNodeName(cNodeName);
		if(strNodeName != (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_UIKey())
		{
			continue;
		}
		if(FindChildNodeName(&nodeTemp,strErrorInfo))
		{
			nRet = 1;
		}
		if(CheckNode(nodeTemp,(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_UIKey(),(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_UpdateKey(),strErrorInfo))
			return 1;

		if(CheckUI(&nodeTemp,strErrorInfo))
		{
			return 1;
		}
	}
	return nRet;
	//return 0;
}

long CSetFilesXml_DSC::CheckUI(pugi::xml_node *pNode,CString& strErrorInfo)
{
	int nRet = 0;
	CString strDesc = "";
	xml_attribute xmlAttDesc = pNode->attribute(L"class");
	if(!xmlAttDesc.empty())
	{
		char_t* cClassValue = (char_t*)xmlAttDesc.value();
		CString strClassValue(cClassValue);
		strDesc = strClassValue;
	}
	if(FindAttributeName(pNode,strErrorInfo,strDesc))
	{
		//���������д��󣬲�������֤����ǰ�ڵ�ֱ�ӷ��ش���
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 3 && nAttCount != 4)
		{
			//strErrorInfo += _T("UI�ڵ�������������\r\n");
			nRet = 1;
			//return 1;
		}

		CString strOtherAttName = "";
		if(nAttCount <= 3)
		{
			strOtherAttName = (CString)CSetFileXmlParseXmlRWKeys::GrpKey();
		}
		if(AttributeIsLack(pNode,strErrorInfo,strDesc,strOtherAttName))
		{
			//����������ȱ�٣���������֤����ǰ�ڵ�ֱ�ӷ��ش���
			nRet = 1;
			//return nRet;
		}
		else
		{
#ifdef CHECK_XML_ATTRIBUTE_ORDER
			char_t* cNodeName = (char_t*)pNode->name();
			CString strNodeName(cNodeName);
			xml_attribute xmlAtt = pNode->first_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::DevIdKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;

			xmlAtt = xmlAtt.next_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::ClassKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;

			if(nAttCount == 4)
			{
				xmlAtt = xmlAtt.next_attribute();
				if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::GrpKey(),strNodeName,strDesc,strErrorInfo))
					nRet = 1;
			}

			xmlAtt = xmlAtt.next_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::Md5Key(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;
#else
			nRet = 0;
#endif

		}
	}
	return nRet;
	//return 0;
}

long CSetFilesXml_DSC::CheckDevInfo(pugi::xml_node *pNode,CString& strErrorInfo)
{
	int nRet = 0;
	CString strDesc = "";
	if(FindAttributeName(pNode,strErrorInfo,strDesc))
	{
		//���������д��󣬲�������֤����ǰ�ڵ�ֱ�ӷ��ش���
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 1)
		{
			//strErrorInfo += _T("DevInfo�ڵ�������������\r\n");
			nRet = 1;
		}
		if(AttributeIsLack(pNode,strErrorInfo,strDesc))
		{
			//����������ȱ�٣���������֤����ǰ�ڵ�ֱ�ӷ��ش���
			nRet = 1;
			//return nRet;
		}
		else
		{
#ifdef CHECK_XML_ATTRIBUTE_ORDER
			char_t* cNodeName = (char_t*)pNode->name();
			CString strNodeName(cNodeName);
			xml_attribute xmlAtt = pNode->first_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::ItemNumKey(),strNodeName,strDesc,strErrorInfo))
				return 1;
#else
			nRet = 0;
#endif

		}
	}

	//Ĭ���ļ�DI �ڵ���ڵ��� 1��
	int nChildCount = pNode->child_number();
	if(pNode->child_number() < 1)
	{
		strErrorInfo += _T("�ڵ�DevInfo,�ӽڵ�DI������С��1 \r\n");
		nRet = 1;
	}

	for(pugi::xml_node nodeTemp = pNode->first_child();nodeTemp;nodeTemp = nodeTemp.next_sibling())
	{
		char_t* cNodeName = (char_t*)nodeTemp.name();
		CString strNodeName(cNodeName);
		if(strNodeName != (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_DIKey())
		{
			continue;
		}
		if(FindChildNodeName(&nodeTemp,strErrorInfo))
		{
			nRet = 1;
		}
		if(CheckNode(nodeTemp,(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_DIKey(),(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_DevInfoKey(),strErrorInfo))
			nRet = 1;

		if(CheckDI(&nodeTemp,strErrorInfo))
		{
			nRet = 1;
		}
	}

	return nRet;
	//return 0;
}

long CSetFilesXml_DSC::CheckDI(pugi::xml_node *pNode,CString& strErrorInfo)
{
	int nRet = 0;
	CString strDesc = "";
	xml_attribute xmlAttDesc = pNode->attribute(L"desc");
	if(!xmlAttDesc.empty())
	{
		char_t* cDescValue = (char_t*)xmlAttDesc.value();
		CString strDescValue(cDescValue);
		strDesc = strDescValue;
	}
	if(FindAttributeName(pNode,strErrorInfo,strDesc))
	{
		//���������д��󣬲�������֤����ǰ�ڵ�ֱ�ӷ��ش���
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 1)
		{
			//strErrorInfo += _T("DI�ڵ�������������\r\n");
			nRet = 1;
			//return 1;
		}
		if(AttributeIsLack(pNode,strErrorInfo,strDesc))
		{
			//����������ȱ�٣���������֤����ǰ�ڵ�ֱ�ӷ��ش���
			nRet = 1;
			//return nRet;
		}
		else
		{
#ifdef CHECK_XML_ATTRIBUTE_ORDER
			char_t* cNodeName = (char_t*)pNode->name();
			CString strNodeName(cNodeName);
			xml_attribute xmlAtt = pNode->first_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::DescKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;
#else
			nRet = 0;
#endif
			
		}
	}
	//text��ֵ�Ƿ���Ҫ��֤  �Ƿ���

	return nRet;
	//return 0;
}

long CSetFilesXml_DSC::CheckFileInfo(pugi::xml_node *pNode,CString& strErrorInfo)
{
	int  nRet = 0;
	CString strDesc = "";
	if(FindAttributeName(pNode,strErrorInfo,strDesc))
	{
		//���������д��󣬲�������֤����ǰ�ڵ�ֱ�ӷ��ش���
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 1)
		{
			//strErrorInfo += _T("FileInfo�ڵ�������������\r\n");
			nRet = 1;
			//return 1;
		}
		if(AttributeIsLack(pNode,strErrorInfo,strDesc))
		{
			//����������ȱ�٣���������֤����ǰ�ڵ�ֱ�ӷ��ش���
			nRet = 1;
			//return nRet;
		}
		else
		{
#ifdef CHECK_XML_ATTRIBUTE_ORDER
			char_t* cNodeName = (char_t*)pNode->name();
			CString strNodeName(cNodeName);
			xml_attribute xmlAtt = pNode->first_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::ItemNumKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;
#else
			nRet = 0;
#endif
			
		}
	}

	//Ĭ���ļ�FI �ڵ���ڵ��� 1��
	int nChildCount = pNode->child_number();
	if(pNode->child_number() < 1)
	{
		strErrorInfo += _T("�ڵ�FileInfo,�ӽڵ�FI������С��1 \r\n");
		nRet = 1;
	}

	for(pugi::xml_node nodeTemp = pNode->first_child();nodeTemp;nodeTemp = nodeTemp.next_sibling())
	{
		char_t* cNodeName = (char_t*)nodeTemp.name();
		CString strNodeName(cNodeName);
		if(strNodeName != (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_FIKey())
		{
			continue;
		}
		if(FindChildNodeName(&nodeTemp,strErrorInfo))
		{
			nRet = 1;
		}
		if(CheckNode(nodeTemp,(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_FIKey(),(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_FileInfoKey(),strErrorInfo))
			nRet = 1;

		if(CheckFI(&nodeTemp,strErrorInfo))
		{
			nRet = 1;
		}
	}

	return nRet;
	//return 0;
}

long CSetFilesXml_DSC::CheckFI(pugi::xml_node *pNode,CString& strErrorInfo)
{
	int nRet = 0;
	CString strDesc = "";
	xml_attribute xmlAttDesc = pNode->attribute(L"desc");
	if(!xmlAttDesc.empty())
	{
		char_t* cDescValue = (char_t*)xmlAttDesc.value();
		CString strDescValue(cDescValue);
		strDesc = strDescValue;
	}
	if(FindAttributeName(pNode,strErrorInfo,strDesc))
	{
		//���������д��󣬲�������֤����ǰ�ڵ�ֱ�ӷ��ش���
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 1)
		{
			//strErrorInfo += _T("FI�ڵ�������������\r\n");
			nRet = 1;
			//return 1;
		}
		if(AttributeIsLack(pNode,strErrorInfo,strDesc))
		{
			//����������ȱ�٣���������֤����ǰ�ڵ�ֱ�ӷ��ش���
			nRet = 1;
			//return nRet;
		}
		else
		{
#ifdef CHECK_XML_ATTRIBUTE_ORDER
			char_t* cNodeName = (char_t*)pNode->name();
			CString strNodeName(cNodeName);
			xml_attribute xmlAtt = pNode->first_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::DescKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;
#else
			nRet = 0;
#endif

		}
	}
	//text��ֵ�Ƿ���Ҫ��֤  �Ƿ���

	return nRet;
	//return 0;
}

long CSetFilesXml_DSC::CheckSetting(pugi::xml_node *pNode,CString& strErrorInfo)
{
	int nRet = 0;
	CString strDesc = "";
	xml_attribute xmlAttDesc = pNode->attribute(L"class");
	if(!xmlAttDesc.empty())
	{
		char_t* cClassValue = (char_t*)xmlAttDesc.value();
		CString strClassValue(cClassValue);
		strDesc = strClassValue;
	}
	if(FindAttributeName(pNode,strErrorInfo,strDesc))
	{
		//���������д��󣬲�������֤����ǰ�ڵ�ֱ�ӷ��ش���
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 3 && nAttCount != 4)
		{
			//strErrorInfo += _T("Settings�ڵ�������������\r\n");
			nRet = 1;
			//return 1;
		}

		CString strOtherAttName = "";
		if(nAttCount <= 3)
		{
			strOtherAttName = (CString)CSetFileXmlParseXmlRWKeys::GrpKey();
		}
		if(AttributeIsLack(pNode,strErrorInfo,strDesc,strOtherAttName))
		{
			//����������ȱ�٣���������֤����ǰ�ڵ�ֱ�ӷ��ش���
			nRet = 1;
			//return nRet;
		}
		else
		{
#ifdef CHECK_XML_ATTRIBUTE_ORDER
			char_t* cNodeName = (char_t*)pNode->name();
			CString strNodeName(cNodeName);
			xml_attribute xmlAtt = pNode->first_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::LdKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;

			xmlAtt = xmlAtt.next_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::ClassKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;

			if(nAttCount == 4)
			{
				xmlAtt = xmlAtt.next_attribute();
				if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::GrpKey(),strNodeName,strDesc,strErrorInfo))
					nRet = 1;
			}

			xmlAtt = xmlAtt.next_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::InfoGrpNumKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;
#else
			nRet = 0;
#endif


		}
	}
	
	//Ĭ���ļ�InfoGrp �ڵ���ڵ��� 1��
	int nChildCount = pNode->child_number();
	if(pNode->child_number() < 1)
	{
		//strErrorInfo += _T("�ڵ�Settings,[%s]InfoGrp�ڵ�����С��1\r\n");
		strErrorInfo.AppendFormat(_T("�ڵ�Settings,[%s]���ӽڵ�InfoGrp������С��1 \r\n"),strDesc);
		nRet = 1;
	}

	for(pugi::xml_node nodeTemp = pNode->first_child();nodeTemp;nodeTemp = nodeTemp.next_sibling())
	{
		char_t* cNodeName = (char_t*)nodeTemp.name();
		CString strNodeName(cNodeName);
		if(strNodeName != (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_InfoGrpKey())
		{
			continue;
		}
		//��֤InfoGrp�����Ƿ��зǷ����ӽڵ�
		if(FindChildNodeName(&nodeTemp,strErrorInfo))
		{
			nRet = 1;
		}
		if(CheckNode(nodeTemp,(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_InfoGrpKey(),(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_SettingsKey(),strErrorInfo))
			nRet = 1;

		if(CheckInfoGrp(&nodeTemp,strErrorInfo))
		{
			nRet = 1;
		}
	}

	return nRet;
	//return 0;
}

long CSetFilesXml_DSC::CheckInfoGrp(pugi::xml_node *pNode,CString& strErrorInfo)
{
	int nRet = 0;
	CString strDesc = "";
	xml_attribute xmlAttDesc = pNode->attribute(L"desc");
	if(!xmlAttDesc.empty())
	{
		char_t* cDescValue = (char_t*)xmlAttDesc.value();
		CString strDescValue(cDescValue);
		strDesc = strDescValue;
	}
	if(FindAttributeName(pNode,strErrorInfo,strDesc))
	{
		//���������д��󣬲�������֤����ǰ�ڵ�ֱ�ӷ��ش���
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 4)
		{
			//strErrorInfo += _T("InfoGrp�ڵ�������������\r\n");
			nRet = 1;
			//return 1;
		}
		if(AttributeIsLack(pNode,strErrorInfo,strDesc))
		{
			//����������ȱ�٣���������֤����ǰ�ڵ�ֱ�ӷ��ش���
			nRet = 1;
			//return nRet;
		}
		else
		{
#ifdef CHECK_XML_ATTRIBUTE_ORDER
			char_t* cNodeName = (char_t*)pNode->name();
			CString strNodeName(cNodeName);
			xml_attribute xmlAtt = pNode->first_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::DescKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;

			xmlAtt = xmlAtt.next_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::SetGrpNumKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;
			xmlAtt = xmlAtt.next_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::ItemNumKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;

			xmlAtt = xmlAtt.next_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::RemoteKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;
#else
			nRet = 0;
#endif
	
		}
	}
	
	//Ĭ���ļ�SI �ڵ���ڵ��� 1��
	int nChildCount = pNode->child_number();
	if(pNode->child_number() < 1)
	{
		//strErrorInfo += _T("SI�ڵ�����С��1\r\n");
		strErrorInfo.AppendFormat(_T("�ڵ�InfoGrp [%s],�ӽڵ�SI������С��1 \r\n"),strDesc);
		nRet = 1;
	}

	for(pugi::xml_node nodeTemp = pNode->first_child();nodeTemp;nodeTemp = nodeTemp.next_sibling())
	{
		char_t* cNodeName = (char_t*)nodeTemp.name();
		CString strNodeName(cNodeName);
		if(strNodeName != (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_SIKey())
		{
			continue;
		}
		if(FindChildNodeName(&nodeTemp,strErrorInfo))
		{
			nRet = 1;
		}
		if(CheckNode(nodeTemp,(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_SIKey(),(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_InfoGrpKey(),strErrorInfo))
			nRet = 1;

		if(CheckSI(&nodeTemp,strErrorInfo))
		{
			nRet = 1;
		}
	}

	return nRet;
	//return 0;
}

long CSetFilesXml_DSC::CheckSI(pugi::xml_node *pNode,CString& strErrorInfo)
{
	int nRet = 0;
	CString strDesc = "";
	xml_attribute xmlAttDesc = pNode->attribute(L"desc");
	if(!xmlAttDesc.empty())
	{
		char_t* cDescValue = (char_t*)xmlAttDesc.value();
		CString strDescValue(cDescValue);
		strDesc = strDescValue;
	}
	if(FindAttributeName(pNode,strErrorInfo,strDesc))
	{
		//���������д��󣬲�������֤����ǰ�ڵ�ֱ�ӷ��ش���
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 6 && nAttCount != 7)
		{
			//strErrorInfo += _T("SI�ڵ�������������\r\n");
			nRet = 1;
			//return 1;
		}

		CString strOtherAttName = "";
		if(nAttCount <= 6)
		{
			strOtherAttName = (CString)CSetFileXmlParseXmlRWKeys::UnitKey();
		}
		if(AttributeIsLack(pNode,strErrorInfo,strDesc,strOtherAttName))
		{
			//����������ȱ�٣���������֤����ǰ�ڵ�ֱ�ӷ��ش���
			nRet = 1;
			//return nRet;
		}
		else
		{
#ifdef CHECK_XML_ATTRIBUTE_ORDER
			char_t* cNodeName = (char_t*)pNode->name();
			CString strNodeName(cNodeName);
			xml_attribute xmlAtt = pNode->first_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::DescKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;

			xmlAtt = xmlAtt.next_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::TypeKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;

			if(nAttCount == 7)
			{
				xmlAtt = xmlAtt.next_attribute();
				if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::UnitKey(),strNodeName,strDesc,strErrorInfo))
					nRet = 1;
			}

			xmlAtt = xmlAtt.next_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::MinKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;

			xmlAtt = xmlAtt.next_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::MaxKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;

			xmlAtt = xmlAtt.next_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::StepKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;

			xmlAtt = xmlAtt.next_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::RefKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;
#else
			nRet = 0;
#endif
			
		}
	}
	
	//Ĭ���ļ�Val �ڵ���ڵ��� 1��
	int nChildCount = pNode->child_number();
	if(pNode->child_number() < 1)
	{
		//strErrorInfo += _T("Val�ڵ�����С��1\r\n");
		strErrorInfo.AppendFormat(_T("�ڵ�SI [%s],�ӽڵ�Val������С��1 \r\n"),strDesc);
		nRet = 1;
	}

	for(pugi::xml_node nodeTemp = pNode->first_child();nodeTemp;nodeTemp = nodeTemp.next_sibling())
	{
		char_t* cNodeName = (char_t*)nodeTemp.name();
		CString strNodeName(cNodeName);
		if(strNodeName != (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_ValKey())
		{
			continue;
		}
		if(FindChildNodeName(&nodeTemp,strErrorInfo))
		{
			nRet = 1;
		}
		if(CheckNode(nodeTemp,(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_ValKey(),(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_SIKey(),strErrorInfo))
			nRet = 1;

		if(CheckVal(&nodeTemp,strErrorInfo))
		{
			nRet = 1;
		}
	}

	return nRet;
	//return 0;
}

long CSetFilesXml_DSC::CheckVal(pugi::xml_node *pNode,CString& strErrorInfo)
{
	int nRet = 0;
	CString strDesc = "";
	if(FindAttributeName(pNode,strErrorInfo,strDesc))
	{
		//���������д���
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		//if(nAttCount != 1)
		if(nAttCount == 0)//û��grp������
		{ 
			//����ǵ������ǿ���û��grp���ԣ������ڴ��󣬶���û�����ڴ���  û��grp���� ����Ϊ 0
			pugi::xml_node nodeSetting =  (pNode->parent()).parent().parent();
			if(!nodeSetting.empty())
			{
				xml_attribute arrGrp = nodeSetting.attribute(L"grp");
				//Setting û��grp ���� Ĭ���ǵ���
				if(arrGrp.empty())
				{
					nRet = 0;
				}
				else
				{
					char_t* cGrpValue = (char_t*)arrGrp.value();
					CString strGpValue(cGrpValue);
					int nGrp = atoi(strGpValue);
					if(nGrp > 0)
					{
						strErrorInfo += _T("Val�ڵ�������������\r\n");
						nRet = 1;
					}
					else
					{
						nRet = 0;
					}
				}
			}
			//strErrorInfo += _T("Val�ڵ�������������;");
			//nRet = 1;
			//return 1;
		}
		else if(nAttCount == 1)//��grp�����ԣ���֤grp
		{
			char_t* cNodeName = (char_t*)pNode->name();
			CString strNodeName(cNodeName);
			xml_attribute xmlAtt = pNode->first_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::GrpKey(),strNodeName,strDesc,strErrorInfo))
			{
				nRet = 1;
			}
		}
		else
		{
			strErrorInfo += _T("Val�ڵ�������������,���ֻ��һ������\r\n");
			nRet = 1;
		}
	}

	return nRet;
	//return 0;
}

long CSetFilesXml_DSC::CheckRemark(pugi::xml_node *pNode,CString& strErrorInfo)
{
	int nRet = 0;
	CString strDesc = "";
	if(FindAttributeName(pNode,strErrorInfo,strDesc))
	{
		//���������д��󣬲�������֤����ǰ�ڵ�ֱ�ӷ��ش���
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 3 && nAttCount != 2)
		{
			//strErrorInfo = "Rslt=0;ErrorInfo=Remark�ڵ�������������;";
			//strErrorInfo += _T("Remark�ڵ�������������\r\n");
			nRet = 1;
			//return 1;
		}

		CString strOtherAttName = "";
		if(nAttCount <= 2)
		{
			strOtherAttName = (CString)CSetFileXmlParseXmlRWKeys::UpdateKey();
		}
		if(AttributeIsLack(pNode,strErrorInfo,strDesc,strOtherAttName))
		{
			//����������ȱ�٣���������֤����ǰ�ڵ�ֱ�ӷ��ش���
			nRet = 1;
			//return nRet;
		}
		else
		{
#ifdef CHECK_XML_ATTRIBUTE_ORDER
			char_t* cNodeName = (char_t*)pNode->name();
			CString strNodeName(cNodeName);
			xml_attribute xmlAtt = pNode->first_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::ItemNumKey(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;

			if(nAttCount == 3)
			{
				xmlAtt = xmlAtt.next_attribute();
				if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::UpdateKey(),strNodeName,strDesc,strErrorInfo))
					nRet = 1;
			}

			xmlAtt = xmlAtt.next_attribute();
			if(CheckAttribute(xmlAtt,(CString)CSetFileXmlParseXmlRWKeys::Md5Key(),strNodeName,strDesc,strErrorInfo))
				nRet = 1;
#else
			nRet = 0;
#endif
			
		}
	}

	
	//Ĭ���ļ�RI �ڵ����û�У�Ϊ0��
	/*int nChildCount = pNode->child_number();
	if(pNode->child_number() < 1)
	{
	return 1;
	}*/
	for(pugi::xml_node nodeTemp = pNode->first_child();nodeTemp;nodeTemp = nodeTemp.next_sibling())
	{
		char_t* cNodeName = (char_t*)nodeTemp.name();
		CString strNodeName(cNodeName);
		if(strNodeName != (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_RIKey())
		{
			continue;
		}
		if(FindChildNodeName(&nodeTemp,strErrorInfo))
		{
			nRet = 1;
		}                
		if(CheckNode(nodeTemp,(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_RIKey(),(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_RemarkKey(),strErrorInfo))
			nRet = 1;

		//��ע��Ϣ RI�ڵ� û������ ����Ҫ��֤���Ե�˳�������
		/*if(CheckRI(&nodeTemp))
		{
		return 1;
		}*/
	}

	return nRet;
	//return 0;
}

long CSetFilesXml_DSC::CheckRI(pugi::xml_node *pNode,CString& strErrorInfo)
{
	return 0;
}

long CSetFilesXml_DSC::CheckNode(pugi::xml_node oNode,CString strNodeText,CString strParentName,CString& strErrorInfo)
{
	int nRet = 0;
	if(!oNode.empty())
	{
		char_t* cNodeName = (char_t*)oNode.name();
		CString strNodeName(cNodeName);
		if(strNodeName != strNodeText)
		{		
			//strErrorInfo.AppendFormat(_T("DSC�ӽڵ�%s��˳�򲻶� \r\n"),strNodeName.GetString());
			strErrorInfo.AppendFormat(_T("%s���ӽڵ�%s��˳�򲻶� \r\n"),strParentName,strNodeName.GetString());
			nRet = 1;
		}
	}
	return nRet;
}

long CSetFilesXml_DSC::CheckAttribute(pugi::xml_attribute xmlAtt,CString strAttText,CString& strNodeName,CString &strDesc,CString& strErrorInfo)
{
	int nRet = 0;
	if(!xmlAtt.empty())
	{
		char_t* cAttName = (char_t*)xmlAtt.name();
		CString strAttName(cAttName);
		if(strAttName != strAttText)
		{
			if(strDesc != "")
			{
				strErrorInfo.AppendFormat(_T("�ڵ�%s [%s],[%s]����˳����� \r\n"),strNodeName,strDesc,strAttName);
			}
			else
			{
			strErrorInfo.AppendFormat(_T("�ڵ�%s,[%s]����˳����� \r\n"),strNodeName,strAttName);
			}
			
			nRet = 1;
		}
	}
	else
	{
		//strErrorInfo.AppendFormat(_T("ȱ�����ԣ����� %s \r\n"),strAttText);
		nRet = 1;  //ȱ������
	}

	return nRet;
	//return 0;
}


//��ʼ����������
void CSetFilesXml_DSC::InitAttributeName()
{
	m_mapAttributeName.clear();
	//DSC����
	list<CString> strListDSC;
	strListDSC.push_back((CString)CSetFileXmlParseXmlRWKeys::ConfigVersionKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetFilesXml_DSCKey()] = strListDSC;

	//Dsc���ӽڵ�
	list<CString> strListDSCNode;
	strListDSCNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HeaderKey());
	strListDSCNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HashInfoKey());
	strListDSCNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_UpdateKey());
	strListDSCNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_DevInfoKey());
	strListDSCNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_FileInfoKey());
	strListDSCNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_SettingsKey());
	strListDSCNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_RemarkKey());
	CString strKey = (CString)CSetFileXmlParseXmlRWKeys::CSetFilesXml_DSCKey() + "-Child";
	m_mapAttributeName[strKey] = strListDSCNode;


	//����Headr����������
	list<CString> strListHeader;
	strListHeader.push_back((CString)CSetFileXmlParseXmlRWKeys::DevTypeKey());
	strListHeader.push_back((CString)CSetFileXmlParseXmlRWKeys::DevIdKey());
	strListHeader.push_back((CString)CSetFileXmlParseXmlRWKeys::IedNameKey());
	strListHeader.push_back((CString)CSetFileXmlParseXmlRWKeys::UpdateTimeKey());
	strListHeader.push_back((CString)CSetFileXmlParseXmlRWKeys::Md5Key());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HeaderKey()] = strListHeader;

	//����HashInfo���ӽڵ�HI����������
	list<CString> strListHashInfo;
	strListHashInfo.push_back((CString)CSetFileXmlParseXmlRWKeys::ItemNumKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HashInfoKey()] = strListHashInfo;
	//HashInfo���ӽڵ�
	list<CString> strListHashInfoNode;
	strListHashInfoNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HIKey());
	strKey = (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HashInfoKey() + "-Child";
	m_mapAttributeName[strKey] = strListHashInfoNode;
	//HI����
	list<CString> strListHI;
	strListHI.push_back((CString)CSetFileXmlParseXmlRWKeys::ClassKey());
	strListHI.push_back((CString)CSetFileXmlParseXmlRWKeys::Md5Key());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HIKey()] = strListHI;
	
	//����Update���ӽڵ�UI����������
	list<CString> strListUpdate;
	strListUpdate.push_back((CString)CSetFileXmlParseXmlRWKeys::ItemNumKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_UpdateKey()] = strListUpdate;
	//Update���ӽڵ�
	list<CString> strListUpdateNode;
	strListUpdateNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_UIKey());
	strKey = (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_UpdateKey() + "-Child";
	m_mapAttributeName[strKey] = strListUpdateNode;
	//UI����
	list<CString> strListUI;
	strListUI.push_back((CString)CSetFileXmlParseXmlRWKeys::LdKey());
	strListUI.push_back((CString)CSetFileXmlParseXmlRWKeys::ClassKey());
	strListUI.push_back((CString)CSetFileXmlParseXmlRWKeys::GrpKey());
	strListUI.push_back((CString)CSetFileXmlParseXmlRWKeys::Md5Key());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_UIKey()] = strListUI;

	//����DevInfo���ӽڵ�DI����������
	list<CString> strListDevInfo;
	strListDevInfo.push_back((CString)CSetFileXmlParseXmlRWKeys::ItemNumKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_DevInfoKey()] = strListDevInfo;
	//DevInfo���ӽڵ�
	list<CString> strListDevInfoNode;
	strListDevInfoNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_DIKey());
	strKey = (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_DevInfoKey() + "-Child";
	m_mapAttributeName[strKey] = strListDevInfoNode;
	//DI����
	list<CString> strListDI;
	strListDI.push_back((CString)CSetFileXmlParseXmlRWKeys::DescKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_DIKey()] = strListDI;

	//����FileInfo���ӽڵ�FI����������
	list<CString> strListFileInfo;
	strListFileInfo.push_back((CString)CSetFileXmlParseXmlRWKeys::ItemNumKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_FileInfoKey()] = strListFileInfo;
	//FileInfo���ӽڵ�
	list<CString> strListFileInfoNode;
	strListFileInfoNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_FIKey());
	strKey = (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_FileInfoKey() + "-Child";
	m_mapAttributeName[strKey] = strListFileInfoNode;
	//FI����
	list<CString> strListFI;
	strListFI.push_back((CString)CSetFileXmlParseXmlRWKeys::DescKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_FIKey()] = strListFI;

	//����Setting���ӽڵ�InfoGrp,SI,Val����������
	list<CString> strListSetting;
	strListSetting.push_back((CString)CSetFileXmlParseXmlRWKeys::LdKey());
	strListSetting.push_back((CString)CSetFileXmlParseXmlRWKeys::ClassKey());
	strListSetting.push_back((CString)CSetFileXmlParseXmlRWKeys::GrpKey());
	strListSetting.push_back((CString)CSetFileXmlParseXmlRWKeys::InfoGrpNumKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_SettingsKey()] = strListSetting;
	//Setting���ӽڵ�
	list<CString> strListSettingNode;
	strListSettingNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_InfoGrpKey());
	strKey = (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_SettingsKey() + "-Child";
	m_mapAttributeName[strKey] = strListSettingNode;
	//InfoGrp������
	list<CString> strListInfoGrp;
	strListInfoGrp.push_back((CString)CSetFileXmlParseXmlRWKeys::DescKey());
	strListInfoGrp.push_back((CString)CSetFileXmlParseXmlRWKeys::SetGrpNumKey());
	strListInfoGrp.push_back((CString)CSetFileXmlParseXmlRWKeys::ItemNumKey());
	strListInfoGrp.push_back((CString)CSetFileXmlParseXmlRWKeys::RemoteKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_InfoGrpKey()] = strListInfoGrp;
	//InfoGrp���ӽڵ�
	list<CString> strListInfoGrpNode;
	strListInfoGrpNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_SIKey());
	strKey = (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_InfoGrpKey() + "-Child";
	m_mapAttributeName[strKey] = strListInfoGrpNode;
	//SI������
	list<CString> strListSI;
	strListSI.push_back((CString)CSetFileXmlParseXmlRWKeys::DescKey());
	strListSI.push_back((CString)CSetFileXmlParseXmlRWKeys::TypeKey());
	strListSI.push_back((CString)CSetFileXmlParseXmlRWKeys::UnitKey());
	strListSI.push_back((CString)CSetFileXmlParseXmlRWKeys::MinKey());
	strListSI.push_back((CString)CSetFileXmlParseXmlRWKeys::MaxKey());
	strListSI.push_back((CString)CSetFileXmlParseXmlRWKeys::StepKey());
	strListSI.push_back((CString)CSetFileXmlParseXmlRWKeys::RefKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_SIKey()] = strListSI;
	//SI���ӽڵ�
	list<CString> strListSINode;
	strListSINode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_ValKey());
	strKey = (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_SIKey() + "-Child";
	m_mapAttributeName[strKey] = strListSINode;
	//Val������
	list<CString> strListVal;
	strListVal.push_back((CString)CSetFileXmlParseXmlRWKeys::GrpKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_ValKey()] = strListVal;

	//����Remark���ӽڵ�RI����������
	list<CString> strListRemark;
	strListRemark.push_back((CString)CSetFileXmlParseXmlRWKeys::ItemNumKey());
	strListRemark.push_back((CString)CSetFileXmlParseXmlRWKeys::UpdateKey());
	strListRemark.push_back((CString)CSetFileXmlParseXmlRWKeys::Md5Key());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_RemarkKey()] = strListRemark;
	//Remark���ӽڵ�
	list<CString> strListRemarkNode;
	strListRemarkNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_RIKey());
	strKey = (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_RemarkKey() + "-Child";
	m_mapAttributeName[strKey] = strListRemarkNode;
	//RI������
	list<CString> strListRI;
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_RIKey()] = strListRI;
}

long CSetFilesXml_DSC::FindAttributeName(pugi::xml_node *pNode,CString& strErrorInfo,CString &strDesc)
{
	int nRet = 0;
	char_t* cNodeName = (char_t*)pNode->name();
	CString strNodeName(cNodeName);
    
	///��֤���������Ƿ���ȷ
	CString strErrorName = "";
	xml_attribute xmlAttTemp = pNode->first_attribute();
	while(!xmlAttTemp.empty())
	{
		//���б��У����Ҳ��������ڷǷ�������
		char_t* cName = (char_t*)xmlAttTemp.name();
		CString strName(cName);
		list<CString>::iterator it = std::find(m_mapAttributeName[strNodeName].begin(), m_mapAttributeName[strNodeName].end(), strName);
		if (it == m_mapAttributeName[strNodeName].end()) 
		{
			strErrorName.AppendFormat(_T("%s,"),strName.GetString());
		}
		xmlAttTemp = xmlAttTemp.next_attribute();
	}
	if(strErrorName != "")
	{
		CString strNodeNameText;
		if(strDesc == "")
		{
			strNodeNameText.Format(_T("�ڵ�%s,���ڷǷ�����<"),strNodeName.GetString());
		}
		else
		{
			strNodeNameText.Format(_T("�ڵ�%s [%s],���ڷǷ�����<"),strNodeName.GetString(),strDesc);
		}

		strErrorName.Delete(strErrorName.GetLength() - 1);
		strErrorName += _T(">");

		CString strError;
		strError = strNodeNameText + strErrorName;
		strErrorInfo.AppendFormat(_T("%s\r\n"), strError);
		nRet = 1;
	}
	
	return nRet;
}

long CSetFilesXml_DSC::AttributeIsLack(pugi::xml_node *pNode,CString& strErrorInfo,CString &strDesc,CString strOtherAttName)
{
	int nRet = 0;
	char_t* cNodeName = (char_t*)pNode->name();
	CString strNodeName(cNodeName);

	//�����������ƣ��ҵ������б���ɾ��
	list<CString> lstTemp = m_mapAttributeName[strNodeName];
	xml_attribute xmlAttTemp = pNode->first_attribute();
	while(!xmlAttTemp.empty())
	{
		char_t* cName = (char_t*)xmlAttTemp.name();
		CString strName(cName);
		list<CString>::iterator it = std::find(lstTemp.begin(), lstTemp.end(), strName);
		if (it != lstTemp.end()) 
		{
			lstTemp.erase(it);
		}
		xmlAttTemp = xmlAttTemp.next_attribute();
	}

	//�б���ʣ��ģ����Ƕ��ڵ�ǰ�ڵ� ȱ�ٵ�����
	CString strErrorName = "";
	if(lstTemp.size() > 0)
	{
		CString strNodeNameText;
		if(strDesc == "")
		{
			strNodeNameText.Format(_T("�ڵ�%s,ȱ������<"),strNodeName.GetString());
		}
		else
		{
			strNodeNameText.Format(_T("�ڵ�%s [%s],ȱ������<"),strNodeName.GetString(),strDesc);
		}
		
		list<CString>::iterator it;
		for(it = lstTemp.begin();it != lstTemp.end();it++)
		{
			CString strName = *it;
			if(strName != strOtherAttName)
			{
				strErrorName.AppendFormat(_T("%s,"),strName);
			}
		}

		if (strErrorName.GetLength() > 0)
		{
			strErrorName.Delete(strErrorName.GetLength() - 1);
			strErrorName += _T(">");

			CString strError;
			strError = strNodeNameText + strErrorName;
			strErrorInfo.AppendFormat(_T("%s\r\n"), strError);
			nRet = 1;
		}
	}
	
	return nRet;
}

long CSetFilesXml_DSC::FindChildNodeName(pugi::xml_node *pNode,CString& strErrorInfo)
{
	int nRet = 0;
	char_t* cNodeName = (char_t*)pNode->name();
	CString strNodeName(cNodeName);
	//CString strKey = (CString)CSetFileXmlParseXmlRWKeys::CSetFilesXml_DSCKey() + "-Child";
	CString strKey = strNodeName + "-Child";

	///��֤ �ӽڵ��Ƿ���ڷǷ�
	CString strErrorName = "";
	pugi::xml_node nodeTemp = pNode->first_child();
	while (! nodeTemp.empty())
	{
		char_t* cChildNodeName = (char_t*)nodeTemp.name();
		CString strChildNodeName(cChildNodeName);
		//û���ӽڵ㣬��value��text��ֵ������ʾ���ӽڵ�
		if(strChildNodeName == "")
		{
			nodeTemp = nodeTemp.next_sibling();
			continue;
		}
		//�Ȳ���key�Ƿ����
		map<CString,list<CString>>::iterator itmap = m_mapAttributeName.find(strKey);
		//�����ڣ���ʾ��ǰ�ڵ㣬û���ӽڵ㣬��������ӽڵ㶼�ǷǷ��ڵ�
		if(itmap == m_mapAttributeName.end())
		{
			strErrorName.AppendFormat(_T("%s,"),strChildNodeName.GetString());
		}
		else
		{
			list<CString>::iterator it = std::find(m_mapAttributeName[strKey].begin(), m_mapAttributeName[strKey].end(), strChildNodeName);
		if (it == m_mapAttributeName[strKey].end()) 
		{
				strErrorName.AppendFormat(_T("%s,"),strChildNodeName.GetString());
		}
		}
		nodeTemp = nodeTemp.next_sibling();
	}
	if(strErrorName != "")
	{
		CString strNodeNameText = "";
		strNodeNameText.Format(_T("�ڵ�%s,���ڷǷ��Ӷ���<"),strNodeName.GetString());

		strErrorName.Delete(strErrorName.GetLength() - 1);
		strErrorName += _T(">");

		CString strError;
		strError = strNodeNameText + strErrorName;
		strErrorInfo.AppendFormat(_T("%s\r\n"), strError);
		nRet = 1;
	}
	return nRet;
}


//��֤���ӽڵ� �Ƿ�ȱ��
long CSetFilesXml_DSC::ChildNodeIsLack(pugi::xml_node *pNode,CString& strErrorInfo)
{
	int nRet = 0;
	//CString strKey = (CString)CSetFileXmlParseXmlRWKeys::CSetFilesXml_DSCKey() + "-Child";
	char_t* cNodeName = (char_t*)pNode->name();
	CString strNodeName(cNodeName);
	CString strKey = strNodeName + "-Child";

	list<CString> lstTemp = m_mapAttributeName[strKey];
	pugi::xml_node nodeTemp = pNode->first_child();
	while (! nodeTemp.empty())
	{
		char_t* cChildNodeName = (char_t*)nodeTemp.name();
		CString strChildNodeName(cChildNodeName);
		list<CString>::iterator it = std::find(lstTemp.begin(), lstTemp.end(), strChildNodeName);
		if (it != lstTemp.end()) 
		{
			lstTemp.erase(it);
		}
		nodeTemp = nodeTemp.next_sibling();
	}

	CString strErrorName = "";
	if(lstTemp.size() > 0)
	{
		//CString strNodeNameText = _T("�ڵ�DSC,ȱ���Ӷ���<");
		CString strNodeNameText = "";
		strNodeNameText.Format(_T("�ڵ�%s,ȱ���Ӷ���<"),strNodeName.GetString());

		list<CString>::iterator it;
		for(it = lstTemp.begin();it != lstTemp.end();it++)
		{
			CString strName = *it;
			strErrorName.AppendFormat(_T("%s,"),strName);
		}

		if (strErrorName.GetLength() > 0)
		{
			strErrorName.Delete(strErrorName.GetLength() - 1);
			strErrorName += _T(">");

			CString strError;
			strError = strNodeNameText + strErrorName;
			strErrorInfo.AppendFormat(_T("%s\r\n"), strError);
			nRet = 1;
		}
	}
	return nRet;
}
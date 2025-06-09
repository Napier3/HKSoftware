//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
	//初始化属性

	//初始化成员变量
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
		if ( !xml_OpenFile(pRWDoc, strFile) )//调用XMLInterface.h中的全局函数，加载资源，入口返回给oDoc；
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
	BSTR bstrElementKey = GetXmlElementKey();//虚函数，利用多态直接调用子类的此函数，返回静态成员变量的值；实际操作为{      return CXLanguageXmlRWKeys::CXLanguageMngrKey();     }
	return OpenXmlFile(strFile, bstrElementKey, pXmlRWKeys,nXmlRWType);//中间参数为刚刚在语言关键子里静态变量指针指向的对象成员变量的值；其对应了根节点的名称；
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
		//V1.00版本
		GetSettingsValTotl(strClass, strValTotal);
	}
	else if (m_strConfigVersion.Find(_T("1.10")) >= 0)
	{
		//V1.10版本
		GetSettingsValTotl_V110(strClass, strValTotal, bReCalMd5);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("当前版本，暂不支持计算md5值，configVersion=%s"), m_strConfigVersion.GetString());
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
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("没找到对应的定值分组信息段，class=%s"), strClass.GetString());
		return;
	}

	pSettings->GetValStringTotal_V110(strValTotal, bReCalMd5);
}

//返回定值单文件中的哈希值
void CSetFilesXml_DSC::GetMd5_FromFile(const CString &strClass, CString &strMd5)
{
	if (strClass == _T(""))
	{
		//为空  返回总的哈希值
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

	//xml 和node 同时更新为0
	m_pUpdateInfo->SetItemNum(0);
}

/*
md5值的计算，是分区计算的。即对于多区定值而言，是根据定值区号计算的
对于多区定值，下装定值时，若同时修改过多个区的定值，Update信息段中，是根据定值区号进行区分的
但HashInfo段中，无法区分多区，因此在下装定值文件前，将HI条目全部清空
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

	//移除/删除pNode     node移除子节点，会删除内存  后期重新添加
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

		//添加 pNode下面的HI
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

//下装前，根据编辑，计算定值的md5，并存到Update信息段
void CSetFilesXml_DSC::CalSettingsMd5ByModify()
{
	//TODO：YUANTING：此处要增加判断m_pUpdateInfo是否为空，因为可能模拟过异常1。
	//若m_pUpdateInfo为空，则需要将m_pUpdateInfo  new出来，需同时处理m_pNode的地方及this类对象
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
			//多区定值，需要遍历判断每个区，是否被编辑。只计算被编辑的区的md5
			CalSettingsMd5ByModify_Multi(pSettings);
		}
		else
		{
			//单区定值。grp不定义。软件初始化值为0或-1；
			//单区定值，直接计算即可
			CString strTotalText, strMd5;
			pSettings->GetValStringTotal_V110_Single(strTotalText);
			pSettings->GetMd5_ForCal(strMd5, strTotalText, TRUE);
			m_pUpdateInfo->AddNewUI(pSettings->m_strLd, pSettings->m_strClass, 0, strMd5);//定值区号 = 0，表示单区定值
		}
	}
}

//多区定值，根据编辑，计算md5，并存到Update信息段
void CSetFilesXml_DSC::CalSettingsMd5ByModify_Multi(CSetsFileXml_Settings *pSettings)
{
	if (pSettings == NULL)
	{
		return;
	}

	if (pSettings->m_nGrp <= 0)
	{
		//说明是单区定值
		return;
	}

	long nSetGrpNum = pSettings->GetSetGrpNum(); //定值区的数量

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

//形参为源，更新到this指针中，只更新Setting部分
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

//形参是被编辑的对象，通过m_dwReserved标记，添加被修改的对象到this指针
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

		CSetsFileXml_Settings *pNew = (CSetsFileXml_Settings *)pSettings->CloneEx(); //仅克隆自身
		AddNewChild(pNew);
		pNew->AppendByModify(pSettings);
	}
}

//更新头部信息：文件修改时间、文件总MD5码
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
校核范围为所有<Settings>所在
首行与</Settings>所在末行之间（包括首行和末行）去掉空格、制表符、
回车、换行后的所有字符内容，十六进制字符采用大写，类型为HEX
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

	//去掉空格、制表符、回车符、换行符
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
实现数据集和定值文件的数值比较。
参数1(Path)：文件路径，GBRPTPATH，表示测试记录的数据文件路径
参数2(SetsFile)：定值参数文件；
参数3(DsFile)：表示数据集文件名；保存的CdvmDataset对象，
参数4(Grp)：定值区号（从1开始，单区定值不生效）；
返回结果：是否相同；异常信息文本。参数1、参数2与参数3拼接得到绝对路径。
说明：
A）	返回的异常信息，举例如下：“***定值数值不一致：MMS=***，定值文件=***”
B）	定值数据的对应，通过名称进行查找
C）	对于多区定值，数据集文件也需要保存所有区的定值。【一个定值区一个定值区去比】
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
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=定值文件不存在<%s>;", strSetsFile);
		return -1;
	}

	if (!IsFileExist(strDatasetFile))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=数据集文件不存在<%s>;", strDatasetFile);
		return -1;
	}

	CDvmDataset oDataset;
	CSetFilesXml_DSC oDsc;

	if (! oDataset.OpenXmlFile(strDatasetFile, CDataMngrXmlRWKeys::g_pXmlKeys))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=数据集文件打开失败;");
		return -1;
	}

	if (! oDsc.OpenXmlFile(strSetsFile, CSetFileXmlParseXmlRWKeys::g_pXmlKeys))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=定值文件打开失败;");
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

	//先定位数据集
	if (pDataset->m_strID.Find(SETTING_CLASS_PARAMETER) >= 0)
	{
		strClass = SETTING_CLASS_PARAMETER;  //装置参数
	}
	else if(pDataset->m_strID.Find(SETTING_CLASS_SETTING) >= 0)
	{
		strClass = SETTING_CLASS_SETTING;  //保护定值
	}
	else if(pDataset->m_strID.Find(SETTING_CLASS_RELAYENA) >= 0)
	{
		strClass = SETTING_CLASS_RELAYENA;  //保护压板
	}
	else if(pDataset->m_strID.Find(SETTING_CLASS_CTRL) >= 0)
	{
		strClass = SETTING_CLASS_CTRL;  //控制字
	}
	else if(pDataset->m_strID.Find(SETTING_CLASS_MATRIX) >= 0)
	{
		strClass = SETTING_CLASS_SETTING;  //跳闸矩阵，在模型中没有专门的数据集，是跟定值数据集是一起的
	}
	else if (pDataset->m_strID.Find(SETTING_CLASS_PARAMETER) >= 0)
	{
		strClass = SETTING_CLASS_PARAMETER;  //免配置参数
	}
	else
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=不支持的数据集;");
		return -1;
	}

	CSetsFileXml_Settings *pSettings = FindSettingsByClass(strClass);

	if (pSettings == NULL)
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=定值文件中，没有和数据集文件同类型的定值分组信息段;");
		return -1;
	}

	BOOL bRet = pSettings->CmpDataset(pDataset, nGrp, ppszRet);
	sprintf(*ppszRet, "Rslt=%d;ErrorInfo=%s;", bRet, *ppszRet);
	return bRet;
}

/*定值文件数值比较
1、定值文件和多个数据集比较，传参为设备模型文件和定值文件，进行多区定值同时比较
2、返回参数和CmpDataset和一致；
3、对于多区定值，例如保护定值数据集。通过在逻辑设备下存多个dataset的方式实现，例如：dsSetting_1、dsSetting_2、……
4、对于模型中本身就有多个数据集的，例如变压器保护，一般有dsSetting1、dsSetting2、……。则会将一个区的定值合并成一个数据集，例如：dsSetting1_1、dsSetting1_2、……
5、对于多区定值，可以根据数据集在逻辑设备下的索引号，确认所属定值区号。例如第一个dsSetting_*，表示1区定值。此时，*=1
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
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=定值文件不存在<%s>;", strSetsFile);
		return -1;
	}

	if (!IsFileExist(strDvmFilePath))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=设备模型文件不存在<%s>;", strDvmFilePath);
		return -1;
	}

	CDvmDevice oDvmDevice;
	CSetFilesXml_DSC oDsc;

	if (! oDvmDevice.OpenXmlFile(strDvmFilePath, CDataMngrXmlRWKeys::g_pXmlKeys))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=数据集文件打开失败;");
		return -1;
	}

	if (! oDsc.OpenXmlFile(strSetsFile, CSetFileXmlParseXmlRWKeys::g_pXmlKeys))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=定值文件打开失败;");
		return -1;
	}

	//return oDsc.CmpDatasets(&oDvmDevice, ppszRet);
	CString strErrorInfo  = "";
	int nRet1 = 1,nRet2 = 1;
	if(!oDsc.CmpDatasets(&oDvmDevice, strErrorInfo))  //仅比较定值的数值，是否一致
	{
		nRet1 = 0;
	}

	//2024-12-16 yuanting 对比定制文件中的装置型号、唯一性编码、IEDname和模型文件中的是否一致
	nRet2 = oDsc.CmpDatasets(&oDvmDevice,strErrorInfo,strDeviceModel,bIsDeviceModel);
	//nRet2==200：其他都合格，仅装置型号为空
	//nRet2==100：装置型号为空，且其他也存在不合格
	//nRet2==0：装置型号不为空，存在其他不合格；
	//nRet2==1：全部合格

	//1）确认装置型号不存在，此项缺失不判定为异常；
	//2）确认装置型号存在，此项缺失判定为异常；
	if(nRet2 == 100 || nRet2 == 200)
	{
		int nRet = MessageBox(NULL,_T("模型文件中，装置型号为空，请确认是否判定为异常\r\n\r\n选择是，确认装置型号存在，此项缺失判定为异常；\r\n选择否，确认装置型号不存在，此项缺失不判定为异常。"),_T("提示"),MB_YESNO|MB_ICONQUESTION);
		if (nRet == IDNO)
		{
			if(nRet2 == 200)
			{
				//nRet2==200：其他都合格，仅装置型号为空
				//人工选择否，则判定结果为正常
				nRet2 = 1;
			}
			else
			{
				//nRet2==100：装置型号为空，且其他也存在不合格
				//人工选择否，由于其他存在不合格，仅判定不合格，不追加异常原因
				nRet2 = 0;
			}
		}
		else
		{
			//人工选择是，则判定为异常，且追加异常原因；
			nRet2 = 0;
			strErrorInfo.AppendFormat(_T("设备模型文件中，装置型号为空\r\n"));
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
		//strErrorInfo.Format(_T("设模型文件中没找到逻辑设备 [%s]"), strDevID);
		strErrorInfo.AppendFormat(_T("设模型文件中没找到逻辑设备 [%s]"), strDevID);
		return 0;
	}

	CDvmDataset *pDataset = NULL;
	pDataset = (CDvmDataset *)pLDevice->FindByID(strDataSetID);
	if (pDataset == NULL)
	{
		strErrorInfo.AppendFormat(_T("设备模型文件中没找到数据集 [%s]"), strDataSetID);
		return 0;
	}

	CString strZZID = "LPHD1$DC$PhyNam$serNum"; //装置识别代码
	CDvmData *pZZData = NULL;
	pZZData = (CDvmData *)pDataset->FindByID(strZZID);
	if (pZZData == NULL)
	{
		strErrorInfo.AppendFormat(_T("设备模型文件没有找到装置识别代码数据 [%s]"), strZZID);
		return 0;
	}
	else if(pZZData->m_strValue != m_pHeader->m_strDevID)
	{
		strErrorInfo.AppendFormat(_T("装置识别码不一致，设备模型文件中[%s]，定值文件中[%s]\r\n"), pZZData->m_strValue, m_pHeader->m_strDevID);
		nRet = 0;
	}

	CString strZZTypeID = "IEDModel"; //装置型号
	CDvmData* pZZTypeData = (CDvmData *)pDataset->FindByID(strZZTypeID);
	if (pZZTypeData == NULL)
	{
		strErrorInfo.AppendFormat(_T("设备模型文件没有找到装置型号数据 [%s]"), strZZTypeID);
		return 0;
	}
	else 
	{
		//先替换装置型号  strDeviceModel 外部传输
		if(bIsDeviceModel)
		{
			pZZTypeData->m_strValue = strDeviceModel;
		}

		//判断装置型号是否为空
		//若模型文件中装置型号的值为空，则弹窗人工选择是否存在异常
		if(pZZTypeData->m_strValue == "")
		{
			//strErrorInfo.AppendFormat(_T("设备模型文件中的装置型号为空;"));	
			nRetType = 100; //标记为空，返回后弹窗人工判定是否合格
			//return 100;
		}
		else
		{
			if(pZZTypeData->m_strValue != m_pHeader->m_strDevType)
			{
				strErrorInfo.AppendFormat(_T("装置型号不一致，设备模型文件中[%s]，定值文件中[%s]\r\n"),pZZTypeData->m_strValue, m_pHeader->m_strDevType);	
				nRet = 0;
			}
		}
	}

	CString strIedNameID = "IEDName"; //IedName
	CDvmData *pIedNameData = NULL;
	pIedNameData = (CDvmData *)pDataset->FindByID(strIedNameID);
	if (pIedNameData == NULL)
	{
		strErrorInfo.AppendFormat(_T("设备模型文件中没有找到IEDName数据 [%s]"),strIedNameID);	
		return 0;
	}
	else if(pIedNameData->m_strValue != m_pHeader->m_strIedName)
	{
		strErrorInfo.AppendFormat(_T("IedName不一致，设备模型文件中[%s]，定值文件中[%s]\r\n"),pIedNameData->m_strValue, m_pHeader->m_strIedName);
		nRet = 0;
		//return 0;
	}

	//验证MD5
	CString strMD5ID = "";
	CDvmData *pMD5Data = NULL;
	POS nHPos = m_pHashInfo->GetHeadPosition();
	while(nHPos != NULL)
	{
		CSetsFileXml_HI* pHiTemp = (CSetsFileXml_HI*)m_pHashInfo->GetNext(nHPos);
		if(pHiTemp->m_strClass == "dsParameter")
		{
			strMD5ID = "LPHD1$SP$SysParaMd5$setVal"; //系统参数
		}
		else if(pHiTemp->m_strClass == "dsSetting")
		{
			strMD5ID = "LPHD1$SP$SettingMd5$setVal"; //保护定值
		}
		else if(pHiTemp->m_strClass == "dsRelayEna")
		{
			strMD5ID = "LPHD1$SP$RelEnaMd5$setVal"; //软压板
		}
		else if(pHiTemp->m_strClass == "dsMatrixSet")
		{
			strMD5ID = "LPHD1$SP$MatrixMd5$setVal"; //出口定值
		}
		else if(pHiTemp->m_strClass == "dsVtcParameter")
		{
			strMD5ID = "LPHD1$SP$VtcParaMd5$setVal"; //免配置参数
		}
		else if (pHiTemp->m_strClass == "dsRemark")  //备注信息
		{
			strMD5ID = "LPHD1$SP$RemarkMd5$setVal";
		}

		pMD5Data = (CDvmData *)pDataset->FindByID(strMD5ID);
		if (pMD5Data == NULL)
		{
			strErrorInfo.AppendFormat(_T("设备模型文件没有找到 [%s] 的MD5数据"),pHiTemp->m_strClass);
			return 0;
		}
		else if(pMD5Data->m_strValue != pHiTemp->m_strmd5)
		{
			strErrorInfo.AppendFormat(_T("[%s]的MD5码不一致，设备模型文件中[%s]，定值文件中[%s]\r\n"),pHiTemp->m_strClass, pMD5Data->m_strValue, pHiTemp->m_strmd5);
			nRet = 0;
			//return 0;
		}
	}

	//验证Remark的MD5
	strMD5ID = "LPHD1$SP$RemarkMd5$setVal"; //备注信息
	pMD5Data = (CDvmData *)pDataset->FindByID(strMD5ID);
	if (pMD5Data == NULL)
	{
		strErrorInfo.AppendFormat(_T("设备模型文件中没有找到Remark的MD5数据"));
		return 0;
	}
	else if(pMD5Data->m_strValue != m_pRemark->m_strmd5)
	{
		strErrorInfo.AppendFormat(_T("备注信息段Remark的MD5码不一致，设备模型文件中[%s]，定值文件中[%s]\r\n"),pMD5Data->m_strValue, m_pRemark->m_strmd5);
		nRet = 0;
		//return 0;
	}

	if(nRet == 1 && nRetType == 100)
	{
		//其他都合格，仅装置型号为空
		return 200;
	}
	else if(nRet == 0 && nRetType == 100)
	{
		//其他存在不合格，且装置型号为空
		return 100;
	}
	return nRet;
	//return 1;
}

/*定值文件数值比较
1、两个定值文件比较。
<paras>
<value name="定值文件名_上召" id="SetsFileUp" data-type="string" value=""/>
<value name="定值文件名_下装" id="SetsFileDown" data-type="string" value=""/>
<value name="文件路径" id="Path" data-type="string" value="GBRPTDATAPATH"/>
<value name="装置编号" id="DeviceSN" data-type="string" value="GBRPTNAME"/>
</paras>
2、返回参数：返回结果：是否相同；异常信息文本。
3、定值文件比较，是校验定值下装后，重新上召，检查下装定值是否生效。因此需以下装的定值为基准；
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
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=定值文件_上召不存在<%s>;", strSetsFileUp);
		return -1;
	}

	if (!IsFileExist(strSetsFileDown))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=定值文件_下装不存在<%s>;", strSetsFileDown);
		return -1;
	}

	CSetFilesXml_DSC oDscUp;
	CSetFilesXml_DSC oDscDown;

	if (! oDscUp.OpenXmlFile(strSetsFileUp, CSetFileXmlParseXmlRWKeys::g_pXmlKeys))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=定值文件_上召打开失败;");
		return -1;
	}

	if (! oDscDown.OpenXmlFile(strSetsFileDown, CSetFileXmlParseXmlRWKeys::g_pXmlKeys))
	{
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=定值文件_下装打开失败;");
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
	//2024-12-16 yuanting 先对比 下装文件中的装置型号、唯一性编码、IEDname和上召文件中的是否一致
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
		strErrorInfo += _T("上召文件缺失Header节点");
		return 0;
	}
	if(m_pHeader == NULL)
	{
		strErrorInfo += _T("下装召文件缺失Header节点");
		return 0;
	}

	//装置识别代码
	if (pSrcUp->m_pHeader->m_strDevID != m_pHeader->m_strDevID)
	{
		strErrorInfo.AppendFormat(_T("上召与下装的装置识别代码不一致 上召[%s] 下装[%s]\r\n"),pSrcUp->m_pHeader->m_strDevID,m_pHeader->m_strDevID);
		nRet = 0;
	}
	//装置型号
	if(pSrcUp->m_pHeader->m_strDevType != m_pHeader->m_strDevType)
	{
		strErrorInfo.AppendFormat(_T("上召与下装的装置型号不一致 上召[%s] 下装[%s]\r\n"),pSrcUp->m_pHeader->m_strDevType,m_pHeader->m_strDevType);
		nRet = 0;
	}
	////IedName
	if(pSrcUp->m_pHeader->m_strIedName != m_pHeader->m_strIedName)
	{
		strErrorInfo.AppendFormat(_T("上召与下装的IedName不一致 上召[%s] 下装[%s]\r\n"), pSrcUp->m_pHeader->m_strIedName,m_pHeader->m_strIedName);
		nRet = 0;
	}

	if(pSrcUp->m_pHashInfo == NULL)
	{
		strErrorInfo += _T("下装召文件缺失HashInfo节点");
		return 0;
	}

	if(m_pHashInfo == NULL)
	{
		strErrorInfo += _T("下装召文件缺失HashInfo节点");
		return 0;
	}

	//验证MD5
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
					strErrorInfo.AppendFormat(_T("上召与下装[%s]的MD5不一致 上召[%s] 下装[%s]\r\n"), pHiTempDown->m_strClass,pHiTempUp->m_strmd5,pHiTempDown->m_strmd5);
					nRet = 0;
				}
				break;
			}
		}
	}

	if(pSrcUp->m_pRemark == NULL)
	{
		strErrorInfo += _T("下装召文件缺失Remark节点");
		return 0;
	}

	if(m_pRemark == NULL)
	{
		strErrorInfo += _T("下装召文件缺失Remark节点");
		return 0;
	}

	//验证Remark的MD5
	if(pSrcUp->m_pRemark->m_strmd5 != m_pRemark->m_strmd5)
	{
		//strErrorInfo.Format(_T("上召文件与下装文件中的Remark的MD5不一致，上召[%s] 下装[%s]"), pSrcUp->m_pRemark->m_strmd5,m_pRemark->m_strmd5);
		strErrorInfo.AppendFormat(_T("上召与下装的Remark的MD5不一致 上召[%s] 下装[%s]\r\n"), pSrcUp->m_pRemark->m_strmd5,m_pRemark->m_strmd5);
		nRet = 0;
	}

	return nRet;
}

/*
编辑修改定值文件的数据
测试模板编辑：自定义界面 ，选择数据对象，显示对象下数据，供用户手动编辑。返回和记录需要修改的定值数据，XML或者JSON格式。
自动测试执行：传入需要修改的定值数据，修改定值文件数据
*/
long CSetFilesXml_DSC::EditSettings(char* strPara, char**ppszRet)
{
	return 0;
}

/*
保存定值参数文件。
参数1(Path)：文件路径，为GBRPTPATH，表示测试记录的数据文件路径
参数2(SetsFile)：保存的定值参数文件名称。
增加此函数的目的，就是能够记录下装的定值文件，因为测试过程中可能不止一次需要下装定值参数文件。
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
		strErrorInfo = _T("文件保存失败");
	}

	sprintf(*ppszRet, "Rslt=%ld;ErrorInfo=%s;", bRet, strErrorInfo);

	return 0;
}

/*
读取定值参数文件。
参数1(Path)：文件路径，为GBRPTPATH，表示测试记录的数据文件路径
参数2(SetsFile)：保存的定值参数文件名称。
增加此函数的目的，就是能够将读取到的定值文件载入SetsFileTest.dll，因为测试过程中第一次从装置读取定值文件，需要加载到内存中，从而基于此文件数据进行编辑修改。
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
		strErrorInfo.Format(_T("定值文件不存在[%s]"), strSetsFile);
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=%s;", strErrorInfo);
		return -1;
	}

	DeleteAll();

	if (! OpenXmlFile(strSetsFile, CSetFileXmlParseXmlRWKeys::g_pXmlKeys))
	{
		strErrorInfo.Format(_T("定值文件打开失败[%s]"), strSetsFile);
		sprintf(*ppszRet, "Rslt=0;ErrorInfo=%s;", strErrorInfo);
		return 0;
	}

	// 	//先创建一个新的对象打开，如果成功则替换，否则则保持原来的数据
	// 	CSetFilesXml_DSC *pNew = new CSetFilesXml_DSC();
	// 
	// 	if (! pNew->OpenXmlFile(strSetsFile, CSetFileXmlParseXmlRWKeys::g_pXmlKeys))
	// 	{
	// 		strErrorInfo = _T("定值文件打开失败");
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
		//文件不存在
		return -1;
	}

	//先创建一个新的对象打开，如果成功则替换，否则则保持原来的数据
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
	//在xml 中添加
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

	//在node中添加
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

//验证定制文件的格式是否正确
long CSetFilesXml_DSC::FileFormatCheck(CString& strErrorInfo)
{
	int nRet = 0;// 0 是正确 1 是错误  原来返回值
	InitAttributeName();//初始化属性名称

	if(m_pNode == NULL)
	{
		strErrorInfo = "Rslt=0;ErrorInfo=文件为空";
		return 1;
	}
	//验证DSC根元素的属性数量和名称
	if(CheckDSC(m_pNode,strErrorInfo))
		nRet = 1;

	//验证DSC下面子节点的数量和顺序名称
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
	//没有非法的子节点  不缺少子节点 验证顺序
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
		//中间Settings 可有有多个，不用验证顺序
		//最后一个是Remark
		nodeTemp1 = m_pNode->last_child();
		if(!nodeTemp1.empty())
		{
			if(CheckNode(nodeTemp1,(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_RemarkKey(),(CString)CSetFileXmlParseXmlRWKeys::CSetFilesXml_DSCKey(),strErrorInfo))
				nRet = 1;
		}
	}
	
	//验证DSC子节点的规则
		pugi::xml_node nodeTemp = m_pNode->first_child();
		while (! nodeTemp.empty())
		{
			char_t* cNodeName = (char_t*)nodeTemp.name();
			CString strNodeName(cNodeName);

		//验证是否是合法子节点，若非法，直接跳过	
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
	
		//验证当前节点是否有非法的子节点
		if(FindChildNodeName(&nodeTemp,strErrorInfo))
		{
			nRet = 1;
		}
		/*if(ChildNodeIsLack(&nodeTemp,strErrorInfo))
		{
			nRet = 1;
		}*/


		//验证子节点
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
		//属性名称有错误，不继续验证，当前节点直接返回错误
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 1)
		{
			//strErrorInfo += _T("HashInfo节点属性数量错误\r\n");
			nRet = 1;
			//return 1;
		}

		if(AttributeIsLack(pNode,strErrorInfo,strDesc))
		{
			//属性名称有缺少，不继续验证，当前节点直接返回错误
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
		//属性名称有错误，不继续验证，当前节点直接返回错误
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 4 && nAttCount != 5)
		{
			//strErrorInfo += _T("Header节点属性数量错误\r\n");
			nRet = 1;
		}

		CString strOtherAttName = "";
		if(nAttCount <= 4)
		{
			strOtherAttName = (CString)CSetFileXmlParseXmlRWKeys::DevIdKey();
		}

		if(AttributeIsLack(pNode,strErrorInfo,strDesc,strOtherAttName))
		{
			//属性名称有缺少，不继续验证，当前节点直接返回错误
			nRet = 1;
			//return nRet;
		}
		else
		{
			//属性等于4或者5 ，属性不缺少的情况 没有非法名称前提下 验证属性的顺序
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
		//属性名称有错误，不继续验证，当前节点直接返回错误
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 1)
		{
			//strErrorInfo += _T("HashInfo节点属性数量错误\r\n");
			nRet = 1;
			//return 1;
		}

		if(AttributeIsLack(pNode,strErrorInfo,strDesc))
		{
			//属性名称有缺少，不继续验证，当前节点直接返回错误
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
	//默认上召文件HI 节点大于等于 1个
	int nChildCount = pNode->child_number();
	if(pNode->child_number() < 1)
	{
		strErrorInfo += _T("节点HashInfo,子节点HI的数量小于1 \r\n");
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
		//属性名称有错误，不继续验证，当前节点直接返回错误
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 2)
		{
			//strErrorInfo += _T("HI节点属性数量错误\r\n");
			nRet = 1;
			//return 1;
		}

		if(AttributeIsLack(pNode,strErrorInfo,strDesc))
		{
			//属性名称有缺少，不继续验证，当前节点直接返回错误
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
	//默认上召文件 Update
	int nRet = 0;
	CString strDesc = "";
	if(FindAttributeName(pNode,strErrorInfo,strDesc))
	{
		//属性名称有错误，不继续验证，当前节点直接返回错误
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 1)
		{
			//strErrorInfo += _T("Update节点属性数量错误\r\n");
			nRet = 1;
			//return 1;
		}

		if(AttributeIsLack(pNode,strErrorInfo,strDesc))
		{
			//属性名称有缺少，不继续验证，当前节点直接返回错误
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
	//默认上召文件UI 节点大于等于 0个
	//下召文件至少有一个
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
		//属性名称有错误，不继续验证，当前节点直接返回错误
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 3 && nAttCount != 4)
		{
			//strErrorInfo += _T("UI节点属性数量错误\r\n");
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
			//属性名称有缺少，不继续验证，当前节点直接返回错误
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
		//属性名称有错误，不继续验证，当前节点直接返回错误
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 1)
		{
			//strErrorInfo += _T("DevInfo节点属性数量错误\r\n");
			nRet = 1;
		}
		if(AttributeIsLack(pNode,strErrorInfo,strDesc))
		{
			//属性名称有缺少，不继续验证，当前节点直接返回错误
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

	//默认文件DI 节点大于等于 1个
	int nChildCount = pNode->child_number();
	if(pNode->child_number() < 1)
	{
		strErrorInfo += _T("节点DevInfo,子节点DI的数量小于1 \r\n");
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
		//属性名称有错误，不继续验证，当前节点直接返回错误
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 1)
		{
			//strErrorInfo += _T("DI节点属性数量错误\r\n");
			nRet = 1;
			//return 1;
		}
		if(AttributeIsLack(pNode,strErrorInfo,strDesc))
		{
			//属性名称有缺少，不继续验证，当前节点直接返回错误
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
	//text的值是否需要验证  是否有

	return nRet;
	//return 0;
}

long CSetFilesXml_DSC::CheckFileInfo(pugi::xml_node *pNode,CString& strErrorInfo)
{
	int  nRet = 0;
	CString strDesc = "";
	if(FindAttributeName(pNode,strErrorInfo,strDesc))
	{
		//属性名称有错误，不继续验证，当前节点直接返回错误
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 1)
		{
			//strErrorInfo += _T("FileInfo节点属性数量错误\r\n");
			nRet = 1;
			//return 1;
		}
		if(AttributeIsLack(pNode,strErrorInfo,strDesc))
		{
			//属性名称有缺少，不继续验证，当前节点直接返回错误
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

	//默认文件FI 节点大于等于 1个
	int nChildCount = pNode->child_number();
	if(pNode->child_number() < 1)
	{
		strErrorInfo += _T("节点FileInfo,子节点FI的数量小于1 \r\n");
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
		//属性名称有错误，不继续验证，当前节点直接返回错误
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 1)
		{
			//strErrorInfo += _T("FI节点属性数量错误\r\n");
			nRet = 1;
			//return 1;
		}
		if(AttributeIsLack(pNode,strErrorInfo,strDesc))
		{
			//属性名称有缺少，不继续验证，当前节点直接返回错误
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
	//text的值是否需要验证  是否有

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
		//属性名称有错误，不继续验证，当前节点直接返回错误
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 3 && nAttCount != 4)
		{
			//strErrorInfo += _T("Settings节点属性数量错误\r\n");
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
			//属性名称有缺少，不继续验证，当前节点直接返回错误
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
	
	//默认文件InfoGrp 节点大于等于 1个
	int nChildCount = pNode->child_number();
	if(pNode->child_number() < 1)
	{
		//strErrorInfo += _T("节点Settings,[%s]InfoGrp节点数量小于1\r\n");
		strErrorInfo.AppendFormat(_T("节点Settings,[%s]下子节点InfoGrp的数量小于1 \r\n"),strDesc);
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
		//验证InfoGrp下面是否有非法的子节点
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
		//属性名称有错误，不继续验证，当前节点直接返回错误
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 4)
		{
			//strErrorInfo += _T("InfoGrp节点属性数量错误\r\n");
			nRet = 1;
			//return 1;
		}
		if(AttributeIsLack(pNode,strErrorInfo,strDesc))
		{
			//属性名称有缺少，不继续验证，当前节点直接返回错误
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
	
	//默认文件SI 节点大于等于 1个
	int nChildCount = pNode->child_number();
	if(pNode->child_number() < 1)
	{
		//strErrorInfo += _T("SI节点数量小于1\r\n");
		strErrorInfo.AppendFormat(_T("节点InfoGrp [%s],子节点SI的数量小于1 \r\n"),strDesc);
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
		//属性名称有错误，不继续验证，当前节点直接返回错误
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 6 && nAttCount != 7)
		{
			//strErrorInfo += _T("SI节点属性数量错误\r\n");
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
			//属性名称有缺少，不继续验证，当前节点直接返回错误
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
	
	//默认文件Val 节点大于等于 1个
	int nChildCount = pNode->child_number();
	if(pNode->child_number() < 1)
	{
		//strErrorInfo += _T("Val节点数量小于1\r\n");
		strErrorInfo.AppendFormat(_T("节点SI [%s],子节点Val的数量小于1 \r\n"),strDesc);
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
		//属性名称有错误，
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		//if(nAttCount != 1)
		if(nAttCount == 0)//没有grp的属性
		{ 
			//如果是单区，是可以没有grp属性，不属于错误，多区没有属于错误  没有grp属性 数量为 0
			pugi::xml_node nodeSetting =  (pNode->parent()).parent().parent();
			if(!nodeSetting.empty())
			{
				xml_attribute arrGrp = nodeSetting.attribute(L"grp");
				//Setting 没有grp 属性 默认是单区
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
						strErrorInfo += _T("Val节点属性数量错误\r\n");
						nRet = 1;
					}
					else
					{
						nRet = 0;
					}
				}
			}
			//strErrorInfo += _T("Val节点属性数量错误;");
			//nRet = 1;
			//return 1;
		}
		else if(nAttCount == 1)//有grp的属性，验证grp
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
			strErrorInfo += _T("Val节点属性数量错误,最多只有一个属性\r\n");
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
		//属性名称有错误，不继续验证，当前节点直接返回错误
		nRet = 1;
		//return nRet;
	}
	else
	{
		int nAttCount = pNode->attribute_number();
		if(nAttCount != 3 && nAttCount != 2)
		{
			//strErrorInfo = "Rslt=0;ErrorInfo=Remark节点属性数量错误;";
			//strErrorInfo += _T("Remark节点属性数量错误\r\n");
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
			//属性名称有缺少，不继续验证，当前节点直接返回错误
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

	
	//默认文件RI 节点可以没有，为0个
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

		//备注信息 RI节点 没有属性 不需要验证属性的顺序和名称
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
			//strErrorInfo.AppendFormat(_T("DSC子节点%s，顺序不对 \r\n"),strNodeName.GetString());
			strErrorInfo.AppendFormat(_T("%s的子节点%s，顺序不对 \r\n"),strParentName,strNodeName.GetString());
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
				strErrorInfo.AppendFormat(_T("节点%s [%s],[%s]属性顺序错误 \r\n"),strNodeName,strDesc,strAttName);
			}
			else
			{
			strErrorInfo.AppendFormat(_T("节点%s,[%s]属性顺序错误 \r\n"),strNodeName,strAttName);
			}
			
			nRet = 1;
		}
	}
	else
	{
		//strErrorInfo.AppendFormat(_T("缺少属性，名称 %s \r\n"),strAttText);
		nRet = 1;  //缺少属性
	}

	return nRet;
	//return 0;
}


//初始化属性名称
void CSetFilesXml_DSC::InitAttributeName()
{
	m_mapAttributeName.clear();
	//DSC属性
	list<CString> strListDSC;
	strListDSC.push_back((CString)CSetFileXmlParseXmlRWKeys::ConfigVersionKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetFilesXml_DSCKey()] = strListDSC;

	//Dsc的子节点
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


	//增加Headr的所有属性
	list<CString> strListHeader;
	strListHeader.push_back((CString)CSetFileXmlParseXmlRWKeys::DevTypeKey());
	strListHeader.push_back((CString)CSetFileXmlParseXmlRWKeys::DevIdKey());
	strListHeader.push_back((CString)CSetFileXmlParseXmlRWKeys::IedNameKey());
	strListHeader.push_back((CString)CSetFileXmlParseXmlRWKeys::UpdateTimeKey());
	strListHeader.push_back((CString)CSetFileXmlParseXmlRWKeys::Md5Key());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HeaderKey()] = strListHeader;

	//增加HashInfo和子节点HI的所有属性
	list<CString> strListHashInfo;
	strListHashInfo.push_back((CString)CSetFileXmlParseXmlRWKeys::ItemNumKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HashInfoKey()] = strListHashInfo;
	//HashInfo的子节点
	list<CString> strListHashInfoNode;
	strListHashInfoNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HIKey());
	strKey = (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HashInfoKey() + "-Child";
	m_mapAttributeName[strKey] = strListHashInfoNode;
	//HI属性
	list<CString> strListHI;
	strListHI.push_back((CString)CSetFileXmlParseXmlRWKeys::ClassKey());
	strListHI.push_back((CString)CSetFileXmlParseXmlRWKeys::Md5Key());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_HIKey()] = strListHI;
	
	//增加Update和子节点UI的所有属性
	list<CString> strListUpdate;
	strListUpdate.push_back((CString)CSetFileXmlParseXmlRWKeys::ItemNumKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_UpdateKey()] = strListUpdate;
	//Update的子节点
	list<CString> strListUpdateNode;
	strListUpdateNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_UIKey());
	strKey = (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_UpdateKey() + "-Child";
	m_mapAttributeName[strKey] = strListUpdateNode;
	//UI属性
	list<CString> strListUI;
	strListUI.push_back((CString)CSetFileXmlParseXmlRWKeys::LdKey());
	strListUI.push_back((CString)CSetFileXmlParseXmlRWKeys::ClassKey());
	strListUI.push_back((CString)CSetFileXmlParseXmlRWKeys::GrpKey());
	strListUI.push_back((CString)CSetFileXmlParseXmlRWKeys::Md5Key());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_UIKey()] = strListUI;

	//增加DevInfo和子节点DI的所有属性
	list<CString> strListDevInfo;
	strListDevInfo.push_back((CString)CSetFileXmlParseXmlRWKeys::ItemNumKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_DevInfoKey()] = strListDevInfo;
	//DevInfo的子节点
	list<CString> strListDevInfoNode;
	strListDevInfoNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_DIKey());
	strKey = (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_DevInfoKey() + "-Child";
	m_mapAttributeName[strKey] = strListDevInfoNode;
	//DI属性
	list<CString> strListDI;
	strListDI.push_back((CString)CSetFileXmlParseXmlRWKeys::DescKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_DIKey()] = strListDI;

	//增加FileInfo和子节点FI的所有属性
	list<CString> strListFileInfo;
	strListFileInfo.push_back((CString)CSetFileXmlParseXmlRWKeys::ItemNumKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_FileInfoKey()] = strListFileInfo;
	//FileInfo的子节点
	list<CString> strListFileInfoNode;
	strListFileInfoNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_FIKey());
	strKey = (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_FileInfoKey() + "-Child";
	m_mapAttributeName[strKey] = strListFileInfoNode;
	//FI属性
	list<CString> strListFI;
	strListFI.push_back((CString)CSetFileXmlParseXmlRWKeys::DescKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_FIKey()] = strListFI;

	//增加Setting和子节点InfoGrp,SI,Val的所有属性
	list<CString> strListSetting;
	strListSetting.push_back((CString)CSetFileXmlParseXmlRWKeys::LdKey());
	strListSetting.push_back((CString)CSetFileXmlParseXmlRWKeys::ClassKey());
	strListSetting.push_back((CString)CSetFileXmlParseXmlRWKeys::GrpKey());
	strListSetting.push_back((CString)CSetFileXmlParseXmlRWKeys::InfoGrpNumKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_SettingsKey()] = strListSetting;
	//Setting的子节点
	list<CString> strListSettingNode;
	strListSettingNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_InfoGrpKey());
	strKey = (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_SettingsKey() + "-Child";
	m_mapAttributeName[strKey] = strListSettingNode;
	//InfoGrp的属性
	list<CString> strListInfoGrp;
	strListInfoGrp.push_back((CString)CSetFileXmlParseXmlRWKeys::DescKey());
	strListInfoGrp.push_back((CString)CSetFileXmlParseXmlRWKeys::SetGrpNumKey());
	strListInfoGrp.push_back((CString)CSetFileXmlParseXmlRWKeys::ItemNumKey());
	strListInfoGrp.push_back((CString)CSetFileXmlParseXmlRWKeys::RemoteKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_InfoGrpKey()] = strListInfoGrp;
	//InfoGrp的子节点
	list<CString> strListInfoGrpNode;
	strListInfoGrpNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_SIKey());
	strKey = (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_InfoGrpKey() + "-Child";
	m_mapAttributeName[strKey] = strListInfoGrpNode;
	//SI的属性
	list<CString> strListSI;
	strListSI.push_back((CString)CSetFileXmlParseXmlRWKeys::DescKey());
	strListSI.push_back((CString)CSetFileXmlParseXmlRWKeys::TypeKey());
	strListSI.push_back((CString)CSetFileXmlParseXmlRWKeys::UnitKey());
	strListSI.push_back((CString)CSetFileXmlParseXmlRWKeys::MinKey());
	strListSI.push_back((CString)CSetFileXmlParseXmlRWKeys::MaxKey());
	strListSI.push_back((CString)CSetFileXmlParseXmlRWKeys::StepKey());
	strListSI.push_back((CString)CSetFileXmlParseXmlRWKeys::RefKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_SIKey()] = strListSI;
	//SI的子节点
	list<CString> strListSINode;
	strListSINode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_ValKey());
	strKey = (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_SIKey() + "-Child";
	m_mapAttributeName[strKey] = strListSINode;
	//Val的属性
	list<CString> strListVal;
	strListVal.push_back((CString)CSetFileXmlParseXmlRWKeys::GrpKey());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_ValKey()] = strListVal;

	//增加Remark和子节点RI的所有属性
	list<CString> strListRemark;
	strListRemark.push_back((CString)CSetFileXmlParseXmlRWKeys::ItemNumKey());
	strListRemark.push_back((CString)CSetFileXmlParseXmlRWKeys::UpdateKey());
	strListRemark.push_back((CString)CSetFileXmlParseXmlRWKeys::Md5Key());
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_RemarkKey()] = strListRemark;
	//Remark的子节点
	list<CString> strListRemarkNode;
	strListRemarkNode.push_back((CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_RIKey());
	strKey = (CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_RemarkKey() + "-Child";
	m_mapAttributeName[strKey] = strListRemarkNode;
	//RI的属性
	list<CString> strListRI;
	m_mapAttributeName[(CString)CSetFileXmlParseXmlRWKeys::CSetsFileXml_RIKey()] = strListRI;
}

long CSetFilesXml_DSC::FindAttributeName(pugi::xml_node *pNode,CString& strErrorInfo,CString &strDesc)
{
	int nRet = 0;
	char_t* cNodeName = (char_t*)pNode->name();
	CString strNodeName(cNodeName);
    
	///验证属性名称是否正确
	CString strErrorName = "";
	xml_attribute xmlAttTemp = pNode->first_attribute();
	while(!xmlAttTemp.empty())
	{
		//在列表中，查找不到，属于非法的属性
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
			strNodeNameText.Format(_T("节点%s,存在非法属性<"),strNodeName.GetString());
		}
		else
		{
			strNodeNameText.Format(_T("节点%s [%s],存在非法属性<"),strNodeName.GetString(),strDesc);
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

	//查找属性名称，找到就在列表中删除
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

	//列表中剩余的，就是对于当前节点 缺少的属性
	CString strErrorName = "";
	if(lstTemp.size() > 0)
	{
		CString strNodeNameText;
		if(strDesc == "")
		{
			strNodeNameText.Format(_T("节点%s,缺少属性<"),strNodeName.GetString());
		}
		else
		{
			strNodeNameText.Format(_T("节点%s [%s],缺少属性<"),strNodeName.GetString(),strDesc);
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

	///验证 子节点是否存在非法
	CString strErrorName = "";
	pugi::xml_node nodeTemp = pNode->first_child();
	while (! nodeTemp.empty())
	{
		char_t* cChildNodeName = (char_t*)nodeTemp.name();
		CString strChildNodeName(cChildNodeName);
		//没有子节点，有value的text的值，会显示有子节点
		if(strChildNodeName == "")
		{
			nodeTemp = nodeTemp.next_sibling();
			continue;
		}
		//先查找key是否存在
		map<CString,list<CString>>::iterator itmap = m_mapAttributeName.find(strKey);
		//不存在，表示当前节点，没有子节点，多出来的子节点都是非法节点
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
		strNodeNameText.Format(_T("节点%s,存在非法子对象<"),strNodeName.GetString());

		strErrorName.Delete(strErrorName.GetLength() - 1);
		strErrorName += _T(">");

		CString strError;
		strError = strNodeNameText + strErrorName;
		strErrorInfo.AppendFormat(_T("%s\r\n"), strError);
		nRet = 1;
	}
	return nRet;
}


//验证是子节点 是否缺少
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
		//CString strNodeNameText = _T("节点DSC,缺少子对象<");
		CString strNodeNameText = "";
		strNodeNameText.Format(_T("节点%s,缺少子对象<"),strNodeName.GetString());

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
//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
	//初始化属性
	m_nInfoGrpNum = 0;
	//由于装置参数和压板数据集，是单区定值。没有定义定值区号；
	//此处需要将定值区号默认为-1；
	m_nGrp = -1;

	m_pNode = NULL;
	//初始化成员变量
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
	{//只有定值才有当前运行区
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

	m_dwReserved = 1; //从模板编辑预置的值更新过来，视为被编辑
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

//形参是被编辑的对象，通过m_dwReserved标记，添加被修改的对象到this指针
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

		CSetsFileXml_InfoGrp *pNew = (CSetsFileXml_InfoGrp *)pInfoGrp->CloneEx(); //仅克隆自身
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

	//long nGrp = 1;   //定值区号
	CString strName;
 	if (m_strClass == SETTING_CLASS_SETTING)
 	{
 		strName = _T("保护定值");
 	}
 
 	if (m_strClass == SETTING_CLASS_PARAMETER)
 	{
 		strName = _T("设备参数");
 	}
 
 	if (m_strClass == SETTING_CLASS_RELAYENA)
 	{
 		strName = _T("软压板");
 	}
	
	//定值数据集，是多区定值，装置参数和功能软压板数据集，是单区定值
	//单区定值，不定义定值区号
	//但为了后续代码一致性，构造函数中，将单区定值的定值区号，默认为1
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

//将定值数据，拼接成一个大字符串返回，用于计算Md5值
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

	//去掉空格、制表符、回车符、换行符
// 	strValTotal.Replace(_T(" "), _T(""));
// 	strValTotal.Replace(_T("\t"), _T(""));
// 	strValTotal.Replace(_T("\r"), _T(""));
// 	strValTotal.Replace(_T("\n"), _T(""));
	strValTotal = RemoveOffsetChars(strValTotal);

	CString strMd5;
	GetMd5_ForCal(strMd5, strValTotal, bReCalMd5);
}

//单区定值，获取定值数据的大文本
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

	//去掉空格、制表符、回车符、换行符
// 	strValTotal.Replace(_T(" "), _T(""));
// 	strValTotal.Replace(_T("\t"), _T(""));
// 	strValTotal.Replace(_T("\r"), _T(""));
// 	strValTotal.Replace(_T("\n"), _T(""));
	strValTotal = RemoveOffsetChars(strValTotal);
}

//多区定值，获取指定定值区的定值数据的大文本
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

	//去掉空格、制表符、回车符、换行符
	// 	strValTotal.Replace(_T(" "), _T(""));
	// 	strValTotal.Replace(_T("\t"), _T(""));
	// 	strValTotal.Replace(_T("\r"), _T(""));
	// 	strValTotal.Replace(_T("\n"), _T(""));
	strValTotal = RemoveOffsetChars(strValTotal);
}

//多区定值，获取指定定值区的定值数据的大文本
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
		//不需要重复计算时，判断已经计算过，则直接返回
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

//获取定值区的数量
long CSetsFileXml_Settings::GetSetGrpNum()
{
	if (m_nGrp <= 0)
	{
		return 1;
	}

	//对于多区定值，不存在不同定值分组，定值区数量不一致的情况。因此随便取一个定值分组就行
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

//暂时只处理了定值文件多出来的定值 + 定值数值不正确
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

	//测试内容为：通过定值文件下装的方式修改装置定值，再通过MMS/CMS读定值文件，与下装定值进行比较
	//因此，以定值文件的定值分组信息段为基准，遍历this指针。
	POS pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		//存在多个定值分组信息，需要遍历
		CSetsFileXml_InfoGrp *pInfoGrp = (CSetsFileXml_InfoGrp *)GetNext(pos);
		POS pos2 = pInfoGrp->GetHeadPosition();

		while (pos2 != NULL)
		{
			CSetsFileXml_SI *pSI = (CSetsFileXml_SI *)pInfoGrp->GetNext(pos2);
			//pData = (CDvmData *)pDataset->FindByName(pSI->m_strDesc);  //通过名称映射
			CString strLd = pSI->GetLd();
			pData = FindData(pDataset, pSI->m_strDesc, pSI->m_strType, strLd, pSI->m_strRef);

			if (pData == NULL)
			{
				bRet = FALSE;
				strErrorInfo.AppendFormat(_T("CMS/MMS读取定值中缺少定值<%s>\r\n"), pSI->m_strDesc);
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
				//描述不一致，同样输出为不合格
				bRet = FALSE;

				if (nGrp <= 0)
				{
					strErrorInfo.AppendFormat(_T("定值<%s>路径不一致，CMS/MMS读取：%s，定值文件中：%s\r\n")
						, pSI->m_strDesc, pData->m_strID, strID);
				}
				else
				{
					strErrorInfo.AppendFormat(_T("<%d区>定值<%s>路径不一致，CMS/MMS读取：%s，定值文件中：%s\r\n")
						, nGrp, pSI->m_strDesc, pData->m_strID, strID); 
				}
			}
			
			if (nGrp > 0)
			{
				strSIVal = pSI->GetValByGrp_String(nGrp); //多区定值，只取指定定值区
			}
			else
			{
				strSIVal = pSI->GetVal_String();  //说明是单区定值
			}

			CString strNewValue;
			if (! IsEqualValue(strSIVal, pSI->m_strUnit, pSI->m_strStep, pData, strNewValue, pSI->m_strType)/*strSIVal != pData->m_strValue*/)
			{
				//此处要求模型文件中的值，按照步长保存。例如：step=0.01，value保留2位小数
				bRet = FALSE;

				if (nGrp <= 0)
				{
					strErrorInfo.AppendFormat(_T("定值<%s>数值不一致，CMS/MMS读取：%s，定值文件中：%s\r\n")
						, pSI->m_strDesc, strNewValue, strSIVal);
				}
				else
				{
					strErrorInfo.AppendFormat(_T("<%d区>定值<%s>数值不一致，CMS/MMS读取：%s，定值文件中：%s\r\n")
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
	//先根据ld，查找到对应的逻辑设备：LD0、PROT
	CDvmLogicDevice *pLDevice = pDvmDevice->FindByIDHas(m_strLd);

	if (pLDevice == NULL)
	{
		strErrorInfo.Format(_T("设备模型文件中没找到逻辑设备 [%s]"), m_strLd);
		return FALSE;
	}

	CExBaseList oList;
	long nCount = pLDevice->GetDatasetList(m_strClass, oList);  //获取数据集列表

	if (m_nGrp <= 0)
	{
		//单区定值
		ASSERT(nCount == 1);

		if (nCount != 1)
		{
			strErrorInfo.Format(_T("设备模型文件中找到 [%d] 个单区定值数据集 [%s]"), nCount, m_strClass);
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
		//多区定值
		long nGrpNum = GetSetGrpNum();
		ASSERT(nCount == nGrpNum);

		if (nCount != nGrpNum)
		{
			strErrorInfo.Format(_T("多区定值数据集 [%s]，定值区数量不匹配，模型文件中：[%d]个，定值文件中：[%d]个；"), m_strClass, nCount, nGrpNum);
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
		strErrorInfo.Format(_T("定值文件_上召，找不到定值分组信息 [class：%s, ld：%s]"), m_strClass, m_strLd);
		return FALSE;
	}

	long nSetNumUp = pSettings->GetSetGrpNum();
	long nSetNum = GetSetGrpNum();

	if (nSetNum != nSetNumUp)
	{
		strErrorInfo.Format(_T("定值分组信息段 [class：%s, ld：%s]，定值区数量不一致 [定值文件_上召：%d，定值文件_下装：%d]")
			, m_strClass, m_strLd, nSetNumUp, nSetNum);
		return FALSE;
	}

	if (nSetNum == 1)
	{
		//单区定值
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
		strErrorInfo.Format(_T("定值分组信息段 [class：%s, ld：%s]，定值分组数量不一致 [定值文件_上召：%d，定值文件_下装：%d]")
			, m_strClass, m_strLd, pSettings->m_nInfoGrpNum, m_nInfoGrpNum);
		return 0;
	}

	BOOL bRet = TRUE;
	CString strSIVal, strSIValUp;

	//测试内容为：通过定值文件下装的方式修改装置定值，再上召定值文件，与下装定值进行比较
	//因此，以下装定值文件的定值分组信息段为基准，遍历this指针。
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		//存在多个定值分组信息，需要遍历
		CSetsFileXml_InfoGrp *pInfoGrp = (CSetsFileXml_InfoGrp *)GetNext(pos);
		POS pos2 = pInfoGrp->GetHeadPosition();
		CSetsFileXml_InfoGrp *pInfoGrpUp = pSettings->FindInforGrpByDesc(pInfoGrp->m_strDesc);

		if (pInfoGrpUp == NULL)
		{
			strErrorInfo.AppendFormat(_T("定值文件_上召中缺少定值分组<%s>"), pInfoGrp->m_strDesc);
			bRet = FALSE;
			continue;
		}

		while (pos2 != NULL)
		{
			CSetsFileXml_SI *pSI = (CSetsFileXml_SI *)pInfoGrp->GetNext(pos2);
			CSetsFileXml_SI *pSIUp = pInfoGrpUp->FindSIByRef(pSI->m_strRef);

			if (pSIUp == NULL)
			{
				strErrorInfo.AppendFormat(_T("定值文件_上召中缺少定值项<ref：%s>   "), pSI->m_strRef);
				bRet = FALSE;
				continue;
			}

			if (nGrp > 0)
			{
				strSIVal = pSI->GetValByGrp_String(nGrp); //多区定值，只取指定定值区
				strSIValUp = pSIUp->GetValByGrp_String(nGrp); 
			}
			else
			{
				strSIVal = pSI->GetVal_String();  //说明是单区定值
				strSIValUp = pSIUp->GetVal_String(); 
			}

			if (strSIVal != strSIValUp)
			{
				//此处要求模型文件中的值，按照步长保存。例如：step=0.01，value保留2位小数
				bRet = FALSE;

				if (nGrp <= 0)
				{
					strErrorInfo.AppendFormat(_T("定值<%s>数值不一致，定值文件_上召：%s，定值文件_下装：%s；   ")
						, pSI->m_strDesc, strSIValUp, strSIVal); 
				}
				else
				{
					strErrorInfo.AppendFormat(_T("<%d区>定值<%s>数值不一致，定值文件_上召：%s，定值文件_下装：%s；   ")
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

	//2024-12-17 因发现存在以下情况：保护装置中，通过模型文件读取，跟定值文件中存在两个定值的路径弄反的情况
	//跟客户沟通后，以描述匹配为准；
	//基于上述，软件处理如下：先通过名称和数据类型查找；
	CDvmData *pFind = NULL;
	CString strName2 = strName;
	//南自的文件，描述是“保护定值：***”、“控制字：***”
	strName2.Replace(_T("保护定值："), _T(""));
	strName2.Replace(_T("控制字："), _T(""));

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

	//再通过路径查找
	//当通过名称和数据类型找不到时，再通过路径查找：时间定值，模型文件中单位为ms，数据类型为INT；定值文件中单位为s，数据类型为FLOAT32
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
//形参为SI的数据类型，返回的是模型中的数据类型
//其中，IPSTR暂时未处理
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
		return _T("UTF8_STR");//默认字符串
	}
}

CString CSetsFileXml_Settings::GetDataType(CDvmData *pData)
{
	if (m_strID == SETTING_CLASS_MATRIX
		&& pData->m_strID.Find(_T("MATR")) >= 0)
	{
		//跳闸矩阵
		return _T("HEX16");
	}

	if (pData->m_strDataType == _T("INT")
		|| pData->m_strDataType == _T("FLOAT")
		|| pData->m_strDataType == _T("UTF8_STR")
		|| pData->m_strDataType == _T("BOOL") )
	{
		return pData->m_strDataType;
	}

	CDvmValue *pFind = pData->GetDataValue();   //返回除$t  $q之外的第一个pDvmData子对象

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
		strDataType = GetDataTypeMap(strSIDataType);; //以定值文件中的数据类型为准
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
		//说明是时间定值，双边单位不一致，定值文件是s、MMS是ms
		//目前存在这种情况：模型文件中的单位为空，因此屏蔽判strUnit2
		double fSIVal = CString_To_double(strSIVal);
		long nValue1 = (fSIVal * 1000);
		long nValue2 = CString_To_long(pData->m_strValue);

		return (nValue2 == nValue1);
	}

	if (strDataType == _T("HEX16"))
	{
		//HEX16是0x0000~0xFFFF。
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
		//HEX32是0x00000000~0xFFFFFFFF
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
		//某些装置，CT二次额定值，min=1，step=4，max=5
		//但是数据类型是FLOAT。定值文件中的值是1或5，没有小数点
		nXS = 0;  
	}
	strFormat.Format(_T("%%.%df"), nXS);

	double fCurrValTemp = atof(strValue);
	CString strNewTextTemp = "";
	strNewValue.Format(strFormat, fCurrValTemp);
	return strNewValue;
}
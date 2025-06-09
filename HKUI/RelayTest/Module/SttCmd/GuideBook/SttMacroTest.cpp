//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMacroTest.cpp  CSttMacroTest


#include "stdafx.h"
#include "SttMacroTest.h"
#include "SttMacroCharItems.h"
#include "../../../../AutoTest/Module/AutoTestGlobalDefine.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSttMacroTestParaData::CSttMacroTestParaData()
{
	m_strValue = _T("");
}	

CSttMacroTestParaData::~CSttMacroTestParaData()
{

}

long CSttMacroTestParaData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetCDATA(oNode,m_strValue,pXmlKeys->m_strMacroIDKey);
	return 0;
}

long CSttMacroTestParaData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetCDATA(oXMLDoc,oElement,m_strValue,pXmlKeys->m_strTestModeKey);

	return 0;
}

void CSttMacroTestParaData::InitAfterRead()
{

}	

//缓冲区串行化
long CSttMacroTestParaData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strValue);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
	}

	return 0;
}

BSTR CSttMacroTestParaData::GetXmlElementKey()
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = CSttCmdDefineXmlRWKeys::g_pXmlKeys;
	return pXmlKeys->m_strParaKey;
}

CExBaseObject* CSttMacroTestParaData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return NULL;
}

CExBaseObject* CSttMacroTestParaData::CreateNewChild(long nClassID)
{
	return NULL;
}

BOOL CSttMacroTestParaData::IsEqual(CBaseObject* pObj)
{
	if (!CExBaseObject::IsEqual(pObj))
	{
		return FALSE;
	}

	CSttMacroTestParaData *p = (CSttMacroTestParaData*)pObj;

	if (p->m_strValue != m_strValue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttMacroTestParaData::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDesObj);
	CSttMacroTestParaData* pMacroTestPara = (CSttMacroTestParaData*)pDesObj;
	pMacroTestPara->m_strValue = m_strValue;

	return TRUE;
}

CBaseObject* CSttMacroTestParaData::Clone()
{
	CSttMacroTestParaData* pMacroTestPara = new CSttMacroTestParaData();
	Copy(pMacroTestPara);

	return pMacroTestPara;
}	
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSttMacroTestParaDatas::CSttMacroTestParaDatas()
{
}

CSttMacroTestParaDatas::~CSttMacroTestParaDatas()
{

}

long CSttMacroTestParaDatas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttMacroTestParaDatas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CSttMacroTestParaDatas::InitAfterRead()
{

}	

//缓冲区串行化
long CSttMacroTestParaDatas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if (oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if (oBinaryBuffer.IsReadMode())
	{
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
	}

	return 0;
}

BSTR CSttMacroTestParaDatas::GetXmlElementKey()
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = CSttCmdDefineXmlRWKeys::g_pXmlKeys;
	return pXmlKeys->m_strFParasKey;
}

CExBaseObject* CSttMacroTestParaDatas::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew = NULL;
	CSttCmdDefineXmlRWKeys *pDefXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pDefXmlKeys->m_strParaKey)
	{
		pNew = new CSttMacroTestParaData();
	}

	return pNew;
}

CExBaseObject* CSttMacroTestParaDatas::CreateNewChild(long nClassID)
{
	CExBaseObject *pNew = NULL;

	if (nClassID == STTGBXMLCLASSID_CSTTMACROPARADATA)
	{
		pNew = new CSttMacroTestParaData();
	}

	return pNew;
}

BOOL CSttMacroTestParaDatas::IsEqual(CBaseObject* pObj)
{
	return FALSE;
}
	
BOOL CSttMacroTestParaDatas::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
	{
		return TRUE;
	}

	CSttMacroTestParaDatas* pMacroTestPara = (CSttMacroTestParaDatas*)pDesObj;

	return TRUE;
}

CBaseObject* CSttMacroTestParaDatas::Clone()
{
	CSttMacroTestParaDatas* pMacroTestPara = new CSttMacroTestParaDatas();
	Copy(pMacroTestPara);

	return pMacroTestPara;
}

BOOL CSttMacroTestParaDatas::CopyChildren(CBaseObject* pDest)
{
	CSttMacroTestParaDatas *pDestList = (CSttMacroTestParaDatas*)pDest;
	CSttMacroTestParaData *pSrcObj = NULL;
	CSttMacroTestParaData *pDstObj = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pSrcObj = (CSttMacroTestParaData*)GetNext(pos);
		pDstObj = (CSttMacroTestParaData*)pDestList->FindByID(pSrcObj->m_strID);

		if (pDstObj != NULL)
		{
			pDstObj->m_strValue = pSrcObj->m_strValue;
		} 
		else
		{
			pDstObj = new CSttMacroTestParaData;
			pSrcObj->Copy(pDstObj);
			pDestList->AddNewChild(pDstObj);
		}
	}

	return TRUE;
}
	
BOOL CSttMacroTestParaDatas::SetDataValue(const CString &strID,const CString &strValue,BOOL bCreate)
{
	CSttMacroTestParaData *pSttMacroTestParaData = (CSttMacroTestParaData*)FindByID(strID);

	if (pSttMacroTestParaData == NULL)
	{
		if (bCreate)
		{
			pSttMacroTestParaData = new CSttMacroTestParaData;
			pSttMacroTestParaData->m_strID = strID;
			AddNewChild(pSttMacroTestParaData);
		}
		else
		{
			return FALSE;
		}
	}

	pSttMacroTestParaData->m_strValue = strValue;
	return TRUE;
}

CSttMacroTestParaData* CSttMacroTestParaDatas::AddData(const CString &strName, const CString &strID, const CString &strValue)
{
	CSttMacroTestParaData *pSttMacroTestParaData = (CSttMacroTestParaData*)FindByID(strID);

	if (pSttMacroTestParaData == NULL)
	{
		pSttMacroTestParaData = new CSttMacroTestParaData();
		AddNewChild(pSttMacroTestParaData);
		pSttMacroTestParaData->m_strName = strName;
		pSttMacroTestParaData->m_strID = strID;
	}

	pSttMacroTestParaData->m_strValue = strValue;

	return pSttMacroTestParaData;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSttMacroTestPara::CSttMacroTestPara()
{
	m_strMacroID = _T("");
	m_strTestMode = _T("auto-test");
	m_pParaDatas = NULL;
}

CSttMacroTestPara::~CSttMacroTestPara()
{
	
}

long CSttMacroTestPara::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMacroIDKey,oNode,m_strMacroID);
	xml_GetAttibuteValue(pXmlKeys->m_strTestModeKey,oNode,m_strTestMode);

	return 0;
}

long CSttMacroTestPara::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMacroIDKey,oElement,m_strMacroID);
	xml_SetAttributeValue(pXmlKeys->m_strTestModeKey,oElement,m_strTestMode);

	return 0;
}

void CSttMacroTestPara::InitAfterRead()
{
	if (m_pParaDatas == NULL)
	{
		m_pParaDatas = (CSttMacroTestParaDatas*)FindByClassID(STTGBXMLCLASSID_CSTTMACROPARADATAS);
	}
}

//缓冲区串行化
long CSttMacroTestPara::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMacroID);
		BinarySerializeCalLen(oBinaryBuffer, m_strTestMode);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMacroID);
		BinarySerializeRead(oBinaryBuffer, m_strTestMode);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMacroID);
		BinarySerializeWrite(oBinaryBuffer, m_strTestMode);
	}

	return 0;
}

BSTR CSttMacroTestPara::GetXmlElementKey()
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = CSttCmdDefineXmlRWKeys::g_pXmlKeys;
	return pXmlKeys->m_strParaKey;
}

CExBaseObject* CSttMacroTestPara::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew = NULL;
	CSttCmdDefineXmlRWKeys *pDefXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pDefXmlKeys->m_strFParasKey)
	{
		pNew = new CSttMacroTestParaDatas();
		m_pParaDatas = (CSttMacroTestParaDatas*)pNew;
	}

	return pNew;
}

CExBaseObject* CSttMacroTestPara::CreateNewChild(long nClassID)
{
	CExBaseObject *pNew = NULL;

	if (nClassID == STTGBXMLCLASSID_CSTTMACROPARADATAS)
	{
		pNew = new CSttMacroTestParaDatas();
		m_pParaDatas = (CSttMacroTestParaDatas*)pNew;
	}

	return pNew;
}

CSttMacroTestParaDatas* CSttMacroTestPara::GetSttMacroTestParaDatas(BOOL bCreate)
{
	if (m_pParaDatas == NULL)
	{
		m_pParaDatas = (CSttMacroTestParaDatas*)FindByClassID(STTGBXMLCLASSID_CSTTMACROPARADATAS);

		if (m_pParaDatas == NULL)
		{
			if (bCreate)
			{
				m_pParaDatas = (CSttMacroTestParaDatas*)CreateNewChild(STTGBXMLCLASSID_CSTTMACROPARADATAS);
				AddNewChild(m_pParaDatas);
			}
			else
			{
				return NULL;
			}
		}
	}

	return m_pParaDatas;
}

CSttMacroTestParaData* CSttMacroTestPara::FindMacroTestParaDataByID(const CString &strID)
{
	if (m_pParaDatas == NULL)
	{
		m_pParaDatas = (CSttMacroTestParaDatas*)FindByClassID(STTGBXMLCLASSID_CSTTMACROPARADATAS);
	}

	if (m_pParaDatas == NULL)
	{
		return NULL;
	}

	return (CSttMacroTestParaData*)m_pParaDatas->FindByID(strID);
}

BOOL CSttMacroTestPara::IsEqual(CBaseObject* pObj)
{
	return FALSE;
}

BOOL CSttMacroTestPara::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
	{
		return TRUE;
	}

	CSttMacroTestPara* pMacroTestPara = (CSttMacroTestPara*)pDesObj;
	pMacroTestPara->m_strMacroID = m_strMacroID;
	pMacroTestPara->m_strTestMode = m_strTestMode;

	return TRUE;
}

CBaseObject* CSttMacroTestPara::Clone()
{
	CSttMacroTestPara* pMacroTestPara = new CSttMacroTestPara();
	Copy(pMacroTestPara);

	return pMacroTestPara;
}

/////////////////////////////////////////////////////////////////////////////////////////
CSttMacroTest::CSttMacroTest()
{
	//初始化属性
	m_nRepeatTimes = 0;
	m_nReportFillUseNoRepeat = 0;
	m_pPara = NULL;
	m_nModified = 0;

	//初始化成员变量
}

CSttMacroTest::~CSttMacroTest()
{
}

BSTR CSttMacroTest::GetXmlElementKey()
{
	if (CSttCmdDefineXmlRWKeys::stt_Is_GuideBookUseItemKey(NULL))
	{
		return CSttCmdDefineXmlRWKeys::CSttItemBaseKey();
	}
	else
	{
		return CSttCmdDefineXmlRWKeys::CSttMacroTestKey(); 
	}
}

long CSttMacroTest::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttItemBase::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strRepeatTimesKey, oNode, m_nRepeatTimes);
	xml_GetAttibuteValue(pXmlKeys->m_strCalModeKey, oNode, m_strReportMode);
	xml_GetAttibuteValue(pXmlKeys->m_strReportFillUseNoRepeatKey, oNode, m_nReportFillUseNoRepeat);
	xml_GetAttibuteValue(pXmlKeys->m_strMacroIDKey, oNode, m_strMacroID);

	return 0;
}

long CSttMacroTest::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttItemBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

//shaolei 2023-2-27  注释此处，保留所有属性
// 	if (CSttCmdDefineXmlRWKeys::IsOnlyGetItem())
// 	{
// 		return 0;
// 	}

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strRepeatTimesKey, oElement, m_nRepeatTimes);
	xml_SetAttributeValue(pXmlKeys->m_strCalModeKey, oElement, m_strReportMode);
	xml_SetAttributeValue(pXmlKeys->m_strReportFillUseNoRepeatKey, oElement, m_nReportFillUseNoRepeat);
	xml_SetAttributeValue(pXmlKeys->m_strMacroIDKey, oElement, m_strMacroID);
	return 0;
}

long CSttMacroTest::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (CSttCmdDefineXmlRWKeys::IsOnlyGetItem())
		{
			//只获取项目目录的情况下，不需要测试功能参数
			//2023-2-27  shaolei
			if (nClassID == STTGBXMLCLASSID_CSTTTESTMACROUIPARAS)
			{
				continue;
			}
		}

		pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}

	return 0;
}

long CSttMacroTest::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttItemBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_nRepeatTimes);
		BinarySerializeCalLen(oBinaryBuffer, m_strReportMode);
		BinarySerializeCalLen(oBinaryBuffer, m_nReportFillUseNoRepeat);
		BinarySerializeCalLen(oBinaryBuffer, m_strMacroID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_nRepeatTimes);
		BinarySerializeRead(oBinaryBuffer, m_strReportMode);
		BinarySerializeRead(oBinaryBuffer, m_nReportFillUseNoRepeat);
		BinarySerializeRead(oBinaryBuffer, m_strMacroID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_nRepeatTimes);
		BinarySerializeWrite(oBinaryBuffer, m_strReportMode);
		BinarySerializeWrite(oBinaryBuffer, m_nReportFillUseNoRepeat);
		BinarySerializeWrite(oBinaryBuffer, m_strMacroID);
	}
	return 0;
}

void CSttMacroTest::InitAfterRead()
{
	if (m_strMacroID.IsEmpty())
	{
		m_strMacroID = GetTestMacroID();
	}

	if (m_pPara == NULL)
	{
		m_pPara = (CSttMacroTestPara*)FindByClassID(STTGBXMLCLASSID_CSTTMACROPARA);
	}

	CSttItemBase::InitAfterRead();
}

BOOL CSttMacroTest::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttItemBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttMacroTest *p = (CSttMacroTest*)pObj;

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	if(m_nRepeatTimes != p->m_nRepeatTimes)
	{
		return FALSE;
	}

	if(m_strReportMode != p->m_strReportMode)
	{
		return FALSE;
	}

	if(m_nReportFillUseNoRepeat != p->m_nReportFillUseNoRepeat)
	{
		return FALSE;
	}

	if(m_strMacroID != p->m_strMacroID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttMacroTest::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttItemBase::CopyOwn(pDest);

	CSttMacroTest *p = (CSttMacroTest*)pDest;

	p->m_strType = m_strType;
	p->m_nRepeatTimes = m_nRepeatTimes;
	p->m_strReportMode = m_strReportMode;
	p->m_nReportFillUseNoRepeat = m_nReportFillUseNoRepeat;
	p->m_strMacroID = m_strMacroID;

	return TRUE;
}

CBaseObject* CSttMacroTest::Clone()
{
	CSttMacroTest *p = new CSttMacroTest();
	Copy(p);
	return p;
}

CBaseObject* CSttMacroTest::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttMacroTest *p = new CSttMacroTest();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttMacroTest::CanPaste(UINT nClassID)
{
	if (nClassID == STTGBXMLCLASSID_CSTTCOMMCMD)
	{
		return TRUE;
	}

	if (nClassID == STTGBXMLCLASSID_CSTTSAFETY)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttMacroTest::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttCommCmdKey)
	{
		pNew = new CSttCommCmd();
	}
	else if (strClassID == pXmlKeys->m_strCSttSafetyKey)
	{
		pNew = new CSttSafety();
	}
	else if (strClassID == pXmlKeys->m_strTestMacroUiParasKey)
	{
		pNew = new CSttTestMacroUiParas();
	}
	else if (strClassID == pXmlKeys->m_strParaKey)
	{
		pNew = new CSttMacroTestPara();
		m_pPara = (CSttMacroTestPara*)pNew;
	}
	else
	{
		return CSttItemBase::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
	}

	return pNew;
}

CExBaseObject* CSttMacroTest::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == STTGBXMLCLASSID_CSTTCOMMCMD)
	{
		pNew = new CSttCommCmd();
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTSAFETY)
	{
		pNew = new CSttSafety();
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTTESTMACROUIPARAS)
	{
		pNew = new CSttTestMacroUiParas();
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTMACROPARA)
	{
		pNew = new CSttMacroTestPara();
		m_pPara = (CSttMacroTestPara*)pNew;
	}
	else
	{
		return CSttItemBase::CreateNewChild(nClassID);
	}

	return pNew;
}

CString CSttMacroTest::GetTestMacroID()
{
	if (m_pPara == NULL)
	{
		return m_strMacroID;
	}

	CString strMacroID;
	strMacroID = m_pPara->GetMacroID();

	if (strMacroID.IsEmpty() && (!m_strMacroID.IsEmpty()))
	{
		strMacroID = m_strMacroID;
	}

	return strMacroID;
}

CSttMacroTestPara* CSttMacroTest::GetSttMacroTestPara(BOOL bCreate)
{
	if (bCreate && m_pPara == NULL)
	{
		m_pPara = new CSttMacroTestPara();
		AddNewChild(m_pPara);
		m_pPara->InitAfterRead();
	}

	return m_pPara;
}

CSttMacroTestPara* CSttMacroTest::GetAddMacroTestPara(const CString &strMacroID)
{
	if (m_pPara != NULL)
	{
		return m_pPara;
	}

	m_pPara = new CSttMacroTestPara;
	AddNewChild(m_pPara);
	m_pPara->SetMacroID(strMacroID);
	m_pPara->SetTestMode("auto-test");
	return m_pPara;
}

CSttMacroTestParaDatas* CSttMacroTest::GetSttMacroTestParaDatas(BOOL bCreate ,const CString &strMacroID)
{
	if (m_pPara == NULL)
	{
		m_pPara = (CSttMacroTestPara*)FindByClassID(STTGBXMLCLASSID_CSTTMACROPARA);

		if (m_pPara == NULL)
		{
			if (bCreate &&(!strMacroID.IsEmpty()))
			{
				m_strMacroID = strMacroID;
				m_pPara = (CSttMacroTestPara*)CreateNewChild(STTGBXMLCLASSID_CSTTMACROPARA);
				m_pPara->SetMacroID(strMacroID);
				m_pPara->SetTestMode("auto-test");
				AddNewChild(m_pPara);
			}
			else
			{
				return NULL;
			}
		}
	}

	return m_pPara->GetSttMacroTestParaDatas(bCreate);
}

BOOL CSttMacroTest::UpdateItemState_ByLastRptRsltJdg()
{
	CSttReports *pSttReports = GetSttReports();

	if (pSttReports == NULL)
	{
		return FALSE;
	}

	CSttReport *pReport = (CSttReport*)pSttReports->GetTail();

	if (pReport == NULL)
	{
		return FALSE;
	}

	if (pReport->m_pValues == NULL)
	{
		return FALSE;
	}

	long nValue = 1;

	if (!pReport->m_pValues->GetValue("RsltJdg",nValue))
	{
		return FALSE;
	} 

	if (nValue>0)
	{
		m_nState = TEST_STATE_ELIGIBLE;
	} 
	else
	{
		m_nState = TEST_STATE_INLEGIBLE;
	}

	return TRUE;
}

CDvmValues* CSttMacroTest::GetLastRptDvmValues()
{
	CSttReports *pSttReports = GetSttReports();

	if (pSttReports == NULL)
	{
		return NULL;
	}

	CSttReport *pReport = (CSttReport*)pSttReports->GetTail();

	if (pReport == NULL)
	{
		return NULL;
	}

	return pReport->m_pValues;
}

CSttTestMacroUiParas* CSttMacroTest::GetSttTestMacroUiParas(BOOL bCreate)
{
	CSttTestMacroUiParas* pUIParas = (CSttTestMacroUiParas *)FindByClassID(STTGBXMLCLASSID_CSTTTESTMACROUIPARAS);

	if (pUIParas == NULL)
	{
		if (bCreate)
		{
			pUIParas = new CSttTestMacroUiParas();
			AddNewChild(pUIParas);
		}
	}

	return pUIParas;
}

long CSttMacroTest::GetItemTestCount()
{
	CSttItemBase *pParent = (CSttItemBase *)GetParent();

	return m_nRepeatTimes * pParent->GetItemTestCount();
}
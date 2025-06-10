//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMacroTest.cpp  CSttMacroTest


#include "stdafx.h"
#include "SttMacroTest.h"
#include "SttMacroCharItems.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////////////////////
CSttMacroTestPara::CSttMacroTestPara()
{
	m_strMacroID = _T("");
	m_strTestMode = _T("auto-test");
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
	return NULL;
}

CExBaseObject* CSttMacroTestPara::CreateNewChild(long nClassID)
{
	return NULL;
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
		return _T("");
	}

	return m_pPara->GetMacroID();
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
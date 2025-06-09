//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMacroTest.cpp  CSttMacroTest


#include "stdafx.h"
#include "SttMacroTest.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXSttMacroTest::CXSttMacroTest()
{
	//初始化属性
	m_nRepeatTimes = 0;
	m_nReportFillUseNoRepeat = 0;

	//初始化成员变量
}

CXSttMacroTest::~CXSttMacroTest()
{
}

long CXSttMacroTest::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttItemBase::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strRepeatTimesKey, oNode, m_nRepeatTimes);
	xml_GetAttibuteValue(pXmlKeys->m_strCalModeKey, oNode, m_strReportMode);
	xml_GetAttibuteValue(pXmlKeys->m_strReportFillUseNoRepeatKey, oNode, m_nReportFillUseNoRepeat);
	return 0;
}

long CXSttMacroTest::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttItemBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strRepeatTimesKey, oElement, m_nRepeatTimes);
	xml_SetAttributeValue(pXmlKeys->m_strCalModeKey, oElement, m_strReportMode);
	xml_SetAttributeValue(pXmlKeys->m_strReportFillUseNoRepeatKey, oElement, m_nReportFillUseNoRepeat);
	return 0;
}

long CXSttMacroTest::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttItemBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_nRepeatTimes);
		BinarySerializeCalLen(oBinaryBuffer, m_strReportMode);
		BinarySerializeCalLen(oBinaryBuffer, m_nReportFillUseNoRepeat);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_nRepeatTimes);
		BinarySerializeRead(oBinaryBuffer, m_strReportMode);
		BinarySerializeRead(oBinaryBuffer, m_nReportFillUseNoRepeat);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_nRepeatTimes);
		BinarySerializeWrite(oBinaryBuffer, m_strReportMode);
		BinarySerializeWrite(oBinaryBuffer, m_nReportFillUseNoRepeat);
	}
	return 0;
}

void CXSttMacroTest::InitAfterRead()
{
}

BOOL CXSttMacroTest::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttItemBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXSttMacroTest *p = (CXSttMacroTest*)pObj;

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

	return TRUE;
}

BOOL CXSttMacroTest::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttItemBase::CopyOwn(pDest);

	CXSttMacroTest *p = (CXSttMacroTest*)pDest;

	p->m_strType = m_strType;
	p->m_nRepeatTimes = m_nRepeatTimes;
	p->m_strReportMode = m_strReportMode;
	p->m_nReportFillUseNoRepeat = m_nReportFillUseNoRepeat;
	return TRUE;
}

CBaseObject* CXSttMacroTest::Clone()
{
	CXSttMacroTest *p = new CXSttMacroTest();
	Copy(p);
	return p;
}

CBaseObject* CXSttMacroTest::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CXSttMacroTest *p = new CXSttMacroTest();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CXSttMacroTest::CanPaste(UINT nClassID)
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

CExBaseObject* CXSttMacroTest::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
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
	else
	{
		return CSttItemBase::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
	}

	return pNew;
}

CExBaseObject* CXSttMacroTest::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
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
	else
	{
		return CSttItemBase::CreateNewChild(nClassID);
	}

	return pNew;
}

//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttSysParas.cpp  CSttSysParas


#include "stdafx.h"
#include "SttSysParas.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttSysParas::CSttSysParas()
{
	//初始化属性

	//初始化成员变量
}

CSttSysParas::~CSttSysParas()
{
}

long CSttSysParas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDvmDataset::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strRWAttrKey, oNode, m_strRWAttr);
	return 0;
}

long CSttSysParas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDvmDataset::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strRWAttrKey, oElement, m_strRWAttr);
	return 0;
}

long CSttSysParas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDvmDataset::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_strRWAttr);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_strRWAttr);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_strRWAttr);
	}
	return 0;
}

void CSttSysParas::InitAfterRead()
{
}

BOOL CSttSysParas::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDvmDataset::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttSysParas *p = (CSttSysParas*)pObj;

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	if(m_strRWAttr != p->m_strRWAttr)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttSysParas::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDvmDataset::CopyOwn(pDest);

	CSttSysParas *p = (CSttSysParas*)pDest;

	p->m_strType = m_strType;
	p->m_strRWAttr = m_strRWAttr;
	return TRUE;
}

CBaseObject* CSttSysParas::Clone()
{
	CSttSysParas *p = new CSttSysParas();
	Copy(p);
	return p;
}

CBaseObject* CSttSysParas::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttSysParas *p = new CSttSysParas();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttSysParas::CanPaste(UINT nClassID)
{
	return CDvmDataset::CanPaste(nClassID);
// 	if (nClassID == STTGBXMLCLASSID_CSTTDATAOBJ)
// 	{
// 		return TRUE;
// 	}
// 
// 	return FALSE;
}

CExBaseObject* CSttSysParas::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return CDvmDataset::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
// 	CExBaseObject *pNew  = NULL;
// 	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;
// 
// 
// 	if (strClassID == pXmlKeys->m_strCSttDataObjKey)
// 	{
// 		pNew = new CSttDataObj();
// 	}
// 
// 	return pNew;
}

CExBaseObject* CSttSysParas::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	return CDvmDataset::CreateNewChild(nClassID);
// 	CExBaseObject *pNew  = NULL;
// 
// 
// 	if (nClassID == STTGBXMLCLASSID_CSTTDATAOBJ)
// 	{
// 		pNew = new CSttDataObj();
// 	}
// 
// 	return pNew;
}

//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttSysParaEdit.cpp  CSttSysParaEdit


#include "stdafx.h"
#include "SttSysParaEdit.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttSysParaEdit::CSttSysParaEdit()
{
	//初始化属性

	//初始化成员变量
}

CSttSysParaEdit::~CSttSysParaEdit()
{
}

BSTR CSttSysParaEdit::GetXmlElementKey() 
{ 
	if (CSttCmdDefineXmlRWKeys::stt_Is_GuideBookUseItemKey(NULL))
	{
		return CSttCmdDefineXmlRWKeys::CSttItemBaseKey();
	}
	else
	{
		return CSttCmdDefineXmlRWKeys::CSttSysParaEditKey();
	}
}

long CSttSysParaEdit::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttItemBase::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strDatasetPath);
	return 0;
}

long CSttSysParaEdit::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttItemBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strDatasetPath);
	return 0;
}

long CSttSysParaEdit::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttItemBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
        BinarySerializeCalLen(oBinaryBuffer, m_strDatasetPath);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
        BinarySerializeRead(oBinaryBuffer, m_strDatasetPath);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
        BinarySerializeWrite(oBinaryBuffer, m_strDatasetPath);
	}
	return 0;
}

void CSttSysParaEdit::InitAfterRead()
{
	CSttItemBase::InitAfterRead();
}

BOOL CSttSysParaEdit::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttItemBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttSysParaEdit *p = (CSttSysParaEdit*)pObj;

    if(m_strDatasetPath != p->m_strDatasetPath)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttSysParaEdit::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttItemBase::CopyOwn(pDest);

	CSttSysParaEdit *p = (CSttSysParaEdit*)pDest;

    p->m_strDatasetPath = m_strDatasetPath;
	return TRUE;
}

CBaseObject* CSttSysParaEdit::Clone()
{
	CSttSysParaEdit *p = new CSttSysParaEdit();
	Copy(p);
	return p;
}

CBaseObject* CSttSysParaEdit::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttSysParaEdit *p = new CSttSysParaEdit();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttSysParaEdit::CanPaste(UINT nClassID)
{
	if (nClassID == STTGBXMLCLASSID_CSTTCOMMCMD)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttSysParaEdit::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttCommCmdKey)
	{
		pNew = new CSttCommCmd();
	}
	else
	{
		return CSttItemBase::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
	}

	return pNew;
}

CExBaseObject* CSttSysParaEdit::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == STTGBXMLCLASSID_CSTTCOMMCMD)
	{
		pNew = new CSttCommCmd();
	}
	else
	{
		return CSttItemBase::CreateNewChild(nClassID);
	}

	return pNew;
}

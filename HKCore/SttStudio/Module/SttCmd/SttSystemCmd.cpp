//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttSystemCmd.cpp  CSttSystemCmd


#include "stdafx.h"
#include "SttSystemCmd.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttSystemCmd::CSttSystemCmd()
{
	//��ʼ������

	//��ʼ����Ա����
	m_strTestor = g_strIDSoft;
}

CSttSystemCmd::~CSttSystemCmd()
{
}

long CSttSystemCmd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdBase::XmlReadOwn(oNode, pXmlRWKeys);
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTestorKey, oNode, m_strTestor);
	return 0;
}

long CSttSystemCmd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTestorKey, oElement, m_strTestor);
	return 0;
}

long CSttSystemCmd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttCmdBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strTestor);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strTestor);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strTestor);
	}
	return 0;
}

BOOL CSttSystemCmd::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttCmdBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttSystemCmd *p = (CSttSystemCmd*)pObj;

	if(m_strTestor != p->m_strTestor)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttSystemCmd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttCmdBase::CopyOwn(pDest);

	CSttSystemCmd *p = (CSttSystemCmd*)pDest;

	p->m_strTestor = m_strTestor;
	return TRUE;
}

CBaseObject* CSttSystemCmd::Clone()
{
	CSttSystemCmd *p = new CSttSystemCmd();
	Copy(p);
	return p;
}

CBaseObject* CSttSystemCmd::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttSystemCmd *p = new CSttSystemCmd();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttSystemCmd::CanPaste(UINT nClassID)
{
	return FALSE;
}


//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecGenCfgChildKey.cpp  CIecGenCfgChildKey


#include "stdafx.h"
#include "IecGenCfgChildKey.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecGenCfgChildKey::CIecGenCfgChildKey()
{
	//��ʼ������

	//��ʼ����Ա����
}

CIecGenCfgChildKey::~CIecGenCfgChildKey()
{
}

long CIecGenCfgChildKey::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strLogicKey, oNode, m_strLogic);
	return 0;
}

long CIecGenCfgChildKey::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strLogicKey, oElement, m_strLogic);
	return 0;
}

long CIecGenCfgChildKey::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strLogic);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strLogic);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strLogic);
	}
	return 0;
}

void CIecGenCfgChildKey::InitAfterRead()
{
}

BOOL CIecGenCfgChildKey::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecGenCfgChildKey *p = (CIecGenCfgChildKey*)pObj;

	if(m_strLogic != p->m_strLogic)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecGenCfgChildKey::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIecGenCfgChildKey *p = (CIecGenCfgChildKey*)pDest;

	p->m_strLogic = m_strLogic;
	return TRUE;
}

CBaseObject* CIecGenCfgChildKey::Clone()
{
	CIecGenCfgChildKey *p = new CIecGenCfgChildKey();
	Copy(p);
	return p;
}

CBaseObject* CIecGenCfgChildKey::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecGenCfgChildKey *p = new CIecGenCfgChildKey();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIecGenCfgChildKey::IsMatchSuccess(const CString &strName)
{
	CIecGenCfgChildKey *pChildKey = NULL;

	if (m_strLogic == _T("NOT"))//����Ƿ��߼� 
	{
		if (strName.Find(m_strName) >=0)//�ַ����а������ӹؼ�����ƥ��ʧ��
		{
			return FALSE;
		}

		return TRUE;//����ƥ��ɹ�
	}
	else if (strName.Find(m_strName) == -1)//����������߼�,��Ϊ���߼�
	{
		return FALSE;//����ʧ�ܼ�ƥ��ʧ��
	}

	return TRUE;
}


//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Iot_Engine_Dirs.cpp  CIot_Engine_Dirs


#include "stdafx.h"
#include "Iot_Engine_Dirs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Engine_Dirs::CIot_Engine_Dirs()
{
	//��ʼ������

	//��ʼ����Ա����
}

CIot_Engine_Dirs::~CIot_Engine_Dirs()
{
}

long CIot_Engine_Dirs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Engine_Dirs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_Engine_Dirs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CIot_Engine_Dirs::InitAfterRead()
{
}

BOOL CIot_Engine_Dirs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Engine_Dirs *p = (CIot_Engine_Dirs*)pObj;

	return TRUE;
}

BOOL CIot_Engine_Dirs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Engine_Dirs *p = (CIot_Engine_Dirs*)pDest;

	return TRUE;
}

CBaseObject* CIot_Engine_Dirs::Clone()
{
	CIot_Engine_Dirs *p = new CIot_Engine_Dirs();
	Copy(p);
	return p;
}

CBaseObject* CIot_Engine_Dirs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Engine_Dirs *p = new CIot_Engine_Dirs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_Engine_Dirs::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_ENGINE_DIR)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_Engine_Dirs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_Engine_DirKey)
	{
		pNew = new CIot_Engine_Dir();
	}

	return pNew;
}

CExBaseObject* CIot_Engine_Dirs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_ENGINE_DIR)
	{
		pNew = new CIot_Engine_Dir();
	}

	return pNew;
}
CExBaseObject* CIot_Engine_Dirs::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_Engine_Dir();

	return pNew;
}

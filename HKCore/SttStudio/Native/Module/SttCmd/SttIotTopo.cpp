//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttIotTopo.cpp  CSttIotTopo


#include "stdafx.h"
#include "SttIotTopo.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttIotTopo::CSttIotTopo()
{
	//��ʼ������

	//��ʼ����Ա����
}

CSttIotTopo::~CSttIotTopo()
{
}

long CSttIotTopo::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttIotTopo::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttIotTopo::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttIotTopo::InitAfterRead()
{
}

BOOL CSttIotTopo::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttIotTopo *p = (CSttIotTopo*)pObj;

	return TRUE;
}

BOOL CSttIotTopo::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttIotTopo *p = (CSttIotTopo*)pDest;

	return TRUE;
}

CBaseObject* CSttIotTopo::Clone()
{
	CSttIotTopo *p = new CSttIotTopo();
	Copy(p);
	return p;
}

CBaseObject* CSttIotTopo::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttIotTopo *p = new CSttIotTopo();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttIotTopo::CanPaste(UINT nClassID)
{
	if (nClassID == STTCMDCLASSID_CSTTIOTNODE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttIotTopo::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttIotNodeKey)
	{
		pNew = new CSttIotNode();
	}

	return pNew;
}

CExBaseObject* CSttIotTopo::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == STTCMDCLASSID_CSTTIOTNODE)
	{
		pNew = new CSttIotNode();
	}

	return pNew;
}

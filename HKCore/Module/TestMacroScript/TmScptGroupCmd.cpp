//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TmScptGroupCmd.cpp  CTmScptGroupCmd


#include "stdafx.h"
#include "TmScptGroupCmd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTmScptGroupCmd::CTmScptGroupCmd()
{
	//��ʼ������

	//��ʼ����Ա����
}

CTmScptGroupCmd::~CTmScptGroupCmd()
{
}

long CTmScptGroupCmd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return CTmScptCmd::XmlReadOwn(oNode, pXmlRWKeys);
}

long CTmScptGroupCmd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return CTmScptCmd::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
}

CBaseObject* CTmScptGroupCmd::Clone()
{
	CTmScptGroupCmd *p = new CTmScptGroupCmd();
	Copy(p);
	return p;
}

BOOL CTmScptGroupCmd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTmScptGroupCmd *p = (CTmScptGroupCmd*)pDest;

	CTmScptCmd::CopyOwn(pDest);

	return TRUE;
}

BOOL CTmScptGroupCmd::RunScript(CTestMacro *pMacro)
{
	BOOL bTrue = FALSE;
	long nCount = TMS_SetDatasAttrByGroupID(pMacro, m_strDataID, m_strAttrID, m_strValue);
	bTrue = (nCount > 0);
	return bTrue;
}


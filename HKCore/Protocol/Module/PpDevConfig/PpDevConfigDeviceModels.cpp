#include "stdafx.h"
#include "PpDevConfigDeviceModels.h"


long CPpDevConfigDeviceModels::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CPpDevConfigDeviceModels::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

CExBaseObject* CPpDevConfigDeviceModels::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CPpDevConfigXMLKeys::g_pPpDevConfigXMLKeys->m_strDevcieModelKey)
	{
		return new CPpDevConfigDeviceModel();
	}

	return NULL;
}

CExBaseObject* CPpDevConfigDeviceModels::FindDeviceModelDefine(const CString &strModelDefineFile)
{
	POS pos = GetHeadPosition();
	CPpDevConfigDeviceModel *p = NULL;
	CPpDevConfigDeviceModel *pFind = NULL;

	while (pos != NULL)
	{
		p = (CPpDevConfigDeviceModel *)GetNext(pos);

		if (p->m_strFile == strModelDefineFile)
		{
			pFind = p;
			break;
		}
	}

	if (pFind == NULL)
	{
		return NULL;
	}
	else
	{
		return pFind->GetDeviceModel();
	}
}


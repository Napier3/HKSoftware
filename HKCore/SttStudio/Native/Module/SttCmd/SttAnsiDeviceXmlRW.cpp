//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttAnsiDeviceXmlRW.cpp  CSttAnsiDeviceXmlRW


#include "stdafx.h"
#include "SttAnsiDeviceXmlRW.h"

#include "../../../61850/Module/MmsWriteXml.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttAnsiDeviceXmlRW::CSttAnsiDeviceXmlRW()
{
	m_bOblyGetLd = FALSE;
}

CSttAnsiDeviceXmlRW::~CSttAnsiDeviceXmlRW()
{
	
}

BSTR CSttAnsiDeviceXmlRW::GetXmlElementKey()
{
	return CDataMngrXmlRWKeys::CDvmDeviceKey();
}

long CSttAnsiDeviceXmlRW::XmlRead(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	
	return 0;
}

long CSttAnsiDeviceXmlRW::XmlWrite(CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent, BSTR pszElementKey, CXmlRWKeys *pXmlRWKeys)
{
	mms_XmlWrite(&pACSINode[m_nDeviceIndex], oXMLDoc, oParent, m_bOblyGetLd);

	return 0;
}


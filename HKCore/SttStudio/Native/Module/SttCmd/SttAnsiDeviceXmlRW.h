//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttAnsiDeviceXmlRW.h  CSttAnsiDeviceXmlRW

#pragma once

#include "SttCmdDefineGlobal.h"

class CSttAnsiDeviceXmlRW : public CExBaseObject
{
public:
	CSttAnsiDeviceXmlRW();
	virtual ~CSttAnsiDeviceXmlRW();

	long m_nDeviceIndex;
	BOOL m_bOblyGetLd;
	
//���غ���
public:
	virtual BSTR GetXmlElementKey();
	virtual long XmlRead(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWrite(CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent, BSTR pszElementKey, CXmlRWKeys *pXmlRWKeys);

};


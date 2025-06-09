//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
	
//重载函数
public:
	virtual BSTR GetXmlElementKey();
	virtual long XmlRead(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWrite(CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent, BSTR pszElementKey, CXmlRWKeys *pXmlRWKeys);

};


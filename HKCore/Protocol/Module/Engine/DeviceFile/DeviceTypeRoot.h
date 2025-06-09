#pragma once
#include "DeviceTypePathXmlKeys.h"
#include "DeviceType.h"
class CDeviceTypeRoot : public CExBaseList
{
public:
	CDeviceTypeRoot(void);
	virtual ~CDeviceTypeRoot(void);

	//���л�
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	//�����Ӷ���
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail);

	BOOL OpenXMLFile();
	BOOL SaveXMLFile();

};

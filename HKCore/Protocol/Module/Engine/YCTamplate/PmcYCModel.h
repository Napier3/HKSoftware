#pragma once
#include "..\..\..\..\Module\BaseClass\ExBaseList.h"


class CPmcYCModel:public CExBaseList
{
public:
	CPmcYCModel(void);
	virtual ~CPmcYCModel(void);

public:
	//��д
	virtual long XMLReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XMLWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	//�����Ӷ���
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

};

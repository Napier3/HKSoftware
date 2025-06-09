#pragma once
#include "..\..\..\..\Module\BaseClass\ExBaseList.h"


class CPmcYCModel:public CExBaseList
{
public:
	CPmcYCModel(void);
	virtual ~CPmcYCModel(void);

public:
	//读写
	virtual long XMLReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XMLWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	//创建子对象
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

};

#pragma once

#include "../../../../../../Module/XML/XmlRWFactory.h"

class CXmlRWFactoryMd5 : public CXmlRWFactory
{
public:
	CXmlRWFactoryMd5(void);
	virtual ~CXmlRWFactoryMd5(void);

protected:
	virtual CXmlRWDocBase* I_CreateXmlRWDoc(long nType);
};

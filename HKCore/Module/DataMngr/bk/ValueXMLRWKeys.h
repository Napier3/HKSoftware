// ValueXMLRWKeys.h : CValueXMLRWKeys µÄÉùÃ÷

#pragma once


#include "..\BaseClass\ExBaseObject.h"


class CValueXMLRWKeys : public CXmlRWKeys
{
public:
	CValueXMLRWKeys();
	virtual ~CValueXMLRWKeys();

public:
	BSTR m_strValueKey;
	BSTR m_strValueElementKey;
	BSTR m_strValuesElementKey;
	BSTR m_strValuesNameAttrKey;
	BSTR m_strValuesIDAttrKey;
	BSTR m_strValuesMngrElementKey;
};

#pragma once
#include "Binarys.h"
#include "GuideBookDefine.h"

class CBinaryOuts :public CBinarys
{
public:
	CBinaryOuts(void);
	virtual ~CBinaryOuts(void);

public:
	virtual UINT GetClassID()				{		return GBCLASSID_BINARYOUTS;		}
	virtual BSTR GetXmlElementKey()	{      return CGbXMLKeys::g_pGbXMLKeys->m_strBinaryOutsKey;     }
	virtual CBaseObject* Clone();

protected:

private:

};
//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TmScptValue.h  CTmScptValue

#pragma once

#include "MacroScriptMngrGlobal.h"


#include "TmScptCmd.h"
#include "TmScptGroupCmd.h"

class CTmScptValue : public CExBaseList
{
public:
	CTmScptValue();
	virtual ~CTmScptValue();


	CString  m_strValue;
//���غ���
public:
	virtual UINT GetClassID() {    return MCSCLASSID_CTMSCPTVALUE;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroScriptMngrXmlRWKeys::CTmScptValueKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

public:
	BOOL RunScript(CTestMacro *pMacro);
};


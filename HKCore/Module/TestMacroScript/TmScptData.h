//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TmScptData.h  CTmScptData

#pragma once

#include "MacroScriptMngrGlobal.h"
#include "TmScptValue.h"

class CTmScptData : public CExBaseList
{
public:
	CTmScptData();
	virtual ~CTmScptData();


//���غ���
public:
	virtual UINT GetClassID() {    return MCSCLASSID_CTMSCPTDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroScriptMngrXmlRWKeys::CTmScptDataKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);

//˽�г�Ա����
private:
	CString m_strOldData;

//˽�г�Ա�������ʷ���
public:

public:
	CTmScptValue* FindByValue(const CString &strValue);
	BOOL RunScript(CTestMacro *pMacro, CShortData *pData);
};


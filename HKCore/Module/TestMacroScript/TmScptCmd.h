//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TmScptCmd.h  CTmScptCmd

#pragma once

#include "MacroScriptMngrGlobal.h"



class CTmScptCmd : public CExBaseObject
{
public:
	CTmScptCmd();
	virtual ~CTmScptCmd();


	CString  m_strDataID;
	CString  m_strAttrID;
	CString  m_strValue;
//���غ���
public:
	virtual UINT GetClassID() {    return MCSCLASSID_CTMSCPTCMD;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroScriptMngrXmlRWKeys::CTmScptCmdKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:


public:
	virtual BOOL RunScript(CTestMacro *pMacro);

};


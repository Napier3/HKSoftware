//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TmScptGroupCmd.h  CTmScptGroupCmd

#pragma once

#include "MacroScriptMngrGlobal.h"
#include "TmScptCmd.h"


class CTmScptGroupCmd : public CTmScptCmd
{
public:
	CTmScptGroupCmd();
	virtual ~CTmScptGroupCmd();


//���غ���
public:
	virtual UINT GetClassID() {    return TMSCLASSID_CTMSCPTGROUPCMD;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroScriptMngrXmlRWKeys::CTmScptGroupCmdKey();     }
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


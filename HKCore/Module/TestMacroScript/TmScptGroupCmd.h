//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TmScptGroupCmd.h  CTmScptGroupCmd

#pragma once

#include "MacroScriptMngrGlobal.h"
#include "TmScptCmd.h"


class CTmScptGroupCmd : public CTmScptCmd
{
public:
	CTmScptGroupCmd();
	virtual ~CTmScptGroupCmd();


//重载函数
public:
	virtual UINT GetClassID() {    return TMSCLASSID_CTMSCPTGROUPCMD;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroScriptMngrXmlRWKeys::CTmScptGroupCmdKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);

//私有成员变量
private:

//私有成员变量访问方法
public:

public:
	virtual BOOL RunScript(CTestMacro *pMacro);

};


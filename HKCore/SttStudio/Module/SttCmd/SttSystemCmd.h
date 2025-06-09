//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttSystemCmd.h  CSttSystemCmd

#pragma once

#include "SttCmdDefineGlobal.h"

#include "SttCmdBase.h"


class CSttSystemCmd : public CSttCmdBase
{
public:
	CSttSystemCmd();
	virtual ~CSttSystemCmd();


	CString  m_strTestor;
//重载函数
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTSYSTEMCMD;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttSystemCmdKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};


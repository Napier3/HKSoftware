//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMacroTestUI_TestMacroUIRef.h  CSttMacroTestUI_TestMacroUIRef

#pragma once

#include "SttTestCtrrlMacroTestUIMngrGlobal.h"



class CSttMacroTestUI_TestMacroUIRef : public CExBaseObject
{
public:
	CSttMacroTestUI_TestMacroUIRef();
	virtual ~CSttMacroTestUI_TestMacroUIRef();


//重载函数
public:
	virtual UINT GetClassID() {    return MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUIREF;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestCtrrlMacroTestUIMngrXmlRWKeys::CSttMacroTestUI_TestMacroUIRefKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	long GetDefaultRepeatTimes();
};


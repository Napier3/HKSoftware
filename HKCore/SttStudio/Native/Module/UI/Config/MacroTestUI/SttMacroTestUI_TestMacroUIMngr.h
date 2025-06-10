//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMacroTestUI_TestMacroUIMngr.h  CSttMacroTestUI_TestMacroUIMngr

#pragma once

#include "SttTestCtrrlMacroTestUIMngrGlobal.h"


#include "SttMacroTestUI_Group.h"
#include "SttMacroTestUI_TestMacroUIRef.h"

class CSttMacroTestUI_TestMacroUIMngr : public CExBaseList
{
public:
	CSttMacroTestUI_TestMacroUIMngr();
	virtual ~CSttMacroTestUI_TestMacroUIMngr();


//重载函数
public:
	virtual UINT GetClassID() {    return MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUIMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestCtrrlMacroTestUIMngrXmlRWKeys::CSttMacroTestUI_TestMacroUIMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};


//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DLLCallMngr.h  CDllCallDefMngr

#pragma once

#include "DllCallGlobal.h"


#include "DLLCallDef.h"

class CDllCallDefFile : public CExBaseList
{
public:
	CDllCallDefFile();
	virtual ~CDllCallDefFile();

	virtual BSTR GetXmlElementKey()  {      return CDllCallXmlRWKeys::CDllCallDefMngrKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	BOOL OpenDllCallDefFile(const CString &strFile);
};

class CDllCallDefMngr : public CExBaseList
{
protected:
	CDllCallDefMngr();
	virtual ~CDllCallDefMngr();

	static long g_nDllCallDefMngrRef;

public:
	static CDllCallDefMngr* g_pDllCallDefMngr;
	static CDllCallDefMngr* Create();
	static void Release();
	static CDllCallDefFile* GetDllCallFile(const CString &strDllCallFile);

//重载函数
public:
	virtual UINT GetClassID() {    return DLCLCLASSID_CDLLCALLMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CDllCallXmlRWKeys::CDllCallDefMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:

protected:
	CDllCallDefFile* In_GetDllCallFile(const CString &strDllCallFile);

};


//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdTestMacro.h  CSttGdTestMacro

#pragma once

#include "SttTestGridDefineGlobal.h"


#include "SttGdDataProcess.h"
#include "SttGdGridDefine.h"
#include "SttGdGridInsts.h"

class CSttGdTestMacro : public CExBaseList
{
public:
	CSttGdTestMacro();
	virtual ~CSttGdTestMacro();


	CString  m_strMacroID;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTGDTESTMACRO;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestGridDefineXmlRWKeys::CSttGdTestMacroKey();     }
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
	CSttGdGridDefine *m_pSttGdGridDefine;
	CSttGdGridInsts *m_pSttGdGridInsts;

//私有成员变量访问方法
public:
	CSttGdGridDefine* GetSttGdGridDefine();
	CSttGdGridInsts* GetSttGdGridInsts();

//属性变量访问方法
public:
	void InitGridInsts();//初始化全部表格实例
};


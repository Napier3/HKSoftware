//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdGridInst.h  CSttGdGridInst

#pragma once

#include "SttTestGridDefineGlobal.h"


#include "SttGdInst_Cols.h"
#include "SttGdCondition.h"

class CSttGdGridInst : public CExBaseList
{
public:
	CSttGdGridInst();
	virtual ~CSttGdGridInst();


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTGDGRIDINST;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestGridDefineXmlRWKeys::CSttGdGridInstKey();     }
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
	CSttGdInst_Cols *m_pSttGdInst_Cols;

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	long GetColCount();
};


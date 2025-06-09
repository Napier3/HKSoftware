//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecGenRule_CtrlCh.h  CIecGenRule_CtrlCh

#pragma once

#include "IecfgGenMngrGlobal.h"


#include "IecGenCfgKeys.h"

class CIecGenRule_CtrlCh : public CExBaseList
{
public:
	CIecGenRule_CtrlCh();
	virtual ~CIecGenRule_CtrlCh();


	CString  m_strAppCh;
	CString  m_strChType;
	long  m_nMatchRatio;
	CString m_strPhsID;  //phsA, phsB, phsC
//重载函数
public:
	virtual UINT GetClassID() {    return GENRATECLASSID_CIECGENRULE_CTRLCH;   }
	virtual BSTR GetXmlElementKey()  {      return CIecfgGenMngrXmlRWKeys::CIecGenRule_CtrlChKey();     }
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


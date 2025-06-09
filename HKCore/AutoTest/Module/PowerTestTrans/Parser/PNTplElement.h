//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PNTplElement.h  CPNTplElement

#pragma once

#include "PNTplMngrGlobal.h"


#include "PNTplEquation.h"
#include "PNTplGroup.h"
#include "PNTplText.h"

class CPNTplElement : public CExBaseList
{
public:
	CPNTplElement();
	virtual ~CPNTplElement();

	CString m_strElementData;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CPNTPLELEMENT;   }
	virtual BSTR GetXmlElementKey()  {      return CPNTplMngrXmlRWKeys::CPNTplElementKey();     }
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
	CPNTplEquation* FindEquation(const CString &strVarID);
	CPNTplEquation* FindEquationEx(const CString &strVarID);
	CPNTplGroup* FindGroupByValueID(const CString &strVarID);
	CPNTplEquation* FindEquationByValue(const CString &strValue);

	BOOL HasProtectionRelayParent();
	BOOL IsRepeatNode(const CString &strCurNodeName);//对于部分模板重复出现两个<ReportBegin>的情况作特例处理zhouhj
};


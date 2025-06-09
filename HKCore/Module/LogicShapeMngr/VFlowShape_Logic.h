//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VFlowShape_Logic.h  CVFlowShape_Logic

#pragma once

#include "LogicShapeMngrGlobal.h"

#include "VFlowShape.h"


class CVFlowShape_Logic : public CVFlowShape
{
public:
	CVFlowShape_Logic();
	virtual ~CVFlowShape_Logic();


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CVFLOWSHAPE_LOGIC;   }
	virtual BSTR GetXmlElementKey()  {      return CLogicShapeMngrXmlRWKeys::CVFlowShape_LogicKey();     }
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
	virtual void UpdateLineType_Color();

protected:
	long CalcLogicValue();
	long CalcLogicValue_AND();
	long CalcLogicValue_OR();
	long CalcLogicValue_NOT();
};


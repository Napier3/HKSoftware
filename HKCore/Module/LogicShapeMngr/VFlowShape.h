//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VFlowShape.h  CVFlowShape

#pragma once

#include "LogicShapeMngrGlobal.h"

#include "VFlowShapeBase.h"
#include "VFlowShapeLines.h"


class CVFlowShape : public CVFlowShapeBase
{
public:
	CVFlowShape();
	virtual ~CVFlowShape();


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CVFLOWSHAPE;   }
	virtual BSTR GetXmlElementKey()  {      return CLogicShapeMngrXmlRWKeys::CVFlowShapeKey();     }
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
	BOOL m_bHasAttachCalc;//判断是否关联了算法的链表

//属性变量访问方法
public:
	virtual void UpdateLineType_Color();//更新Shape线条类型、颜色
	virtual void InitDataTypeUnit();//初始化Shape对象、其基类对象、及输出端line里的数据类型及属性

	CVFlowShapeLines m_oInLines;//所有输入端线条
	CVFlowShapeLines m_oOutLines;//所有输出端线条
};


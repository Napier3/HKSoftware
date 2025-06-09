//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VFlowShape_Branch.h  CVFlowShape_Branch

#pragma once

#include "LogicShapeMngrGlobal.h"

#include "VFlowShape.h"


class CVFlowShape_Branch : public CVFlowShape
{
public:
	CVFlowShape_Branch();
	virtual ~CVFlowShape_Branch();


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CVFLOWSHAPE_BRANCH;   }
	virtual BSTR GetXmlElementKey()  {      return CLogicShapeMngrXmlRWKeys::CVFlowShape_BranchKey();     }
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
	virtual void InitDataTypeUnit();//初始化Shape对象、其基类对象、及输出端line里的数据类型及属性
	CVFlowShape* GetBeginShape_Connected(); //获取与该分支节点相连的首端Shape，首端必须唯一、且必须有
};


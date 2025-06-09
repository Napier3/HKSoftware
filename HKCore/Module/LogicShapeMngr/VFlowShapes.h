//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VFlowShapes.h  CVFlowShapes

#pragma once

#include "LogicShapeMngrGlobal.h"

#include "VFlowShapesBase.h"

#include "VFlowShapeLine.h"
#include "VFlowShape_Data.h"
#include "VFlowShape_Logic.h"
#include "VFlowShape_Expression.h"
#include "VFlowShape_Branch.h"
#include "VFlowShape_Threshold.h"

class CVFlowShapes : public CVFlowShapesBase
{
public:
	CVFlowShapes();
	virtual ~CVFlowShapes();


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CVFLOWSHAPES;   }
	virtual BSTR GetXmlElementKey()  {      return CLogicShapeMngrXmlRWKeys::CVFlowShapesKey();     }
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
	void InitShapes();//初始化Shape中的算法运行使用的标识为0
	void GetAllResultShapes(CVFlowShapes *pResultRefShapes);//获取全部没有输出,只有输入的Shape，即结果Shape
};


//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VFlowShapesBase.h  CVFlowShapesBase

#pragma once

#include "LogicShapeMngrGlobal.h"
#include "VFlowShapeBase.h"



class CVFlowShapesBase : public CExBaseList
{
public:
	CVFlowShapesBase();
	virtual ~CVFlowShapesBase();


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CVFLOWSHAPESBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CLogicShapeMngrXmlRWKeys::CVFlowShapesBaseKey();     }
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
	virtual BOOL UpdateAllShapes();//根据当前值,更新全部Shape、Line

	CVFlowShapeBase *FindByVisioID(long nVisioID);
	CVFlowShapeBase *FindByData1(const CString &strData1);
	BOOL SetValueByID(const CString &strID,const CString &strValue);
	BOOL GetValueByID(const CString &strID,CString &strValue);
	BOOL SetValueByData1(const CString &strData1,const CString &strValue);
	BOOL SetValueByID_UI(const CString &strID,const CString &strValue);
	BOOL SetValueByData1_UI(const CString &strData1,const CString &strValue);
	BOOL GetValueByData1_UI(const CString &strData1,CString &strValue);
};


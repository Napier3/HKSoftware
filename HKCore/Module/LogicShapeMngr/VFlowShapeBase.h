//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VFlowShapeBase.h  CVFlowShapeBase

#pragma once

#include "LogicShapeMngrGlobal.h"
#include "../Visio/MSVisio15.h"

#define  VISIO_SHAPE_SHOW_LINE_TYPE_DATA               MSVisio15::visSolid   //对于原始数据类的显示线条类型
#define  VISIO_SHAPE_SHOW_LINE_TYPE_FALSE               MSVisio15::visThinCross   //值为0的显示线条类型
#define  VISIO_SHAPE_SHOW_LINE_TYPE_TRUE               MSVisio15::visSolid   //值为1的显示线条类型

#define  VISIO_SHAPE_SHOW_TYPE_COLOR_DATA               _T("THEMEGUARD(RGB(0,0,255))")   //对于原始数据类的显示线条颜色
#define  VISIO_SHAPE_SHOW_TYPE_COLOR_FALSE               _T("THEMEGUARD(RGB(255,0,0))")   //值为0的显示线条颜色
#define  VISIO_SHAPE_SHOW_TYPE_COLOR_TRUE               _T("THEMEGUARD(RGB(0,255,0))")  //值为1的显示线条颜色



#include "VFlowShapeProperty.h"

class CVFlowShapeBase : public CExBaseList
{
public:
	CVFlowShapeBase();
	virtual ~CVFlowShapeBase();


	long  m_nVisioID;
	CString  m_strDataType;
	CString  m_strHelp;
	CString  m_strData1;
	CString  m_strData2;
	CString  m_strData3;
	CString  m_strUnit;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CVFLOWSHAPEBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CLogicShapeMngrXmlRWKeys::CVFlowShapeBaseKey();     }
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
	BOOL Has_VisioShapeObj();

	BOOL SetData3_UI(const CString &strValue);//设置Data3值并更新界面显示
	BOOL GetData3_UI(CString &strValue);//设置Data3值并更新界面显示

	void AddNewProperty(const long &nRowIndex);
	BOOL SetShapeLineType(const long &nLineType);
	BOOL SetShapeColor(const CString &strColor);
//	BOOL SetPropertyValueByRowIndex_UI(const long &nRowIndex,const CString &strPropertyValue);//将属性值填入属性并更新Visio图
//	BOOL GetPropertyValueByRowIndex_UI(const long &nRowIndex,const CString &strPropertyValue);//根据RowIndex更新属性值
	BOOL SetPropertyValueByPath_UI(const CString &strPropertyPath,const CString &strValue);//根据属性路径设置属性值，同时更新Visio图
	BOOL GetPropertyValueByPath_UI(const CString &strPropertyPath,CString &strValue);//根据属性路径从界面获取属性值
	BOOL GetPropertyValueByPath(const CString &strPropertyPath,CString &strValue);//根据属性路径从内存获取属性值

	BOOL SetPropertyDataTypeUnitByID(const CString &strPropertyID,const CString &strDataType,const CString &strUnit);//根据属性ID设置属性单位、数据类型，实际更新Visio图


	BOOL GetPropertyValueByID(const CString &strPropertyID,CString &strValue);//从链表中获取属性值
	BOOL SetPropertyValueByID(const CString &strPropertyID,const CString &strValue);//设置链表中属性值
	BOOL GetPropertyValueByID_UI(const CString &strPropertyID,CString &strValue);//从界面获取属性值
	BOOL SetPropertyValueByID_UI(const CString &strPropertyID,const CString &strValue);//设置界面属性值并更新链表值

	BOOL GetPropertyValuesByRowIndex_UI(CVFlowShapeProperty *pShapeProperty);//根据该对象中现有的RowIndex获取该属性其它Visio界面值
	BOOL GetPropertyByRowIndex_UI(const long &nRowIndex,CString &strPropertyName,CString &strPropertyValue,CString &strPropertyLabel,CString &strPropertyTip);
	virtual void UpdateLineType_Color();

	CVFlowShapeProperty* FindByPath(const CString &strPath);

	MSVisio15::CVShape m_oShape;
};


//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdColDef.h  CSttGdColDef

#pragma once

#include "SttTestGridDefineGlobal.h"


#include "SttGdColDef_Para.h"
#include "SttGdColDef_Script.h"
#include "../../../../../Module/DataMngr/DvmValues.h"
#include "../../../../../Module/DataMngr/ShortDatas.h"

class CSttGdColDef : public CExBaseList
{
public:
	CSttGdColDef();
	virtual ~CSttGdColDef();


	CString  m_strDataType;
	CString  m_strUnit;
	CString  m_strDecimal;
	CString  m_strMax;
	CString  m_strMin;
	long  m_nEditable;
	long  m_nWidth;
	CString  m_strCtrlType;
	double  m_fRate;
	long  m_nSettingAttach;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTGDCOLDEF;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestGridDefineXmlRWKeys::CSttGdColDefKey();     }
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
	CString GetParaID();
	BOOL IsCombBoxCtrl();//判断是否为下拉框控件
	BOOL IsRateItemCtrl();//包含比率系数的表格控件
	BOOL IsZSettingItemCtrl();//特殊控件,界面显示实际阻抗值,数据对象中对应阻抗定值和对应系数
	BOOL IsImpedanceCustomItemCtrl();//阻抗自定义控件,按ID指定
   BOOL GetTestRsltString(CDvmValues *pDvmValues, CShortDatas *pResults, CString &strText);

protected:
	BOOL GetTestRsltStringByResultParas(CDvmValues *pDvmValues, CShortDatas *pResults, CString &strText);
};


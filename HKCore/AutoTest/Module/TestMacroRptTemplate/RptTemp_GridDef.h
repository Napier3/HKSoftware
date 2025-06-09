//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_GridDef.h  CRptTemp_GridDef

#pragma once

#include "TestMacroRptTemplateGlobal.h"


#include "RptTemp_ColsDef.h"
#include "RptTemp_RowsDef.h"
#include "RptTemp_Head.h"
#include "RptTemp_Row.h"
#include "RptTemp_Col.h"
#include "RptTemp_MacroTest.h"
#include "RptTemp_Enable.h"
class CRptTemp_MacroTest;

class CRptTemp_GridDef : public CExBaseList
{
public:
	CRptTemp_GridDef();
	virtual ~CRptTemp_GridDef();

	//表格填写模式：
	/*1、row-item：行为测试项目。针对单点测试，一行对应一个测试项目（电气量，macrotest）。
	  2、col-item：列为测试项目。（暂不实现）
	  3、row-rpt：行为测试报告。针对重复测试，一行对应一个report-def
	  4、col-rpt：列为测试报告。（暂不实现）
	*/
	CString  m_strData_Mode;
	long m_nShowBorders;  //是否显示边框
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_GRIDDEF;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_GridDefKey();     }
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
	CRptTemp_Enable *m_pEnable;
//私有成员变量访问方法
public:
	CRptTemp_Enable* GetEnable()	{	return m_pEnable;	}

//属性变量访问方法
public:
	long GetRowsCount();
	long GetRowsCount_RowItem();
	long GetRowsCount_ColItem();
	long GetRowsCount_RowRpt();
	long GetRowsCount_ColRpt();

	long GetColsCount();
	long GetColsCount_RowItem();
	long GetColsCount_ColItem();
	long GetColsCount_RowRpt();
	long GetColsCount_ColRpt();

	long GetHeadCount();

	BOOL IsDataMode_Row(); //是否是行填写模式
	BOOL IsDataMode_Col(); //是否是列填写模式

	CRptTemp_MacroTest* GetMacroTest(long nIndex);
	BOOL IsEnable(CExBaseList *pParas);
};


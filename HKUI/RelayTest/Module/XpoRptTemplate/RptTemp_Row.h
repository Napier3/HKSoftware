//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_Row.h  CRptTemp_Row

#pragma once

#include "TestMacroRptTemplateGlobal.h"


#include "RptTemp_Cell.h"

class CRptTemp_Row : public CExBaseList
{
public:
	CRptTemp_Row();
	virtual ~CRptTemp_Row();

	//对于列合并，合并后，列号需要递减
	//记录已经合并的列的数量
	long m_nMergeCol; 

	//同一行的数据来自相同的项目。若需要实现同一行不同单元格的数据来自不同项目，需在cell中扩展记录项目的相对路径
	CString m_strItemPath;  //绑定的测试项目的路径信息
	void *m_pGbItemBase;  //绑定的测试项目（CGbItemBase或者CSttItemBase）


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_ROW;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_RowKey();     }
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
	CRptTemp_Cell* AddNewCell(const CString &strText);

//属性变量访问方法
public:
};


//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_Items.h  CRptTemp_Items

#pragma once

#include "TestMacroRptTemplateGlobal.h"


//#include "RptTemp_MacroCharItems.h"
//#include "RptTemp_MacroTest.h"
#include "RptTemp_ReportTemplate.h"

class CRptTemp_Items : public CExBaseList
{
public:
	CRptTemp_Items();
	virtual ~CRptTemp_Items();


	long  m_nRpt_Title;
	long  m_ntitle_level;

	CExBaseList m_oList;  //临时链表。存放该节点下所有需要实时更新的text和row对象。
	void *m_pItems;  //绑定的测试项目。rootnode节点。（CItems或者CSttItems）
private:
	//是否已经生成。针对rpt-mode=items的。
	BOOL m_bHasGen;  
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_ITEMS;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_ItemsKey();     }
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
	long GetMacroTestCount();
    //CRptTemp_MacroTest* GetMacroTestByIndex(long nIndex);

	BOOL IsHasGen()	{	return m_bHasGen;	}
	void SetHasGen(BOOL bHasGen)	{	m_bHasGen = bHasGen;	}
	void AddTailToIndexList(CExBaseObject *pObj);
	void RemoveIndexList(CExBaseObject *pObj);
	BOOL IsAncestorOf(CRptTemp_Items *pChildItems);  //判断this指针是否是形参的祖先节点
};


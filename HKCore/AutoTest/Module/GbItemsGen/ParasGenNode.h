//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ParasGenNode.h  CParasGenNode

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"
#include "GenNodeBase.h"
#include "ItemsGenParaDef.h"

/*
测试模板生成定义的生成节点类，节点类可以嵌套
根据不同的项目分支，例如：故障方向（正反向）、故障相别（A、B、C）、倍数（0.95,1.05,1.2，1.0），分别嵌套定义各自的生成节点；
对于不同的项目分支，根据各自定义的生成节点，应当找到最底层的生成节点（叶子生成节点），并以乘法去生成对应的电气量项目
电气量项目的数量 = 各分支的叶子生成节点数相乘，例如：2*3*4
*/
class CParasGenNode : public CGenNodeBase
{
public:
	CParasGenNode();
	virtual ~CParasGenNode();

	long  m_nNewItems;
//重载函数
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CPARASGENNODE;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CParasGenNodeKey();     }
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
	CItemsGenParaDef *m_pItemsGenParaDef;

//私有成员变量访问方法
public:
	CItemsGenParaDef* GetItemsGenParaDef()	{	return m_pItemsGenParaDef;	}
	void SetItemsGenParaDef(CItemsGenParaDef* pItemsGenParaDef)	{	m_pItemsGenParaDef = pItemsGenParaDef;	}

//属性变量访问方法
public:
	virtual CString GetNameAdd_Name(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup);
	virtual CString GetNameAdd_ID(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup);
	virtual CItemsGenInterface* GetGenInterface();
	virtual CItemsGenInterface* GetGenInterface_BK();
};


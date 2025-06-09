//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenDataMap.h  CItemsGenDataMap

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"
#include "../../../Module/DataMngr/DataGroup.h"
#include "../../../Module/Expression/EpExpression.h"


/**************************
CItemsGenDataMap，参数映射的数据对象
m_strID_Map为映射的参数ID，对应界面参数的ID；
当与电气量参数进行映射时，m_strID为电气量项目参数的ID
当与使能数据接口映射时，m_strID为使能接口数据的ID
当映射的参数ID不为空时，m_strValue取值自映射的参数
*/
class CItemsGenDataMap : public CExBaseObject
{
public:
	CItemsGenDataMap();
	virtual ~CItemsGenDataMap();


	CString  m_strID_Map;
	CString  m_strValue;

	//2022-3-1  lijunqing  是否映射成功。从命名上看，m_nIsMap更多的理解是否为映射，增加Succ，提高可读性
	long m_nIsMapSucc;   //映射是否成功，即根据id-map映射的数据是否存在。不存在的映射参数，将不放入电气量项目参数中
	long m_nKeepExpr;  //模板生成时，电气量项目参数是否将值保留为表达式
//重载函数
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENDATAMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenDataMapKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	BOOL GetValue_String(CString &strValue, CDataGroup *pDataGroup);
	BOOL GetValue_Long(long &nValue, CDataGroup *pDataGroup);
	BOOL GetValue_Float(float &fValue, CDataGroup *pDataGroup);

	//通过表达式，进行参数映射初始化
	BOOL InitParaByExpression(CDataGroup *pUIParas);
	BOOL InitParaByExpression(CEpExpression *pEpEpr, CDataGroup *pUIParas);

	//根据表达式，进行参数映射。映射后保留表达式
	BOOL InitParasMapByInterface_Ex(CExBaseList *pInterface);

	//通过表达式，进行参数映射初始化，映射后保留表达式的值
	BOOL InitParaByInterface_Expression(CExBaseList *pInterfac);
	BOOL InitParaByInterface_Expression(CEpExpression *pEpEpr, CExBaseList *pInterfac);
};


/////////////////////////////////////////////////////////////////////////////////////////////////
//该类用于给通讯命令生成节点，设计通讯参数使用，与interface映射
class CItemsGenDataset : public CItemsGenDataMap
{
public:
	CItemsGenDataset();
	virtual ~CItemsGenDataset();

	//重载函数
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENDATASET;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenDatasetKey();     }
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

};
//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenParasMap.h  CItemsGenParasMap

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"


#include "ItemsGenDataMap.h"
class CItemsGenInterface;

//参数映射结果日
/*
//参数映射包括两种：
1、与界面参数的映射，用于判断使能
2、电气量项目参数与接口参数之间的映射
*/
#define PARAMAP_LOG_LEVEL_UIPARAS 0
#define PARAMAP_LOG_LEVEL_INTERFACE 1

//CItemsGenParasMap，为界面参数（形成的CDataGroup对象），与电气量项目参数之间的映射
class CItemsGenParasMap : public CExBaseList
{
public:
	CItemsGenParasMap();
	virtual ~CItemsGenParasMap();


//重载函数
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENPARASMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenParasMapKey();     }
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
	BOOL GetParaValueByID(const CString &strID, CDataGroup *pDataGroup, CString &strValue);
	void InitParaValueByUIParas(CDataGroup *pUIParas);
	CDvmData* GetDataByIDPath_Sort(CDataGroup *pUIParas, const CString &strIDPath);
	CDvmData* GetDataByIDPath(CDataGroup *pUIParas, const CString &strIDPath);
	CDvmData* GetDataByIDPathEx(CDataGroup *pUIParas, CDataGroup *pGrp, const CString &strIDPath);
	void InitParasMapByInterface(CItemsGenInterface *pInterface);
	void InitParasMapByInterface_Ex(CItemsGenInterface *pInterface);
	void LogParasMapError(UINT nLogLevel = PARAMAP_LOG_LEVEL_UIPARAS);
};


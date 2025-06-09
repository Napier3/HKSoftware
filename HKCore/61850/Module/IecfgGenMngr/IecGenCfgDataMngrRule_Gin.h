//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecGenCfgDataMngrRule_Gin.h  CIecGenCfgDataMngrRule_Gin

#pragma once

#include "IecfgGenMngrGlobal.h"

#include "IecGenCfgDataMngrRule_Base.h"

#include "IecGenRule_CtrlBlock.h"
#include "IecGenRule_CtrlCh.h"

class CIecGenCfgDataMngrRule_Gin : public CIecGenCfgDataMngrRule_Base
{
public:
	CIecGenCfgDataMngrRule_Gin();
	virtual ~CIecGenCfgDataMngrRule_Gin();


//重载函数
public:
	virtual UINT GetClassID() {    return GENRATECLASSID_CIECGENCFGDATAMNGRRULE_GIN;   }
	virtual BSTR GetXmlElementKey()  {      return CIecfgGenMngrXmlRWKeys::CIecGenCfgDataMngrRule_GinKey();     }
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
//	BOOL GenarateIecCfgGinDatas(CIecCfgGinDatas* pGinMngr);
//	BOOL GenerateIecCfgDatas_Bin(CIecCfgGinDatas* pGinMngr);
};


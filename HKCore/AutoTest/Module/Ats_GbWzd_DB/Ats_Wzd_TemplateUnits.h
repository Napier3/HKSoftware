//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_TemplateUnits.h  CAts_Wzd_TemplateUnits

#pragma once

#include "AtsGbWizrdGlobal.h"


#include "Ats_Wzd_TemplateUnit.h"

class CAts_Wzd_TemplateUnits : public CExBaseList
{
public:
	CAts_Wzd_TemplateUnits();
	virtual ~CAts_Wzd_TemplateUnits();


//重载函数
public:
	virtual UINT GetClassID() {    return ATSGBWIZRDCLASSID_CATS_WZD_TEMPLATEUNITS;   }
	virtual BSTR GetXmlElementKey()  {      return CAtsGbWizrdXmlRWKeys::CAts_Wzd_TemplateUnitsKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CAtsGbWizrdXmlRWKeys::CAts_Wzd_TemplateUnitKey();     }
	virtual BSTR DB_GetChildTableName(CXmlRWKeys *pXmlRWKeys)  {      return CAtsGbWizrdXmlRWKeys::CAts_Wzd_TemplateUnitKey();     }
	virtual CExBaseObject* DB_CreateNewChild();

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	long GetSelectedCount();
	void SetSelected(long nSelect=1);
};


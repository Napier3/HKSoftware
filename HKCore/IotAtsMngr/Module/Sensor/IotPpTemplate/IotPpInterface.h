//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpInterface.h  CIotPpInterface

#pragma once

#include "IOTPPGlobal.h"
#include "../../../../Module/DataMngr/DvmDataset.h"


#include "IotPpValue.h"

class CIotPpInterface : public CExBaseList
{
public:
	CIotPpInterface();
	virtual ~CIotPpInterface();


//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOTPPINTERFACE;   }
	virtual BSTR GetXmlElementKey()  {      return CIOTPPXmlRWKeys::CIotPpInterfaceKey();     }
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
	void UpdateInterfaceValue(CExBaseList *pSrcInterface);
	void UpdateValueByDataset(CDvmDataset *pSrcDataset);

	BOOL GetValueByID(const CString &strID,CString &strValue);
	BOOL GetValueByID(const CString &strID,long &nValue);
};


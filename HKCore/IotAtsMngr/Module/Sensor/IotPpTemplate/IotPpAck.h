//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpAck.h  CIotPpAck

#pragma once

#include "IOTPPGlobal.h"


#include "IotPpJumps.h"
class CDvmDataset;

class CIotPpAck : public CExBaseList
{
public:
	CIotPpAck();
	virtual ~CIotPpAck();


	CString  m_strPkg_Id;
//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOTPPACK;   }
	virtual BSTR GetXmlElementKey()  {      return CIOTPPXmlRWKeys::CIotPpAckKey();     }
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
	CIotPpJumps *m_pIotPpJumps;

//私有成员变量访问方法
public:
	CIotPpJumps* GetIotPpJumps()	{	return m_pIotPpJumps;	}

//属性变量访问方法
public:
	void UpdateTimers(CDvmDataset *pAttrDataset,CExBaseList *pInterface);
};


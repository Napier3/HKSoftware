//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpDeviceNode.h  CEpDeviceNode

#pragma once

#include "EpDeviceGlobal.h"


#include "EpDeviceData.h"

class CEpDeviceNode : public CExBaseList
{
public:
	CEpDeviceNode();
	virtual ~CEpDeviceNode();


//重载函数
public:
	virtual UINT GetClassID() {    return EPDCLASSID_CEPDEVICENODE;   }
	virtual BSTR GetXmlElementKey()  {      return CEpDeviceXmlRWKeys::CEpDeviceNodeKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	LPVOID *m_pArrDatas;
	long   m_nArrDatas;

//私有成员变量访问方法
public:
	void InitArrDatas();
	long GetArrDatas()	{		return m_nArrDatas;		}
	CEpDeviceData* operator[] (long nIndex);
	CEpDeviceData* GetData(long nIndex);

};


//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharInterface.h  CCharInterface

#pragma once

#include "CharacteristicGlobal.h"


#include "CharInterfaceVariable.h"

class CCharInterface : public CExBaseList
{
public:
	CCharInterface();
	virtual ~CCharInterface();


//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARINTERFACE;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharInterfaceKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE,BOOL bCopyChildren=FALSE);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BOOL CanPaste(UINT nClassID);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long InsertToListCtrl(CListCtrl *pListCtrl);

//私有成员变量
private:

//私有成员变量访问方法
public:
	BOOL GetVariableValue(const CString &strVariable, CString &strValue);
	void InitVariableValues();
};


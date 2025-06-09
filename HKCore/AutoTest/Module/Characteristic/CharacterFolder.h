//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharacterFolder.h  CCharacterFolder

#pragma once

#include "CharacteristicGlobal.h"

#include "CharacteristicTmplate.h"

class CCharacterFolder : public CExBaseList
{
public:
	CCharacterFolder();
	virtual ~CCharacterFolder();
	

//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARFOLDER;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharacterFolderKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:
	CCharacteristic* FindCharTempByName(const CString &strName);
	CCharacteristic* FindCharTempByID(const CString &strID);
};


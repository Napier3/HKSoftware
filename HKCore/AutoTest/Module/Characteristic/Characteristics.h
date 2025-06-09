//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Characteristics.h  CCharacteristics

#pragma once

#include "CharacteristicGlobal.h"


#include "CharacteristicTmplate.h"

class CCharacteristics : public CExBaseList
{
public:
	CCharacteristics();
	virtual ~CCharacteristics();


//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARACTERISTICS;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharacteristicsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

//私有成员变量
private:

//私有成员变量访问方法
public:
	void InitVariableValues();
	void CalCharElement(CExBaseList *pDrawList);

	BOOL IsCharTempExist(CCharacteristic *pCharTmp);
	BOOL AddCharTempClone(CCharacteristic *pCharTmp);

	CCharacteristic* FindChar(CDvmData *pAttrs);

	//2021-9-17  初始化空的特性曲线
	void InitEmptyCharacter(const CString &strAxis);
	//2023-2-15  shaolei   通过id和index，结合查找特性曲线
	CCharacteristic* FindCharByID_Index(const CString &strID, const CString &strIndex);
};


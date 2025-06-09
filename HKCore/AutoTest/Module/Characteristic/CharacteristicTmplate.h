//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharacteristicTmplate.h  CCharacteristicTmplate

#pragma once

#include "CharacteristicGlobal.h"


#include "CharInterface.h"
#include "Characteristic.h"

class CCharacteristicTmplate : public CExBaseList
{
public:
	CCharacteristicTmplate();
	virtual ~CCharacteristicTmplate();

	long  m_nAutoClose;
	CString  m_strAxis;
	CString  m_strXMin;
	CString  m_strXMax;
	CString  m_strYMin;
	CString  m_strYMax;
	CString  m_strTestLineMode;

	
	double  m_fXMin;
	double  m_fXMax;
	double  m_fYMin;
	double  m_fYMax;

	BOOL  m_bXMin;
	BOOL  m_bXMax;
	BOOL  m_bYMin;
	BOOL  m_bYMax;

//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARACTERISTICTMPLATE;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharacteristicTmplateKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

//私有成员变量
private:
	CCharacteristic *m_pCharacteristic;
	CCharInterface *m_pCharacteristicInterface;

//私有成员变量访问方法
public:
	CCharInterface* DettachCCharInterface();
	CCharacteristic* GetCharacteristic();

private:
	CCharInterface* GetCharInterface();

	BOOL CalCharElementExpression(const CString &strExpress, double &dValue, BOOL bLogError);
	CCharacterArea* GetCharacterArea();
// 	CCharMacroDraws* GetCharMacroDraws();

	void InitVariableValues();
	void CalCharElement(CExBaseList *pDrawList);
	void CalTestLines(CExBaseList *pDrawList);

	void GetAllMacroTestLines(CExBaseList *pList);
};

void char_CChaTmplate_to_Characteristic(CCharacteristicTmplate *pCharTemplate, CCharacteristic* &pChar);
void char_CChaTmplate_to_Characteristic(CExBaseList *pList);

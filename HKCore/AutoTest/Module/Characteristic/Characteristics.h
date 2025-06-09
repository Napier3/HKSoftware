//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Characteristics.h  CCharacteristics

#pragma once

#include "CharacteristicGlobal.h"


#include "CharacteristicTmplate.h"

class CCharacteristics : public CExBaseList
{
public:
	CCharacteristics();
	virtual ~CCharacteristics();


//���غ���
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

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	void InitVariableValues();
	void CalCharElement(CExBaseList *pDrawList);

	BOOL IsCharTempExist(CCharacteristic *pCharTmp);
	BOOL AddCharTempClone(CCharacteristic *pCharTmp);

	CCharacteristic* FindChar(CDvmData *pAttrs);

	//2021-9-17  ��ʼ���յ���������
	void InitEmptyCharacter(const CString &strAxis);
	//2023-2-15  shaolei   ͨ��id��index����ϲ�����������
	CCharacteristic* FindCharByID_Index(const CString &strID, const CString &strIndex);
};


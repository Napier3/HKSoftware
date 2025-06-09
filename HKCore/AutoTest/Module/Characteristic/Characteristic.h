//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Characteristic.h  CCharacteristic

#pragma once

#include "CharacteristicGlobal.h"


#include "CharacterArea.h"
#include "CharInterface.h"

class CCharacteristic : public CExBaseList
{
public:
	CCharacteristic();
	virtual ~CCharacteristic();

	static CCharacteristic* _New(CBaseObject *pParent=NULL)
	{
		CCharacteristic *pNew = new CCharacteristic();
		pNew->SetParent(pParent);
		return pNew;
	}

	BOOL m_bOldVersion;

	long  m_nAutoClose;
	CString  m_strAxis;
	CString  m_strXMin;
	CString  m_strXMax;
	CString  m_strYMin;
	CString  m_strYMax;
	CString  m_strTestLineMode;
	CString	 m_strIndex;	//20210913 sf  ��������õõ����Զ�������ʱ�ò���

	double  m_fXMin;
	double  m_fXMax;
	double  m_fYMin;
	double  m_fYMax;

	BOOL  m_bXMin;
	BOOL  m_bXMax;
	BOOL  m_bYMin;
	BOOL  m_bYMax;

	//2020-3-13  �������߱�ʾ�����ڼ����������ߣ���ʱ���ã�����Ϊ����������
	//���������Ա�����Ŀ�ģ���Ϊ���ܹ�����֮ǰ�İ汾
	CDvmData *m_pCharAttrs;

//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARACTERISTIC;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharacteristicKey();     }
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
	CCharacterArea *m_pArea;
	CCharInterface *m_pCharacteristicInterface;

//˽�г�Ա�������ʷ���
public:
	BOOL IsAutoclose()	{	return m_nAutoClose;	}
	CCharacterArea* GetCharacterArea();
	CCharInterface* GetCharInterface();
	BOOL CalCharElementExpression(const CString &strExpress, double &dValue, BOOL bLogError);
	void AttachCCharInterface(CCharInterface *pCharInterface);

	void InitVariableValues();
	void CalCharElement(CExBaseList *pDrawList);
	void CalTestLines(CExBaseList *pDrawList);
	void GetAllMacroTestLines(CExBaseList *pList);
	BOOL CmpAttrs(CDvmData *pAttrs);
	CDvmData* GetAttrs(BOOL bCreateNew);

	//���������������Բ�����Ŀ�Ľӿ�
	//2020-3-19
	void DeleteAllTestLines();
	void AddTestLines(CXDrawData_Line *pValRange, double dLenStep);
	void AddTestLine(CXDrawData_Line *pCurrValLine);

	//2020-08-07  lijunqing
	CXDrawList* InitCharDrawElement_ForDraw();
	CXDrawList* InitCharDrawElement_ForCalOnly();

	//2022-7-24  lijunqing
	void InitAllMacroTestLinesID();
	CCharElementTestLine* FindTestLine(const CString &strID);
};


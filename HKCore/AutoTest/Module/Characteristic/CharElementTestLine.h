//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharElementTestLine.h  CCharElementTestLine

#pragma once

#include "CharacteristicGlobal.h"
#include "../../../Module/XDrawBase/XDrawList.h"

//2022-7-24  lijunqing �ƶ���AutoTestGlobalDefine.h
// #define TESTLINE_ACT_STATE_NONE     -255
// #define TESTLINE_ACT_STATE_ACT      1
// #define TESTLINE_ACT_STATE_NOACT    0

class CCharElementTestLine : public CExBaseObject
{
public:
	CCharElementTestLine();
	virtual ~CCharElementTestLine();


	////////���������/////////////////////
	//�����߶���ģʽ��sys��(user) 
	CString  m_strType;      

	//λ�ñ�����ϵ��sys=���ţ�1~TestPoints��user=��λ�ã�0<ֵ��Χ<1
	double  m_fPos;

	 //��ת�ĽǶ�
	double  m_fRotateAngle; 

	//�����߽Ƕȶ��壺�գ���ʾ���߻��߽�ƽ���ߣ��Ƕȼ��㹫ʽ
	//��ʼ���x��yλ�ü���ű���
	CString m_strAngleDef;   
	CString m_strPosScpt;

	//�������ʵ��ֵ��ִ�в���ʱ����ʱ��ֵ
	double  m_fXb;
	double  m_fYb;
	double  m_fXe;
	double  m_fYe;
	double  m_fXset;
	double  m_fYset;

	long    m_nActState;
	double  m_fXact;
	double  m_fYact;

	//�����Ĳ�����Ŀ
	CExBaseObject *m_pMacroTestItemRef;

	long m_nTestLineID;
//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTTESTLINE;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementTestLineKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

// 	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
// 	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	long GetXDrawElement(CXDrawList *pDrawList);
	BOOL IsTestLineUserDef()	{	return m_strType == CHAR_TEST_LINE_TYPE_USER;	}
	BOOL IsTestLineSys()	{	return m_strType == CHAR_TEST_LINE_TYPE_SYS;	}
};


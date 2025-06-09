//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementTestLine.h  CCharElementTestLine

#pragma once

#include "CharacteristicGlobal.h"
#include "../../../Module/XDrawBase/XDrawList.h"

//2022-7-24  lijunqing 移动到AutoTestGlobalDefine.h
// #define TESTLINE_ACT_STATE_NONE     -255
// #define TESTLINE_ACT_STATE_ACT      1
// #define TESTLINE_ACT_STATE_NOACT    0

class CCharElementTestLine : public CExBaseObject
{
public:
	CCharElementTestLine();
	virtual ~CCharElementTestLine();


	////////定义测试线/////////////////////
	//测试线定义模式：sys，(user) 
	CString  m_strType;      

	//位置比例关系：sys=点编号，1~TestPoints；user=线位置，0<值范围<1
	double  m_fPos;

	 //旋转的角度
	double  m_fRotateAngle; 

	//测试线角度定义：空，表示垂线或者角平分线；角度计算公式
	//起始点的x、y位置计算脚本，
	CString m_strAngleDef;   
	CString m_strPosScpt;

	//计算出来实际值，执行测试时的临时数值
	double  m_fXb;
	double  m_fYb;
	double  m_fXe;
	double  m_fYe;
	double  m_fXset;
	double  m_fYset;

	long    m_nActState;
	double  m_fXact;
	double  m_fYact;

	//关联的测试项目
	CExBaseObject *m_pMacroTestItemRef;

	long m_nTestLineID;
//重载函数
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

//私有成员变量
private:

//私有成员变量访问方法
public:
	long GetXDrawElement(CXDrawList *pDrawList);
	BOOL IsTestLineUserDef()	{	return m_strType == CHAR_TEST_LINE_TYPE_USER;	}
	BOOL IsTestLineSys()	{	return m_strType == CHAR_TEST_LINE_TYPE_SYS;	}
};


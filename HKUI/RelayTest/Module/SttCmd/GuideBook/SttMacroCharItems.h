//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMacroCharItems.h  CSttMacroCharItems

#pragma once

#include "../SttCmdDefineGlobal.h"
#include "SttItemBase.h"
#include "SttMacroTest.h"
//#include "SttContents.h"


class CSttCharacteristic : public CExBaseList
{
public:
	CSttCharacteristic();
	virtual ~CSttCharacteristic();

	static CSttCharacteristic* _New(CBaseObject *pParent=NULL)
	{
		CSttCharacteristic *pNew = new CSttCharacteristic();
		pNew->SetParent(pParent);
		return pNew;
	}

	long  m_nAutoClose;
	CString  m_strAxis;
	CString  m_strXMin;
	CString  m_strXMax;
	CString  m_strYMin;
	CString  m_strYMax;
	CString  m_strTestLineMode;
	CString	 m_strIndex;	//20210913 sf  单机软件用得到，自动测试暂时用不到

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
	virtual UINT GetClassID() {    return STTGBXMLCLASSID_CSTTCHARACTERISTIC;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttCharacteristicKey();     }
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

	//私有成员变量访问方法
public:
};



class CSttMacroCharItems : public CSttItemBase
{
public:
	CSttMacroCharItems();
	virtual ~CSttMacroCharItems();

//重载函数
public:
	virtual UINT GetClassID() {    return STTGBXMLCLASSID_CSTTMACROCHARITEMS;   }
	virtual BSTR GetXmlElementKey();
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

	virtual long GetItemTestCount();
//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
// 	//2023-3-21 zhouhj 将特性曲线放入链表中
// 	void CloneCharacteristics(CExBaseList *pCharacteristics);
};


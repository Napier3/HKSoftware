//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharTestObjects.h  CCharTestObjects

#pragma once

#include "CharacteristicGlobal.h"
#include "CharTestPoints.h"

class CCharTestObjects : public CExBaseList
{
public:
    CCharTestObjects();
    virtual ~CCharTestObjects();

//重载函数
public:
    virtual UINT GetClassID() {    return CHARCLASSID_CCHARTESTOBJECTS;   }
    virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharTestObjectsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE,BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InitAfterRead();
	void InitCharDrawTestObj_ForDraw(CExBaseList *pDrawList, int nFaultType, CExBaseObject *pCurTestObj, int nTestObjDrawMode);   //20240822 wanmj 添加m_pTestObjects的测试线到drawlist

//私有成员变量
private:
	CCharTestPoints *m_pTestPoints;
	
//私有成员变量访问方法
public:
    CCharTestPoints* GetCharTestPoints()	{	return m_pTestPoints;	}
	
};


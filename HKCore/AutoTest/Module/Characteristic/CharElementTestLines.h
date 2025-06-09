//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementTestLines.h  CCharElementTestLines

#pragma once

#include "CharacteristicGlobal.h"
#include "XCharElementTestPoints.h"

class CCharElementTestLines : public CExBaseList
{
public:
	CCharElementTestLines();
	virtual ~CCharElementTestLines();

//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTTESTLINES;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementTestLinesKey();     }
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

//私有成员变量
private:
	CXCharElementTestPoints *m_pTestPoints;
	
//私有成员变量访问方法
public:
	CXCharElementTestPoints* GetCharElementTestPoints()	{	return m_pTestPoints;	}
	
};


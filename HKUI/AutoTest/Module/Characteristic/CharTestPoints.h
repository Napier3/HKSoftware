//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharTestPoints.h  CCharTestPoints

#pragma once

#include "CharacteristicGlobal.h"
#include "../../../Module/XDrawBase/XDrawList.h"

class CCharTestPoints : public CExBaseObject
{
public:
    CCharTestPoints();
    virtual ~CCharTestPoints();

	CString  m_strFrom;
	CString  m_strTo;
	CString  m_strStep;

	double m_dFrom;
	double m_dTo;
	double m_dStep;
	
//重载函数
public:
    virtual UINT GetClassID() {    return CHARCLASSID_CCharElementPointS;   }
    virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementPointsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

//私有成员变量
private:

//私有成员变量访问方法
public:

};
class CCharTestPoint : public CExBaseObject
{
public:
	CCharTestPoint();
	virtual ~CCharTestPoint();

	double m_fX;//测试点坐标
	double m_fY;

	long  m_nFaultType;//保存测试项故障类型
	long  m_nZoneType;//保存测试项段号，对应非距离类区段为-1,缺省为-1
	long  m_nTestState; //当前测试项的状态   初始/选中/合格/不合格/测试完成
	CXDrawPoint *m_pDrawPointRef;//20240924 luozibing 最新添加的测试点

	//重载函数
public:
	virtual UINT GetClassID() { return CHARCLASSID_CCHARTESTPOINT; }
	virtual BSTR GetXmlElementKey()  { return CCharacteristicXmlRWKeys::CCharTestPointKey(); }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	//私有成员变量
private:

	//私有成员变量访问方法
public:
	void SetTestPoint(CString strIDPath, float fX, float fY, int  nFaultType = -1, int nTestState = -1, int  nZoneType = -1);
	long GetXDrawElement(CXDrawList *pDrawList);

};

//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PxPkgDataBase.h  CPxPkgDataBase

#pragma once

#include "TcpEdgePkgGlobal.h"
#include "TcpEdgePkgData.h"
#include "../../../../Module/xml/JSON/CJSON.h"
#include "../../../../Module/xml/JsonRW.h"

class CPxPkgDataBase : public CTcpEdgePkgData
{
public:
	CPxPkgDataBase();
	virtual ~CPxPkgDataBase();

	CString m_strCmdID; //用于表示当前报文ID


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CPXPKGDATABASE;   }
	virtual BSTR GetXmlElementKey()  {      return CTcpEdgePkgXmlRWKeys::CPxPkgDataBaseKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CTcpEdgePkgXmlRWKeys::CPxPkgDataBaseKey();     }

public:
	//判断百分比类的参数格式和范围是否正确
	virtual QString CheckRangePer(CString strPkgID, CString strObjectID, CString strNodeID, CString strNode);

	//判断日期是否合法,格式是否正确
	virtual QString CheckTimeFormat(CString strPkgID, CString strArrayID1, CString strArrayID2, CString strArrayID3, CString strNodeID, CString strTime);
	virtual QString CheckDateLegal(CString strPkgID, CString strArrayID1, CString strArrayID2, CString strArrayID3, CString strNodeID, long year, long month, long day, long nHour, long nMinute, long nSecond, long nMillisecond);

};


class CPxPkgDataBaseArrayObj
{
public:
	CPxPkgDataBaseArrayObj(){}
	virtual ~CPxPkgDataBaseArrayObj(){}

public:
	virtual long XmlWriteChildrenEx(CPxPkgDataBase* pData, CJSON* pJson);
	virtual long XmlWriteChildrenEx(CPxPkgDataBase* pData, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
};
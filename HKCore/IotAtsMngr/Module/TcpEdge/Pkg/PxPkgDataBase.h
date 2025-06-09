//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

	CString m_strCmdID; //���ڱ�ʾ��ǰ����ID


//���غ���
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
	//�жϰٷֱ���Ĳ�����ʽ�ͷ�Χ�Ƿ���ȷ
	virtual QString CheckRangePer(CString strPkgID, CString strObjectID, CString strNodeID, CString strNode);

	//�ж������Ƿ�Ϸ�,��ʽ�Ƿ���ȷ
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
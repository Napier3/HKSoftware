//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapDeviceModel.h  CEpCapDeviceModel

#pragma once

#include "EpCapDeviceModelGlobal.h"


#include "EcdmProtocolAddrs.h"
#include "EcdmDatas.h"

class CEpCapDeviceModel : public CExBaseList
{
public:
	CEpCapDeviceModel();
	virtual ~CEpCapDeviceModel();

	long  m_nYxAddr;
	long  m_nYcAddr;
	long  m_nYtAddr;

//重载函数
public:
	virtual UINT GetClassID() {    return ECDMCLASSID_CEPCAPDEVICEMODEL;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapDeviceModelXmlRWKeys::CEpCapDeviceModelKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InitAfterRead();

//私有成员变量
private:
	CEcdmDatas *m_pEcdmDatas;
	CEcdmProtocolAddrs *m_pEcdmProtocolAddrs;

	void InitAllDatasOffset();

//私有成员变量访问方法
public:
	CEcdmDatas* GetEcdmDatas()	{	return m_pEcdmDatas;	}
	BOOL OpenDeviceModelFile(const CString &strFile);
	BOOL SaveDeviceModelFile();

	CEcdmProtocolAddr* FindEcdmProtocolAddr(const CString &strID)
	{
		if (m_pEcdmProtocolAddrs != NULL)
		{
			return (CEcdmProtocolAddr*)m_pEcdmProtocolAddrs->FindByID(strID);
		}
		else
		{
			return NULL;
		}
	}

	CEcdmData* FindData(long nDataType, long nItemIndex)
	{
		if (m_pEcdmDatas != NULL)
		{
			return m_pEcdmDatas->FindData(nDataType, nItemIndex);
		}
		else
		{
			return NULL;
		}
	}

	void GetDatas(CEcdmDatas &oDatas, long nType)	{	m_pEcdmDatas->GetDatas(oDatas, nType);	}

};

class CEpCapDeviceModels : public CExBaseList
{
public:
	CEpCapDeviceModels();
	virtual ~CEpCapDeviceModels();

public:
	CEpCapDeviceModel* AddDeviceModels(const CString &strFile);
};
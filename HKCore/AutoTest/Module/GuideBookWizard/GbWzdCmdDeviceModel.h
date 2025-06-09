#pragma once

#include "GbWzdCmd.h"

class CGbWzdCmdDeviceModel : public CGbWzdCmd
{
public:
	CGbWzdCmdDeviceModel();
	virtual ~CGbWzdCmdDeviceModel();

	virtual UINT GetClassID()			{		return GBWZDCLASSID_DEVICEMODEL;	} 
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey() ;

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();

	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL IsCmdFinish();


public:
	virtual BOOL Execute(DWORD dwExecMode);
	virtual void GetCmdInfor(CString &strText);
	long m_nGbWzdCmdDeviceModelIndex;

public:
	CString m_strDvmName;
	CString m_strDvmID;
	CString m_strFactory;
	long m_nIsTimeSetsUnit_ms;   //时间定值的单位是否为s
	CString m_strDeviceType;						//型号
	CCpus* m_pCpus;
	CCharacteristics* m_pCharacteristics;   //特性曲线

	void SetCpus(CCpus *pCpus);
	void SetCharacteristics(CCharacteristics *pCharacteristics);
	void InitByDevice(CDevice *pDevice);

	void InitDevice(CDevice *pDevice);

protected:
	void FreeCpus()
	{
		if (m_pCpus != NULL)
		{
			Delete(m_pCpus);
			m_pCpus = NULL;
		}
	}
	void FreeCharacteristics()
	{
		if (m_pCharacteristics != NULL)
		{
			Delete(m_pCharacteristics);
			m_pCharacteristics = NULL;
		}
	}
};
//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfg91StatusDataSet.h  CIecCfg91StatusDataSet

#pragma once

#include "IecCfgDataMngrGlobal.h"


#include "IecCfg91StatusDataSetCh.h"

class CIecCfg91StatusDataSet : public CExBaseList
{
public:
	CIecCfg91StatusDataSet();
	virtual ~CIecCfg91StatusDataSet();


// 	DWORD  m_dwLDName;
// 	DWORD  m_dwLNName;
// 	DWORD  m_dwDataSetName;
// 	DWORD  m_dwSmprate;
// 	DWORD  m_dwVersion;
	long  m_nValid;
	long  m_nOldData;
	long  m_nFailure;
	long  m_nOscillatory;
	long  m_nInconsistent;
	long  m_nLeapSecond;
	long  m_nClockFailure;
	long  m_nClockNotSynchronized;
//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG91STATUSDATASET;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfg91StatusDataSetKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InitAfterRead();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	void SetChCount(long nCount);
	DWORD Get_Q();
	DWORD Get_S_SetByUser();
};


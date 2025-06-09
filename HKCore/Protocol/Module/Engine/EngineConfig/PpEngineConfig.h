//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PpEngineConfig.h  CPpEngineConfig

#pragma once

#include "PpEngineConfigGlobal.h"


class CPpEngineConfig : public CExBaseList
{
public:
	CPpEngineConfig();
	virtual ~CPpEngineConfig();

	long m_nDebugMode;
	long m_nLogDataBind;
	long m_nLogPkgInfor;
	long m_nLogPkg;
	long m_nLogDebugInfor;
	long m_nNoChangeWhenSame;

//���غ���
public:
	virtual UINT GetClassID() {    return MSCFGCLASSID_CPPENGINECONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CPpEngineConfigXmlRWKeys::CPpEngineConfigKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InitAfterRead();

//˽�г�Ա����
private:
	CString GetPpEngineConfigFile();

//˽�г�Ա�������ʷ���
public:
	void ReadPpEngineConfig();
	void SavePpEngineConfig();
};


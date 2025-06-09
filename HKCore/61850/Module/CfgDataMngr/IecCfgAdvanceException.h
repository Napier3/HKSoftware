//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgAdvanceException.h  CIecCfgAdvanceException

#pragma once

#include "IecCfgDataMngrGlobal.h"

#define CFG_EXCEPTION_NONE  0
#define CFG_EXCEPTION_XHPC  1
#define CFG_EXCEPTION_DZCS  2
#define CFG_EXCEPTION_TBCS  3
#define CFG_EXCEPTION_PZCS  4
#define CFG_EXCEPTION_XHTB  5
#define CFG_EXCEPTION_CZCS  6


class CIecCfgAdvanceException : public CExBaseObject
{
public:
	CIecCfgAdvanceException();
	virtual ~CIecCfgAdvanceException();


	long  m_nExceptionType;
	long  m_nSerialNumErr;
	long  m_nFrameLossGap;
	long  m_nFrameLossPoints;
	long  m_nSynGap;
	long  m_nSynPoints;
	long  m_nQualityGap;
	long  m_nQualityPoints;
	long  m_nQualityValue;
	long  m_nSerialJmpGap;
	long  m_nSerialJmpPoints;
	long  m_nSerialJmpStep;
	long  m_nFaultValGap;
	long  m_nFaultValPoints;
	DWORD  m_nFaultValRate;
	long  m_nExceptionBeginIndex;
	long  m_nExceptionLimit;
	long  m_nExceptionCount;
//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGADVANCEEXCEPTION;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgAdvanceExceptionKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	DWORD GetFaultType();
	DWORD GetFaultInteval();
	DWORD GetFaultCount();
	DWORD GetFaultValue();
	DWORD GetFaultChannels(BYTE *byteChs);
};


#pragma once
#include "ExBaseList.h"
#include "BbVariables.h"
#include "PpScript.h"
#include "PpTtPackage.h"
#include "ByteBlocks.h"
#include "BbVariables.h"
#include "DataQueryBindStatck.h"

#include "PpPackageText.h"

//class CPpTtPackage;

class CPpPackage :	public CExBaseList
{
public:
	CPpPackage(void);
	virtual ~CPpPackage(void);

	//��Լ���ķ��ͻ��߽��ܵ�ʱ��
	SYSTEMTIME m_tm;
	DWORD m_dwTickCount;
	BOOL  m_bValid;
public:
	CString m_strTID;	// ��Ӧ��ģ��֡

	CBbVariables *m_pDataInterface;
	CBbVariables *m_pVariables;
	CPpScript *m_pInitScript;
	CPpScript *m_pEndScript;
	CPpTtPackage *m_pTtPackage;

	long m_nPkgLen;
	long m_nPkgNum;
	
	BOOL AddSystemVariables();

	void SetPkgLength(long nLen)
	{
		m_nPkgLen = nLen;

		if (m_pTtPackage != NULL)
		{
			m_pTtPackage->m_nPkgLen = nLen;
		}
	}

	void RunInitScript();
	void RunEndScript();

protected:
	CExBaseList m_oAllVariables;		//��ʱ����������һ֡�ж�������б�����DataInterface
	CDataQueryBindStatck m_oDataQuery;

#ifdef _PP_DEV_MODE_
	CPpPackageText *m_pPpPackageText;
	CPpPackageTexts *m_pPpPackageTexts;
#endif

public:
	virtual UINT GetClassID()				{        return PPCLASSID_PPPAKAGE;													}
	virtual BSTR GetXmlElementKey()	{      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackagesKey;		}

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	// 	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual void InitAfterRead();

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

#ifdef _PP_DEV_MODE_
	CPpPackageText* GetPackageText();
	CPpPackageTexts* GetPackageTexts();
#endif

public:
	//�ֽڿ�Ľ���		����Ľ�������������ִ�н���
	virtual DWORD Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)			{		return PpParseError();		}

	//�ֽڿ��ƥ��		��Ҫ���ڽ���
	virtual DWORD Match(PACKAGEBUFFERPOS &oPkgBufPos)										{		return PpParseError();		}

	//�ֽڿ������
	virtual DWORD Produce(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)		{		return PpParseError();		}

	void GetAllVariables(CExBaseList &oDestList);
	void GetDataInterface(CExBaseList &oDestList);
	long InitOwnAllVariables(BOOL bIncludeTtPkg=FALSE);

	void GetPackageVaraibles(CExBaseList &oDestList, BOOL bClone=TRUE);   //��ȡ������ݽӿڡ�����������ֽڿ������

	//ȫ��������صĽӿ�
	CExBaseList* GetAllVariables()		{		return &m_oAllVariables;		}
	CBbVariable* FindVariableByName(const CString &strName);
	CBbVariable* FindVariableByID(const CString &strID);
	BOOL GetVariableValue(const CString &strVariable, long &nValue);
	BOOL GetVariableValue(const CString &strVariable, CString &strValue);
	BOOL SetVariableValue(const CString &strVariable, const long &nValue);
	BOOL SetVariableValue(const CString &strVariable, const double &dValue);
	BOOL SetVariableValue(const CString &strVariable, const CString &strValue);
	CDataQueryBindStatck* GetDataQueryBindStatck()   {      return &m_oDataQuery;  }

	//��֤m_pTtPackage�Ƿ���Ч
	BOOL VerifyTtPackage();
	void InitTtPackage();
	
	void InitPackageTime()
	{
		::GetLocalTime(&m_tm);
		m_dwTickCount = ::GetTickCount();
	}

	void InitPackageTime(const SYSTEMTIME &tm, DWORD dwTickCount)
	{
		m_tm = tm;
		m_dwTickCount = dwTickCount;
	}

	void GetTmString(CString &strTm)
	{
		strTm.Format(_T("%d-%d-%d %d:%d:%d %d"), m_tm.wYear, m_tm.wMonth, m_tm.wDay
			, m_tm.wHour, m_tm.wMinute, m_tm.wSecond, m_tm.wMilliseconds);
	}
#ifdef _DVM_VALUE_USE_CHAR_
	void GetTmString(wchar_t *strTm);
#endif
};


CPpPackage* PpFindPackageByID(const CString &strPackageID, CExBaseObject *pPpData);
CExBaseObject* PpFindPackage(CExBaseObject* pPpData);

//����Data���ڵ�Package�ı���
CBbVariable* PpFindVariableByID(CExBaseObject* pPpCurrData, const CString &strID);
void PpUpdatePackageAllVariables(CExBaseObject* pPpCurrData);

BOOL PpIsPackage(CExBaseObject *pObj);
BOOL PpIsPackage(UINT nClassID);

DWORD Pp_Check(CExBaseList *pDetail, CExBaseObject *pChkByteBlock);
DWORD Pp_SumCheck(CExBaseList *pDetail, CExBaseObject *pChkByteBlock);
DWORD Pp_Crc16Check(CExBaseList *pDetail, CExBaseObject *pChkByteBlock, WORD wValue=0xFFFF);

DWORD Pp_Crc16CheckTable(CExBaseList *pDetail, CExBaseObject *pChkByteBlock, WORD wValue=0);



inline BOOL Pp_IsParsePkg(CExBaseObject *pPpData)
{
	if (pPpData == NULL)
	{
		return FALSE;
	}

	UINT nClassID = pPpData->GetClassID();

	if (!PpIsPackage(nClassID))
	{
		return FALSE;
	}

	return (nClassID == PPCLASSID_PPPARSEPACKGE);
}


inline BOOL Pp_IsProducePkg(CExBaseObject *pPpData)
{
	if (pPpData == NULL)
	{
		return FALSE;
	}

	UINT nClassID = pPpData->GetClassID();

	if (!PpIsPackage(nClassID))
	{
		return FALSE;
	}

	return (nClassID == PPCLASSID_PPPRODUCEPACKGE);
}


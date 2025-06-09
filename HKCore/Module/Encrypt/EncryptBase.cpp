// EncryptBase.cpp: implementation of the CEncryptBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EncryptBase.h"
#include "..\API\GloblaDrawFunctions.h"
#include "GetDiskID32.h"
#include "..\..\Module\BaseClass\RegKeyEdit.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CEncryptCode::CEncryptCode()
{

}

CEncryptCode::~CEncryptCode()
{

}

long CEncryptCode::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strCpu);
		BinarySerializeCalLen(oBinaryBuffer, m_strHdCode);
		BinarySerializeCalLen(oBinaryBuffer, m_strMac);
		BinarySerializeCalLen(oBinaryBuffer, m_strSN);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strCpu);
		BinarySerializeRead(oBinaryBuffer, m_strHdCode);
		BinarySerializeRead(oBinaryBuffer, m_strMac);
		BinarySerializeRead(oBinaryBuffer, m_strSN);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strCpu);
		BinarySerializeWrite(oBinaryBuffer, m_strHdCode);
		BinarySerializeWrite(oBinaryBuffer, m_strMac);
		BinarySerializeWrite(oBinaryBuffer, m_strSN);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

inline void Encrypt_InitEncryptFileVersion(char *pszPrefix, DWORD &dwVersion)
{
	strcpy(pszPrefix, "ATS.REG");
	dwVersion = g_dwEncryptCurrVersion;
}


CEncryptBase::CEncryptBase()
{
	m_bRegistered = FALSE;
	m_nMaxUseCount = 0;
	m_nCurrUseCount = 0;
	m_dwUseDog = 1;
	m_dwDevStudio = 1;
	m_dwAutoTest = 1;
// 	m_dwBeginTime = 0;
// 	m_dwEndTime = 0;
// 	SetMode(Encrypt_Mode_Develop);
}

CEncryptBase::~CEncryptBase()
{
	
}


void CEncryptBase::SetSNEx(const CString &strSN)
{
	SetSN(strSN);

	POS pos = GetHeadPosition();
	CEncryptCode *pCode = NULL;

	while (pos != NULL)
	{
		pCode = (CEncryptCode *)GetNext(pos);
		pCode->m_strSN = CodeString(pCode->m_strRegCode);
	}
}

void CEncryptBase::SetDemoTemplate(const CString &str, long nIndex)
{
	if (nIndex > 4)
	{
		return;
	}

	m_strDemoTemplate[nIndex] = CodeString(str);
}

void CEncryptBase::SetUseTimeLong(long nValue)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);
	m_strUseTimeLong = CodeString(strValue);
}

void CEncryptBase::SetTimeUsed(long nValue)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);
	m_strTimeUsed= CodeString(strValue);
}

long CEncryptBase::GetUseTimeLong()
{
	CString strVal;
	strVal = DisCodeString(m_strUseTimeLong);

	return CString_To_long(strVal);
}

long CEncryptBase::GetTimeUsed()
{
	CString strVal;
	strVal = DisCodeString(m_strUseTimeLong);

	return CString_To_long(strVal);
}

BOOL CEncryptBase::IsDemo()
{
	CString strMode = DisCodeString(m_strMode);

	return strMode == _T("demo");
}

BOOL CEncryptBase::CanUseTemplate(const CString &strTempate)
{
	CString strTemp = DisCodeString(m_strUserCode);
	return TRUE;
}

BOOL CEncryptBase::IsEncrypt()
{
	CString strCode;
	CString strMachine;

	strMachine = GetMachineCode();
	strCode = GetRegisterCode(strMachine);

	if (m_strSN.Compare(strCode) != 0)
	{
		m_bRegistered = FALSE;
	}
	else
	{
		m_bRegistered = TRUE;
	}

	return m_bRegistered;
}

BOOL CEncryptBase::IsEncrypt(CEncryptCode *pCode)
{
	CString strCode;
	CString strMachine;

	strMachine = GetMachineCode(pCode);
	strCode = GetRegisterCode(strMachine);

	if (m_strSN.Compare(strCode) != 0)
	{
		m_bRegistered = FALSE;
	}
	else
	{
		m_bRegistered = TRUE;
	}

	return m_bRegistered;
}


BOOL CEncryptBase::CanUseAutoTest()
{
	return (m_dwAutoTest > 0);
}

BOOL CEncryptBase::CanUseDevStudio()
{
	return (m_dwDevStudio > 0);
}

void CEncryptBase::IncreaseTimeUse(long nTimeAdd)
{
	long nVal = GetTimeUsed();
	nVal += nTimeAdd;
	SetTimeUsed(nVal);

	SaveEncryptFile();
}

CString CEncryptBase::CodeString(const CString &strText)
{
	char *pBufferSrc = NULL;
	char *pBufferDest = NULL;

	if (strText.GetLength() == 0)
	{
		return strText;
	}

	CString_to_char(strText, &pBufferSrc);
	long nLenSrc = strlen(pBufferSrc);
	long nLenDest = nLenSrc * 4 + 10;
	pBufferDest = new char[nLenDest];
	ZeroMemory(pBufferDest, nLenDest);
	ValueToHex((BYTE*)pBufferSrc, nLenSrc, pBufferDest, FALSE, FALSE);
	char *p = pBufferDest;
	char *pEnd = pBufferDest +nLenDest;
	char ch;

	while (p < pEnd)
	{
		if (*p == 0 || *(p+1) == 0)
		{
			break;
		}

		ch = *p;
		*p = *(p+1);
		*(p+1) = ch;

		p += 2;
	}

	CString strRet;
	strRet = pBufferDest;
	delete pBufferDest;
	delete pBufferSrc;

	return strRet;
}

CString CEncryptBase::DisCodeString(const CString &strText)
{
	char *pBufferSrc = NULL;
	char *pBufferDest = NULL;

	if (strText.GetLength() <= 1)
	{
		return _T("");
	}

	CString_to_char(strText, &pBufferSrc);
	long nLen = strlen(pBufferSrc);
	char *p = pBufferSrc;
	char *pEnd = pBufferSrc +nLen;
	char ch;

	while (p < pEnd)
	{
		if (*p == 0 || *(p+1) == 0)
		{
			break;
		}

		ch = *p;
		*p = *(p+1);
		*(p+1) = ch;

		p += 2;
	}

	pBufferDest = new char[nLen];
	ZeroMemory(pBufferDest, nLen);
	HexToValue(pBufferSrc, (BYTE*)pBufferDest, 0);

	CString strRet;
	strRet = pBufferDest;
	delete pBufferDest;
	delete pBufferSrc;

	return strRet;
}

CString CEncryptBase::GetRegisterCode(const CString &strMachine)
{
	CString strRet, strTmp, str;
	BYTE xor=0, sum=0, sub=0, sft_l=0, sft_r=0, mul=1, mass=0, oth=0;

	strTmp = strMachine;

	for (int i=0; i<strMachine.GetLength(); i++)
	{
		xor ^= strMachine.GetAt(i) + 0x0a;
		sum += strMachine.GetAt(i) & 0x7e;
		sub -= strMachine.GetAt(i);
		sft_l += _rotl(strMachine.GetAt(i), i);
		sft_r += _rotr(strMachine.GetAt(i), i);
		mul += strMachine.GetAt(i)*strMachine.GetAt(i) + strMachine.GetAt(i)*3 - i;
		mass += strMachine.GetAt(i) + (sum^xor) + (sft_l*sft_r);
		oth += sub*sum + mass*2 + (i%6) + (mul&0x4e);
	}

	// 1
	strTmp.Format(_T("%02X"), sft_r);
// 	if (strTmp.GetAt(0)>47 && strTmp.GetAt(0)<53)  // 0~4
// 	{
// 		strTmp.SetAt(0, strTmp.GetAt(0)+36);
// 	}
	strRet += strTmp;

	// 2
	strTmp.Format(_T("%02X"), mul);
// 	if (strTmp.GetAt(1)>64 && strTmp.GetAt(1)<71)  // A~F
// 	{
// 		strTmp.SetAt(1, strTmp.GetAt(1)+6);
// 	}
	strRet += strTmp + _T("-");

	// 3
	strTmp.Format(_T("%02X"), sum);
	strRet += strTmp;

	// 4
	strTmp.Format(_T("%02X"), sft_l);
	strRet += strTmp + _T("-");

	// 5
	strTmp.Format(_T("%02X"), mass);
// 	if (strTmp.GetAt(0)>47 && strTmp.GetAt(0)<58)  // 0~4
// 	{
// 		strTmp.SetAt(0, strTmp.GetAt(0)+34);
// 	}
// 	if (strTmp.GetAt(1)>64 && strTmp.GetAt(1)<71)  // A~F
// 	{
// 		strTmp.SetAt(1, strTmp.GetAt(1)-17);
// 	}
	strRet += strTmp;

	// 6
	strTmp.Format(_T("%02X"), xor);
// 	if (strTmp.GetAt(0)>52 && strTmp.GetAt(0)<58)  // 5~9
// 	{
// 		strTmp.SetAt(0, strTmp.GetAt(0)+23);
// 	}
	strRet += strTmp + _T("-");

	// 7
	strTmp.Format(_T("%02X"), oth);
	strRet += strTmp;

	// 8
	strTmp.Format(_T("%02X"), sub);
	strRet += strTmp;

	return strRet;
}

CString CEncryptBase::GetRegisterCodeEx(const CString &strMachine)
{
	CString strCode;

	POS pos = GetHeadPosition();
	CEncryptCode *pCode = NULL;

	while (pos != NULL)
	{
		pCode = (CEncryptCode *)GetNext(pos);
		strCode = GetMachineCode(pCode);
		pCode->m_strRegCode = GetRegisterCode(strCode);
	}

	strCode = GetRegisterCode(strMachine);

	return strCode;
}

CString CEncryptBase::CalMachineCode()
{
	CString strMachineCode;
	CString strRet;

	POS pos = GetHeadPosition();
	CEncryptCode *pCode = NULL;

	if (pos == NULL)
	{
		return _T("");
	}

	pCode = (CEncryptCode *)GetNext(pos);
	strRet = pCode->m_strHdCode;
	strRet += pCode->m_strCpu;
	strRet += pCode->m_strMac;
	pCode->m_strRegCode = GetMachineCode(pCode);

	while (pos != NULL)
	{
		pCode = (CEncryptCode *)GetNext(pos);
		pCode->m_strRegCode = GetMachineCode(pCode);
		strRet += pCode->m_strMac;
	}

	strMachineCode = GetRegisterCode(strRet);

	return strMachineCode;
}

CString CEncryptBase::GetMachineCode()
{
	DeleteAll();

	CSystemCode code;
	CString strRet, strTmp, str;
	CString strHdCode, strCpu, strMac;

	//code.GetHardDiscCode();
	UINT i = 0;
	int j = 0;

// 	for (i=8; i<code.uSystemInfoLen; i++)
// 	{
// 		strTmp.Format(_T("%02X"), code.szSystemInfo[i]);
// 
// 		strHdCode += strTmp;
// 	}
	CGetDiskID32 oDiskID32;
	oDiskID32.GetDiskID32();
	strHdCode = oDiskID32.GetDiskID32Ex();

	strRet += strHdCode;
// 	for (j=0; j<str.GetLength(); j++)
// 	{
// 		if (j<12 || j>str.GetLength()-13)
// 			strRet += str.GetAt(j);
// 	}

	code.GetCPUCode();
	//str.Empty();
	for (i=2; i<code.uSystemInfoLen; i++)
	{
		strTmp.Format(_T("%02X"), code.szSystemInfo[i]);	
		strCpu += strTmp;
	}

	strRet += strCpu;
// 	for (j=0; j<str.GetLength(); j++)
// 	{
// 		if (j<4 || j>str.GetLength()-5)
// 			strRet += str.GetAt(j);
// 	}

	code.GetMacCode();
	//str.Empty();
	for (i=0; i<code.uSystemInfoLen; i++)
	{
		strTmp.Format(_T("%02X"), code.szSystemInfo[i]);	
		strMac += strTmp;
	}

	strRet += strMac;

	if (code.m_nSysInfoCount > 0)
	{
		long nPos = 0;
		long nMacLen = strMac.GetLength() / code.m_nSysInfoCount;
		CEncryptCode *pNew = NULL;

		for (i=0; i<code.m_nSysInfoCount; i++)
		{
			pNew = new CEncryptCode();
			pNew->m_strCpu = strCpu;
			pNew->m_strHdCode = strHdCode;
			pNew->m_strMac = strMac.Mid(nPos, nMacLen);
			nPos += nMacLen;
			AddNewChild(pNew);
		}
	}
// 	for (j=0; j<str.GetLength(); j++)
// 	{
// //		if (j<4 || j>str.GetLength()-5)
// 		strRet += str.GetAt(j);
// 	}

	CString strMachineCode = GetRegisterCode(strRet);

	return strMachineCode;
}


CString CEncryptBase::GetMachineCodeEx()
{
	CString strMachineCode;
	strMachineCode = GetMachineCode();

	POS pos = GetHeadPosition();
	CEncryptCode *pCode = NULL;

	while (pos != NULL)
	{
		pCode = (CEncryptCode *)GetNext(pos);
		pCode->m_strRegCode = GetMachineCode(pCode);
	}

	return strMachineCode;
}

CString CEncryptBase::GetMachineCode(CEncryptCode *pCode)
{
	CString strRet;
	strRet = pCode->m_strHdCode;
	strRet += pCode->m_strCpu;
	strRet += pCode->m_strMac;
	CString strMachineCode = GetRegisterCode(strRet);

	return strMachineCode;
}

CString CEncryptBase::GetSNEx()
{
	CString strSnRet;

	POS pos = GetHeadPosition();
	CEncryptCode *pCode = NULL;

	while (pos != NULL)
	{
		pCode = (CEncryptCode *)GetNext(pos);
		pCode->m_strRegCode = DisCodeString(pCode->m_strSN);
	}

	strSnRet = DisCodeString(m_strSN);

	return strSnRet;
}

CString CEncryptBase::GetEncryptFile()
{
	return Encrypt_GetEncryptFile();
}

long CEncryptBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDev);
		BinarySerializeCalLen(oBinaryBuffer, m_strUserName);
		BinarySerializeCalLen(oBinaryBuffer, m_strSN);
		BinarySerializeCalLen(oBinaryBuffer, m_nMaxUseCount);
		BinarySerializeCalLen(oBinaryBuffer, m_nCurrUseCount);

		BinarySerializeCalLen(oBinaryBuffer, m_dwDevStudio);
		BinarySerializeCalLen(oBinaryBuffer, m_dwAutoTest);
		BinarySerializeCalLen(oBinaryBuffer, m_dwUseDog);
		BinarySerializeCalLen(oBinaryBuffer, m_strUserCop);
		BinarySerializeCalLen(oBinaryBuffer, m_strUserCode);
		BinarySerializeCalLen(oBinaryBuffer, m_strMode);
		BinarySerializeCalLen(oBinaryBuffer, m_strOwnership);
		BinarySerializeCalLen(oBinaryBuffer, m_strSysName);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDev);
		BinarySerializeRead(oBinaryBuffer, m_strUserName);
		BinarySerializeRead(oBinaryBuffer, m_strSN);
		BinarySerializeRead(oBinaryBuffer, m_nMaxUseCount);
		BinarySerializeRead(oBinaryBuffer, m_nCurrUseCount);
		BinarySerializeRead(oBinaryBuffer, m_dwDevStudio);
		BinarySerializeRead(oBinaryBuffer, m_dwAutoTest);
		BinarySerializeRead(oBinaryBuffer, m_dwUseDog);
		BinarySerializeRead(oBinaryBuffer, m_strUserCop);
		BinarySerializeRead(oBinaryBuffer, m_strUserCode);
		BinarySerializeRead(oBinaryBuffer, m_strMode);
		BinarySerializeRead(oBinaryBuffer, m_strOwnership);
		BinarySerializeRead(oBinaryBuffer, m_strSysName);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDev);
		BinarySerializeWrite(oBinaryBuffer, m_strUserName);
		BinarySerializeWrite(oBinaryBuffer, m_strSN);
		BinarySerializeWrite(oBinaryBuffer, m_nMaxUseCount);
		BinarySerializeWrite(oBinaryBuffer, m_nCurrUseCount);

		BinarySerializeWrite(oBinaryBuffer, m_dwDevStudio);
		BinarySerializeWrite(oBinaryBuffer, m_dwAutoTest);
		BinarySerializeWrite(oBinaryBuffer, m_dwUseDog);

		BinarySerializeWrite(oBinaryBuffer, m_strUserCop);
		BinarySerializeWrite(oBinaryBuffer, m_strUserCode);
		BinarySerializeWrite(oBinaryBuffer, m_strMode);
		BinarySerializeWrite(oBinaryBuffer, m_strOwnership);
		BinarySerializeWrite(oBinaryBuffer, m_strSysName);
	}

	return 0;
}

long CEncryptBase::Serialize(CBinarySerialBuffer &oBinaryBuffer)
{
	SerializeOwn(oBinaryBuffer);
	SerializeChildren(oBinaryBuffer);

	//时间参数
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strUseTimeLong);
		BinarySerializeCalLen(oBinaryBuffer, m_strTimeUsed);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		if (oBinaryBuffer.Tell_Curr_to_End() <= 0)
		{//2023-4-27  lijunqing 兼容之前的版本
			return 0;
		}

		BinarySerializeRead(oBinaryBuffer, m_strUseTimeLong);
		BinarySerializeRead(oBinaryBuffer, m_strTimeUsed);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strUseTimeLong);
		BinarySerializeWrite(oBinaryBuffer, m_strTimeUsed);
	}

	return 0;
}

CExBaseObject* CEncryptBase::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	return new CEncryptCode();
}

CEncryptCode* CEncryptBase::FindCode(CEncryptCode *pCode)
{
	CEncryptCode *p = NULL;
	CEncryptCode *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CEncryptCode *)GetNext(pos);

		if (p->m_strCpu == pCode->m_strCpu && p->m_strHdCode == pCode->m_strHdCode && p->m_strMac == pCode->m_strMac)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CEncryptCode* CEncryptBase::FindCodeSN(CEncryptCode *pCode)
{
	CEncryptCode *p = NULL;
	CEncryptCode *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CEncryptCode *)GetNext(pos);

		if (p->m_strSN == pCode->m_strSN)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CEncryptCode* CEncryptBase::FindSN(const CString &strSN)
{
	CEncryptCode *p = NULL;
	CEncryptCode *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CEncryptCode *)GetNext(pos);

		if (p->m_strSN == strSN)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CEncryptBase::OpenEncryptFile()
{
	CString strFile = GetEncryptFile();
	OpenEncryptFile(strFile);
}

void CEncryptBase::OpenEncryptFile(const CString &strFile)
{
	DeleteAll();
	CBinarySerialBuffer oBinaryBuffer;
	Encrypt_InitEncryptFileVersion(oBinaryBuffer.m_chPrefix, oBinaryBuffer.m_dwVersion);
	long nRet = oBinaryBuffer.OpenFromFile(strFile);

	if (!nRet)
	{
		return;
	}

	oBinaryBuffer.SetReadMode();
	oBinaryBuffer.ReadVersion();
	Serialize(oBinaryBuffer);
}

BOOL CEncryptBase::OpenEncryptFile(CWnd *pParent, CString &strFile)
{
	BOOL b = PopupOpenFileDialog(pParent, strFile,ENCRYPTFILE_FILTER, ENCRYPTFILE_POSTFIX);
	BOOL bRead = false;

	if (b)
	{
		OpenEncryptFile(strFile);
		//SaveEncryptFile();
	}

	return bRead;
}

BOOL CEncryptBase::OpenEncryptCodeFile(CWnd *pParent, CString &strFile)
{
	BOOL b = PopupOpenFileDialog(pParent, strFile,ENCRYPTFILE_FILTER_M, ENCRYPTFILE_POSTFIX_M);

	if (b)
	{
		OpenEncryptFile(strFile);
	}

	return b;
}

void CEncryptBase::SaveEncryptFile()
{
	CString strFile = GetEncryptFile();
	SaveEncryptFile(strFile);
}

void CEncryptBase::SaveEncryptReg()
{
	CRegKeyEdit oReg;
	oReg.CreateEx_User(ENCRYPTREG_KEY_ROOT);
}

BOOL CEncryptBase::CanRegister()
{
	CRegKeyEdit oReg;
	
	if (!oReg.OpenEx_User(ENCRYPTREG_KEY_ROOT))
	{
		return TRUE;
	}


	return TRUE;
}

void CEncryptBase::SaveEncryptFile(const CString &strFile)
{
	CBinarySerialBuffer oBinaryBuffer;

	Encrypt_InitEncryptFileVersion(oBinaryBuffer.m_chPrefix, oBinaryBuffer.m_dwVersion);

	oBinaryBuffer.SetCalSizeMode();
	oBinaryBuffer.WriteVersion();
	Serialize(oBinaryBuffer);

	oBinaryBuffer.AllocBuffer(0);
	oBinaryBuffer.ResetBufferPointer();
	oBinaryBuffer.SetWriteMode();
	oBinaryBuffer.WriteVersion();
	Serialize(oBinaryBuffer);
	oBinaryBuffer.SaveToFile(strFile);
}


void CEncryptBase::SaveEncryptFile(CWnd *pParent, const CString &strName)
{
	CString strFile;
	strFile.Format(_T("%s.%s"), strName, ENCRYPTFILE_POSTFIX);

	BOOL b = PopupSaveAsFileDialog(pParent, strFile, ENCRYPTFILE_FILTER, ENCRYPTFILE_POSTFIX);

	if (b)
	{
		SaveEncryptFile(strFile);
		CString strHisFile;
		strHisFile = _P_GetDBPath();
		strHisFile += _T("FileAuthorityHis\\");
		CreateAllDirectories(strHisFile);
		strHisFile += GetFileNameFromFilePath(strFile);
		::CopyFile(strFile, strHisFile, FALSE);
	}
}

void CEncryptBase::SaveEncryptCodeFile(CWnd *pParent, const CString &strCode)
{
	CString strFile;
	strFile = strCode;
	strFile += _T(".");
	strFile += ENCRYPTFILE_POSTFIX_M;

	BOOL b = PopupSaveAsFileDialog(pParent, strFile, ENCRYPTFILE_FILTER_M, ENCRYPTFILE_POSTFIX_M);

	if (b)
	{
		SaveEncryptFile(strFile);
	}
}


CString Encrypt_GetEncryptFile()
{
// 	CString strBinFile;
// 	strBinFile = _P_GetBinPath();
// 	strBinFile += ENCRYPTFILE_NAME;
// 
// 	if (IsFileExist(strBinFile))
// 	{
// 		return strBinFile;
// 	}

	CString strFile;
	strFile = _P_GetCommonBinPath();
	strFile += ENCRYPTFILE_NAME;

	if (IsFileExist(strFile))
	{
		return strFile;
	}
#ifdef USE_Old_EngineSystemDefine
	strFile = ChangeFileName(strFile,_T("iiTest"));
#endif

	return strFile;
}

CString Encrypt_GetEncryptRegister()
{
	CString strFile;
	strFile = _P_GetBinPath();
	strFile += ENCRYPTFILE_REGISTER;

	if (IsFileExist(strFile))
	{
		return strFile;
	}

	strFile = _P_GetCommonBinPath();
	strFile += ENCRYPTFILE_REGISTER;

	return strFile;
}

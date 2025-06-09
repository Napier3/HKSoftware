// CBaseObject.cpp: implementation of the CBaseObject class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "BaseObjectList.h"

//////////////////////////////////////////////////////////////////////


//IMPLEMENT_DYNCREATE(CBaseObject,CObject)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
CBaseObject::CBaseObject()
{
}

CBaseObject::~CBaseObject()
{ 
	
}

BOOL CBaseObject::operator!=(CBaseObject &odTemp)
{
	if ((operator ==(odTemp))==FALSE) 
		return TRUE;
	else 
		return FALSE;
}

BOOL CBaseObject::operator==(CBaseObject &odTemp) 
{
	if (&odTemp==this) 
		return TRUE;
	return TRUE;
}
const CBaseObject & CBaseObject::operator =(CBaseObject &odTemp)
{
	return *this;
}

CBaseObject* CBaseObject::GetNewObject(BOOL bCopy)
{
	CBaseObject *pObj = new CBaseObject();
	if (bCopy)
	{
		pObj[0]=(*this);
	}
	return pObj;
}
*/

CBaseObjectList::CBaseObjectList(int iK):CPtrList()
{

}
CBaseObjectList::CBaseObjectList():CPtrList()
{

}
CBaseObjectList::~CBaseObjectList()
{
	EndIt();
}

void CBaseObjectList::RemoveOneItem(POSITION pos,BOOL bDel)
{
	if  (!pos) 
		return;
		
	if (bDel)
	{
		CObject  *pObj=(CObject *)GetAt(pos);
		if (pObj) 
		{
			delete pObj;
			pObj=NULL;
		}
	}
	RemoveAt(pos);
}

void CBaseObjectList::EndIt()
{
	int nCount = GetCount();
	POSITION pos = GetHeadPosition();
	for (int i=0;i<nCount;i++)
	{
		if (!pos) 
			break;
		POSITION posOld = pos;
		CObject * pObj = (CObject *)GetNext(pos);
		if (pObj)
		{
			delete pObj;
			pObj=NULL;
		}
		RemoveAt(posOld);
	}
}

//通用工具
CString GetAppModuleFilePath()
{
	CString strPath;
/*	TCHAR pszPath[MAX_PATH];
	memset(pszPath,0,MAX_PATH);

	CWinApp* pApp = AfxGetApp();
	if (pApp)
	{
		_tcscpy_s(pszPath,MAX_PATH,pApp->m_pszHelpFilePath);		
	}
	else
	{
		HINSTANCE hInstance = GetModuleHandle(_T("EnvironmentDataTester.dll"));
		GetModuleFileName(hInstance,pszPath,MAX_PATH);  
	}
	strPath.Format(_T("%s"),pszPath);
	int nPos = strPath.ReverseFind('\\');
	strPath = strPath.Mid(0,nPos+1);
*/
	return strPath;
}

void GetIPFromString(CString strIP,BYTE *bytIP)
{
	int iB=0,iE=0,i=0;
	iE = strIP.Find(_T("."),0);

	while (iE>0)
	{
#ifdef UNICODE
		bytIP[i] = _wtoi(strIP.Mid(iB,iE-iB));
#else
		bytIP[i] = atoi(strIP.Mid(iB,iE-iB));
#endif
		i++;
		iB = iE+1;
		iE = strIP.Find(_T("."),iB);
	}

#ifdef UNICODE
	bytIP[i] = _wtoi(strIP.Mid(iB,strIP.GetLength()-iB));
#else
	bytIP[i] = atoi(strIP.Mid(iB,strIP.GetLength()-iB));
#endif

}


#include <ATLCONV.h>
int ConverStrToNum(CString m_DealStr)
{
	int nLen = m_DealStr.GetLength();
	LPTSTR lpsz = new TCHAR[nLen+1];
//	_tcscpy_s(lpsz,m_DealStr.GetLength(),m_DealStr);
	lstrcpy(lpsz,m_DealStr);
	int ReturnValue;

#ifdef UNICODE
	ReturnValue = _wtoi(lpsz);
#else
	ReturnValue = atoi(lpsz);
#endif
	delete []lpsz;
	return ReturnValue;
}

CString BinToDec(CString strBin)//2进制转换10进制
{
	CString strDec;
	long nDec = 0, nLen;
	int i, j, k;
	nLen = strBin.GetLength();
	for (i=0; i<nLen;i++)
	{
		if (strBin.GetAt(nLen-i-1)=='0')continue;
		else
		{
			k = 1;
			for(j=0;j<i;j++)k= k*2;
			nDec+=k;
		}
	}
	strDec.Format(_T("%ld"), nDec);
	return strDec;
}

CString DecToBin(CString strDec)//10进制到2进制
{
	int nDec=ConverStrToNum(strDec);
	int nYushu, nShang;
	CString strBin = _T(""), strTemp;
	TCHAR buf[2];
	BOOL bContinue = TRUE;
	while ( bContinue )
	{
		nYushu = nDec%2;
		nShang = nDec/2;
		wsprintf(buf,_T("%d"),nYushu);
		strTemp = strBin;
		strBin.Format(_T("%s%s"), buf, strTemp);
		nDec = nShang;
		if (nShang==0)bContinue=FALSE;
	}
	int nTemp = strBin.GetLength()%4;
	switch(nTemp)
	{
	case 1:
		strTemp.Format(_T("000%s"),strBin);
		strBin = strTemp;
		break;
	case 2:
		strTemp.Format(_T("00%s"),strBin);
		strBin = strTemp;
		break;
	case 3:
		strTemp.Format(_T("0%s"), strBin);
		strBin = strTemp;
		break;
	default:
		break;
	}
	return strBin;
}

CString BinToHex(CString m_strBin)//2-16
{
	CString strDec, strBin, strHex;
	strBin = m_strBin;
	strDec = BinToDec(strBin);
	int nDec;
	nDec = ConverStrToNum(strDec);
	strHex.Format(_T("%x"), nDec);
	return strHex;
}

CString HexToBin(CString m_strHex)//16-2
{
	CString strDec,strBin,strHex;
	strHex = m_strHex;
//	USES_CONVERSION;
	char *pCh = NULL;	//StringToChar(strHex);
	CString_to_char(strHex, &pCh);

#ifdef UNICODE
	DWORD dwHex = wcstoul(strHex, NULL, 16);
#else
	DWORD dwHex = strtoul(strHex, NULL, 16);
#endif

	delete []pCh;
	strDec.Format(_T("%ld"), dwHex);
	strBin = DecToBin(strDec);
	return strBin;
}
CString DecToHex(CString m_strDec)//10-16
{
	int nDec = ConverStrToNum(m_strDec);
	CString str;
	str.Format(_T("%x"), nDec);
	return str;
}
CString HexToDec(CString m_strHex)//16-10
{
	CString strDec, strHex;
	strHex = m_strHex;
//	USES_CONVERSION;
	char *pCh = NULL;	//StringToChar(strHex);
	CString_to_char(strHex, &pCh);

#ifdef UNICODE
	DWORD dwHex = wcstoul(strHex, NULL,16);
#else
	DWORD dwHex = strtoul(strHex, NULL,16);
#endif

	delete []pCh;
	strDec.Format(_T("%ld"), dwHex);
	return strDec;
}
int GetDataFromHex(CString strTemp)
{
	CString str1,str2;
	TCHAR chr[10];
	int mm,nn,kk;
	if(strTemp.GetLength()<4)
	{
		for(int i=strTemp.GetLength();i<5;i++)
		{
			strTemp.Insert(i,_T("0"));
		}
	}
	str1=strTemp.Left(1);
	str2=strTemp.Mid(1,1);
	_tcscpy_s(chr, 10,str1);
	if((chr[0]>='0')&&(chr[0]<='9'))mm=16*(chr[0]-0x30);
	else if((chr[0]>='A')&&(chr[0]<='F'))mm=16*(chr[0]-'A'+10);
	else if((chr[0]>='a')&&(chr[0]<='f'))mm=16*(chr[0]-'a'+10);
	_tcscpy_s(chr, 10,str2);
	if((chr[0]>='0')&&(chr[0]<='9'))nn=(chr[0]-0x30);
	else if((chr[0]>='A')&&(chr[0]<='F'))nn=(chr[0]-'A'+10);
	else if((chr[0]>='a')&&(chr[0]<='f'))nn=(chr[0]-'a'+10);
	mm=mm+nn;
	str1=strTemp.Mid(2,1);
	str2=strTemp.Mid(3,1);
	_tcscpy_s(chr, 10,str1);
	if((chr[0]>='0')&&(chr[0]<='9'))nn=16*(chr[0]-0x30);
	else if((chr[0]>='A')&&(chr[0]<='F'))nn=16*(chr[0]-'A'+10);
	else if((chr[0]>='a')&&(chr[0]<='f'))nn=16*(chr[0]-'a'+10);
	_tcscpy_s(chr, 10,str2);
	if((chr[0]>='0')&&(chr[0]<='9'))kk=(chr[0]-0x30);
	else if((chr[0]>='A')&&(chr[0]<='F'))kk=(chr[0]-'A'+10);
	else if((chr[0]>='a')&&(chr[0]<='f'))kk=(chr[0]-'a'+10);
	nn=nn+kk;
	return (mm+256*nn);
}
int GetDataFrom2Hex(CString strTemp)
{
	CString str1,str2;
	TCHAR chr[10];
	int mm,nn;
	str1=strTemp.Left(1);
	str2=strTemp.Mid(1,1);
	_tcscpy_s(chr, 10,str1);
	if((chr[0]>='0')&&(chr[0]<='9'))mm=16*(chr[0]-0x30);
	else if((chr[0]>='A')&&(chr[0]<='F'))mm=16*(chr[0]-'A'+10);
	else if((chr[0]>='a')&&(chr[0]<='f'))mm=16*(chr[0]-'a'+10);
	_tcscpy_s(chr, 10,str2);
	if((chr[0]>='0')&&(chr[0]<='9'))nn=(chr[0]-0x30);
	else if((chr[0]>='A')&&(chr[0]<='F'))nn=(chr[0]-'A'+10);
	else if((chr[0]>='a')&&(chr[0]<='f'))nn=(chr[0]-'a'+10);
	mm=mm+nn;
	return (mm);
}

#ifdef UNICODE
char*	StringToChar(CString &strTrans)
{
	int len = WideCharToMultiByte(CP_ACP,0,strTrans,-1,NULL,0,NULL,NULL);
	char * pTrans = new char[len+1];   //以字节为单位
	memset(pTrans,0,len+1);
	WideCharToMultiByte(CP_ACP,0,strTrans,-1,pTrans,len,NULL,NULL);
	pTrans[len] = 0; 
	return pTrans;
}

CString CharToString(const char *chTrans)
{
	int charLen = strlen(chTrans);
	int len = MultiByteToWideChar(CP_ACP,0,chTrans,charLen,NULL,0);
	TCHAR *buf = new TCHAR[len + 1];
	MultiByteToWideChar(CP_ACP,0,chTrans,charLen,buf,len);
	buf[len] = 0; 
	CString pWideChar;
	pWideChar.Append(buf);
	delete []buf;
	return pWideChar;
}
#endif


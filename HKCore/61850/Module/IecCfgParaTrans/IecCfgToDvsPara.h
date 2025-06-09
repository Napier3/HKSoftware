#pragma once
#include "..\IecCfgTool\IecCfgTool.h"
#include "..\GlobalDataMngr\PonovoIecDataDefine.h"

class CIecCfgToDvsPara : public CExBaseList
{
public:
	CIecCfgToDvsPara(void);
	~CIecCfgToDvsPara(void);

	void AttacthIecPara(PARA_IEC *pIECPara)	{	m_pIECPara = pIECPara;	}

protected:
	PARA_IEC	*m_pIECPara;
	int			m_nSmvIndex;
	int			m_nSmvChIndex;
	int			m_nGinIndex;
	int			m_nGinChIndex;
	int			m_nGoutIndex;
	int			m_nGoutChIndex;
	
public:
	void TransToIecPara(CExBaseObject *pIecCfgDatasMngr);
	
protected:
	void InitPara();

	void TransToIecPara(CIecCfgDatasMngr  *pIecCfgDatasMngr);

	void TransToIecPara_SMV_91(CIecCfg91Data *pCfgSmv);
	void TransToIecPara_SMV_92(CIecCfg92Data *pCfgSmv);
	void TransToIecPara_SMV_60448(CIecCfg6044Data *pCfgSmv);
	void TransToIecPara_Gin(CIecCfgGinData *pCfgGin);
	void TransToIecPara_Gout(CIecCfgGoutData *pCfgGout);


protected:
	void TransToIecPara_SMV_91_Ch(CIecCfg91Ch *pCh);
	void TransToIecPara_SMV_92_Ch(CIecCfg92Ch *pCh);
	void TransToIecPara_SMV_60448_Ch(CIecCfg6044Ch *pCh);
	void TransToIecPara_Gin_Ch(CIecCfgGinCh *pCh);
	void TransToIecPara_Gout_Ch(CIecCfgGoutCh *pCh);

protected:
	//根据数据类型获取数据
	virtual void  GetCfg_Mac(const CString &strMac, BYTE *bytMac);
	virtual void  GetCfg_Tci(const DWORD &dwTci_V, const DWORD &dwTci_P, DWORD *dwTCI);
	virtual void  GetCfg_Map(const CString &strMap, int *nMap, TCHAR *pchMapData=NULL);
	virtual void  GetCfg_Map_Pub(const CString &strMap1, const CString &strMap2, int *nMap, CString &strMapData);

	//通用转换
	int ConverStrToNum(CString m_DealStr)
	{
		int nLen = m_DealStr.GetLength();
		LPTSTR lpsz = new TCHAR[nLen+1];
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

	CString HexToDec(CString m_strHex)//16-10
	{
		CString strDec, strHex;
		strHex = m_strHex;
		DWORD dwHex = _tcstoul(strHex, NULL,16);
		strDec.Format(_T("%ld"), dwHex);
		return strDec;
	}

	CString HexToBin(CString m_strHex)//16-2
	{
		CString strDec,strBin,strHex;
		strHex = m_strHex;
		DWORD dwHex = _tcstoul(strHex, NULL, 16);
		strDec.Format(_T("%ld"), dwHex);
		strBin = DecToBin(strDec);
		return strBin;
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

};

#pragma once
#include "..\GlobalDataMngr\PonovoIecDataDefine.h"

#define SMVTYPE_91       0
#define SMVTYPE_92       1
#define SMVTYPE_6044    2

class CDvsParaToPTPara : public CExBaseList
{
public:
	CDvsParaToPTPara(void);
	~CDvsParaToPTPara(void);

	void AttacthIecPara(PARA_IEC *pIECPara)	{	m_pIECPara = pIECPara;	}

protected:
	PARA_IEC	*m_pIECPara;
	int			m_nSmvIndex;
	int			m_nSmvChIndex;
	int			m_nGinIndex;
	int			m_nGinChIndex;
	int			m_nGoutIndex;
	int			m_nGoutChIndex;

	CString		m_strPtPara;
	CString		m_strSubPara1;
	CString		m_strSubPara2;
	CString		m_strReplace;

public:
	void TransToPTPara(CString strPtParaPath);
	
protected:
	void InitPara();

	void TransToPTPara_SMV();
	void TransToPTPara_SMV_91();
	void TransToPTPara_SMV_92();
	void TransToPTPara_SMV_60448();
	void TransToPTPara_Gin();
	void TransToPTPara_Gout();

	void TransToPTPara_SMV_91_Sub(int nIndex);
	void TransToPTPara_SMV_92_Sub(int nIndex);
	void TransToPTPara_SMV_60448_Sub(int nIndex);
	void TransToPTPara_Gin_Sub(int nIndex);
	void TransToPTPara_Gout_Sub(int nIndex);

private:
	BOOL GetFileData(CString strPath);
	int  GetSubPara1(CString strBegin, CString strEnd);
	int  GetSubPara2(CString strBegin, CString strEnd);
	int  GetSubPara(CString strBegin, CString strEnd, CString strBasePara, CString &strSubPara);
	int  ReplaceSubPara(CString strID, CString strNew);

};

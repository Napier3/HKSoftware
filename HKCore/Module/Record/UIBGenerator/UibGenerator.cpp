//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UibGenerator.cpp  CUibGenerator


#include "stdafx.h"
#include "UibGenerator.h"
#include "..\..\API\FileApi.h"

//analog + binary + generator + xml
const CString CUibGenerator::g_strUibGenFilePostfix = _T("abgxml");
const CString CUibGenerator::g_strUibGenFileFilter = _T("Comtrade File Generator Config(*.abgxml)|*.abgxml||");
const CString CUibGenerator::g_strUibGenFileTitle = _T("Comtrade file generator config");

CUibGenerator::CUibGenerator()
{
	//初始化属性
	m_fFreq = 0;
	m_nSampRate = 10000;
	m_nUchCount = 3;  //Uabc
	m_nIchCount = 4;   //Iabc0
	m_nBchCount = 0;

	//初始化成员变量
	m_pRcdComtradeFile = NULL;

	m_nTotalPoints = 0;
}

CUibGenerator::~CUibGenerator()
{
	if (m_pRcdComtradeFile != NULL)
	{
		CRcdComtradeFileMngr::CloseComtradeFile(m_pRcdComtradeFile);
	}
}

long CUibGenerator::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIBGeneratorXmlRWKeys *pXmlKeys = (CUIBGeneratorXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strFreqKey, oNode, m_fFreq);
	xml_GetAttibuteValue(pXmlKeys->m_strSampRateKey, oNode, m_nSampRate);
	xml_GetAttibuteValue(pXmlKeys->m_strUchCountKey, oNode, m_nUchCount);
	xml_GetAttibuteValue(pXmlKeys->m_strIchCountKey, oNode, m_nIchCount);
	xml_GetAttibuteValue(pXmlKeys->m_strBchCountKey, oNode, m_nBchCount);
	return 0;
}

long CUibGenerator::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIBGeneratorXmlRWKeys *pXmlKeys = (CUIBGeneratorXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strFreqKey, oElement, m_fFreq);
	xml_SetAttributeValue(pXmlKeys->m_strSampRateKey, oElement, m_nSampRate);
	xml_SetAttributeValue(pXmlKeys->m_strUchCountKey, oElement, m_nUchCount);
	xml_SetAttributeValue(pXmlKeys->m_strIchCountKey, oElement, m_nIchCount);
	xml_SetAttributeValue(pXmlKeys->m_strBchCountKey, oElement, m_nBchCount);
	return 0;
}

long CUibGenerator::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_fFreq);
		BinarySerializeCalLen(oBinaryBuffer, m_nSampRate);
		BinarySerializeCalLen(oBinaryBuffer, m_nUchCount);
		BinarySerializeCalLen(oBinaryBuffer, m_nIchCount);
		BinarySerializeCalLen(oBinaryBuffer, m_nBchCount);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_fFreq);
		BinarySerializeRead(oBinaryBuffer, m_nSampRate);
		BinarySerializeRead(oBinaryBuffer, m_nUchCount);
		BinarySerializeRead(oBinaryBuffer, m_nIchCount);
		BinarySerializeRead(oBinaryBuffer, m_nBchCount);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_fFreq);
		BinarySerializeWrite(oBinaryBuffer, m_nSampRate);
		BinarySerializeWrite(oBinaryBuffer, m_nUchCount);
		BinarySerializeWrite(oBinaryBuffer, m_nIchCount);
		BinarySerializeWrite(oBinaryBuffer, m_nBchCount);
	}
	return 0;
}

void CUibGenerator::InitAfterRead()
{
}

BOOL CUibGenerator::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CUibGenerator *p = (CUibGenerator*)pObj;

	if(m_fFreq != p->m_fFreq)
	{
		return FALSE;
	}

	if(m_nSampRate != p->m_nSampRate)
	{
		return FALSE;
	}

	if(m_nUchCount != p->m_nUchCount)
	{
		return FALSE;
	}

	if(m_nIchCount != p->m_nIchCount)
	{
		return FALSE;
	}

	if(m_nBchCount != p->m_nBchCount)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUibGenerator::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUibGenerator *p = (CUibGenerator*)pDest;

	p->m_fFreq = m_fFreq;
	p->m_nSampRate = m_nSampRate;
	p->m_nUchCount = m_nUchCount;
	p->m_nIchCount = m_nIchCount;
	p->m_nBchCount = m_nBchCount;
	return TRUE;
}

CBaseObject* CUibGenerator::Clone()
{
	CUibGenerator *p = new CUibGenerator();
	Copy(p);
	return p;
}

BOOL CUibGenerator::CanPaste(UINT nClassID)
{
	if (nClassID == UIBGCLASSID_CUIBGENSTATE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CUibGenerator::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBGeneratorXmlRWKeys *pXmlKeys = (CUIBGeneratorXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCUibGenStateKey)
	{
		pNew = new CUibGenState();
	}

	return pNew;
}

CExBaseObject* CUibGenerator::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == UIBGCLASSID_CUIBGENSTATE)
	{
		pNew = new CUibGenState();
	}

	return pNew;
}

//////////////////////////////////////////////////////////////////////////
//
BOOL CUibGenerator::OpenUibGeneratorFile(CWnd *pParentWnd)
{
	CString strFile;

	if (pParentWnd == NULL)
	{
		pParentWnd = AfxGetMainWnd();
	}

	BOOL b = PopupOpenFileDialog(AfxGetMainWnd(), strFile, g_strUibGenFileFilter, g_strUibGenFilePostfix, _T("COMTRADE file"));

	if (b)
	{
		b = OpenUibGeneratorFile(strFile);
	}
	
	return b;
}

BOOL CUibGenerator::OpenUibGeneratorFile(const CString &strFile)
{
	BOOL b = OpenXmlFile(strFile, CUIBGeneratorXmlRWKeys::g_pXmlKeys);

	if (b)
	{
		m_strUibGenFile = strFile;
		InitUIBGenerate();
		UIBGenerate();
	}

	return b;
}

void CUibGenerator::InitUIBGenerate()
{
	//创建ComtradeFile对象
	if (m_pRcdComtradeFile == NULL)
	{
		m_pRcdComtradeFile = CRcdComtradeFileMngr::NewComtradeFile();
	}

	m_pRcdComtradeFile->m_strID = m_strUibGenFile;
	m_pRcdComtradeFile->m_strName = m_strUibGenFile;
	m_pRcdComtradeFile->m_strComtradeFile = m_strUibGenFile;

	//根据设置初始化m_pRcdComtradeFile
	CExBaseList listAnalogs, listBinarys;
	long nAnalogs, nBinarys;
	float fTimeLong = 0;

	GetAnalogs(listAnalogs);
	GetBinarys(listBinarys);
	nAnalogs = listAnalogs.GetCount();
	nBinarys = listBinarys.GetCount();
	fTimeLong = CalTimeLong();

	fTimeLong = fTimeLong * m_nSampRate;
	m_nTotalPoints = fTimeLong;

	if (fTimeLong - m_nTotalPoints > 0.5)
	{
		m_nTotalPoints++;
	}

	m_pRcdComtradeFile->CreateComtradeFile(nAnalogs, nBinarys, m_nTotalPoints);

	//初始化各状态序列的Analog、Binary通道关联的缓冲区，并计算波形产生时的常量
	POS pos = listAnalogs.GetHeadPosition();
	CUibGenAnalog *pAnalog = NULL;
	long nIndex = 0;

	while (pos != NULL)
	{
		pAnalog = (CUibGenAnalog *)listAnalogs.GetNext(pos);
		m_pRcdComtradeFile->SetAnalogAttr(nIndex, pAnalog->m_strName, pAnalog->m_strChID, pAnalog->m_strUnit
			, pAnalog->m_fZero, pAnalog->m_fCoef
			, pAnalog->m_fPrimary, pAnalog->m_fSecondary
			, &pAnalog->m_pnAttachBuffer);
		nIndex++;
	}

	listAnalogs.RemoveAll();
	listBinarys.RemoveAll();

	InitGenerate();
}

void CUibGenerator::UIBGenerate()
{
	POS pos = GetHeadPosition();
	CUibGenState *pState = NULL;
	long nUibGenIndex = 0;

	while (pos != NULL)
	{
		pState = (CUibGenState *)GetNext(pos);
		pState->Generate(nUibGenIndex, m_nSampRate);
	}

	m_pRcdComtradeFile->InitAfterCreate(m_fFreq, m_nSampRate, m_nTotalPoints);
}

void CUibGenerator::InitGenerate()
{
	POS pos = GetHeadPosition();
	CUibGenState *pState = NULL;
	CUibGenState *pStateHead = (CUibGenState*)GetHead();
	long nUibGenIndex = 0;
	double dCoef_FreqAngleT = m_fFreq * 3.141592654 * 2 / m_nSampRate;

	while (pos != NULL)
	{
		pState = (CUibGenState *)GetNext(pos);
		pState->InitGenerate(dCoef_FreqAngleT);
	}

	pos = GetHeadPosition();
	GetNext(pos);
	POS posState = pos;

	long nChIndex = 0;
	POS posCh = pStateHead->GetHeadPosition();
	CUibChGenInterface *pChGen = NULL;

	while (posCh != NULL)
	{
		pChGen = (CUibChGenInterface *)pStateHead->GetNext(posCh);
		pos = posState;

		while (pos != NULL)
		{
			pState = (CUibGenState *)GetNext(pos);
			pState->InitGenerate(nChIndex, pChGen->m_pnAttachBuffer);
		}

		nChIndex++;
	}
}

void CUibGenerator::GetAnalogs(CExBaseList &listAnalogs)
{
	CUibGenState *pState = NULL;
	pState = (CUibGenState *)GetHead();

	if (pState == NULL)
	{
		return;
	}

	pState->GetAnalogs(listAnalogs);
}

void CUibGenerator::GetBinarys(CExBaseList &listBinarys)
{
	CUibGenState *pState = NULL;
	pState = (CUibGenState *)GetHead();

	if (pState == NULL)
	{
		return;
	}

	pState->GetBinarys(listBinarys);
}

float CUibGenerator::CalTimeLong()
{
	CUibGenState *pState = NULL;
	POS pos = GetHeadPosition();
	float  fTimeLong = 0;

	while (pos != NULL)
	{
		pState = (CUibGenState *)GetNext(pos);
		fTimeLong += pState->m_fTimeLong;
	}

	return fTimeLong;
}

//////////////////////////////////////////////////////////////////////////
//
CUibGeneratorMngr* CUibGeneratorMngr::g_pUibGeneratorMngr = NULL;
long CUibGeneratorMngr::g_nUibGeneratorMngr = 0;

CUibGeneratorMngr::CUibGeneratorMngr()
{

}

CUibGeneratorMngr::~CUibGeneratorMngr()
{

}


CUibGeneratorMngr* CUibGeneratorMngr::Create()
{
	g_nUibGeneratorMngr++;

	if (g_nUibGeneratorMngr == 1)
	{
		CUIBGeneratorXmlRWKeys::Create();
		g_pUibGeneratorMngr = new CUibGeneratorMngr();
	}

	return g_pUibGeneratorMngr;
}

void CUibGeneratorMngr::Release()
{
	g_nUibGeneratorMngr--;

	if (g_nUibGeneratorMngr == 0)
	{
		delete g_pUibGeneratorMngr;
		g_pUibGeneratorMngr = NULL;
		CUIBGeneratorXmlRWKeys::Release();
	}
}

BOOL CUibGeneratorMngr::PopOpenUibGenerator(CString &strFile)
{
	BOOL b = PopupOpenFileDialog(AfxGetMainWnd(), strFile
		, CUibGenerator::g_strUibGenFileFilter, CUibGenerator::g_strUibGenFilePostfix, CUibGenerator::g_strUibGenFileTitle);

	return b;
}

CUibGenerator* CUibGeneratorMngr::OpenUibGenerator()
{
	CString strFile;

	if (! PopOpenUibGenerator(strFile))
	{
		return NULL;
	}
	else
	{
		return OpenUibGenerator(strFile);
	}
}

CUibGenerator* CUibGeneratorMngr::OpenUibGenerator(const CString &strFile)
{
	CUibGenerator *pUibGenerator = (CUibGenerator*)g_pUibGeneratorMngr->FindByID(strFile);

	if (pUibGenerator != NULL)
	{
		return pUibGenerator;
	}

	pUibGenerator = new CUibGenerator();
	pUibGenerator->OpenUibGeneratorFile(strFile);
	g_pUibGeneratorMngr->AddNewChild(pUibGenerator);

	return pUibGenerator;
}

CUibGenerator* CUibGeneratorMngr::FindUibGenerator(const CString &strFile)
{
	CUibGenerator *pUibGenerator = (CUibGenerator*)g_pUibGeneratorMngr->FindByID(strFile);

	return pUibGenerator;
}
CUibGenerator* CUibGeneratorMngr::GetUibGenerator(long nIndex)
{
	if (g_pUibGeneratorMngr == NULL)
	{
		return NULL;
	}

	return (CUibGenerator*)g_pUibGeneratorMngr->GetAtIndex(nIndex);
}

BOOL CUibGeneratorMngr::CloseUibGenerator(const CString &strFile)
{
	CUibGenerator *pUibGenerator = (CUibGenerator*)g_pUibGeneratorMngr->FindByID(strFile);

	if (pUibGenerator == NULL)
	{
		return TRUE;
	}

	g_pUibGeneratorMngr->Delete(pUibGenerator);

	return TRUE;
}

BOOL CUibGeneratorMngr::CloseUibGenerator(CUibGenerator *pUibGenerator)
{
	return g_pUibGeneratorMngr->Delete(pUibGenerator);
}

BOOL CUibGeneratorMngr::CloseComtradeFile(CRcdComtradeFile *pComtradeFile)
{
	POS pos = g_pUibGeneratorMngr->GetHeadPosition();
	CUibGenerator *pUibGenerator = NULL;

	while (pos != NULL)
	{
		pUibGenerator = (CUibGenerator *)g_pUibGeneratorMngr->GetNext(pos);

		if (pUibGenerator->m_pRcdComtradeFile == pComtradeFile)
		{
			g_pUibGeneratorMngr->Delete(pUibGenerator);
			break;
		}
	}

	return TRUE;
}

CUibGenerator* CUibGeneratorMngr::FindByComtradeFile(CRcdComtradeFile *pComtradeFile)
{
	POS pos = g_pUibGeneratorMngr->GetHeadPosition();
	CUibGenerator *pUibGenerator = NULL;
	CUibGenerator *pFind = NULL;

	while (pos != NULL)
	{
		pUibGenerator = (CUibGenerator *)g_pUibGeneratorMngr->GetNext(pos);

		if (pUibGenerator->m_pRcdComtradeFile == pComtradeFile)
		{
			pFind = pUibGenerator;
			break;
		}
	}

	return pFind;
}

long CUibGeneratorMngr::GetUibGeneratorCount()
{
	return g_pUibGeneratorMngr->GetCount();
}

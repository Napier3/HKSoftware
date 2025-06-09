#include "StdAfx.h"
#include "GuideBookTool.h"
#include "../../../Module/DataMngr/ValuesParse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CGuideBookTool* CGuideBookTool::g_pGuideBookTool = NULL;
long CGuideBookTool::g_nGuideBookToolRef = 0;

/*
<group name="BinputsResult" id="BinputsResult" value="." data-type="BinaryDataTypes.xml">
	<group name="Device1" id="Device1" value="1">
		<group name="CDC37-X1" id="CDC37-X1" value="1">
			<data name="X1-C2" id="X1-C2" data-type="BOOL" format="1" remark="1"/>
*/

CGuideBookTool::CGuideBookTool(void)
{

}

CGuideBookTool::~CGuideBookTool(void)
{

}

void CGuideBookTool::InitTool()
{
	InitToolConfigFile(g_strBinaryParaID_Boutputs);
	InitToolConfigFile(g_strBinaryParaID_BinputsResult);
}

void CGuideBookTool::InitToolConfigFile(const CString &strID)
{
	CDataGroup *pDataGroup = (CDataGroup*)FindByID(strID);

	if (pDataGroup != NULL)
	{
		return;
	}

	pDataGroup = new CDataGroup();
	CString strFile;

	strFile = _P_GetConfigPath();
    strFile.AppendFormat(_T("%s.xml"), strID.GetString());
	pDataGroup->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	pDataGroup->InitReserved(0);
	pDataGroup->InitItemData(0);
	pDataGroup->m_strName = strID;
	pDataGroup->m_strID = strID;
	AddNewChild(pDataGroup);

	AddDataTypes(pDataGroup->m_strDataType);
}

void CGuideBookTool::AddDataTypes(const CString &strDataTypesFile)
{
	CString strTemp = strDataTypesFile;
	strTemp.MakeLower();
	CDataTypes *pFind = (CDataTypes*)m_listDataTypes.FindByID(strTemp);

	if (pFind != NULL)
	{
		return;
	}

	pFind = new CDataTypes();
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += strTemp;
	pFind->Open(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	m_listDataTypes.AddNewChild(pFind);
}

CGuideBookTool* CGuideBookTool::Create()
{
	g_nGuideBookToolRef++;

	if (g_nGuideBookToolRef == 1)
	{
		g_pGuideBookTool = new CGuideBookTool();
		g_pGuideBookTool->InitTool();
	}

	return g_pGuideBookTool;
}

void CGuideBookTool::Release()
{
	g_nGuideBookToolRef--;

	if (g_nGuideBookToolRef == 0)
	{
		delete g_pGuideBookTool;
		g_pGuideBookTool = NULL;
	}
}

CDataTypes* CGuideBookTool::FindDataTypes(const CString &strDataTypesFile)
{
	ASSERT (g_pGuideBookTool != NULL);

	if (g_pGuideBookTool == NULL)
	{
		return NULL;
	}

	CString strTemp = strDataTypesFile;
	strTemp.MakeLower();
	CDataTypes *pFind = (CDataTypes*)g_pGuideBookTool->m_listDataTypes.FindByID(strTemp);

	return pFind;
}


CShortData* CGuideBookTool::FindDataRoot(CDataGroup *pRootGroup, const CString &strPath)
{
	POS pos = pRootGroup->GetHeadPosition();
	CDataGroup *pDataGroup = NULL;
	CShortData *pFind = NULL;

	while (pos != NULL)
	{
		pDataGroup = (CDataGroup *)pRootGroup->GetNext(pos);

		if (pDataGroup->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			pFind = FindData(pDataGroup, strPath, pRootGroup->m_strValue);

			if (pFind != NULL)
			{
				break;
			}
		}
	}

	return pFind;
}

CShortData* CGuideBookTool::FindData(CDataGroup *pGroup, const CString &strPath, const CString &strFlag)
{
	POS pos = pGroup->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	CShortData *pFind = NULL;

	CString strLeft, strRight;
	long nPos = strPath.Find(strFlag);

	if (nPos > 0)
	{
		strLeft = strPath.Left(nPos);
		strRight = strPath.Mid(nPos+1);
	}
	else
	{
		strLeft = strPath;
	}

	if (strLeft != pGroup->m_strValue)
	{
		return NULL;
	}

	while (pos)
	{
		pObj = (CExBaseObject *)pGroup->GetNext(pos);

		if (pObj->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			pFind = FindData((CDataGroup*)pObj, strRight, strFlag);

			if (pFind != NULL)
			{
				break;
			}
		}
		else if (pObj->GetClassID() == DTMCLASSID_CSHORTDATA)
		{
			if (strRight == ((CShortData*)pObj)->m_strRemark)
			{
				pFind = (CShortData*)pObj;
				break;
			}
		}
	}

	return pFind;
}

void CGuideBookTool::ParseDatas(CDataGroup *pDataGroup, const CString &strDatas, CExBaseList &listDatas)
{
	pDataGroup->InitReserved(0);
	pDataGroup->InitItemData(0);

	CValuesParse oParse;
	oParse.Parse(strDatas);
	g_pGuideBookTool->ParseDatas(pDataGroup, oParse, listDatas);
}

void CGuideBookTool::ParseDatas(CDataGroup *pDataGroup, CValuesParse &oParse, CExBaseList &listDatas, BOOL bSetValue)
{
	POS pos = oParse.GetHeadPosition();
	CValue *pValue = NULL;
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pValue = (CValue *)oParse.GetNext(pos);
		pData = FindDataRoot(pDataGroup, pValue->m_strID);

		if (pData != NULL)
		{
			listDatas.AddTail(pData);

			if (!bSetValue)
			{
				continue;
			}

			pData->m_dwReserved = 1;
			pData->m_dwItemData = CString_To_long(pValue->m_strValue) - 1;
			pData->m_strValue = pValue->m_strValue;
		}
	}
}

void CGuideBookTool::ParseDatas_ID_To_Index(CDataGroup *pDataGroup, CValuesParse &oParse, CExBaseList &listDatas)
{
	POS pos = oParse.GetHeadPosition();
	CValue *pValue = NULL;
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pValue = (CValue *)oParse.GetNext(pos);
		pData = FindDataRoot(pDataGroup, pValue->m_strID);

		if (pData != NULL)
		{
			listDatas.AddTail(pData);
			pValue->m_strID = pData->m_strFormat;
		}
	}
}

void CGuideBookTool::ParseDatas_Index(CDataGroup *pDataGroup, CValuesParse &oParse, CExBaseList &listDatas, BOOL bSetValue, long nOffset)
{
	POS pos = oParse.GetHeadPosition();
	CValue *pValue = NULL;
	CShortData *pData = NULL;
	long nIndex = 0;

	while (pos != NULL)
	{
		pValue = (CValue *)oParse.GetNext(pos);
		nIndex = CString_To_long(pValue->m_strID) - 1;
		nIndex += nOffset;
		pData = (CShortData*)pDataGroup->GetAtIndex(nIndex);

		if (pData != NULL)
		{
			listDatas.AddTail(pData);
	
			if (!bSetValue)
			{
				continue;
			}

			pData->m_dwReserved = 1;
			pData->m_dwItemData = CString_To_long(pValue->m_strValue) - 1;
			pData->m_strValue = pValue->m_strValue;
		}
	}
}
CString CGuideBookTool::GetDataPath(CShortData *pData, CExBaseObject *pRoot, const CString &strFlag)
{
	CString strPath;
	CDataGroup *pParent = (CDataGroup*)pData->GetParent();
	CString strTemp;

	strPath = pData->m_strRemark;

	while (pParent != NULL)
	{
		if (pParent == pRoot)
		{
			break;
		}

        strTemp.Format(_T("%s%s"), ((CDataGroup*)pParent)->m_strValue.GetString(), strFlag.GetString());
		strPath = strTemp + strPath;
		pParent = (CDataGroup *)pParent->GetParent();
	}

	return strPath;
}

void CGuideBookTool::InitDestDatas(CDataGroup *pRootGroup, CExBaseList &listDatas, CString &strDatas)
{
	POS pos = listDatas.GetHeadPosition();
	CShortData *pData = NULL;
	CString strPath;
	strDatas = _T("\"");

	while(pos != NULL)
	{
		pData = (CShortData *)listDatas.GetNext(pos);
		strPath = GetDataPath(pData, pRootGroup, pRootGroup->m_strValue);
        strDatas.AppendFormat(_T("(%s,%s)"), strPath.GetString(), pData->m_strValue.GetString());
	}

	strDatas += _T("\"");
}

//////////////////////////////////////////////////////////////////////////
//OffsetBinary
void CGuideBookTool::OffsetBinary(CGuideBook *pGuideBook, long nBinOffset, long nBoutOffset)
{
	ASSERT (g_pGuideBookTool != NULL);

	if (g_pGuideBookTool == NULL)
	{
		return;
	}

	g_pGuideBookTool->In_OffsetBinary(pGuideBook, nBinOffset, nBoutOffset);
}

void CGuideBookTool::In_OffsetBinary(CGuideBook *pGuideBook, long nBinOffset, long nBoutOffset)
{
	In_OffsetBinaryList(pGuideBook, nBinOffset, nBoutOffset);
}

void CGuideBookTool::In_OffsetBinaryList(CExBaseList *pList, long nBinOffset, long nBoutOffset)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == GBCLASSID_MACROTEST)
		{
			In_OffsetBinaryMacroTest((CMacroTest*)p, nBinOffset, nBoutOffset);
		}
		else if (nClassID == GBCLASSID_DEVICE || nClassID == GBCLASSID_ITEMS)
		{
			In_OffsetBinaryList((CExBaseList*)p, nBinOffset, nBoutOffset);
		}
	}
}

void CGuideBookTool::In_OffsetBinaryMacroTest(CMacroTest *pMacroTest, long nBinOffset, long nBoutOffset)
{
	CMacroTestPara *pPara = pMacroTest->GetMacroTestPara();
	CMacroTestParaDatas *pParaDatas = pPara->GetFaultParaDatas();
	POS pos = pParaDatas->GetHeadPosition();
	CMacroTestParaData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CMacroTestParaData *)pParaDatas->GetNext(pos);
		In_OffsetBinaryMacroTestPara(pData, nBinOffset, nBoutOffset);
	}
}

void CGuideBookTool::In_OffsetBinaryMacroTestPara(CMacroTestParaData *pPara, long nBinOffset, long nBoutOffset)
{
	CDataGroup *pDataGroup = (CDataGroup*)FindByID(pPara->m_strID);

	if (pDataGroup == NULL)
	{
		return;
	}

	if (pDataGroup->m_strID == g_strBinaryParaID_Boutputs)
	{
		In_OffsetBinaryMacroTestPara(pDataGroup, pPara, nBoutOffset);
	}
	else if (pDataGroup->m_strID == g_strBinaryParaID_BinputsResult)
	{
		In_OffsetBinaryMacroTestPara(pDataGroup, pPara, nBinOffset);
	}
}

void CGuideBookTool::In_OffsetBinaryMacroTestPara(CDataGroup *pDataGroup, CMacroTestParaData *pPara, long nOffset)
{
	if (nOffset <= 0)
	{
		return;
	}

	if (pPara->m_strExpression.GetLength() < 4)
	{
		return;
	}

	CExBaseList listParaDatas, listAllDatas, listOffsetDatas;
	ParseDatas(pDataGroup, pPara->m_strExpression, listParaDatas);
	pDataGroup->SelectAllDatas(listAllDatas);

	POS pos = listParaDatas.GetHeadPosition();
	CShortData *p = NULL;
	CShortData *pFind = NULL;
	long nIndex = 0;

	while (pos != NULL)
	{
		p = (CShortData*)listParaDatas.GetNext(pos);
		nIndex = listAllDatas.FindIndex(p);
		ASSERT (nIndex >= 0);
		nIndex += nOffset;
		pFind = (CShortData*)listAllDatas.GetAtIndex(nIndex);

		if (pFind != NULL)
		{
			pFind->m_strValue = p->m_strValue;
			listOffsetDatas.AddTail(pFind);
		}
	}

	InitDestDatas(pDataGroup, listOffsetDatas, pPara->m_strExpression);

	listParaDatas.RemoveAll();
	listAllDatas.RemoveAll();
	listOffsetDatas.RemoveAll();
}

//////////////////////////////////////////////////////////////////////////
//

BOOL CGuideBookTool::HasBinaryTestParas(const CString &strPataDatas)
{
	if (strPataDatas.Find(g_strBinaryParaID_Boutputs) >= 0)
	{
		return TRUE;
	}

	if (strPataDatas.Find(g_strBinaryParaID_BinputsResult) >= 0)
	{
		return TRUE;
	}

	return FALSE;
}

void CGuideBookTool::CombineTestParaDatas(CString &strDestParaDatas, const CString &strSrcDatas, const CString &strParaID)
{
	CString strParaBegin;
    strParaBegin.Format(_T("%s="), strParaID.GetString());
	long nPos = strDestParaDatas.Find(strParaBegin);
	long nPos2 = strSrcDatas.Find(strParaBegin);
	long nPosEnd2 = 0, nPosEnd = 0, nCount=0;
	CString strData, strData2;

	if (nPos2 < 0 || nPos < 0)
	{
		return;
	}

	nPosEnd2 = strSrcDatas.Find(';', nPos2);
	ASSERT (nPosEnd2 > 0);
	nPos2 += strParaBegin.GetLength();
	strData2 = strSrcDatas.Mid(nPos2, nPosEnd2 - nPos2); //��ȡ��***=�����������

	nPosEnd = strDestParaDatas.Find(';', nPos);
	ASSERT (nPosEnd > 0);
	nCount = nPosEnd - nPos;
	strData = strDestParaDatas.Mid(nPos, nCount); //��ȡ��***=##����ʽ�����ݣ���������;��
	strDestParaDatas.Delete(nPos, nCount+1);//ɾ����***=##;����ʽ������

	//ȥ�����ţ���ɲ���ƴ��
	strData = strData.Left(strData.GetLength() - 1);
	strData2 = strData2.Mid(1);
    strDestParaDatas.AppendFormat(_T("%s%s;"), strData.GetString(), strData2.GetString());
}

void CGuideBookTool::CombineTestParaDatas(CString &strDestParaDatas, const CString &strSrcDatas)
{
	g_pGuideBookTool->CombineTestParaDatas(strDestParaDatas, strSrcDatas, g_strBinaryParaID_Boutputs);  //ƴ���ù���ֵ
	g_pGuideBookTool->CombineTestParaDatas(strDestParaDatas, strSrcDatas, g_strBinaryParaID_BinputsResult); //ƴ������ֵ
}


void CGuideBookTool::ExtractBinputsResult(CValues *pValues, long nBinBegin, long nBinEnd, long nBinOffset)
{
	ASSERT (g_pGuideBookTool != NULL);

// 	g_pGuideBookTool->ExtractBinputsResult(g_strBinaryRsltID_BinputsResult, pValues, nBinBegin, nBinEnd, nBinOffset);
// 	g_pGuideBookTool->ExtractBinputsResult(g_strBinaryRsltID_BinRslt, pValues, nBinBegin, nBinEnd, nBinOffset);
	g_pGuideBookTool->ExtractBinputsResult(g_strBinaryRsltID_SwitchGroup, pValues, nBinBegin, nBinEnd, nBinOffset);
	g_pGuideBookTool->ExtractBinputsResult(g_strBinaryRsltID_CheckGroup, pValues, nBinBegin, nBinEnd, nBinOffset);
	g_pGuideBookTool->ExtractBinputsResult2(g_strBinaryRsltID_BinputsResult, pValues, nBinBegin, nBinEnd, nBinOffset);
	//g_pGuideBookTool->ExtractBinputsResult(g_strBinaryRsltID_SwitchGroupAll, pValues, nBinBegin, nBinEnd, nBinOffset);
}

void CGuideBookTool::ExtractBinputsResult(const CString &strValueID, CValues *pValues, long nBinBegin, long nBinEnd, long nBinOffset)
{
	CValue *pBinRslt = (CValue *)pValues->FindByID(strValueID);

	if (pBinRslt == NULL)
	{
		return;
	}

	if (pBinRslt->m_strValue.GetLength() < 4)
	{
		return;
	}

	CDataGroup *pDataGroup = (CDataGroup*)FindByID(g_strBinaryParaID_BinputsResult);
	pDataGroup->InitReserved(0);
	pDataGroup->InitItemData(0);

	CValuesParse oParse;
	oParse.Parse(pBinRslt->m_strValue);
	CExBaseList listDatas;
	pDataGroup->SelectAllDatas(listDatas);

	POS pos = oParse.GetHeadPosition();
	CValue *pValue = NULL;
	CShortData *pData = NULL;
	long nIndex = 0;
	CExBaseList listBinValue;

	while (pos != NULL)
	{
		pValue = (CValue *)oParse.GetNext(pos);
		nIndex = CString_To_long(pValue->m_strID) - 1;
		pData = (CShortData*)listDatas.GetAtIndex(nIndex);

		if (pData == NULL)
		{
			continue;
		}

		if (nBinBegin <=nIndex && nIndex < nBinEnd)
		{
			listBinValue.AddTail(pValue);
			pData = (CShortData*)listDatas.GetAtIndex(nIndex - nBinOffset);
			pValue->m_dwItemData = (DWORD)pData;
		}
	}

	pos = listBinValue.GetHeadPosition();
	pBinRslt->m_strValue = _T("");

	while (pos != NULL)
	{
		pValue = (CValue *)listBinValue.GetNext(pos);
		pData = (CShortData *)pValue->m_dwItemData;

		if (pData == NULL)
		{
            pBinRslt->m_strValue.AppendFormat(_T("(%s,%s)"), pValue->m_strID.GetString(), pValue->m_strValue.GetString());
		}
		else
		{
            pBinRslt->m_strValue.AppendFormat(_T("(%s,%s)"), pData->m_strFormat.GetString(), pValue->m_strValue.GetString());
		}
	}

	listDatas.RemoveAll();
	listBinValue.RemoveAll();
}

void CGuideBookTool::ExtractBinputsResult2(const CString &strValueID, CValues *pValues, long nBinBegin, long nBinEnd, long nBinOffset)
{
	CValue *pBinRslt = (CValue *)pValues->FindByID(strValueID);

	if (pBinRslt == NULL)
	{
		return;
	}

	if (pBinRslt->m_strValue.GetLength() < 4)
	{
		return;
	}

	CDataGroup *pDataGroup = (CDataGroup*)FindByID(g_strBinaryParaID_BinputsResult);
	pDataGroup->InitReserved(0);
	pDataGroup->InitItemData(0);

	CValuesParse oParse;
	oParse.Parse(pBinRslt->m_strValue);
	CExBaseList listDatas;
	pDataGroup->SelectAllDatas(listDatas);

	POS pos = oParse.GetHeadPosition();
	CValue *pValue = NULL;
	CShortData *pData = NULL;
	long nIndex = 0;
	CExBaseList listBinValue;

	while (pos != NULL)
	{
		pValue = (CValue *)oParse.GetNext(pos);

		char *pchIndex;
		CString_to_char(pValue->m_strID, &pchIndex);
		nIndex = ParserIndexParas(pchIndex) - 1;
	
		//nIndex = CString_To_long(pValue->m_strID) - 1;
		pData = (CShortData*)listDatas.GetAtIndex(nIndex);

		if (pData == NULL)
		{
			continue;
		}

		if (nBinBegin <=nIndex && nIndex < nBinEnd)
		{
			listBinValue.AddTail(pValue);
			pData = (CShortData*)listDatas.GetAtIndex(nIndex - nBinOffset);
			pValue->m_dwItemData = (DWORD)pData;
		}
	}

	pos = listBinValue.GetHeadPosition();
	pBinRslt->m_strValue = _T("");

	while (pos != NULL)
	{
		pValue = (CValue *)listBinValue.GetNext(pos);

		char *pchIndex;
		CString_to_char(pValue->m_strID, &pchIndex);

		pValue->m_strID = ParserValueParas(pchIndex, nBinBegin);
        pBinRslt->m_strValue.AppendFormat(_T("(%s,%s)"), pValue->m_strID.GetString(), pValue->m_strValue.GetString());

	}

	listDatas.RemoveAll();
	listBinValue.RemoveAll();
}

int	CGuideBookTool::ParserIndexParas(char *pchIndex)
{
	int nGroup[3]={0};
	char *pNext= NULL;
	char *pCh = strtok_s(pchIndex, ".", &pNext);

	int n=0;
	while (pCh!=NULL)
	{
		if (n>2)
			break;
		nGroup[n] = atoi(pCh);
		pCh = strtok_s( NULL, ".", &pNext);
		n++;
	}

	if (nGroup[1]<17)	// �����
	{
		return (nGroup[0]-1)*512+(nGroup[1]-1)*32+nGroup[2];
	}
	else		// Goose��
	{
		return 512+nGroup[2];
	}
}

CString CGuideBookTool::ParserValueParas(char *pchIndex, long nOffset)
{
	CString strValue;

	int nGroup[3]={0};
	char *pNext= NULL;
	char *pCh = strtok_s(pchIndex, ".", &pNext);

	int n=0;
	while (pCh!=NULL)
	{
		if (n>2)
			break;
		nGroup[n] = atoi(pCh);
		pCh = strtok_s( NULL, ".", &pNext);
		n++;
	}

	int nIndex = nOffset / 32;

	if (nGroup[1] <= nIndex)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�����зֳ���%s��ƫ������%d"), pchIndex, nOffset);
		return strValue;
	}

	nGroup[1] -= nIndex;

	strValue.AppendFormat(_T("%d.%d.%d"), nGroup[0], nGroup[1], nGroup[2]);

	return strValue;
}

BOOL CGuideBookTool::ValuesParseHasValue(CValuesParse &oValParse, const CString &strValue, CString &strValueUnwant)
{
	POS pos = oValParse.GetHeadPosition();
	CValue *pValRslt = NULL;
	BOOL bHas = FALSE;
	CString strCurr;

	while (pos != NULL)
	{
		pValRslt = (CValue *)oValParse.GetNext(pos);
		strCurr = pValRslt->m_strValue.Left(1);

		if (strCurr == strValue)
		{
            strValueUnwant.AppendFormat(_T("��%s��"), pValRslt->m_strID.GetString());
			bHas = TRUE;
			continue;
		}
	}

	return bHas;
}

BOOL CGuideBookTool::ValuesParseRedundancy(CValuesParse &oValParse, CString &strValueUnwant)
{
	POS pos = oValParse.GetHeadPosition();
	CValue *pValRslt = NULL;
	BOOL bHas = FALSE;

	while (pos != NULL)
	{
		pValRslt = (CValue *)oValParse.GetNext(pos);
        strValueUnwant.AppendFormat(_T("��%s��"), pValRslt->m_strID.GetString());
		bHas = TRUE;
		continue;
	}

	return bHas;
}

BOOL CGuideBookTool::NeedExtractBinputsResult(CValues *pValues)
{
	CValue *pBinRslt1 = (CValue *)pValues->FindByID(g_strBinaryRsltID_SwitchGroup);
	CValue *pBinRslt2 = (CValue *)pValues->FindByID(g_strBinaryRsltID_SwitchGroupAll);

	if (pBinRslt1 != NULL && pBinRslt2 != NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CGuideBookTool::FindRefuseBinary(CValuesParse *pParsePara, CValuesParse *pParseResult, CString &strValueRefuse)
{
	POS pos = pParsePara->GetHeadPosition();

	CValue *pParse = NULL;
	CValue *pResult = NULL;

	while (pos != NULL)
	{
		pParse = (CValue *)pParsePara->GetNext(pos);
		pResult = (CValue *)pParseResult->FindByID(pParse->m_strID);

		if (pResult == NULL)
		{//û�ҵ�������ʾ�����ͷû�иö��Ĳ��������ܶ�
            strValueRefuse.AppendFormat(_T("��%s��"), pParse->m_strID.GetString());
		}
	}
}

/*
strValuePara:(path, value)====(1.2.1,1)
strValueRslt(Index,value, t)====(33,1)
*/
long CGuideBookTool::BinRslt(const CString &strParaID, const CString &strValuePara, const CString &strValueRslt, CString &strValueRefuse, CString &strValueUnwant)
{
	CDataGroup *pDataGroup = (CDataGroup*)g_pGuideBookTool->FindByID(strParaID);

	if (pDataGroup == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("����ID[%s]��Ӧ�������ļ�������"), strParaID.GetString());
		return 0;
	}

	pDataGroup->InitReserved(0);
	pDataGroup->InitItemData(0);
	CValuesParse oParsePara(strValuePara);
	CValuesParse oParseRslt(strValueRslt);
	CExBaseList listParaDatas, listRsltDatas;

	g_pGuideBookTool->ParseDatas_Index(pDataGroup, oParseRslt, listRsltDatas, FALSE);
	g_pGuideBookTool->ParseDatas_ID_To_Index(pDataGroup, oParsePara, listParaDatas);

	POS pos = oParseRslt.GetHeadPosition();
	CValue *pValue = NULL;
	CValue *pFind = NULL;
	long nRslt = 1;
	CString strValue;

	while (pos != NULL)
	{
		pValue = (CValue*)oParseRslt.GetNext(pos);
		pFind = (CValue *)oParsePara.FindByID(pValue->m_strID);

		if (pFind == NULL)
		{//�ද pValue���Ƕද�ĵ㣬����࣬������
            strValueUnwant.AppendFormat(_T("��%s��"), pValue->m_strID.GetString());
			nRslt = 0;
			break;
		}

		strValue = pValue->m_strValue.Left(1);

		if (strValue != pFind->m_strValue)
		{//״̬���ԣ����Ǿܶ�
            strValueRefuse.AppendFormat(_T("��%s��"), pFind->m_strID.GetString());
			nRslt = 0;
			break;
		}
	}

	if(oParseRslt.GetCount() != oParsePara.GetCount())
	{//�����࣬����٣����Ǿܶ���Ӧ�ñ����������ڽ���в��ң���¼�Ҳ����Ľڵ㣬���Ǿܶ��ĵ�
		FindRefuseBinary(&oParsePara, &oParseRslt, strValueRefuse);
		nRslt = 0;
	}
	
	listRsltDatas.RemoveAll();
	listParaDatas.RemoveAll();

	return nRslt;
}

long CGuideBookTool::BinStateRslt(const CString &strParaID, const CString &strValuePara, const CString &strValueRslt, CString &strValueRefuse, CString &strValueUnwant)
{
	CDataGroup *pDataGroup = (CDataGroup*)g_pGuideBookTool->FindByID(strParaID);

	if (pDataGroup == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("����ID[%s]��Ӧ�������ļ�������"), strParaID.GetString());
		return 0;
	}
	
	pDataGroup->InitReserved(0);
	pDataGroup->InitItemData(0);

	CValuesParse oParsePara(strValuePara);
	CValuesParse oParseRslt(strValueRslt);
	CExBaseList listParaDatas, listRsltDatas;

	g_pGuideBookTool->ParseDatas_Index(pDataGroup, oParseRslt, listRsltDatas, FALSE);
	g_pGuideBookTool->ParseDatas_ID_To_Index(pDataGroup, oParsePara, listParaDatas);

	POS pos = oParsePara.GetHeadPosition();
	CValue *pValue = NULL;
	CValue *pValRslt = NULL;
	long nRslt = 1;
	CString strValue;

	while (pos != NULL)
	{
		pValue = (CValue*)oParsePara.GetNext(pos);  //���������������ֵ                   
		pValRslt = (CValue *)oParseRslt.FindByID(pValue->m_strID);   //�����������SwitchGroup��CheckGroup

		if (pValRslt == NULL)
		{//������״̬������ӽ��������û���ҵ�
			//ֱ���в��ϸ񣬲��Խ��״̬��ȱʡֵ��Ϊ���֣���Ҫ���״̬������Ҫ��CheckGroup��Ϊ����������SwitchGroup
			nRslt = 0;
            strValueRefuse.AppendFormat(_T("��%s��"), pValue->m_strID.GetString());
			continue;
// 			if (pValue->m_strValue == _T("1"))
// 			{//��������״ֵ̬Ϊ1�����ϸ���Ϊ���״̬ȱʡֵΪ0����װ��״̬������0�������ͱ�λ��Ϣ��
// 				nRslt = 0;
// 				strValueRefuse.AppendFormat(_T("��%s��"), pValue->m_strID);
// 				break;
// 			}
// 			else
// 			{
// 				continue;
// 			}
		}

		strValue = pValRslt->m_strValue.Left(1);    //���������ֵ

		if (strValue != pValue->m_strValue)
		{//���������״̬
            strValueRefuse.AppendFormat(_T("��%s��"), pValue->m_strID.GetString());
			nRslt = 0;
			//continue;;
		}

		oParseRslt.Delete(pValRslt);
	}

	if (nRslt == 1)
	{
		if (ValuesParseRedundancy(oParseRslt, strValueUnwant))
		{//����Ľ����������Ϊ���󶯵�
			nRslt = 0;
		}
		//��������û����ȫ������ϵģ���ΪȱʡֵΪ0�����ԣ�ֻҪ�ǰ�����1���������в��ϸ�
	//	if (ValuesParseHasValue(oParseRslt, _T("1"), strValueUnwant))
	//	{
	//		nRslt = 0;
	//	}
	}

	listRsltDatas.RemoveAll();
	listParaDatas.RemoveAll();

	return nRslt;
}

long CGuideBookTool::BinChngCntRslt(const CString &strParaID, const CString &strBinChngData, const CString &strValueRslt)
{
	CDataGroup *pDataGroup = (CDataGroup*)g_pGuideBookTool->FindByID(strParaID);

	if (pDataGroup == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("����ID[%s]��Ӧ�������ļ�������"), strParaID.GetString());
		return 0;
	}

	pDataGroup->InitReserved(0);
	pDataGroup->InitItemData(0);

	CValuesParse oParseBinChngData(strBinChngData);
	CValuesParse oParseRslt(strValueRslt);
	CExBaseList listParaDatas, listRsltDatas;

	g_pGuideBookTool->ParseDatas_Index(pDataGroup, oParseRslt, listRsltDatas, FALSE);

	POS pos = oParseBinChngData.GetHeadPosition();
	CValue *pValue = NULL;
	CValue *pValRslt = NULL;
	long nRslt = 1;
	CString strValue;
	long nChngCount = 0, nRsltChgCount=0;
	POS posRslt = NULL, posRsltPrev = NULL;

	while (pos != NULL)
	{
		pValue = (CValue*)oParseBinChngData.GetNext(pos);
		nChngCount = CString_To_long(pValue->m_strValue);
		nRsltChgCount = 0;
		posRslt = oParseRslt.GetHeadPosition();

		while (posRslt != NULL)
		{
			posRsltPrev = posRslt;
			pValRslt = (CValue *)oParseRslt.GetNext(pos);
			
			if (pValRslt->m_strID == pValue->m_strID)
			{
				oParseRslt.DeleteAt(posRsltPrev);
				nRsltChgCount++;
			}
		}

		if (nRsltChgCount != nChngCount)
		{
			nRslt = 0;
			break;
		}
	}

	if (nRslt == 1)
	{//��������û����ȫ������ϵģ��������ı�λ�����в��ϸ�
		//if (ValuesParseHasValue(oParseRslt, _T("1")))
		if (oParseRslt.GetCount() > 0)
		{
			nRslt = 0;
		}
	}

	listRsltDatas.RemoveAll();
	listParaDatas.RemoveAll();

	return nRslt;
}

//////////////////////////////////////////////////////////////////////////
//�������滻
/*
���뿪�������滻�㷨˵����
	1����ȡg_strBinaryParaID_Boutputs��g_strBinaryParaID_BinputsResult����¼ParaData����
	2������ParaData����Ĳ�������ȡ���ڵ�
	3���Ը��ڵ㰴�����ν�������Ȼ�����滻��ӳ���ϵ��
	4������ParaData���󣬽����滻

���ݼ��滻
	1��

*/
void CGuideBookTool::BinaryReplace(CGuideBook *pGuideBook, CDvmDataset *pBinParas, CDvmDataset *pBoutParas, CDvmDataset *pDsBins, CDvmDataset *pDvmBouts)
{
	
}

//////////////////////////////////////////////////////////////////////////
//
CGuideBookReadTool::CGuideBookReadTool()
{
	memset(m_pGbAttrReadBuffer, 0, GuideBook_Attrs_Read_Buffer_Len);
	memset(m_pWGbAttrReadBuffer, 0, GuideBook_Attrs_Read_Buffer_Len*2);
}

CGuideBookReadTool::~CGuideBookReadTool()
{

}

BOOL CGuideBookReadTool::ReadAttrs(const CString &strFile, CGuideBook *pGuideBook)
{
	CFile oFile;

	if (!oFile.Open(strFile, CFile::modeRead))
	{
		return FALSE;
	}

	m_nGbAttrBufferLen = oFile.Read(m_pGbAttrReadBuffer, GuideBook_Attrs_Read_Buffer_Len-10);
	ProcessBuffer();
	str_char_to_wchar(m_pWGbAttrReadBuffer, m_pGbAttrReadBuffer, m_nGbAttrBufferLen);

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(_PUGI_XML_TYPE_);
	pRWDoc->SetXml(m_pWGbAttrReadBuffer);
	CXmlRWNodeBase *pDocRoot = pRWDoc->GetDocNode();
	pDocRoot = pDocRoot->GetChildNode(CGbXMLKeys::g_pGbXMLKeys->m_strGuideBookKey);

	if(!pDocRoot->IsValid())
	{
		return FALSE;
	}

	pGuideBook->FreeGuideBook();
	pGuideBook->XmlRead(*pDocRoot,CGbXMLKeys::g_pGbXMLKeys);

	return TRUE;
}
/*
<guidebook
	<dataset name="Develop" id="Develop" 
		........................
	</dataset>

*/
void CGuideBookReadTool::ProcessBuffer()
{
	char *pTemp = m_pGbAttrReadBuffer;
	char *pPos = NULL;
	char *pEnd = m_pGbAttrReadBuffer + m_nGbAttrBufferLen - 10;

	while (pTemp < pEnd)
	{
		if (pTemp[0] == '<' && pTemp[1] == '/' && pTemp[2] == 'd' && pTemp[3] == 'a' && pTemp[4] == 't' && pTemp[5] == 'a' && pTemp[6] == 's' && pTemp[7] == 'e' && pTemp[8] == 't' && pTemp[9] == '>')
		{
			pTemp += 10;
			strcpy(pTemp, "</guidebook>");
			pTemp += 12;
			memset(pTemp, 0, 10);
			m_nGbAttrBufferLen = pTemp - m_pGbAttrReadBuffer;
			break;
		}

		pTemp++;
	}
}


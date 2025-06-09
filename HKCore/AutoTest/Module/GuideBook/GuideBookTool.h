#pragma once
#include "GuideBook.h"
#include "MacroTest.h"
#include "../../../Module/DataMngr/ValuesParse.h"

class CGuideBookTool : public CExBaseList
{
private:
	CGuideBookTool(void);
	virtual ~CGuideBookTool(void);

	static CGuideBookTool *g_pGuideBookTool;
	static long g_nGuideBookToolRef;

	CExBaseList m_listDataTypes;

	void InitTool();
	void InitToolConfigFile(const CString &strID);

	void AddDataTypes(const CString &strDataTypesFile);

	static CShortData* FindDataRoot(CDataGroup *pGroup, const CString &strPath);
	static CShortData* FindData(CDataGroup *pGroup, const CString &strPath, const CString &strFlag);
	static CString GetDataPath(CShortData *pData, CExBaseObject *pRoot, const CString &strFlag);

public:
	static CGuideBookTool* Create();
	static void Release();

//////////////////////////////////////////////////////////////////////////
//开关量偏移
public:
	static CDataTypes* FindDataTypes(const CString &strDataTypesFile);
	static void ParseDatas(CDataGroup *pDataGroup, const CString &strDatas, CExBaseList &listDatas);
	static void InitDestDatas(CDataGroup *pRootGroup, CExBaseList &listDatas, CString &strDatas);

	static void OffsetBinary(CGuideBook *pGuideBook, long nBinOffset, long nBoutOffset);

protected:
	void ParseDatas(CDataGroup *pDataGroup, CValuesParse &oParse, CExBaseList &listDatas, BOOL bSetValue=TRUE);
	void ParseDatas_ID_To_Index(CDataGroup *pDataGroup, CValuesParse &oParse, CExBaseList &listDatas);
	void ParseDatas_Index(CDataGroup *pDataGroup, CValuesParse &oParse, CExBaseList &listDatas, BOOL bSetValue=TRUE, long nOffset=0);
	void In_OffsetBinary(CGuideBook *pGuideBook, long nBinOffset, long nBoutOffset);
	void In_OffsetBinaryList(CExBaseList *pList, long nBinOffset, long nBoutOffset);
	void In_OffsetBinaryMacroTest(CMacroTest *pMacroTest, long nBinOffset, long nBoutOffset);
	void In_OffsetBinaryMacroTestPara(CMacroTestParaData *pPara, long nBinOffset, long nBoutOffset);
	void In_OffsetBinaryMacroTestPara(CDataGroup *pDataGroup, CMacroTestParaData *pPara, long nOffset);

public:
	static void CombineTestParaDatas(CString &strDestParaDatas, const CString &strSrcDatas);
	static BOOL HasBinaryTestParas(const CString &strParaDatas);
	static void ExtractBinputsResult(CValues *pValues, long nBinBegin, long nBinEnd, long nBinOffset);
	static long BinRslt(const CString &strParaID, const CString &strValuePara, const CString &strValueRslt, CString &strValueRefuse, CString &strValueUnwant);
	static long BinStateRslt(const CString &strParaID, const CString &strValuePara, const CString &strValueRslt, CString &strValueRefuse, CString &strValueUnwant);
	static long BinChngCntRslt(const CString &strParaID, const CString &strBinChngData, const CString &strValueRslt);
	static void FindRefuseBinary(CValuesParse *pParsePara, CValuesParse *pParseResult, CString &strValueRefuse);
	static BOOL NeedExtractBinputsResult(CValues *pValues);

protected:
	void CombineTestParaDatas(CString &strDestParaDatas, const CString &strSrcDatas, const CString &strParaID);
	void ExtractBinputsResult(const CString &strValueID, CValues *pValues, long nBinBegin, long nBinEnd, long nBinOffset);
	void ExtractBinputsResult2(const CString &strValueID, CValues *pValues, long nBinBegin, long nBinEnd, long nBinOffset);
	static BOOL ValuesParseHasValue(CValuesParse &oValParse, const CString &strValue, CString &strValueUnwant); //冗余的结果为strValue的结果参数
	static BOOL ValuesParseRedundancy(CValuesParse &oValParse, CString &strValueUnwant); //冗余的结果参数
	int	ParserIndexParas(char *pchIndex);
	CString ParserValueParas(char *pchIndex, long nOffset);

//////////////////////////////////////////////////////////////////////////
//开关量替换
public:
	static void BinaryReplace(CGuideBook *pGuideBook, CDvmDataset *pBinParas, CDvmDataset *pBoutParas, CDvmDataset *pDsBins, CDvmDataset *pDvmBouts);

};

#define GuideBook_Attrs_Read_Buffer_Len   4100
class CGuideBookReadTool
{
public:
	CGuideBookReadTool();
	virtual ~CGuideBookReadTool();

public:
	BOOL ReadAttrs(const CString &strFile, CGuideBook *pGuideBook);

private:
	char m_pGbAttrReadBuffer[GuideBook_Attrs_Read_Buffer_Len];
	wchar_t m_pWGbAttrReadBuffer[GuideBook_Attrs_Read_Buffer_Len];
	long m_nGbAttrBufferLen;

	void ProcessBuffer();
};
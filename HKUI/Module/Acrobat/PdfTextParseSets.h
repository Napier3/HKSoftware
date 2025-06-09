#pragma once

#include "PdfTextParse.h"
#include "../DataMngr/DvmLogicDevice.h"
#include "../DataMngr/DvmDataset.h"

class CPdfTextParseSets : public CPdfTextParse
{
public:
	CPdfTextParseSets();
	virtual ~CPdfTextParseSets();

	CDvmLogicDevice *m_pDestLogicDevice;

	virtual void Parse(CExpandMemBuf *pBuffer);

	void AddDatasetTitle(const CString &strTitle)
	{
		m_astrDatasetTitle.Add(strTitle);
	}


protected:
	CDvmDataset *m_pCurrDataset;
	long m_nDataIndex;
	CStringArray m_astrDatasetTitle;
	BOOL m_bCan_ParseLine_attr;

	virtual BOOL IsDatasetTitle(const CString &strText, CString &strKey);
	virtual BOOL IsLineDatasetTitle(CPdfTextLine *pLine, CString &strKey);
	virtual CString GetDatasetTitle(const CString &strKey);

	void ParseLine(CPdfTextLine *pLine);
	void ParseLine_attr(CPdfTextLine *pLine);
	void ParseLine_data(CPdfTextLine *pLine);
	void ParseLine_data_prev(CPdfTextLine *pLine);
	void GetNameAndUnit(const CString &strText, CString &strName, CString &strUnit);
	void GetNameUnitValue(const CString &strText, CString &strName, CString &strUnit, CString &strValue);

	CString GetValue(long nIndex, CPdfTextData *pTextValue, CPdfTextData *pTextValue2, CString &strIndexNext);
	BOOL MergeName(CPdfTextData *pTextName, CPdfTextData *pTextValue);
	BOOL CanMergeName(CPdfTextData *pTextName);

protected:
	virtual void FormatEx(CBufferBase *pBuffer);

	void FormatEx_Degree(CBufferBase *pBuffer);
};

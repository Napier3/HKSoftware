#pragma once

#include "..\GuideBook\GuideBook.h"

class CGbDvmComboBox :	public CComboBox
{
public:
	CGbDvmComboBox(void);
	~CGbDvmComboBox(void);

public:
	void ShowDvmTree(CDevice *pDevice);
	CDataSet* GetCurrSelDataset();
	void SelectDataset(CDataSet *pDataset);
	void SelectDataset(const CString &strDatasetID);
	
private:
	CString m_strFilterDsID;
	CStringArray m_astrFilterDsID;

public:
	void AddFilterDsID(const CString &strFilterDsID);
};

void GbDvmCmb_ShowDvmTree(CDevice *pDevice, CComboBox *pCombBox, const CStringArray &astrFilterDsID);


class CDvmDatasetFilterTool
{
private:
	CDvmDatasetFilterTool();
	virtual ~CDvmDatasetFilterTool();

public:
	static CFilterTextMngr *g_pDatasetFilter;
	static long g_nDatasetFilterCount;
	static CString g_strDatasetFilterFile;
	static CDWordArray g_dwarrCmbDsFilter;

	static CDvmDatasetFilterTool *g_pDvmDatasetFilterTool;
	static CDvmDatasetFilterTool* Create();
	static void Release();

	static CFilterTextMngr* GetFilterTextMngr();
	static void AddDatasetCmbFilter(CComboBox *pComboBox);
	static void FreeDatasetCmbFilter(CComboBox *pComboBox);
	static void UpdateAllDatasetCmbFilter(CComboBox *pComboBox);

};
#pragma once


// CDvmDatasetComboBox
#include "../../../Module/BaseClass/ExBaseListComboBox.h"
#include "../GuideBook/GuideBook.h"

class CDvmDatasetComboBox : public CExBaseListComboBox
{
	DECLARE_DYNAMIC(CDvmDatasetComboBox)

public:
	CDvmDatasetComboBox();
	virtual ~CDvmDatasetComboBox();

	virtual CExBaseObject* SetCurrSelByID(const CString &strID);
	virtual BOOL GetSelectID(CString &strID);

public:
	virtual void InitComboBox(CExBaseObject* pItem, const CString &strCpuID, const CString &strDataset);
	virtual void InitComboBox(CExBaseList &oListDataset, const CString &strIDPath);
	virtual long AddObj(CExBaseObject *pObj);


protected:
	DECLARE_MESSAGE_MAP()
};



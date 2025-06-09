#pragma once

#include "..\..\Module\KeyDb\XMatchEditGridCtrlBase.h"


class CGbDeviceReplaceByMmsDvmEditGrid : public CXMatchEditGridCtrlBase
{
public:
	CGbDeviceReplaceByMmsDvmEditGrid(void);
	~CGbDeviceReplaceByMmsDvmEditGrid(void);

public:
	void UpdateMap();
	void SetReplaceDatasets(CExBaseList *pDataset)	{	m_pReplaceDatasets = pDataset;	}
	void AddAllDatasToDlg(BOOL bShowDlg=TRUE);

protected:
	//被替换位的数据集
	CExBaseList *m_pReplaceDatasets;
	
	virtual void ShowAllDatasToDlg();
	virtual void CreateAllDatasDlg();
	

};

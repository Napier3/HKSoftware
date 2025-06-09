#ifndef QMUGOOSEBINGRID_H
#define QMUGOOSEBINGRID_H
#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgGoutCh.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgGinCh.h"
#include <QPair>

class QTerminalGooseGrid :public  QExBaseListGridBase
{
	Q_OBJECT

public:

	QTerminalGooseGrid(QWidget* pParent);
	virtual ~QTerminalGooseGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void UpdateData_ByDataType(CIecCfgGinCh *pGinCh,int nRow);
	//20240222chenling实测值，测试结果
	void BoutToGinResultVlaues(float fResultTimeVlaue,char strCharacterIndex);//开出转Goose
	void GoutToBinResultVlaues(float fResultTimeVlaue,char strCharacterIndex);//Goose转开入
	void ClearBoutToGinResultData();
	void ClearGoutToBinResultData();

	
	void UpdateBoutToGinGrid(long nIndex);
	void UpdateGoutToBinGrid(long nIndex);

	QList <QPair<CString, float> >m_pGooseOutData;
	QList <QPair<CString, float> >m_pGooseInData;

};

#endif
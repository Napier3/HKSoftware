#include "SclCtrlChsGridBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfg92Ch.h"
#include "../../Module/CommonMethod/commonMethod.h"

QSclCtrlChsGridBase::QSclCtrlChsGridBase(QWidget* pparent):QExBaseListGridBase(pparent)
{

}

QSclCtrlChsGridBase::~QSclCtrlChsGridBase()
{

}

void QSclCtrlChsGridBase::InitGrid()
{
	InitGridTitle();
#ifdef _PSX_QT_LINUX_
	SetDefaultRowHeight(50);
#endif
	//	AutoAdjColWidth();
}

void QSclCtrlChsGridBase::InitGridTitle()
{
	//	QExBaseListGridBase::InitGridTitle();
}

void QSclCtrlChsGridBase::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	//	QExBaseListGridBase::ShowData(pData,nRow,bInsertRow);
}

CDataType* QSclCtrlChsGridBase::FindDataType(const CString &strDataType)
{
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(strDataType);

	return pDataType;
}


void QSclCtrlChsGridBase::OnDataSelChanged(int nRow, int nCol)
{
	//QExBaseListGridBase::OnDataSelChanged(nRow,nCol);
}


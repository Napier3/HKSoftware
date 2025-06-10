#ifndef QSTTMACROPARAEDITGRID_H
#define QSTTMACROPARAEDITGRID_H

#include "../../../UI/Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../SttTestGridDefine/SttGdGridInst.h"

class QSttMacroParaEditGrid : public QExBaseListGridBase
{
	Q_OBJECT
public:
	explicit QSttMacroParaEditGrid(QWidget *parent);
	virtual ~QSttMacroParaEditGrid();
public:
	void InitColDef(CSttGdGridInst *pCurrGridInst);

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
public:
	CSttGdGridInst *m_pCurrGridInst;
	
};

#endif // QSTTMACROPARAEDITGRID_H

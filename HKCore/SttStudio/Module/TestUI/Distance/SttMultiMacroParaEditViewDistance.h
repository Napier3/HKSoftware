#ifndef STTMULTIMACROPARAEDITVIEWDISTANCE_H
#define STTMULTIMACROPARAEDITVIEWDISTANCE_H

#include <QWidget>
#include "./DistanceAddMultDlg.h"
#include "./DistanceItemParaEditWidget.h"
#include "./DistanceCommonParasDlg.h"
#include "./DistanceBinarysDlg.h"
#include "../QSttMultiMacroParaEditViewBase.h"
#include "../Module/CommonGrid/QSttMacroParaEditGrid.h"

#include "../../../../Module/TestMacro/TestMacro.h"


class QSttMultiMacroParaEditViewDistance : public QSttMultiMacroParaEditViewBase
{
    Q_OBJECT

public:
    explicit QSttMultiMacroParaEditViewDistance(const CString &strGridFile,QWidget *parent = 0);
    virtual ~QSttMultiMacroParaEditViewDistance();

	virtual void InitUI_OneMacro();
	virtual void InitDatas();
	virtual void ConnectAll_SigSlot();
	virtual void DisConnectAll_SigSlot();

protected:
	CSttGdGridInst *m_pZPhiGridInst;
	CSttGdGridInst *m_pRXGridInst;


public slots:
	virtual void on_m_btnAddOneItem_clicked();
	virtual void on_m_btnAddMultiItem_clicked();
	virtual void on_m_btnCommonParas_clicked();
	virtual void on_m_btnBinarys_clicked();
	virtual void on_m_btnDeleteItem_clicked();
	virtual void on_m_btnClearResult_clicked();

private slots:
	void on_m_btnAddOne_LN_clicked();
	void on_m_btnAddOne_LL_clicked();
	void on_m_btnAddMult_clicked();

private:

	CDataGroup *m_pParas;
	QDialog *m_pAddMultiItemSelectDlg;//添加系列选择页面
};

#endif // STTMULTIMACROPARAEDITVIEWDISTANCE_H

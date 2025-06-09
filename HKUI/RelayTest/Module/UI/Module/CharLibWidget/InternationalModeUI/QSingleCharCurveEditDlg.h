#ifndef QSINGLECHARCURVEEDITDLG_H
#define QSINGLECHARCURVEEDITDLG_H

#include <QDialog>
#include "../CharEditWidget_Distance.h"
#include "CharactEditWidget_Eng.h"

namespace Ui {
class QSingleCharCurveEditDlg;
}

class QSingleCharCurveEditDlg : public QDialog, public CExBaseListGridOptrInterface
{
    Q_OBJECT

public:
    explicit QSingleCharCurveEditDlg(CCharacteristic *pCCharacteristic, QWidget *parent = 0);
    ~QSingleCharCurveEditDlg();

    void InitUI();
    void UpdateCharElement();
    void UpdateBtnEnable();
	void UpdateDrawCharacters();
    virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

private slots:
    void on_m_btnModify_clicked();
    void on_m_btnDelete_clicked();
    void on_m_btnInsert_clicked();
    void on_m_cbAutoClose_stateChanged(int arg1);
    void on_m_btnOk_clicked();
    void on_m_btnCancel_clicked();

private:
    Ui::QSingleCharCurveEditDlg *ui;
    QCharEditGrid_TestPoint *m_pGridTestPoint;  //曲线编辑表格
    QCharactEditWidget_Eng* m_pCharactEditWidget;   //曲线编辑坐标轴

    CCharacteristics *m_pCharacteristics_Inner;  //用于绘图，只有m_pCharacteristic_Inner一个子节点
    CCharacteristic *m_pCharacteristic_Inner;   //内部特性曲线对象
    CCharacteristic *m_pCharacteristic_Exter;   //保存传入的外部特性曲线对象指针

    CExBaseList m_oLineCache;
};

#endif // QSINGLECHARCURVEEDITDLG_H

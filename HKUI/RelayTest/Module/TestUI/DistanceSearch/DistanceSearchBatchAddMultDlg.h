#ifndef DISTANCESEARCHBATCHADDMULTDLG_H
#define DISTANCESEARCHBATCHADDMULTDLG_H

#include <QDialog>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include "../../../../Module/DataMngr/DataGroup.h"

namespace Ui {
class QDistanceSearchBatchAddMultDlg;
}

class QDistanceSearchBatchAddMultDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QDistanceSearchBatchAddMultDlg(QWidget *parent = 0);
    ~QDistanceSearchBatchAddMultDlg();
    void InitUI();
    void InitConnect();
	void SetDatas(CDataGroup *pParas);
	void GetDatas(CDataGroup *pParas);
    void UpdateFromCharact();

private:
    void SetValueToPage(CDvmData *pData);
    void GetPageToValue(CDvmData *pData);
    void CheckAllPresence();
	
private:
    Ui::QDistanceSearchBatchAddMultDlg *ui;

    CDataGroup *m_pCurrDataGroup;

    QCheckBox *m_cbLNZoneOne;
	QCheckBox *m_cbLNOneAN;
	QCheckBox *m_cbLNOneBN;
	QCheckBox *m_cbLNOneCN;

    QCheckBox *m_cbLNZoneTwo;
	QCheckBox *m_cbLNTwoAN;
	QCheckBox *m_cbLNTwoBN;
	QCheckBox *m_cbLNTwoCN;

    QCheckBox *m_cbLNZoneThree;
	QCheckBox *m_cbLNThreeAN;
	QCheckBox *m_cbLNThreeBN;
	QCheckBox *m_cbLNThreeCN;

    QCheckBox *m_cbLNZoneFour;
	QCheckBox *m_cbLNFourAN;
	QCheckBox *m_cbLNFourBN;
	QCheckBox *m_cbLNFourCN;

    QCheckBox *m_cbLNZoneFive;
	QCheckBox *m_cbLNFiveAN;
	QCheckBox *m_cbLNFiveBN;
	QCheckBox *m_cbLNFiveCN;

    QCheckBox *m_cbLLZoneOne;
	QCheckBox *m_cbLLOneAB;
	QCheckBox *m_cbLLOneBC;
	QCheckBox *m_cbLLOneCA;
	QCheckBox *m_cbLLOneABC;

    QCheckBox *m_cbLLZoneTwo;
	QCheckBox *m_cbLLTwoAB;
	QCheckBox *m_cbLLTwoBC;
	QCheckBox *m_cbLLTwoCA;
	QCheckBox *m_cbLLTwoABC;

    QCheckBox *m_cbLLZoneThree;
	QCheckBox *m_cbLLThreeAB;
	QCheckBox *m_cbLLThreeBC;
	QCheckBox *m_cbLLThreeCA;
	QCheckBox *m_cbLLThreeABC;

    QCheckBox *m_cbLLZoneFour;
	QCheckBox *m_cbLLFourAB;
	QCheckBox *m_cbLLFourBC;
	QCheckBox *m_cbLLFourCA;
	QCheckBox *m_cbLLFourABC;

    QCheckBox *m_cbLLZoneFive;
	QCheckBox *m_cbLLFiveAB;
	QCheckBox *m_cbLLFiveBC;
	QCheckBox *m_cbLLFiveCA;
	QCheckBox *m_cbLLFiveABC;

	QLineEdit *m_editActTimeLNOne;
	QLineEdit *m_editActTimeLNTwo;
	QLineEdit *m_editActTimeLNThree;
	QLineEdit *m_editActTimeLNFour;
	QLineEdit *m_editActTimeLNFive;

	QLineEdit *m_editActTimeLLOne;
	QLineEdit *m_editActTimeLLTwo;
	QLineEdit *m_editActTimeLLThree;
	QLineEdit *m_editActTimeLLFour;
	QLineEdit *m_editActTimeLLFive;

private slots:
	void on_m_btnOk_clicked();
	void on_m_btnCancel_clicked();
    void on_m_cbLNZoneOne_StateChanged(int state);
    void on_m_cbLNZoneTwo_StateChanged(int state);
    void on_m_cbLNZoneThree_StateChanged(int state);
    void on_m_cbLNZoneFour_StateChanged(int state);
    void on_m_cbLNZoneFive_StateChanged(int state);
    void on_m_cbLLZoneOne_StateChanged(int state);
    void on_m_cbLLZoneTwo_StateChanged(int state);
    void on_m_cbLLZoneThree_StateChanged(int state);
    void on_m_cbLLZoneFour_StateChanged(int state);
    void on_m_cbLLZoneFive_StateChanged(int state);
    void on_m_editActTimeLNOne_editingFinished();
    void on_m_editActTimeLNTwo_editingFinished();
    void on_m_editActTimeLNThree_editingFinished();
    void on_m_editActTimeLNFour_editingFinished();
    void on_m_editActTimeLNFive_editingFinished();
    void on_m_editActTimeLLOne_editingFinished();
    void on_m_editActTimeLLTwo_editingFinished();
    void on_m_editActTimeLLThree_editingFinished();
    void on_m_editActTimeLLFour_editingFinished();
    void on_m_editActTimeLLFive_editingFinished();
};

#endif // DISTANCESEARCHBATCHADDMULTDLG_H

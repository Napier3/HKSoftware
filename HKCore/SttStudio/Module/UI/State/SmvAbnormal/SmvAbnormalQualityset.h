#ifndef QUALITYSET_H
#define QUALITYSET_H

#include <QDialog>
#include <QWidget>
#include "../../Controls/SttLineEdit.h"
#include "ui_SmvAbnormalQualityset.h"


class QSmvAbnormalQualitySet : public QDialog
{
	Q_OBJECT

public:
	Ui::SmvAbnormalQualitySet *ui;

	QSmvAbnormalQualitySet(QList<int> &listQuality, QWidget *parent = 0);
	~QSmvAbnormalQualitySet();

	void initData();
        void InitLanguage();
	int GetValue();
	void GetValues();
	void SetSmvAbnormalQualityFont();

protected slots:
	void slot_pbn_OKClicked();
	void slot_pbn_CancelClicked();
	void slot_cmb_bit1StateChanged(int index);
	void slot_cmb_bit2StateChanged(int index);
	void slot_cmb_bit3StateChanged(int index);
	void slot_cmb_bit4StateChanged(int index);
	void slot_cmb_bit5StateChanged(int index);
	void slot_cmb_bit6StateChanged(int index);
	void slot_cmb_bit7StateChanged(int index);
	void slot_cmb_bit8StateChanged(int index);
	void slot_cmb_bit9StateChanged(int index);
	void slot_cmb_bit10StateChanged(int index);
	void slot_cmb_bit11StateChanged(int index);
	void slot_cmb_bit12StateChanged(int index);
	void slot_cmb_DispTypeStateChanged(int index);
	//void slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor);
	void slot_lne_DispTypeKeyBoard();

signals:
	void sig_QualityPara(QList<int> &);

private:
	QList<int> m_listQualityParas;
};

extern QFont *g_pSttGlobalFont;

#endif // QUALITYSET_H

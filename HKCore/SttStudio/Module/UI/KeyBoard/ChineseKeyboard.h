#ifndef CHINESEKEYBOARD_H
#define CHINESEKEYBOARD_H

#include <QDialog>
#include <QKeyEvent>
#include <QSignalMapper>
#include <QTextEdit>
#include <QListWidget>
#include "ui_ChineseKeyboard.h"
#include "../../../../Module/OSInterface/QT/CString_QT.h"

class ChineseKeyboard : public QDialog, public Ui::ChineseKeyboard
{
	Q_OBJECT
private:
	QWidget* m_pParent;
	QSignalMapper* m_pSignalMapper;
	QList<QToolButton* > m_pButtonsList;

	QString m_strTempText;
	CString m_strEnter;
	CString m_strEsc;
	CString m_strDelete;
	bool m_bCaps;
	bool m_bFuhao;
	bool m_bChinese;

public:
	QString m_strEditInfo;

public:
	ChineseKeyboard(QWidget *parent = NULL);
	virtual ~ChineseKeyboard();

	void InitUI();
	void InitPinyinLib();
	void InitChineseList();
	void keyPressEvent(QKeyEvent *event);
	bool eventFilter(QObject *obj, QEvent *event);
	void showToEdit(QRect rc);  
	bool checkNotTextKey(int keyId);
	void changeTextCaps(bool isCaps);
	void AddItem(const QString &strText);
	void ParsePinyin(const QString& strText);
	void InitLanguage();

private slots:
	void on_btn_clicked(int btn);
	void onItemClicked(QListWidgetItem *item);
	void on_btnReturn_clicked(bool checked);
	void on_btnEsc_clicked(bool checked);
	void on_btnChinese_toggled(bool checked);
	void on_btnCaps_toggled(bool checked);
	void on_btnFuhao_toggled(bool checked);
};

void Global_InitPinyinLib();
#endif//!CHINESEKEYBOARD_H

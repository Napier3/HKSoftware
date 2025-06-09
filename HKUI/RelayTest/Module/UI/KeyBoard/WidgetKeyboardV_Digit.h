#ifndef WIDGETKEYBOARDV_DIGIT
#define WIDGETKEYBOARDV_DIGIT

#include <QDialog>
#include <QKeyEvent>
#include <QSignalMapper>
#include <QTextEdit>
#include "ui_WidgetKeyboardV_Digit.h"
#include "../../../../Module/OSInterface/QT/CString_QT.h"
#include "../Controls/SttLineEdit.h"
#include "../Module/CommonCtrl_QT/CommonCtrlInterface.h"

class WidgetKeyboardV_Digit : public QDialog, public Ui::WidgetKeyboardV_Digit
{
    Q_OBJECT
public:
	WidgetKeyboardV_Digit();
	//数字软键盘初始化
	//nType: 0-电压 1-电流 2-相位 3-频率 4-其它
	WidgetKeyboardV_Digit( long nType,QWidget *parent = NULL);
	~WidgetKeyboardV_Digit();

	void IntUI_ModalLess(long nType,QString& strText,CCommonCtrlInterface *pCommonCtrl
		,QWidget *parent,int bTableWidget);//非模态显示键盘时使用
	void Init(QWidget* parent);
	void keyPressEvent(QKeyEvent *event);
	void ExitHide_ModalLess(bool bUpdateText = false);//非模态显示键盘时使用
	void ClearExternAttach_ModalLess(bool bUpdateText = false);

	bool eventFilter(QObject *obj, QEvent *event);
	void showToEdit();   
	void selectAll();
	bool isDigit(QString);
	int isPosiDigitstr(QString str);
	void setSelState(int);
	void InitTpyeNor();
	void InitTypePh();
	void InitTypeHz();
	void InitTypeA();
	void InitTypeV();
	void CloseOrHideDlg();//关闭或隐藏对话框
	void EnableBtns();  //显示btn控件
private:
    QWidget *m_pParent;
    QSignalMapper * m_pSignalMapper;
	CCommonCtrlInterface *m_pExternalCtrl;
    QList<QToolButton* > m_pButtonsList;
	long m_nType;
	int m_nCurSelPos;
	int m_bTableWidget;

	CString m_strEnter;
	CString m_strAmp;
	CString m_strFreq;
	CString m_strEsc;
	CString m_strDelete;
	CString m_strNega;
	CString m_strZero;
	CString m_strPosi;
public:
    QString m_strEditInfo;

private slots:
    void on_btn_clicked(int btn);

    bool checkNotTextKey(int keyId);
    void on_btnReturn_clicked(bool checked);
    void on_btnEsc_clicked(bool checked);
signals:
	void sig_ZX(QString);//正序
	void sig_FX(QString);//负序
	void sig_LX();//零序
	void sig_120();
	void sig_240();
	void sig_Aamp(QString);
	void sig_Vamp(QString);
	void sig_Hzamp(QString);

    void sig_StepAamp(QString);
    void sig_StepVamp(QString);
    void sig_StepPh(QString);

	void sig_endChanged();

};
#endif /*__WIDGETKEYBOARD_H_*/

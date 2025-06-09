#ifndef STTIECCAPDIALOG_H
#define STTIECCAPDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "SttIecRecordMainWidget.h"
#include "SttOutPutWidget.h"


class QSttIecCapDialog : public QDialog
{
	Q_OBJECT

public:
	QSttIecCapDialog(QWidget *parent = 0 ,bool bIecCap=FALSE);
	virtual ~QSttIecCapDialog();

	void InitUI();
	void StartDetect(bool bStartDetect);
 	QSttOutPutWidget *m_pSttOutPutWidget;

	QSttIecRecordMainWidget *m_pSttIecRecordMainWidget;
	bool m_bIecCapMode; //标记是否为IecCap模式,从主界面入口进入,不显示具体测试功能界面,只显示探测界面,具体独立的打印信息窗口

	void CloseIecCapDetect();//20220629 zhouhj 关闭测试功能界面时,如果底层还处于探测模式,关闭探测通道


private:
	
	QVBoxLayout *m_pMainVLayout;
	QPushButton *m_pOK_PushButton;
	QHBoxLayout *m_pOK_CancelHLayout;

public slots:
	void slot_OKClicked();
	
};

#endif // STTIECCAPDIALOG_H

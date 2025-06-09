#ifndef QSTTSELSCLFILEWIDGET_H
#define QSTTSELSCLFILEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "SttSelSclFileGrid.h"
#include "../../../../61850/Module/SCL_Qt/QSclFileRead.h"
#include "../../../../61850/Module/SCL/SclIecCfgDatas.h"

class QSttSelSclFileWidget : public QWidget ,public CExBaseListGridOptrInterface
{
	Q_OBJECT

public:
	QSttSelSclFileWidget(QWidget *parent);
	virtual ~QSttSelSclFileWidget();
	void InitUI();
	void InitDatas();
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

private:
	void EnableButtons();

	QPushButton *m_pAddScl_Btn;
	QPushButton *m_pDelCurr_Btn;
	QPushButton *m_pClearAll_Btn;
	QPushButton *m_pSclIedSelect_Btn;
	QHBoxLayout *m_pBtns_HBoxLayout;
	QVBoxLayout *m_pMainVLayout;
	CSttSelSclFileGrid *m_pSttSelSclFileGrid;

	CSclStation   m_oSclStation;

public slots:
	void slot_AddScl_Clicked();
	void slot_DelCurr_Clicked();
	void slot_ClearAll_Clicked();
	void slot_SclIedSelect_Clicked();

};

//使用QSclFileRead解析SCD文件
CString Global_ParseSclFileSaveSclCfgs(const CString &strSclFilePath,CSclStation *pSclStation,QWidget *pParent);//解析SCD文件,并将解析内容存入指定文件夹中
#ifndef _PSX_QT_LINUX_
//使用CSclFileRead解析SCD文件
CString Global_ParseSclFileSaveSclCfgs_EX(const CString &strSclFilePath,CSclStation *pSclStation,QWidget *pParent);//解析SCD文件,并将解析内容存入指定文件夹中
#endif
CString Global_SaveSclCfgs(const CString &strSclFilePath, CSclStation *pSclStation);

extern QSttSelSclFileWidget *g_pSttSelSclFileWidget;

#endif // QSTTSELSCLFILEWIDGET_H

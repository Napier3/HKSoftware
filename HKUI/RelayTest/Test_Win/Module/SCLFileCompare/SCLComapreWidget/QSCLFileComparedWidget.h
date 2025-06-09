#ifndef QSCLFILECOMPAREDWIDGET_H
#define QSCLFILECOMPAREDWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include "QSCLComparedTreeCtrl.h"
#include "QSCLXmlComparedTree.h"
#include "QSCLComparedTextWidget.h"


class QSCLFileComparedWidget: public QWidget
{
	Q_OBJECT

public:
	QSCLFileComparedWidget(QWidget *parent = 0,CString strSCLFilePath = "", CString strCompareFilePath = "");
	~QSCLFileComparedWidget();

	void InitUI();

	QVBoxLayout *m_pFileComparedLayout;//总布局
	QSplitter *m_pMainFileComparedSplitter;//总切分视图(水平)
	QSplitter *m_pRightComparedSplitter;//右侧切分视图(垂直)

	QSCLComparedTreeCtrl *m_pSCLComparedTreeCtrl;
	QSCLXmlComparedTree *m_pSCLXmlComparedTree;
	QSCLComparedTextWidget *m_pSCLComparedTextWidget;

	CString m_strSCLFilePath;//导入源文件路径
	CString m_strCompareFilePath;//导入比对文件路径

signals:
	void sig_UpdateXmlComparedTree(QDeliverPugiNode*);
	void sig_UpdateComparedTextView(CString &,CString &);
	void sig_InitComparedTextView(CString* &,CString* &);


};


#endif
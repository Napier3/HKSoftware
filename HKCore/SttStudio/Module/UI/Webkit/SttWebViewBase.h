#ifndef _QSTTWEBVIEW_BASE_H_
#define _QSTTWEBVIEW_BASE_H_

#include <QtWebKit>
#include <QList>
#include <QDomElement>
#include <QDomNode>
#include <QFile>
#include <QVariant>

#include "../../../Module/DataMngr/DataGroup.h"
#include "../../../Module/DataMngr/DvmDataset.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../Interface/SttHtmlViewApi.h"
#include "../Module/ScrollCtrl/ScrollWebView.h"

class QSttWebPageBase : public QWebPage
{
	Q_OBJECT

public:
	QSttWebPageBase(QObject * parent = 0) : QWebPage(parent) {}

	public slots:
		bool shouldInterruptJavaScript()//zhouhj 20220324 直接返回false解决js系统弹框问题
		{
			return false;
		}
};

#ifndef _PSX_QT_LINUX_
class QSttWebViewBase : public QWebView
#else
class QSttWebViewBase : public QScrollWebView
#endif
{
	Q_OBJECT

public:
	CString m_strHtmlFile;

	virtual bool OpenHtmlFile(const CString &strHtmlFile);

public:
    QSttWebViewBase(QWidget* parent = 0);
	virtual ~QSttWebViewBase();
	void ToDvmDataset(QVariant &strParas, CDvmDataset &oDvmDataset);
	void ToDataGroup(QVariant &strParas, CDataGroup &oDataGroup);
	virtual void OnHtmlLoadFinish(bool b);
	QSttWebPageBase* GetWebPage() { return m_pWebPage; }

protected:
	QSttWebPageBase *m_pWebPage;//zhouhj 20220324 解决js弹框问题

signals:
	//APP ==>> HTML

public slots:
 	void populateJavaScriptWindowObject();
    void slot_loadFinished(bool b);
	
	//APP ==>> HTML

	//HTML ==>> APP
	void ShowMsg(QVariant strParas);
	void ShowMsgEx(QVariant strLevel,QVariant strParas);//20230218 zhouhj 扩充用于传递打印信息类别,部分打印信息需要在助手界面显示

	//yzj 2023.12.22 已经由网页实现
// #ifndef _PSX_QT_LINUX_
// 	//windows网页输入限制
// public:
// 	QString GetCurrentText();
// 	void CalInputValid();
//  	virtual void keyPressEvent(QKeyEvent* e);
// #endif
};

#endif // _QSTTWEBVIEW_BASE_H_

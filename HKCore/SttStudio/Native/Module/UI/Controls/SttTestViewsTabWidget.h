#ifndef SttTestViewsTabWidget_H
#define SttTestViewsTabWidget_H

#include <QTabWidget>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class QSttTestViewsTabWidget : public QTabWidget
{
	Q_OBJECT

public:
	explicit QSttTestViewsTabWidget(QWidget* pParent = NULL);
	virtual ~QSttTestViewsTabWidget();
	void InitConnects();
	void SetHasInit(bool bInit)	{	m_bHasInitView = bInit;	}
	void SetCurrMacroView(QWidget *pMacroView);
	bool m_bHasClosed;//判断是否已关闭软件
signals:
	void sig_CurrClickChanged(int nTabIndex);

public slots:
	void slot_CurrChangedTabWidget(int nTabIndex);

private:
	bool m_bHasInitView;//打开测试功能,首先切换到测试功能参数界面,相当于初始化,该次不需要同步
	QWidget *m_pCurrMacroView;
	QWidget *m_pCurrTabView;
};

#endif//!SttTestViewsTabWidget_H

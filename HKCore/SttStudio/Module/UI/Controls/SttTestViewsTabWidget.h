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
	bool m_bHasClosed;//�ж��Ƿ��ѹر����
signals:
	void sig_CurrClickChanged(int nTabIndex);

public slots:
	void slot_CurrChangedTabWidget(int nTabIndex);

private:
	bool m_bHasInitView;//�򿪲��Թ���,�����л������Թ��ܲ�������,�൱�ڳ�ʼ��,�ôβ���Ҫͬ��
	QWidget *m_pCurrMacroView;
	QWidget *m_pCurrTabView;
};

#endif//!SttTestViewsTabWidget_H

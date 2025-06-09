#ifndef QMAINPARA_H
#define QMAINPARA_H

#include <QWidget>
#include "QTemplateWidget.h"
#include "gooseparawidget/QGooseParaWidget.h"
#include "exSwitchSet/exswitchset.h"

//试验视图区域左侧参数设置区域界面类
class QMainPara : public QWidget
{
	Q_OBJECT

public:
	QMainPara(QWidget *parent = 0);
	~QMainPara();

	virtual void initUI();

	QTemplateWidget* getTemplateWidget(){
		return m_templateWidget;
	}

public:
	//垂直切分视图控件
	QSplitter *m_pMainParaSplitterV;//zhouhj 20211207 修改成员变量命名
	//参数设置区域Tab切换控件
	QTabWidget* m_tabWidget;
	//参数模板设置界面,此为基类根据不同的测试功能派生不同的对象,QManuWidget\QHarmWidget\QTemplateWidgetExtend(多测试项表格类)
	//m_templateWidget为m_tabWidget控件下的一个页面,具体在实际测试功能类中实现
	QTemplateWidget* m_templateWidget;
};

#endif // QMAINPARA_H

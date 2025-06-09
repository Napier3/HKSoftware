#ifndef TESTPARAVIEW_H
#define TESTPARAVIEW_H

#include <QWidget>
#include "monitortab.h"
#include "qmainpara.h"

class TestParaView : public QWidget
{
    Q_OBJECT

public:
    explicit TestParaView(QWidget *parent = 0);
    ~TestParaView();

	QMainPara* getMainPara(){
		return m_pMainPara;
	}

	MonitorTab* getMonitor(){
		return m_pMonitor;
	}

	virtual void initUI();

public:
	//试验视图总的水平切分视图
	QSplitter *m_pTestParaViewSplitterH;//zhouhj 20211207 修改成员变量命名
	//左侧参数设置区界面
	QMainPara* m_pMainPara;
	//右侧试图区界面(矢量图、测试过程监视图、信息视图等)
    MonitorTab* m_pMonitor; 
};

#endif // TESTPARAVIEW_H

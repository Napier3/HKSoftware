#ifndef QSWINGSYSDIAGRAMWIDGET_H
#define QSWINGSYSDIAGRAMWIDGET_H

#include <QWidget>
#include "../../UI/Interface/SttMacroParaEditViewOriginal.h"
#include "../../SttTestBase/SttComplexp.h"
#include "../../SttTest/Common/Swing/tmt_swing_test.h"

namespace Ui {
class QSwingSysDiagramWidget;
}

class QSwingSysDiagramWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QSwingSysDiagramWidget(QWidget *parent = 0);
    ~QSwingSysDiagramWidget();
    void InitUI();
    void SetDatas();

private:
	void SearchData();

private:
    Ui::QSwingSysDiagramWidget *ui;

public:
	tmt_SwingTest *m_pCurTest;
	//double m_dRate;  //|Em|\|En|
	Complex m_oZs;  //系统侧阻抗
	Complex m_oZt;  //系统侧阻抗
	Complex m_oXd;  //发电机暂态阻抗
    double m_dVoscmin;
    double m_dIoscmax;
    double m_dZoscmin;
    double m_dPhioscmax;
};

#endif // QSWINGSYSDIAGRAMWIDGET_H

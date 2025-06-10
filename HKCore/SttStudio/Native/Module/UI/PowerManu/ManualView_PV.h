#ifndef MANUALVIEWPV_H
#define MANUALVIEWPV_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>

#include "../Module/ChannelParaSet/QBasicTestParaSet.h"
#include "../Module/ExSwitchSet/exswitchset.h"
#include "../PowerManu/PowerManualGrid.h"

class QManualView_PV
{
public:
    QManualView_PV();
    virtual ~QManualView_PV();

	QPowerManualGrid* m_pPUParaWidget;		//电压功率设置

	QTabWidget* m_pTabWidget;
public:
    void InitUI(int nFuncType);

public:
	void slot_cb_DCClicked(bool bIsChecked);

};

#endif // MANUALVIEWIV_H

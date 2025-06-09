#ifndef _QDeviceInforDlg_H
#define _QDeviceInforDlg_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include "DeviceAttrsGrid.h"
#include "SttModulesGrid.h"
#include "SttModuleAttrsGrid.h"


class QDeviceInforDlg : public QDialog ,public CExBaseListGridOptrInterface
{
	Q_OBJECT

public:
	QDeviceInforDlg(QWidget *parent = 0);
	~QDeviceInforDlg();

	void initUI(BOOL bEnableCmbSel = TRUE);
	void ReleaseUI();
	void InitVersionViewCfg();

public:
	CDataGroup m_oVersionViewCfg;
	CDataGroup *m_pDeviceAttrGroup;

protected:
	void InitDatas();
	void GetAllChildFolder(const QString &strParentFolderPath,QStringList &astrChildFolders);

	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

	QVBoxLayout *m_pVLayout;
	QTabWidget *m_tabWidget;

	CDeviceAttrsGrid *m_pDevcieAttrsGrid;
	CSttModulesGrid *m_pModulesGrid;
	CSttModuleAttrsGrid *m_pModuleAttrsGrid;

	QHBoxLayout *m_pHBoxLayout;
	QLabel *m_pModelLabel;
	QComboBox *m_pModelSelCombobox;//型号选择
	QLabel *m_pSN_Label;
	QComboBox *m_pSN_SelCombobox;//SN选择
	QPushButton *m_pOK_PushButton;

signals:
	void sig_SysParasHasChanged();//发送系统参数改变信号

public slots:
	void slot_changeModelSel(int nCurComboxIndex);
	void slot_changeSN_Sel(int nCurComboxIndex);
	void slot_OKClicked();
	void slot_UpdateTestResource();

private:
	QStringList m_astrModels;//全部装置型号
	QStringList m_astrSNs;//当前选择型号下的全部SN
};

#endif // PLOTWIDGET_H

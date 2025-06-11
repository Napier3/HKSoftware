#ifndef QMODALDLGINTERFACE_H
#define QMODALDLGINTERFACE_H
/*
 * Create By HuangLiang 20240724
 * 用于模态对话框中使用定值关联
*/

//#include <QDialog>
//#include "../../Module/ui/Controls/QSettingLineEdit.h"
//#include "../../Module/ui/Controls/QSettingItem.h"
//#include "../../Module/ui/Controls/settingselectdlg.h"

//class QModalDlgInterface : public QDialog
//{
//	Q_OBJECT
//public:
//	explicit QModalDlgInterface(QWidget *parent = 0);
//	virtual ~QModalDlgInterface();

//	//关联定值界面信号
//    bool ConnectForSettingDlg();

//	//全部取消响应
//    virtual void ClearAllMaps();
//    void ChildInitMaps(QObject *child, int iOperation);
//    void ChildInitTable(QTableWidget *table, int iOperation);

//	void SettingSelect(CExBaseObject *pItem);
//	void SettingSelect(const CString &sValue);

//signals:
//	void sig_SettingSelect(CExBaseObject *pItem);		//响应定值选择结果信号
//	void sig_SettingSelect(QString sValue);				//20240730 huangliang

//public slots:
//	void slot_ShowSetting();
//    void slot_ClearAllMap();
//};

#endif // QMODALDLGINTERFACE_H

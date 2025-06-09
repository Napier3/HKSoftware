 #ifndef QLOWFREPBINBOUTDLG_H
 #define QLOWFREPBINBOUTDLG_H
 
 #include <QWidget>
 #include <QDialog>
 #include <QLabel>
 #include <QLineEdit>
 #include <QPushButton>
 #include <QComboBox>
 #include <QHBoxLayout>
 #include <QVBoxLayout>
 #include "../../UI/Controls/SttCheckBox.h"
 #include <QGroupBox>
 #include "ui_QLowFrepBinBoutDlg.h"
 #include "../../DataMngr/DataGroup.h"
 #include "../../DataMngr/DataMngrGlobal.h"
 #include "../../API/GlobalConfigApi.h"
 #include "../../UI/Controls/SttCheckBox.h"

 namespace Ui{
 	class QLowFrepBinBoutDlg;
 }
 
 class QLowFrepBinBoutDlg : public QDialog
 {
 	Q_OBJECT
 
 public:
 	Ui::QLowFrepBinBoutDlg *ui;
 
 	QLowFrepBinBoutDlg(CDataGroup *m_oLowFrepDataGroup, QWidget *parent = 0);
 	virtual ~QLowFrepBinBoutDlg();

 public:
	  CDataGroup *m_oLowFrepBinBoutDataGroup;
 
 
 public:
	 void InitDatas();
	 void InitFont();
	 void InitConnects();

 public slots:
	 void slot_OK();
	 void slot_Cancel();
 };
 
 #endif 

#ifndef XLanguageAPI_QT_H
#define XLanguageAPI_QT_H

#include "../XLanguageMngr.h"

#ifndef _USE_NO_GUI_
#include <QWidget>
#endif

#define XLang_Ctrls_QPushButton  1
#define XLang_Ctrls_QToolButton  2
#define XLang_Ctrls_QMenu  3
#define XLang_Ctrls_QLabel  4
#define XLang_Ctrls_QCheckBox  5
#define XLang_Ctrls_QGroupBox  6
#define XLang_Ctrls_QTabWidget  7
#define XLang_Ctrls_QTableWidgetItem  8
#define XLang_Ctrls_QTreeWidgetItem  9
#define XLang_Ctrls_QRadioButton  10
#define XLang_Ctrls_QLineEdit 11

//XLanguageAPI_QT
#ifndef _USE_NO_GUI_
bool xlang_SetLangStrToWidget(QWidget* pWidget, const CString& strID,long nCtrlsType);
bool xlang_SetLangStrToWidget_Txt(QWidget* pWidget, const CString& strText,long nCtrlsType);

bool xlang_SetLangStrToAction(QAction* pAction, const CString& strID);
#endif

void xlang_GetLangStrByFile(CString& strTrans, const CString& strID);
#endif // XLanguageAPI_QT_H

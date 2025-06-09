#ifndef SttGbSafetyEDIT_H
#define SttGbSafetyEDIT_H

#include <QDialog>
#include "../../../../Module/BaseClass/ExBaseObject.h"
#include "../../SttCmd/GuideBook/SttSafety.h"
#include "SafetyMsgCfg/SttSafetyMsgCfg.h"

namespace Ui {
class QSttGbSafetyEdit;
}

#define DLG_SAFETY_RUNMODE_NEW   0   //新建
#define DLG_SAFETY_RUNMODE_EDIT  1   //编辑
#define DLG_SAFETY_RUNMODE_RUN   2   //执行

//该对话框，用于创建、修改、执行接线提示项目（safety项目）
class QSttGbSafetyEdit : public QDialog
{
    Q_OBJECT

public:
    explicit QSttGbSafetyEdit(CExBaseList *pParent,QWidget *parent = 0);
    virtual ~QSttGbSafetyEdit();

	CSttSafety *m_pSttSafety;
	CExBaseList *m_pSttParent;
	CSttSafetyMsgCfg *m_pMsgCfg; //符合当前装置类型的配置

public:
	void Init(CSttSafety *pSafety);
	long CalAutoIndex(const CString& strID);
	void SetDlgRunMode(long nRunMode);
	BOOL IsRunMode_New()	{	return m_nRunMode == DLG_SAFETY_RUNMODE_NEW;	}
	BOOL IsRunMode_Edit()	{	return m_nRunMode == DLG_SAFETY_RUNMODE_EDIT;	}
	BOOL IsRunMode_Run()	{	return m_nRunMode == DLG_SAFETY_RUNMODE_RUN;	}

	void OnOKClicked_New();
	void OnOKClicked_Edit();
	void OnOKClicked_Run();
        void InitLanguage();
	void SetMsgs(const CString &strMsgs);
	void InitSafetyMsgCfgs(const CString &strMsgs = _T(""));

protected:
	long m_nRunMode;
	CString m_strMsgs;

public slots:
	void slot_OKClick();
	void slot_CancelClick();
	void on_m_cmbMsgs_currentIndexChanged(int index);

private:
    Ui::QSttGbSafetyEdit *ui;
};

#endif // SttGbSafetyEDIT_H

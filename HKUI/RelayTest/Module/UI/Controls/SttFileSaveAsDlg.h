#ifndef SttFileSaveAsDlg_H
#define SttFileSaveAsDlg_H

#include <QDialog>
#include "../../../../Module/BaseClass/ExBaseObject.h"

namespace Ui {
class QSttFileSaveAsDlg;
}

class QSttFileSaveAsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QSttFileSaveAsDlg(const CString &strPrev, const CString &strFile, QWidget *parent = 0);
    virtual ~QSttFileSaveAsDlg();

	CString m_strFileName;
	CString m_strFolderName;

	CString InitFolderByDate(const CString &strPrev, bool bUseDay);
	CString InitFileByDate(const CString &strPrev, bool bUseDay);
	void DisableFolder();
	void SetFileSaveFont();

public slots:
	void slot_OKClick();
	void slot_CancelClick();
	void slot_FileNameLineEditClicked();

private:
    Ui::QSttFileSaveAsDlg *ui;
};

extern CFont *g_pSttGlobalFont; 

#endif // SttFileSaveAsDlg_H

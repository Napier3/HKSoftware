/*
 * Copyright 2009 EMBITEL (http://www.embitel.com)
 * 
 * This file is part of Virtual Keyboard Project.
 * 
 * Virtual Keyboard is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation
 * 
 * Virtual Keyboard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Virtual Keyboard. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __WIDGETKEYBOARDF_H_
#define __WIDGETKEYBOARDF_H_

#include <QDialog>
#include <QKeyEvent>
#include <QSignalMapper>
#include <QTextEdit>
#include "ui_WidgetKeyboardF.h"

class WidgetKeyboardF : public QDialog, public Ui::WidgetKeyboardF
{
    Q_OBJECT
    
private:
    QWidget *m_pParent;
    qreal opacity;
    bool isCaps;
    bool isShift;
    bool isCtrl;
    //bool isAlt;
    bool isIns;
    QSignalMapper * m_pSignalMapper;
    QList<QToolButton* > m_pButtonsList;

public:
    QString m_strEditInfo;

private slots:
    void on_btn_clicked(int btn);
    void on_btnCaps_toggled(bool checked);
   // void on_btnAltLeft_toggled(bool checked);
    void changeTextShift(bool isShift);
    void changeTextCaps(bool isCaps);
    bool checkNotTextKey(int keyId);
    void on_btnReturn_clicked(bool checked);
    void on_btnEsc_clicked(bool checked);
    void on_btn123_clicked(bool checked);
    void on_btnFuhao_clicked(bool checked);

Q_SIGNALS://自定义信号
    void NotifySuccessF(int);
public:
    WidgetKeyboardF(QWidget *parent = NULL);
    ~WidgetKeyboardF();
    void showToEdit();

    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *, QEvent *);
};
#endif /*__WIDGETKEYBOARDF_H_*/

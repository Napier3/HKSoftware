; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEANDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "EAN.h"

ClassCount=3
Class1=CEANApp
Class2=CEANDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_EAN_DIALOG

[CLS:CEANApp]
Type=0
HeaderFile=EAN.h
ImplementationFile=EAN.cpp
Filter=N

[CLS:CEANDlg]
Type=0
HeaderFile=EANDlg.h
ImplementationFile=EANDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_BITMAPBARCODE

[CLS:CAboutDlg]
Type=0
HeaderFile=EANDlg.h
ImplementationFile=EANDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_EAN_DIALOG]
Type=1
Class=CEANDlg
ControlCount=18
Control1=IDC_COMBO_SYMBOLOGY,combobox,1344340226
Control2=IDC_EDIT_COUNTRYCODE,edit,1350639744
Control3=IDC_EDIT_MANUFACTURER,edit,1350639744
Control4=IDC_EDIT_PRODUCT,edit,1350639744
Control5=IDC_EDIT_CHECKDIGIT,edit,1350639744
Control6=IDC_EDIT_HEIGHT,edit,1350631552
Control7=IDC_COMBO_RATIO,combobox,1478557954
Control8=IDC_EDIT_GUARDBAR,edit,1350639744
Control9=IDC_BUTTON_DRAW,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_BITMAPBARCODE,static,1350566414
Control17=IDC_STATIC,static,1476526080
Control18=IDC_STATIC,static,1342308352


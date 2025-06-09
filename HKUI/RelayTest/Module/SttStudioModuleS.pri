include(../../Module/TestMacro/TestMacro.pri)

INCLUDEPATH +=$$PWD
SOURCES += \
    $$PWD/SttCmd/SttCmdDefineGlobal.cpp \
    $$PWD/SttTestBase/SttMacroXmlKeys.cpp \
    $$PWD/SttTestBase/SttParaObject.cpp \
    $$PWD/SttTestBase/SttParaObjects.cpp \
    $$PWD/SttTestBase/SttParaObjectsGroup.cpp \
    $$PWD/SttTestBase/SttXmlSerialize.cpp \
    $$PWD/SttTestBase/SttXmlSerializeBase.cpp \
   # $$PWD/SttTestBase/SttTestBase.cpp \
   # $$PWD/SttTestBase/SttTestCreator.cpp \
   # $$PWD/SttTestBase/SttTestFactory.cpp \
    $$PWD/UI/Module/QExBaseListGridBase/QExBaseListGridBase.cpp \
    $$PWD/UI/Module/QExBaseListGridBase/QGridDefine.cpp \
    $$PWD/UI/Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.cpp \
    $$PWD/UI/Module/QExBaseListGridBase/QExBaseListFloatEditDelegBase.cpp \
    $$PWD/UI/Module/ScrollCtrl/ScrollComboBox.cpp \
    $$PWD/UI/Module/CommonCtrl_QT/QFloatLineEdit.cpp \
    $$PWD/UI/Module/CommonCtrl_QT/QCovDoubleValidator.cpp \
    $$PWD/UI/Module/CommonCtrl_QT/QDataTypeComboBox.cpp \
    $$PWD/UI/Module/CommonCtrl_QT/QIecLineEdit.cpp \
    $$PWD/UI/Module/CommonCtrl_QT/QLongLineEdit.cpp \
    $$PWD/UI/Module/CommonCtrl_QT/QNumberCheckBox.cpp \
    $$PWD/UI/Module/ScrollCtrl/ScrollTableWidget.cpp \
    $$PWD/UI/Controls/SttLineEdit.cpp \
    $$PWD/UI/Module/ScrollCtrl/ScrollListView.cpp \
    $$PWD/SttGlobalDef.cpp


HEADERS  += \
    $$PWD/SttCmd/SttCmdDefineGlobal.h \
    $$PWD/SttTestBase/SttMacroXmlKeys.h \
    $$PWD/SttTestBase/SttParaObject.h \
    $$PWD/SttTestBase/SttParaObjects.h \
    $$PWD/SttTestBase/SttParaObjectsGroup.h \
    $$PWD/SttTestBase/SttXmlSerialize.h \
    $$PWD/SttTestBase/SttXmlSerializeBase.h \
    $$PWD/SttTestBase/SttTestBaseInterface.h \
   # $$PWD/SttTestBase/SttTestBase.h \
   # $$PWD/SttTestBase/SttTestCreator.h \
   # $$PWD/SttTestBase/SttTestFactory.h \
    $$PWD/UI/Module/QExBaseListGridBase/QExBaseListGridBase.h \
    $$PWD/UI/Module/QExBaseListGridBase/QGridDefine.h \
    $$PWD/UI/Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h \
    $$PWD/UI/Module/QExBaseListGridBase/QExBaseListFloatEditDelegBase.h \
    $$PWD/UI/Module/ScrollCtrl/ScrollComboBox.h \
    $$PWD/UI/Module/CommonCtrl_QT/QFloatLineEdit.h \
    $$PWD/UI/Module/CommonCtrl_QT/QCovDoubleValidator.h \
    $$PWD/UI/Module/CommonCtrl_QT/QDataTypeComboBox.h \
    $$PWD/UI/Module/CommonCtrl_QT/QIecLineEdit.h \
    $$PWD/UI/Module/CommonCtrl_QT/QLongLineEdit.h \
    $$PWD/UI/Module/CommonCtrl_QT/QNumberCheckBox.h \
    $$PWD/UI/Module/ScrollCtrl/ScrollTableWidget.h \
    $$PWD/UI/Controls/SttLineEdit.h \
    $$PWD/UI/Module/ScrollCtrl/ScrollListView.h \
    $$PWD/SttGlobalDef.h




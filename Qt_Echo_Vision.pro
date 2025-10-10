QT       += core gui multimedia network widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    button_chat_send.cpp \
    button_cust_base.cpp \
    button_home_start.cpp \
    button_main_close.cpp \
    button_main_menu.cpp \
    main.cpp \
    thread_funca_smart_chat.cpp \
    thread_funcb_smart_vision.cpp \
    thread_funcc_smart_home.cpp \
    thread_funcd_weather.cpp \
    thread_funce_control_industrial.cpp \
    thread_funcf_control_motor.cpp \
    weatherchartwidget.cpp \
    widget_assist_backdrop.cpp \
    widget_assist_menu.cpp \
    widget_funca_smart_chat.cpp \
    widget_funcb_smart_vision.cpp \
    widget_funcc_smart_home.cpp \
    widget_funcd_weather.cpp \
    widget_funce_control_industrial.cpp \
    widget_funcf_control_motor.cpp \
    widget_main.cpp \
    widget_smart_chat_message.cpp

HEADERS += \
    button_chat_send.h \
    button_cust_base.h \
    button_home_start.h \
    button_main_close.h \
    button_main_menu.h \
    thread_funca_smart_chat.h \
    thread_funcb_smart_vision.h \
    thread_funcc_smart_home.h \
    thread_funcd_weather.h \
    thread_funce_control_industrial.h \
    thread_funcf_control_motor.h \
    weatherchartwidget.h \
    widget_assist_backdrop.h \
    widget_assist_menu.h \
    widget_funca_smart_chat.h \
    widget_funcb_smart_vision.h \
    widget_funcc_smart_home.h \
    widget_funcd_weather.h \
    widget_funce_control_industrial.h \
    widget_funcf_control_motor.h \
    widget_main.h \
    widget_smart_chat_message.h

FORMS += \
    widget_funca_smart_chat.ui \
    widget_funcb_smart_vision.ui \
    widget_funcc_smart_home.ui \
    widget_funcd_weather.ui \
    widget_funce_control_industrial.ui \
    widget_funcf_control_motor.ui \
    widget_main.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    city_id.qrc \
    img.qrc

DISTFILES +=

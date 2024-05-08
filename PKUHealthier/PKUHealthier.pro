QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    backend/cafeteria.cpp \
    backend/dish.cpp \
    backend/man.cpp \
    frontend/achievement.cpp \
    frontend/achievementwall.cpp \
    frontend/login.cpp \
    frontend/menu.cpp \
    frontend/recommenddishes.cpp \
    frontend/signup.cpp \
    frontend/sport.cpp \
    main.cpp

HEADERS += \
    backend/cafeteria.h \
    backend/dish.h \
    backend/man.h \
    frontend/achievement.h \
    frontend/achievementwall.h \
    frontend/login.h \
    frontend/menu.h \
    frontend/recommenddishes.h \
    frontend/signup.h \
    frontend/sport.h

FORMS += \
    frontend/achievementwall.ui \
    frontend/login.ui \
    frontend/menu.ui \
    frontend/recommenddishes.ui \
    frontend/signup.ui \
    frontend/sport.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

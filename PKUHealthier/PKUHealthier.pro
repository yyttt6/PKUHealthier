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
    backend/meal.cpp \
    frontend/achievement.cpp \
    frontend/achievementwall.cpp \
    frontend/login.cpp \
    frontend/mainwindow.cpp \
    frontend/home.cpp \
    frontend/menu.cpp \
    frontend/profile.cpp \
    frontend/recommend.cpp \
    frontend/records.cpp \
    frontend/signup.cpp \
    frontend/sports.cpp \
    main.cpp

HEADERS += \
    backend/cafeteria.h \
    backend/dish.h \
    backend/man.h \
    backend/meal.h \
    frontend/achievement.h \
    frontend/achievementwall.h \
    frontend/login.h \
    frontend/mainwindow.h \
    frontend/home.h \
    frontend/menu.h \
    frontend/profile.h \
    frontend/recommend.h \
    frontend/records.h \
    frontend/signup.h \
    frontend/sports.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/mainwindow.qrc \
    resources/signup.qrc

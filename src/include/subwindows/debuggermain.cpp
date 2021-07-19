#include "debuggermain.h"
#include <QCoreApplication>
#include <QQuickView>
#include <QGuiApplication>
#include <QtQuickWidgets/QQuickWidget>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlComponent>

DebuggerMain::DebuggerMain(QWidget *parent) :
    QMLWindow(parent, QUrl("qrc:/subwindows/DebuggerMain.qml"))
{

    this->setWindowTitle("Debugger");
    this->setBaseSize(100, 100);
}

DebuggerMain::~DebuggerMain()
{

}

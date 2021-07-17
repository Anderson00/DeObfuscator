#include "debuggermain.h"
#include <QCoreApplication>
#include <QQuickView>
#include <QGuiApplication>
#include <QtQuickWidgets/QQuickWidget>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlComponent>

DebuggerMain::DebuggerMain(QWidget *parent) :
    QMainWindow(parent)
{
    QQuickView *qmlView = new QQuickView();
    qmlView->setSource(QUrl("qrc:/subwindows/DebuggerMain.qml"));
    qmlView->rootContext()->setContextProperty("window", this);
    QWidget *container = QWidget::createWindowContainer(qmlView, this);
    this->setCentralWidget(container);
    this->setContentsMargins(0,0,0,0);
    this->setMinimumSize(200, 200);
    this->show();
}

DebuggerMain::~DebuggerMain()
{

}

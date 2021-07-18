#include "qmlwindow.h"
#include <QQuickView>
#include <QGuiApplication>
#include <QtQuickWidgets/QQuickWidget>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlComponent>

QMLWindow::QMLWindow(QWidget *parent) : QMainWindow(parent)
{

    this->m_view = new QQuickView(this->windowHandle());

}

QMLWindow::~QMLWindow()
{
    delete m_view;
}

#include "qmlmdisubwindow.h"
#include <QSettings>

QMLMdiSubWindow::QMLMdiSubWindow(QWidget *parent, const QUrl& source) : QMdiSubWindow(parent), m_window(new QMLWindow(this, source))
{
    this->setWidget(this->m_window->centralWidget());
    this->QMdiSubWindow::setAttribute(Qt::WA_DeleteOnClose);
    this->setMinimumSize(100, 100);
    this->m_window->setMinimumSize(100, 100);

    QObject::connect(this->m_window, &QMLWindow::closeWindow, [=](){
        qDebug() << "Janela fechada";
    });

    loadState();
}

QMLMdiSubWindow::~QMLMdiSubWindow()
{
    saveState();
    delete this->m_window;
}

void QMLMdiSubWindow::saveState()
{
    QSettings settings("QMLMdiSubWindow", "qt");
    settings.setValue("posX", this->pos().x());
    settings.setValue("posY", this->pos().y());
    settings.setValue("width", this->width());
    settings.setValue("height", this->height());
}

void QMLMdiSubWindow::loadState()
{
    QSettings settings("QMLMdiSubWindow", "qt");
    this->move(settings.value("posX").toInt(), settings.value("posY").toInt());
    this->resize(settings.value("width").toInt(), settings.value("height").toInt());
}

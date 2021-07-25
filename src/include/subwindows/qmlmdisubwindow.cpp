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

//    loadState();
}

QMLMdiSubWindow::~QMLMdiSubWindow()
{
    saveState();
    delete this->m_window;
}

void QMLMdiSubWindow::setSaveStateLogic(std::function<QHash<QString, QString> (QMLMdiSubWindow *)> logic)
{
    this->m_logicSaveState = logic;
}

void QMLMdiSubWindow::setLoadStateLogic(std::function<void(QHash<QString, QString>)> logic)
{
    this->m_logicLoadState = logic;
}

QUrl QMLMdiSubWindow::source()
{
    return this->m_window->source();
}

void QMLMdiSubWindow::closeEvent(QCloseEvent *closeEvent)
{
    emit closing();
    QMdiSubWindow::closeEvent(closeEvent);
}

QHash<QString, QString> QMLMdiSubWindow::saveState()
{
    QHash<QString, QString> result;

    result["test"] = "string salva";


    return result;
}

void QMLMdiSubWindow::loadState(const QHash<QString, QString>& fields)
{
    this->move(fields["posX"].toInt(), fields["posY"].toInt());
    this->resize(fields["width"].toInt(), fields["height"].toInt());
}

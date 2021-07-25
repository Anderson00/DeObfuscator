#ifndef QMLMDISUBWINDOW_H
#define QMLMDISUBWINDOW_H

#include <QMdiSubWindow>
#include <QSettings>

#include "../qmlwindow.h"

class QMLMdiSubWindow : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit QMLMdiSubWindow(QWidget *parent = nullptr, const QUrl& source = QUrl(""));
    ~QMLMdiSubWindow();

    void setSaveStateLogic(std::function<QHash<QString, QString>(QMLMdiSubWindow *)> logic);
    void setLoadStateLogic(std::function<void(QHash<QString, QString>)> logic);

    QUrl source();

    virtual QString whoIAm() = 0;

    void closeEvent(QCloseEvent *closeEvent) override;

public slots:
    QHash<QString, QString> saveState();
    void loadState(const QHash<QString, QString>& fields);

signals:
    void closing();

private:
    QMLWindow* m_window;
    std::function<QHash<QString, QString>(QMLMdiSubWindow *)> m_logicSaveState;
    std::function<void(QHash<QString, QString>)> m_logicLoadState;

};

#endif // QMLMDISUBWINDOW_H

#ifndef QMLWINDOW_H
#define QMLWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QQuickView>

class QMLWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit QMLWindow(QWidget *parent = nullptr);
    virtual ~QMLWindow();

protected:
    QQuickView *view();

signals:

private:
    QQuickView *m_view;
};

#endif // QMLWINDOW_H

#ifndef QMLWINDOW_H
#define QMLWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QQuickView>

class QMLWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit QMLWindow(QWidget *parent = nullptr, const QUrl& qmlUrl = QUrl(""));
    virtual ~QMLWindow();

    void changeEvent(QEvent* e);

protected:
    void setQMLSourceUrl(const QUrl& url);
    QQuickView *view();

signals:
    void windowMaximizing(bool isMaximizing);
    void windowMinimizing(bool isMinimizing);
    void windowFullScreen(bool isFullScreen);

private:
    QQuickView *m_view;
};

#endif // QMLWINDOW_H

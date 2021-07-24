#ifndef XMLSAVESTATE_H
#define XMLSAVESTATE_H

#include <QObject>
#include <QDateTime>
#include <QTimer>
#include <QKeySequence>
#include <QHash>
#include <QXmlStreamReader>
#include <QXmlStreamReader>
#include "subwindows/qmlmdisubwindow.h"

class XMLSaveState : public QObject
{
    enum Logic{
        Interval, Shortcut, IntervalAndShortcut, NoLogic
    };

    Q_OBJECT
public:
    explicit XMLSaveState(QObject *parent = nullptr);
    ~XMLSaveState();

    void setLogic(Logic logic);
    void setSaveInterval(int msecs = 5000);

    QWidget *addWidgetsToSave(QWidget *widget, std::function<QHash<QString, QString>(QWidget*)> saveLogic);
    QMLMdiSubWindow *addWidgetsToSave(QMLMdiSubWindow *qmlSubWindows, std::function<QHash<QString, QString>(QMLMdiSubWindow*)> saveLogic);

public slots:
    void onShortcutExecuted(const QKeySequence& shortcutKeys);

private slots:
    void saveState();

signals:
    void saved(QDateTime lastSave);


private:
    Logic m_logic;
    QTimer * m_timer;
    int m_intervalMsecs;
    QHash<QWidget*, std::function<QHash<QString, QString>(QWidget*)>> m_widgetsAndLogics;
    QHash<QMLMdiSubWindow*, std::function<QHash<QString, QString>(QMLMdiSubWindow*)>> m_qmlSubWindowsAndLogics;
    std::function<QHash<QString, QString>(QWidget*)> defaultLogic;
};



#endif // XMLSAVESTATE_H

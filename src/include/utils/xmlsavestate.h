#ifndef XMLSAVESTATE_H
#define XMLSAVESTATE_H

#include <QObject>
#include <QDateTime>
#include <QTimer>
#include <QKeySequence>
#include <QList>
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

    void setMdiSubwindows(QList<QMLMdiSubWindow*> subwindows);
    void setQMLsubwindows(QList<QMLWindow*> subwindows);

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
};

#endif // XMLSAVESTATE_H

#include "xmlsavestate.h"

XMLSaveState::XMLSaveState(QObject *parent) : QObject(parent)
{
    defaultLogic = [](QWidget *widget){
        QHash<QString, QString> result;

        result["posX"] = widget->x();
        result["posY"] = widget->y();

        result["widget"] = widget->width();
        result["height"] = widget->height();

        return result;
    };
    setLogic(Logic::NoLogic);
    setSaveInterval();
}

XMLSaveState::~XMLSaveState()
{
    if(this->m_timer != nullptr)
        delete m_timer;
}

void XMLSaveState::setLogic(XMLSaveState::Logic logic)
{
    this->m_logic = logic;
    switch (this->m_logic) {
        case Logic::Interval:
            this->m_timer = new QTimer();
            this->m_timer->setInterval(this->m_intervalMsecs);
            QObject::connect(this->m_timer, SIGNAL(timeout()), this, SLOT(saveState()));
        break;
        case Logic::Shortcut:

        break;
        case Logic::IntervalAndShortcut:

        break;
        case Logic::NoLogic:

        break;
    }
}

void XMLSaveState::setSaveInterval(int msecs)
{
    this->m_intervalMsecs = msecs;
}

QWidget *XMLSaveState::addWidgetsToSave(QWidget *widget, std::function<QHash<QString, QString> (QWidget *)> saveLogic)
{
    if(!this->m_widgetsAndLogics.contains(widget)){
        this->m_widgetsAndLogics[widget] = saveLogic;
        return widget;
    }

    return nullptr;
}

QMLMdiSubWindow *XMLSaveState::addWidgetsToSave(QMLMdiSubWindow *qmlSubWindows, std::function<QHash<QString, QString> (QMLMdiSubWindow *)> saveLogic)
{
    if(!this->m_qmlSubWindowsAndLogics.contains(qmlSubWindows)){
        this->m_qmlSubWindowsAndLogics[qmlSubWindows] = saveLogic;
        return qmlSubWindows;
    }

    return nullptr;
}

void XMLSaveState::onShortcutExecuted(const QKeySequence &shortcutKeys)
{

}

void XMLSaveState::saveState()
{

}

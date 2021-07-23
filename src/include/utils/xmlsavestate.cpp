#include "xmlsavestate.h"

XMLSaveState::XMLSaveState(QObject *parent) : QObject(parent)
{
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

void XMLSaveState::setMdiSubwindows(QList<QMLMdiSubWindow*> subwindows)
{

}

void XMLSaveState::setQMLsubwindows(QList<QMLWindow *> subwindows)
{

}

void XMLSaveState::onShortcutExecuted(const QKeySequence &shortcutKeys)
{

}

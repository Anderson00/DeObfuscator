#include "xmlsavestate.h"

xml::XMLSaveState *xml::XMLSaveState::m_instance = nullptr;

xml::XMLSaveState::XMLSaveState(QObject *parent) : QObject(parent)
{
    setLogic(Logic::NoLogic);
    setSaveInterval();

}

xml::XMLSaveState::~XMLSaveState()
{
    if(this->m_timer != nullptr)
        delete m_timer;
}

xml::XMLSaveState *xml::XMLSaveState::instance()
{
    if(xml::XMLSaveState::m_instance == nullptr){
        xml::XMLSaveState::m_instance = new XMLSaveState();
    }
    return xml::XMLSaveState::m_instance;
}

void xml::XMLSaveState::setLogic(XMLSaveState::Logic logic)
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

void xml::XMLSaveState::setQMdiArea(QMdiArea *mdiArea)
{
    this->m_mdiArea = mdiArea;
}

void xml::XMLSaveState::setSaveInterval(int msecs)
{
    this->m_intervalMsecs = msecs;
}

QMLMdiSubWindow *xml::XMLSaveState::addWidgetsToSave(QMLMdiSubWindow *qmlSubWindows, std::function<QHash<QString, QString> (QMLMdiSubWindow *)> saveLogic)
{
    if(!this->m_qmlSubWindowsAndLogics.contains(qmlSubWindows)){
        this->m_qmlSubWindowsAndLogics[qmlSubWindows] = saveLogic;
        QObject::connect(qmlSubWindows, &QMLMdiSubWindow::closing, [=](){
            this->m_qmlSubWindowsAndLogics.remove(qmlSubWindows);
        });
        return qmlSubWindows;
    }

    return nullptr;
}

void xml::XMLSaveState::onShortcutExecuted(const QKeySequence &shortcutKeys)
{

}

void xml::XMLSaveState::saveState()
{
    //TODO: use of Threads
    QFile * file = new QFile("XMLSaveStates.xml");

    if (!file->open(QIODevice::WriteOnly | QIODevice::Text)){
        //TODO: throw exception or other logic
        qDebug() << "File not Open";
    }

    QXmlStreamWriter *xmlWriter = new QXmlStreamWriter(file);
    xmlWriter->setAutoFormatting(true);

    xmlWriter->writeStartDocument();

        writeXMLQMLSubWindows(xmlWriter);

    xmlWriter->writeEndDocument();

    file->flush();
    file->close();
    delete xmlWriter;
    delete file;
}

void xml::XMLSaveState::loadState()
{
    QFile * file = new QFile("XMLSaveStates.xml");

    if (!file->open(QIODevice::ReadOnly)){
        //TODO: throw exception or other logic
        qDebug() << "File not open";
    }

    QXmlStreamReader *xmlReader = new QXmlStreamReader(file);

    while(!xmlReader->atEnd()){
        qDebug() << xmlReader->name().toString();

        xmlReader->readNext();
    }

    file->flush();
    file->close();
    delete xmlReader;
    delete file;

}

void xml::XMLSaveState::writeXMLQMLSubWindows(QXmlStreamWriter *xmlWriter)
{
    qDebug() << this->m_qmlSubWindowsAndLogics.size();
    for(auto it = this->m_qmlSubWindowsAndLogics.begin(); it != this->m_qmlSubWindowsAndLogics.end(); it++){
        if(it.key() != nullptr){
            QHash<QString, QString> result = it.value()(it.key());
            result.unite(it.key()->saveState());
            xmlWriter->writeStartElement("QMLSubWindows");
                xmlWriter->writeStartElement(it.key()->whoIAm());
                    for(auto itResult = result.begin(); itResult != result.end(); itResult++){
                        //TODO: implementar possibilidade do caller adicionar elementos com base na key com padrões
                        xmlWriter->writeAttribute(itResult.key(), itResult.value());
                    }
                xmlWriter->writeEndElement();
            xmlWriter->writeEndElement();
        }
    }
}

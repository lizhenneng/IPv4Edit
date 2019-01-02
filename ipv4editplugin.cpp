#include "ipv4edit.h"
#include "ipv4editplugin.h"

#include <QtPlugin>

IPv4EditPlugin::IPv4EditPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void IPv4EditPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool IPv4EditPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *IPv4EditPlugin::createWidget(QWidget *parent)
{
    return new IPv4Edit(parent);
}

QString IPv4EditPlugin::name() const
{
    return QLatin1String("IPv4Edit");
}

QString IPv4EditPlugin::group() const
{
    return QLatin1String("");
}

QIcon IPv4EditPlugin::icon() const
{
    return QIcon(QLatin1String(":/server-normal1-selected.png"));
}

QString IPv4EditPlugin::toolTip() const
{
    return QLatin1String("");
}

QString IPv4EditPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool IPv4EditPlugin::isContainer() const
{
    return false;
}

QString IPv4EditPlugin::domXml() const
{
    return QLatin1String("<widget class=\"IPv4Edit\" name=\"iPv4Edit\">\n</widget>\n");
}

QString IPv4EditPlugin::includeFile() const
{
    return QLatin1String("ipv4edit.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ipv4editplugin, IPv4EditPlugin)
#endif // QT_VERSION < 0x050000

#ifndef WEBGUIPLUGIN_H
#define WEBGUIPLUGIN_H

#include "plugin.h"
#include "stbplugin.h"

#include <QObject>

namespace yasem
{

class AbstractWebPage;

class WebGuiPlugin : public QObject, public StbPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.mvas.yasem.WebGuiPlugin/1.0" FILE "metadata.json")
    Q_INTERFACES(yasem::Plugin yasem::StbPlugin)

    Q_CLASSINFO("author", "Maxim Vasilchuk")
    Q_CLASSINFO("description", "Web GUI plugin for YASEM")
public:
    explicit WebGuiPlugin(QObject *parent = 0);
    ~WebGuiPlugin();

signals:

public slots:

    // Plugin interface
public:
    PLUGIN_ERROR_CODES initialize();
    PLUGIN_ERROR_CODES deinitialize();
    void register_dependencies();
    void register_roles();

    // StbProfilePlugin interface
public:
    QString getProfileClassId();
    Profile *createProfile(const QString &id);
    void init(AbstractWebPage* page);
    QString getIcon(const QSize &size);

protected:
    AbstractWebPage* m_page;
};
}

#endif // WEBGUIPLUGIN_H

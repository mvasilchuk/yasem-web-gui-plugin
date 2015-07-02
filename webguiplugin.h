#ifndef WEBGUIPLUGIN_H
#define WEBGUIPLUGIN_H

#include "plugin.h"

#include <QObject>

namespace yasem
{

class AbstractWebPage;

class WebGuiPlugin: public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.mvas.yasem.WebGuiPlugin/1.0" FILE "metadata.json")
    Q_INTERFACES(yasem::Plugin)

    Q_CLASSINFO("author", "Maxim Vasilchuk")
    Q_CLASSINFO("description", "Web GUI")
    Q_CLASSINFO("version", MODULE_VERSION)
    Q_CLASSINFO("revision", GIT_VERSION)
public:
    explicit WebGuiPlugin(QObject *parent = 0);
    virtual ~WebGuiPlugin();

    void register_dependencies();
    void register_roles();
};
}

#endif // WEBGUIPLUGIN_H

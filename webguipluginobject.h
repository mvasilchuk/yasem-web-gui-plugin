#ifndef WEBGUIPLUGINOBJECT_H
#define WEBGUIPLUGINOBJECT_H

#include "stbpluginobject.h"

namespace yasem
{

class WebGuiPluginObject: public StbPluginObject
{
public:
    WebGuiPluginObject(Plugin* plugin);
    ~WebGuiPluginObject();

    // AbstractPluginObject interface
public:
    PluginObjectResult init();
    PluginObjectResult deinit();

    // StbPluginObject interface
public slots:
    QString getProfileClassId();
    Profile *createProfile(const QString &id);
    void initObject(AbstractWebPage *page);
    QString getIcon(const QSize &size);
};

}

#endif // WEBGUIPLUGINOBJECT_H

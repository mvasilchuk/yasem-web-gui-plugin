#ifndef WEBGUIPLUGINOBJECT_H
#define WEBGUIPLUGINOBJECT_H

#include "stbpluginobject.h"

namespace yasem
{

class WebGuiPluginObject: public SDK::StbPluginObject
{
public:
    WebGuiPluginObject(SDK::Plugin* plugin);
    ~WebGuiPluginObject();

    // AbstractPluginObject interface
public:
    SDK::PluginObjectResult init();
    SDK::PluginObjectResult deinit();

    // StbPluginObject interface
public slots:
    QString getProfileClassId();
    SDK::Profile* createProfile(const QString &id);
    void initObject(SDK::WebPage *page);
    QString getIcon(const QSize &size);

    // StbPluginObject interface
public slots:
    QHash<QByteArray, QByteArray> getRequestHeadersForUrl(const QUrl &url);
};

}

#endif // WEBGUIPLUGINOBJECT_H

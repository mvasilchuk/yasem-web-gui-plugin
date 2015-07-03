#include "webguipluginobject.h"
#include "guiconfigprofile.h"
#include "guistbobject.h"
#include "guipluginobject.h"
#include "browserpluginobject.h"
#include "profilemanager.h"
#include "pluginmanager.h"
#include "macros.h"

using namespace yasem;

WebGuiPluginObject::WebGuiPluginObject(SDK::Plugin* plugin):
    SDK::StbPluginObject(plugin)
{
    QList<SDK::StbSubmodel> &submodels = getSubmodels();
    submodels.append(SDK::StbSubmodel("config", "config"));
}

WebGuiPluginObject::~WebGuiPluginObject()
{

}

SDK::PluginObjectResult WebGuiPluginObject::init()
{
    SDK::StbPluginObject::init();// It's reqired to register profile class id first
    browser(__get_plugin<SDK::BrowserPluginObject*>(SDK::ROLE_BROWSER));

    // Create a stub profile if not created yet (i.e. if the app starts in the first time)
    SDK::ProfileManager::instance()->createProfile(getProfileClassId(), "config", "web-gui-config", true);
    return SDK::PLUGIN_OBJECT_RESULT_OK;
}

SDK::PluginObjectResult yasem::WebGuiPluginObject::deinit()
{
    return SDK::PLUGIN_OBJECT_RESULT_OK;
}

QString yasem::WebGuiPluginObject::getProfileClassId()
{
    return "web-gui-plugin";
}

SDK::Profile *yasem::WebGuiPluginObject::createProfile(const QString &id)
{
    SDK::Profile* profile = new GuiConfigProfile(this, id);
    profile->setId("web-gui-config");
    profile->setName("web-gui-config");
    SDK::ProfileManager::instance()->addProfile(profile);
    return profile;
}

void yasem::WebGuiPluginObject::initObject(SDK::AbstractWebPage *page)
{
    getApi().clear();
    getApi().insert("__GUI__", new GuiStbObject(this, page));
}

QString yasem::WebGuiPluginObject::getIcon(const QSize &size)
{
    return "-N/A-";
}


QHash<QByteArray, QByteArray> yasem::WebGuiPluginObject::getRequestHeadersForUrl(const QUrl &url)
{
    return QHash<QByteArray, QByteArray>();
}

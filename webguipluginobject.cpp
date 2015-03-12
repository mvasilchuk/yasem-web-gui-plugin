#include "webguipluginobject.h"
#include "guiconfigprofile.h"
#include "guistbobject.h"
#include "guipluginobject.h"
#include "browserpluginobject.h"
#include "profilemanager.h"
#include "pluginmanager.h"

using namespace yasem;

WebGuiPluginObject::WebGuiPluginObject(Plugin* plugin):
    StbPluginObject(plugin)
{
    QList<StbSubmodel> &submodels = getSubmodels();
    submodels.append(StbSubmodel("config", "config"));
}

WebGuiPluginObject::~WebGuiPluginObject()
{

}

PluginObjectResult yasem::WebGuiPluginObject::init()
{
    StbPluginObject::init();// It's reqired to register profile class id first

    gui(dynamic_cast<GuiPluginObject*>(PluginManager::instance()->getByRole(ROLE_GUI)));
    browser(dynamic_cast<BrowserPluginObject*>(PluginManager::instance()->getByRole(ROLE_BROWSER)));

    // Create a stub profile if not created yet (i.e. if the app starts in the first time)
    ProfileManager::instance()->createProfile(getProfileClassId(), "config", "web-gui-config", true);
    return PLUGIN_OBJECT_RESULT_OK;
}

PluginObjectResult yasem::WebGuiPluginObject::deinit()
{
    return PLUGIN_OBJECT_RESULT_OK;
}

QString yasem::WebGuiPluginObject::getProfileClassId()
{
    return "web-gui-plugin";
}

Profile *yasem::WebGuiPluginObject::createProfile(const QString &id)
{
    Profile* profile = new GuiConfigProfile(this, id);
    profile->setId("web-gui-config");
    profile->setName("web-gui-config");
    ProfileManager::instance()->addProfile(profile);
    return profile;
}

void yasem::WebGuiPluginObject::initObject(AbstractWebPage *page)
{
    getApi().clear();
    getApi().insert("__GUI__", new GuiStbObject(this));
}

QString yasem::WebGuiPluginObject::getIcon(const QSize &size)
{
    return "-N/A-";
}

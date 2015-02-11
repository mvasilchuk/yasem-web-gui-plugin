#include "webguiplugin.h"
#include "guiconfigprofile.h"
#include "guistbobject.h"
#include "guiplugin.h"
#include "browserplugin.h"
#include "profilemanager.h"

using namespace yasem;

WebGuiPlugin::WebGuiPlugin(QObject *parent) : QObject(parent)
{
    QList<StbSubmodel> &submodels = getSubmodels();
    submodels.append(StbSubmodel("config", "config"));


}

WebGuiPlugin::~WebGuiPlugin()
{

}



PLUGIN_ERROR_CODES yasem::WebGuiPlugin::initialize()
{
    gui(dynamic_cast<GuiPlugin*>(PluginManager::instance()->getByRole(ROLE_GUI)));
    browser(dynamic_cast<BrowserPlugin*>(PluginManager::instance()->getByRole(ROLE_BROWSER)));

    Profile* profile = ProfileManager::instance()->createProfile(getProfileClassId(), "config", "web-gui-config", true);
    Q_ASSERT(profile);
    return PLUGIN_ERROR_NO_ERROR;
}

PLUGIN_ERROR_CODES yasem::WebGuiPlugin::deinitialize()
{
    return PLUGIN_ERROR_NO_ERROR;
}

void yasem::WebGuiPlugin::register_dependencies()
{
    add_dependency(ROLE_BROWSER);
    add_dependency(ROLE_GUI);
    add_dependency(ROLE_WEB_SERVER);
}

void yasem::WebGuiPlugin::register_roles()
{
    register_role(ROLE_WEB_GUI);
}

QString yasem::WebGuiPlugin::getProfileClassId()
{
    return "web-gui-plugin";
}

Profile *yasem::WebGuiPlugin::createProfile(const QString &id)
{
    Profile* profile = new GuiConfigProfile(this, id);
    profile->setId("web-gui-config");
    profile->setName("web-gui-config");
    ProfileManager::instance()->addProfile(profile);
    return profile;
}

void yasem::WebGuiPlugin::init(AbstractWebPage* page)
{
    getApi().clear();
    getApi().insert("__GUI__", new GuiStbObject(this));
}

QString yasem::WebGuiPlugin::getIcon(const QSize &size)
{
    return "-N/A-";
}

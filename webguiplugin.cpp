#include "webguiplugin.h"
#include "webguipluginobject.h"

using namespace yasem;

WebGuiPlugin::WebGuiPlugin(QObject *parent):
    Plugin(parent)
{

}

WebGuiPlugin::~WebGuiPlugin()
{

}

void yasem::WebGuiPlugin::register_dependencies()
{
    add_dependency(ROLE_BROWSER);
    add_dependency(ROLE_GUI);
    add_dependency(PluginDependency(ROLE_STB_API, false, true));
    add_dependency(PluginDependency(ROLE_WEB_SERVER, false));
}

void yasem::WebGuiPlugin::register_roles()
{
    register_role(ROLE_WEB_GUI, new WebGuiPluginObject(this));
}

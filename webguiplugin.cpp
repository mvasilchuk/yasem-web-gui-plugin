#include "webguiplugin.h"
#include "webguipluginobject.h"

using namespace yasem;

WebGuiPlugin::WebGuiPlugin(QObject *parent):
    SDK::Plugin(parent)
{

}

WebGuiPlugin::~WebGuiPlugin()
{
    STUB();
}

void yasem::WebGuiPlugin::register_dependencies()
{
    add_dependency(SDK::ROLE_BROWSER);
    add_dependency({SDK::ROLE_STB_API, false, true});
    add_dependency({SDK::ROLE_WEB_SERVER, false});
}

void yasem::WebGuiPlugin::register_roles()
{
    addFlag(SDK::PLUGIN_FLAG_SYSTEM);
    register_role(SDK::ROLE_WEB_GUI, new WebGuiPluginObject(this));
}

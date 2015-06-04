#include "guiconfigprofile.h"
#include "stbpluginobject.h"
#include "browserpluginobject.h"
#include "abstractwebpage.h"

using namespace yasem;

GuiConfigProfile::GuiConfigProfile(StbPluginObject* profilePlugin, const QString &id) :
    Profile(profilePlugin, id)
{
    addFlag(Profile::HIDDEN); // Don't show in STB list
}

void GuiConfigProfile::start()
{
    STUB();
    configureKeyMap();
    BrowserPluginObject* browser = m_profile_plugin->browser();
    if(browser)
    {
        browser->stb(m_profile_plugin);
        AbstractWebPage* page = browser->getActiveWebPage();
        page->setPageViewportSize(QSize(1920, 1080));
        page->load(QUrl(portal()));
    }
}

void GuiConfigProfile::stop()
{

}

void GuiConfigProfile::initDefaults()
{
    if(datasource())
    {
        if(datasource()->get("common", "url") == "")
        {
#ifdef Q_OS_DARWIN
            datasource()->set("common", "url", "../Resources/gui/html/main.html");
#else
            datasource()->set("common", "url", "gui/html/main.html");
#endif
        }
    }
}

void GuiConfigProfile::configureKeyMap()
{
    BrowserPluginObject* browser = m_profile_plugin->browser();
    if(browser)
    {
        browser->clearKeyEvents();
        //browser->registerKeyEvent(RC_KEY_LEFT, 37, 37);
        //browser->registerKeyEvent(RC_KEY_UP, 38, 38);
        //browser->registerKeyEvent(RC_KEY_RIGHT, 39, 39);
        //browser->registerKeyEvent(RC_KEY_DOWN, 40, 40);
        browser->registerKeyEvent(RC_KEY_OK, 13, 13);

        browser->registerKeyEvent(RC_KEY_RED, 11, 11);

        browser->registerKeyEvent(RC_KEY_EXIT, 27, 27); //ESC

        browser->registerKeyEvent(RC_KEY_RED, 112, 112); //F1 / Red
        browser->registerKeyEvent(RC_KEY_GREEN, 113, 113); //F2 / Green
        browser->registerKeyEvent(RC_KEY_YELLOW, 114, 114); //F3 / Yellow
        browser->registerKeyEvent(RC_KEY_BLUE, 115, 115); //F4 / Blue
    }
}

QString GuiConfigProfile::portal()
{
    QString urlToLoad;
    QString url = datasource()->get("common", "url");

    if(url.startsWith("file:///"))
        urlToLoad = url;
    else
    {
#ifdef Q_OS_WIN
        urlToLoad =  QString("file:///%1/%2").arg(qApp->applicationDirPath()).arg(url);
#else
        urlToLoad = QString("file://%1/%2").arg(qApp->applicationDirPath()).arg(url);
#endif
    }
   return urlToLoad;
}

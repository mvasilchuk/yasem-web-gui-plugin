#include "guiconfigprofile.h"
#include "stbpluginobject.h"
#include "browser.h"
#include "webpage.h"
#include "macros.h"
#include "datasource.h"

using namespace yasem;

#ifdef Q_OS_DARWIN
    #ifdef USE_OSX_BUNDLE
           static const QString DEFAULT_GUI_URL = "../Resources/gui/html/main.html";
    #else
           static const QString DEFAULT_GUI_URL = "../../../gui/html/main.html";
    #endif //USE_OSX_BUNDLE
#else
           static const QString DEFAULT_GUI_URL = "gui/html/main.html";
#endif //Q_OS_DARWIN

GuiConfigProfile::GuiConfigProfile(SDK::StbPluginObject* profilePlugin, const QString &id) :
    SDK::Profile(profilePlugin, id)
{
    addFlag(SDK::Profile::HIDDEN); // Don't show in STB list
}

GuiConfigProfile::~GuiConfigProfile()
{
    STUB() << m_name << m_id;
    //SDK::Core::printCallStack();
}

void GuiConfigProfile::start()
{
    STUB();
    configureKeyMap();
    SDK::Browser* browser = SDK::Browser::instance();
    if(browser)
    {
        browser->stb(m_profile_plugin);
        SDK::WebPage* page = browser->getMainWebPage();
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
            datasource()->set("common", "url", DEFAULT_GUI_URL);
        }
    }
}

void GuiConfigProfile::configureKeyMap()
{
    SDK::Browser* browser = SDK::Browser::instance();
    if(browser)
    {
        //browser->registerKeyEvent(RC_KEY_LEFT, 37, 37);
        //browser->registerKeyEvent(RC_KEY_UP, 38, 38);
        //browser->registerKeyEvent(RC_KEY_RIGHT, 39, 39);
        //browser->registerKeyEvent(RC_KEY_DOWN, 40, 40);
        browser->registerKeyEvent(SDK::GUI::RC_KEY_OK, 13, 13);

        browser->registerKeyEvent(SDK::GUI::RC_KEY_RED, 11, 11);

        browser->registerKeyEvent(SDK::GUI::RC_KEY_EXIT, 27, 27); //ESC

        browser->registerKeyEvent(SDK::GUI::RC_KEY_RED, 112, 112); //F1 / Red
        browser->registerKeyEvent(SDK::GUI::RC_KEY_GREEN, 113, 113); //F2 / Green
        browser->registerKeyEvent(SDK::GUI::RC_KEY_YELLOW, 114, 114); //F3 / Yellow
        browser->registerKeyEvent(SDK::GUI::RC_KEY_BLUE, 115, 115); //F4 / Blue
    }
}

QString GuiConfigProfile::portal()
{
    QString urlToLoad;
#ifdef QT_DEBUG
    QString url = datasource()->get("common", "url");
#else
    QString url = DEFAULT_GUI_URL;
#endif //QT_DEBUG

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

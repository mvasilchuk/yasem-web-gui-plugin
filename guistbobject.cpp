#include "guistbobject.h"
#include "profilemanager.h"
#include "stbprofile.h"
#include "pluginmanager.h"
#include "stbpluginobject.h"
#include "plugin.h"
#include "abstractwebpage.h"


#include <QJsonDocument>
#include <QRegularExpression>

using namespace yasem;

static const QString MENU_TYPE_STB_PROFILE = "stb-profile";
static const QString MENU_TYPE_NEW_STB_PROFILE = "new-stb-profile";

static const QString MENU_MAIN = "main-menu";
static const QString MENU_NEW_PROFILE_CLASSES = "new-profile-classes";

GuiStbObject::GuiStbObject(QObject *parent, AbstractWebPage* page) :
    QObject(parent),
    m_page(page)
{
    datasourcePlugin = dynamic_cast<DatasourcePlugin*>(PluginManager::instance()->getByRole(ROLE_DATASOURCE));
    m_page->setChromaKeyEnabled(false);
}

QJsonObject GuiStbObject::getProfilesMenuJson()
{
    QList<Profile*> profiles = ProfileManager::instance()->getProfiles().toList();
    qSort(profiles.begin(), profiles.end(), [](Profile *first, Profile *second) { return first->getName() < second->getName(); });

    QJsonObject result;
    QJsonObject items;

    foreach(Profile* profile, profiles)
    {
        if(profile->hasFlag(Profile::HIDDEN)) continue;

        StbPluginObject* plugin = profile->getProfilePlugin();
        QString id = profile->getId();

        QJsonObject obj;
        obj.insert("type", MENU_TYPE_STB_PROFILE);
        obj.insert("image", plugin->getIcon());
        obj.insert("title", profile->getName());
        obj.insert("id", id);
        obj.insert("url", profile->datasource()->get("profile", "portal", ""));
        obj.insert("class", plugin->getProfileClassId());

        items.insert(id, obj);
    }


    QJsonObject obj;
    obj.insert("type", QString());
    obj.insert("image", QString("../icons/add-stb-profile.png"));
    obj.insert("title", tr("New profile"));
    obj.insert("submenu", MENU_NEW_PROFILE_CLASSES);

    items.insert("new-profile-parent-menu", obj);

    result.insert("items", items);
    result.insert("count", items.count());

    return result;
}

QJsonObject GuiStbObject::getNewProfileMenuJson()
{
    QMap<QString, StbPluginObject*> stb_plugins = ProfileManager::instance()->getRegisteredClasses();

    QJsonObject result;
    QJsonObject items;

    for(const QString &classId: stb_plugins.keys())
    {
        StbPluginObject* stb_plugin = stb_plugins.value(classId);

        DEBUG() << "STB API found:" << stb_plugin->plugin()->getClassName();

        QList<StbSubmodel> submodels = stb_plugin->getSubmodels();

        for(const StbSubmodel &submodel: submodels)
        {
            QJsonObject obj;
            obj.insert("type", QString("new-stb-profile"));
            obj.insert("image", submodel.m_logo);
            obj.insert("title", submodel.m_name);
            obj.insert("class", classId);
            obj.insert(CONFIG_SUBMODEL, submodel.m_id);

            QString id = classId;
            id.append(":").append(submodel.m_id);
            items.insert(id, obj);
        }

    }

    result.insert("items", items);
    result.insert("count", items.count());

    return result;
}

QString GuiStbObject::makeJsonMenu()
{
    QJsonObject menu;
    QJsonObject items;

    items.insert(MENU_MAIN, getProfilesMenuJson());
    items.insert(MENU_NEW_PROFILE_CLASSES, getNewProfileMenuJson());

    menu.insert("default", MENU_MAIN);
    menu.insert("current", MENU_MAIN);
    menu.insert("current_item_id", QString());
    menu.insert("items", items);

    return QString(QJsonDocument(menu).toJson(QJsonDocument::Indented));
}

QString GuiStbObject::getProfileConfigOptions(const QString &profileId)
{
   DEBUG() << profileId;
   QString result = "";
   Profile* profile = ProfileManager::instance()->findById(profileId);

   if(!profile)
   {
       WARN() << "Profile not found!";
   }
   else
   {
       QJsonObject result_object;
       QJsonArray arr;

       const ProfileConfiguration &config = profile->config();

       for(ProfileConfigGroup group: config.groups)
       {
           DEBUG() << "GROUP:" << group.title;

           for(int index = 0; index < group.options.size(); index++)
           {
               const ConfigOption &option = group.options.at(index);

               QJsonObject obj;

               obj.insert("tag", option.tag);
               obj.insert("name", option.name);
               obj.insert("title", option.title);
               obj.insert("comment", option.comment);
               obj.insert("value", profile->datasource()->get(option.tag, option.name, option.defaultValue));
               obj.insert("type", option.type);

               QJsonObject options;
               for(const QString &key: option.options.keys())
               {
                   options.insert(key, option.options.value(key));
               }

               obj.insert("options", options);

               arr.append(obj);
           }
       }

       result_object.insert("submodel", profile->getSubmodel().m_id);
       result_object.insert("submodel_key", QString("%1/%2").arg(profile->getProfilePlugin()->getSubmodelDatasourceGroup(),
                                                                 profile->getProfilePlugin()->getSubmodelDatasourceField()));
       result_object.insert("options", arr);

       result = QString(QJsonDocument(result_object).toJson(QJsonDocument::Indented));
       qDebug() << result;
   }
   return result;

}

QString GuiStbObject::createProfile(const QString &classId, const QString &submodel, const QString &data = "{}")
{
    STUB();
    qDebug() << classId << submodel << "data" << data;

    Profile* profile = ProfileManager::instance()->createProfile(classId, submodel);

    Q_ASSERT(profile);
    ProfileManager::instance()->addProfile(profile);
    qDebug() << profile;
    return profile->getId();
}

QString GuiStbObject::getTranslations()
{
    QJsonArray result;

    result.append(tr("Create new profile"));
    result.append(tr("Select profile"));
    result.append(tr("Choose base profile"));
    result.append(tr("Configure profile"));

    return QString(QJsonDocument(result).toJson(QJsonDocument::Indented));
}

void GuiStbObject::loadProfile(const QString &id)
{
    Profile* profile = ProfileManager::instance()->findById(id);
    if(profile != NULL)
        ProfileManager::instance()->setActiveProfile(profile);
    else
        WARN() << qPrintable(QString("GuiStbObject::loadProfile: can't load profile %1").arg(id));
}

bool GuiStbObject::saveProfile(const QString &id, const QString& jsonData)
{
    DEBUG() << id << jsonData;
    Profile* profile = ProfileManager::instance()->findById(id);
    if(profile != NULL)
        return profile->saveJsonConfig(jsonData);
    else
        WARN() << qPrintable(QString("GuiStbObject::saveProfile: can't save the profile %1 with data %2").arg(id).arg(jsonData));
    return false;
}

bool GuiStbObject::removeProfile(const QString &id)
{
    Profile* profile = ProfileManager::instance()->findById(id);
    if(profile != NULL)
        return ProfileManager::instance()->removeProfile(profile);
    else
        WARN() << qPrintable(QString("GuiStbObject::removeProfile: can't remove the profile %1").arg(id));
    return false;
}

QString GuiStbObject::getAppInfo()
{
    QJsonObject result;

    result.insert("name", QString("yasem"));
    result.insert("version", QString("version 0.1"));
    result.insert("copyright", QString("Copyright 2014 by Maxim Vasilchuk"));

    return QString(QJsonDocument(result).toJson(QJsonDocument::Indented));
}

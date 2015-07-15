#ifndef GUISTBOBJECT_H
#define GUISTBOBJECT_H

#include <QJsonObject>
#include <QObject>

namespace yasem
{

namespace SDK {
class DatasourcePlugin;
class WebPage;
}

class GuiStbObject : public QObject
{
    Q_OBJECT
public:
    explicit GuiStbObject(QObject *parent, SDK::WebPage* page);

public slots:
    QString makeJsonMenu();

    QString createProfile(const QString &classId, const QString &submodel, const QString &data);
    QString getTranslations();
    QString getProfileConfigOptions(const QString &profileId);
    QJsonObject getProfilesMenuJson();
    QJsonObject getNewProfileMenuJson();

    void loadProfile(const QString &id);

    bool saveProfile(const QString &id, const QString &jsonData);
    QString getAppInfo();
    bool removeProfile(const QString &id);
protected:
    SDK::DatasourcePlugin* datasourcePlugin;
    SDK::WebPage* m_page;

};

}

#endif // GUISTBOBJECT_H

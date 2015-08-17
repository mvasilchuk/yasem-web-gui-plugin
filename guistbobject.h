#ifndef GUISTBOBJECT_H
#define GUISTBOBJECT_H

#include <QJsonObject>
#include <QObject>
#include <QSharedPointer>

namespace yasem
{

namespace SDK {
class Datasource;
class WebPage;
}

class GuiStbObject : public QObject
{
    Q_OBJECT
public:
    explicit GuiStbObject(SDK::WebPage* page);
    virtual ~GuiStbObject();

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
    SDK::WebPage* m_page;

};

}

#endif // GUISTBOBJECT_H

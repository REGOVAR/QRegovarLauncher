#ifndef REGOVARLAUNCHER_H
#define REGOVARLAUNCHER_H

#include <QtCore>
#include <QtNetwork>

class RegovarLauncher: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString clientVersion READ clientVersion NOTIFY dataChanged)
    Q_PROPERTY(QString lastClientVersion READ lastClientVersion NOTIFY dataChanged)
    Q_PROPERTY(QString serverVersion READ serverVersion NOTIFY dataChanged)
    Q_PROPERTY(QString lastServerVersion READ lastServerVersion NOTIFY dataChanged)
    Q_PROPERTY(bool sharedServerAvailable READ sharedServerAvailable NOTIFY dataChanged)
    Q_PROPERTY(QDateTime sharedServerLastUpdate READ sharedServerLastUpdate NOTIFY dataChanged)
    Q_PROPERTY(QDateTime sharedServerLastSynchro READ sharedServerLastSynchro NOTIFY dataChanged)


public:
    // Constructor
    RegovarLauncher();

    // Getters
    inline QString clientVersion() const { return mClientVersion; }
    inline QString lastClientVersion() const { return mLastClientVersion; }
    inline QString serverVersion() const { return mServerVersion; }
    inline QString lastServerVersion() const { return mLastServerVersion; }
    inline bool sharedServerAvailable() const { return mSharedServerAvailable; }
    inline QDateTime sharedServerLastUpdate() const { return mSharedServerLastUpdate; }
    inline QDateTime sharedServerLastSynchro() const { return mSharedServerLastSynchro; }

    // Methods

    //! Check if a new version of QRegovar exists (on gitbub)
    Q_INVOKABLE void init();
    //! Check whole Regovar system and return true if all is ok
    Q_INVOKABLE bool check();
    //! Download the requested version of the client QRegovar
    Q_INVOKABLE void downloadClient(QString version="");
    //! Install the requested version of the client QRegovar
    Q_INVOKABLE void installClient(QString version="");
    //! Uninstall the requested version of the client QRegovar
    Q_INVOKABLE void uninstallClient(QString version="");
    //! Start the QRegovar application
    Q_INVOKABLE void startClient(QString version="");


Q_SIGNALS:
    void dataChanged();

protected:
    QJsonDocument get(QString url);

private:
    QString mClientVersion;
    QString mLastClientVersion;
    QJsonObject mLastClientAsset;
    QString mServerVersion;
    QString mLastServerVersion;
    bool mSharedServerAvailable;
    QDateTime mSharedServerLastUpdate;
    QDateTime mSharedServerLastSynchro;

    QString mGithubClientUrl;
    QString mGithubServerUrl;
    QString mSharedServerUrl;
    QString mLocalServerUrl;

    QString mClientPath;

};

#endif // REGOVARLAUNCHER_H

#include "regovarlauncher.h"

RegovarLauncher::RegovarLauncher()
{

}


QJsonDocument RegovarLauncher::get(QString urlString)
{
    // Retrieve
    QNetworkAccessManager networkManager;

    QUrl url(urlString);
    QNetworkRequest request;
    request.setUrl(url);

    QNetworkReply* req = networkManager.get(request);
    while(!req->isFinished())
    {
        qApp->processEvents();
    }

    if (req->error() != QNetworkReply::NoError)
        return QJsonDocument();

    return QJsonDocument::fromJson(req->readAll());
}

void RegovarLauncher::init()
{
    // TODO: Load settings
    mGithubClientUrl = "https://api.github.com/repos/REGOVAR/QRegovar/releases";
    mGithubServerUrl = "https://api.github.com/repos/REGOVAR/Regovar/releases";
    mSharedServerUrl = "http://shared.regovar.org/stats";
    mLocalServerUrl = "http://dev.regovar.org/config";
    mClientPath = "";
}

//! Return
//!    true: No problem
//!    false: Something that may need user action
bool RegovarLauncher::check()
{
    bool result = true;

    // Github client
    QJsonDocument doc = get(mGithubClientUrl);
    if (!doc.isEmpty())
    {
        QJsonArray data = doc.array();
        if (data.count() > 0 )
        {
            mLastClientAsset =  data[0].toObject();
            mLastClientVersion = mLastClientAsset["tag_name"].toString();
        }
    }
    else
    {
        qDebug() << "Unable to retrieve Github informations for the client";
    }

    // Github server
    doc = get(mGithubServerUrl);
    if (!doc.isEmpty())
    {
        QJsonArray data = doc.array();
        if (data.count() > 0 )
        {
            QJsonObject json = data[0].toObject();
            mLastServerVersion = json["tag_name"].toString();
        }
    }
    else
    {
        qDebug() << "Unable to retrieve Github informations for the server";
    }

    // Get Local server informations
    doc = get(mLocalServerUrl);
    if (!doc.isEmpty())
    {
        QJsonObject data = doc.object();
        if (!data.isEmpty() && data["success"].toBool())
        {
            data = data["data"].toObject();
            mServerVersion = data["version"].toString();
        }
    }
    else
    {
        qDebug() << "Unable to retrieve Github informations";
    }

    // Get Local server informations
    QFileInfo checkFile(mClientPath);
    if (checkFile.exists() && checkFile.isExecutable())
    {
        QProcess* process = new QProcess(this);
        process->start(mClientPath);
    }
    else
    {
        qDebug() << "Not able to run the exe: " << mClientPath;
    }



    // TODO: Check local server url
    // TODO: Check shared server url
    // TODO: Check if new server version exists and compare with local server version
    return true;
}



void RegovarLauncher::downloadClient(QString)
{

}



void RegovarLauncher::installClient(QString)
{
    // todo, check if zip of the client version exists
    // check that folder not already exists
    // unzip and install version
}



void RegovarLauncher::uninstallClient(QString)
{
    // Todo, check if folder  exists, and delete all
}



void RegovarLauncher::startClient(QString)
{
    // Check if application exists
    QFileInfo checkFile(mClientPath);
    if (checkFile.exists() && checkFile.isExecutable())
    {
        QProcess* process = new QProcess(this);
        process->start(mClientPath);
    }
    else
    {
        qDebug() << "Not able to run the exe: " << mClientPath;
    }

}

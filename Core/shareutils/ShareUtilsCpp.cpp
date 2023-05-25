
#include <jni.h>

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>
#include <QUrl>
#include <QJniObject>

#include "ShareUtilsCpp.h"

ShareUtilsCpp::ShareUtilsCpp(QObject *parent) :
    QObject(parent) {
#if defined(Q_OS_IOS)
    mPlatformShareUtils = new IosShareUtils(this);
#elif defined(Q_OS_ANDROID)
    mPlatformShareUtils = new AndroidShareUtils(this);
#else \
    // NOTE: The dummy is here so that the object compiles well for desktop \
    // builds, however, since this project is meant for iOS and Android native \
    // share design patterns, it doesn't really make sense to implement share \
    // methods for desktop as well. If you're interested in accessing files on \
    // desktop, Qt provides `QFileDialog` for this explicit purpose, and this \
    // class better matches the desktop design pattern.
    mPlatformShareUtils = new DummyShareUtils(this);
#endif

    connect(mPlatformShareUtils, SIGNAL(shareFinished(int)),
            this, SLOT(onShareFinished(int)));

    connect(mPlatformShareUtils,
            SIGNAL(shareNoAppAvailable(int)),
            this,
            SLOT(onShareNoAppAvailable(int)));

    connect(mPlatformShareUtils,
            SIGNAL(shareError(int, QString)),
            this,
            SLOT(onShareError(int, QString)));

    connect(mPlatformShareUtils,
            SIGNAL(fileUrlReceived(QString)),
            this,
            SLOT(onFileUrlReceived(QString)));
}

bool ShareUtilsCpp::checkMimeTypeView(const QString &mimeType) {
    return mPlatformShareUtils->checkMimeTypeView(mimeType);
}

void ShareUtilsCpp::sendFile(const QString &filePath, const QString &title, const QString &mimeType, const int &requestId) {
    mPlatformShareUtils->sendFile(filePath, title, mimeType, requestId);
}

void ShareUtilsCpp::viewFile(const QString &filePath, const QString &title, const QString &mimeType, const int &requestId) {
    mPlatformShareUtils->viewFile(filePath, title, mimeType, requestId);
}

void ShareUtilsCpp::checkPendingIntents() {
    mPlatformShareUtils->checkPendingIntents();
}

void ShareUtilsCpp::clearTempDir() {
    mPlatformShareUtils->clearTempDir();
}

void ShareUtilsCpp::onShareFinished(int requestCode) {
    emit shareFinished(requestCode);
}

void ShareUtilsCpp::onShareNoAppAvailable(int requestCode) {
    emit shareNoAppAvailable(requestCode);
}

void ShareUtilsCpp::onShareError(int requestCode, QString message) {
    emit shareError(requestCode, message);
}

void ShareUtilsCpp::onFileUrlReceived(QString url) {
    emit fileUrlReceived(url);
}

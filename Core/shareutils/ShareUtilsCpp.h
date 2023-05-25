
#ifndef SHAREUTILSCPP_H
#define SHAREUTILSCPP_H

#include <QDebug>
#include <QObject>
#include <QQmlEngine>

#include "PlatformShareUtils.h"

#if defined(Q_OS_ANDROID)
#include <QtCore/private/qandroidextras_p.h>
//#include <QAndroidActivityResultReceiver>
//#include <QtAndroid>
#endif // Q_OS_ANDROID

/*!
 * \brief The ShareUtils class interfaces the various ShareUtils for each
 * platform with a standard Qt interface. This allows you to include a
 * `ShareUtils` object in your application as a standard Qt object. The
 * `ShareUtils` class abstracts away the native code and emits signals instead.
 * For android and iOS this provides the ability to view and send files. For
 * desktop builds, this only provides a dummy. In desktop environments this
 * design pattern doesn't make sense and QFileDialog is preferred.
 */
class ShareUtilsCpp : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    /// constructor, the `PlatformShareUtils` will be different in different OSes.
    explicit ShareUtilsCpp(QObject* parent = nullptr);

    /// @copydoc PlatformShareUtils::checkMimeTypeView(const QString&)
    bool checkMimeTypeView(const QString& mimeType);

public slots:

    /// @copydoc PlatformShareUtils::sendFile(const QString&, const QString&,
    /// const QString&, int)
    void sendFile(const QString& filePath,
                  const QString& title,
                  const QString& mimeType,
                  const int& requestId);

    /// @copydoc PlatformShareUtils::viewFile(const QString&, const QString&,
    /// const QString&, int)
    void viewFile(const QString& filePath,
                  const QString& title,
                  const QString& mimeType,
                  const int& requestId);

    /// @copydoc PlatformShareUtils::checkPendingIntents()
    void checkPendingIntents();

    /// @copydoc PlatformShareUtils::clearTempDir();
    void clearTempDir();

signals:
    /// emits when a share finishes successfully
    void shareFinished(int requestCode);

    /// emits when a share fails because an app could not be found
    void shareNoAppAvailable(int requestCode);

    /// emits when there is an error with sharing, will give message and requestID
    /// if provided
    void shareError(int requestCode, QString message);

    /// emits when a URL is received
    void fileUrlReceived(QString url);

    /// emits when a URL is received and a file is saved.
    void fileReceivedAndSaved(QString url);

private slots:
    /// emits a signal when a share finishes successfully
    void onShareFinished(int requestCode);

    /// emits a signal when a share fails because an app could not be found
    void onShareNoAppAvailable(int requestCode);

    /// emits a signal when there is an error with sharing, will give message and
    /// requestID if provided
    void onShareError(int requestCode, QString message);

    /// emits a signal when a URL is received
    void onFileUrlReceived(QString url);

private:
    /*! the object that is used to handle the native share interface. This object
     * will be a different class depending on what OS the Qt code is compiled for.
     */
    PlatformShareUtils* mPlatformShareUtils;
};

#endif // SHAREUTILSCPP_H

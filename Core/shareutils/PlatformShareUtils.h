#ifndef PLATFORMSHAREUTILS_H
#define PLATFORMSHAREUTILS_H

#include <QObject>
#if defined(Q_OS_ANDROID)
#include <QtCore/private/qandroidextras_p.h>
//#include <QAndroidActivityResultReceiver>
//#include <QtAndroid>
#endif // Q_OS_ANDROID

/*!
 * \brief The PlatformShareUtils class is an abstract class that implements the
 * functionality for sending and viewing files through the native mobile
 * interfaces. Each mobile interface has its own derived class that handles
 * communicating with native mobile code.
 */
class PlatformShareUtils : public QObject {
    Q_OBJECT
public:
    PlatformShareUtils(QObject* parent) : QObject(parent) {}

    /*!
     * \brief checkMimeTypeView check whether the mimeType provided is compatible
     * with the application that will be sending/viewing the file. \param mimeType
     * mimeType to check \return true if the mimeType is supported, false
     * otherwise
     */
    virtual bool checkMimeTypeView(const QString& mimeType) = 0;

    /*!
     * \brief sendFile send a file through the native mobile share interface
     * \param filePath the absolute path to the file
     * \param title the title of the share
     * \param mimeType the mimeType of the file
     * \param requestId the ID to give the task of sending a file. Set this to a
     * value other than 0 if you want to track the completion of the task.
     */
    virtual void sendFile(const QString& filePath,
                          const QString& title,
                          const QString& mimeType,
                          int requestId) = 0;

    /*!
     * \brief vuewFile view a file through the native mobile share interface
     * \param filePath the absolute path to the file
     * \param title the title of the share
     * \param mimeType the mimeType of the file
     * \param requestId the ID to give the task of sending a file. Set this to a
     * value other than 0 if you want to track the completion of the task.
     */
    virtual void viewFile(const QString& filePath,
                          const QString& title,
                          const QString& mimeType,
                          int requestId) = 0;

    /*!
     * \brief checkPendingIntents used by android only, this checks for pending
     * intents when an application becomes active again.
     */
    virtual void checkPendingIntents() {}

    /*!
     * \brief clearTempDir android only, this provides an option to clear the temp
     * save directory.
     */
    virtual void clearTempDir() {}

signals:
    /// emits when a share finishes successfully.
    void shareFinished(int requestID);

    /// emits when a share fails because an app could not be found
    void shareNoAppAvailable(int requestID);

    /// emits when there is an error with sharing, will give message and requestID
    /// if provided
    void shareError(int requestID, QString message);

    /// emits when a URL is received
    void fileUrlReceived(QString url);
};

/*!
 * \brief The DummyShareUtils class dervies from the PlatformShareUtils class
 * and exists only to make it so that you don't need to wrap `ShareUtils` in
 * preprocessor macros when compiling for desktop. When working with viewing and
 * sending files on desktop, you should instead use QFileDialog.
 */
class DummyShareUtils : public PlatformShareUtils {
    Q_OBJECT
public:
    DummyShareUtils(QObject* parent) : PlatformShareUtils(parent) {}

    /// @copydoc PlatformShareUtils::checkMimeTypeView(const QString&)
    virtual bool checkMimeTypeView(const QString& mimeType) override {
        qDebug() << __func__ << "mimType:" << mimeType;
        return false;
    }

    /// @copydoc PlatformShareUtils::sendFile(const QString&, const QString&,
    /// const QString&, int)
    virtual void sendFile(const QString& filePath,
                          const QString& title,
                          const QString& mimeType,
                          int requestId) override {
        qDebug() << __func__ << "filePath:" << filePath << " title: " << title
                 << " mimType: " << mimeType << " requestID: " << requestId;
    }

    /// @copydoc PlatformShareUtils::viewFile(const QString&, const QString&,
    /// const QString&, int)
    virtual void viewFile(const QString& filePath,
                          const QString& title,
                          const QString& mimeType,
                          int requestId) override {
        qDebug() << __func__ << "filePath:" << filePath << " title: " << title
                 << " mimType: " << mimeType << " requestID: " << requestId;
    }
};

#if defined(Q_OS_IOS)

/*!
 * \brief The IosShareUtils class dervies from the PlatformShareUtils class and
 * implements communication between the iOS native share and the Qt application.
 */
class IosShareUtils : public PlatformShareUtils {
    Q_OBJECT

public:
    explicit IosShareUtils(QObject* parent);

    /// @copydoc PlatformShareUtils::checkMimeTypeView(const QString&)
    bool checkMimeTypeView(const QString& mimeType) override;

    /// @copydoc PlatformShareUtils::sendFile(const QString&, const QString&,
    /// const QString&, int)
    void sendFile(const QString& filePath,
                  const QString& title,
                  const QString& mimeType,
                  int requestId) override;

    /// @copydoc PlatformShareUtils::viewFile(const QString&, const QString&,
    /// const QString&, int)
    void viewFile(const QString& filePath,
                  const QString& title,
                  const QString& mimeType,
                  int requestId) override;

    void handleDocumentPreviewDone(const int& requestId);

public slots:

    void handleFileUrlReceived(const QUrl& url);
};

#endif

#if defined(Q_OS_ANDROID)

/*!
 * \brief The AndroidShareUtils class dervies from the PlatformShareUtils class
 * and implements communication between the android native share and the Qt
 * application.
 */
class AndroidShareUtils : public PlatformShareUtils, public QAndroidActivityResultReceiver {
    Q_OBJECT
public:
    AndroidShareUtils(QObject* parent = nullptr);

    /// @copydoc PlatformShareUtils::checkMimeTypeView(const QString&)
    bool checkMimeTypeView(const QString& mimeType) override;

    /// @copydoc PlatformShareUtils::sendFile(const QString&, const QString&,
    /// const QString&, int)
    void sendFile(const QString& filePath,
                  const QString& title,
                  const QString& mimeType,
                  int requestId) override;

    /// @copydoc PlatformShareUtils::viewFile(const QString&, const QString&,
    /// const QString&, int)
    void viewFile(const QString& filePath,
                  const QString& title,
                  const QString& mimeType,
                  int requestId) override;

    /// @copydoc PlatformShareUtils::checkPendingIntents()
    void checkPendingIntents() override;

    /// @copydoc PlatformShareUtils::clearTempDir()
    void clearTempDir() override;

    void handleActivityResult(int receiverRequestCode,
                              int resultCode,
                              const QJniObject& data) override;

    void onActivityResult(int requestCode, int resultCode);

    /// gets single instance of the AndroidShareUtils
    static AndroidShareUtils* getInstance();

public slots:
    void setFileUrlReceived(const QString& url);

    bool checkFileExits(const QString& url);

private:
    static AndroidShareUtils* mInstance;

    QString mSavePath;

    void processActivityResult(int requestCode, int resultCode);
};

#endif
#endif // PLATFORMSHAREUTILS_H

#ifndef RESOURCECREATORCPP_H
#define RESOURCECREATORCPP_H

#include <QObject>
#include <QQmlEngine>

class ResourceCreatorCpp : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    ResourceCreatorCpp(QObject *parent = nullptr);

public slots:
    QString pdfPath();

    QString imgPath();

private:
    QString m_pdfPath;
    QString m_imgPath;
};

#endif // RESOURCECREATORCPP_H

#include "ResourceCreatorCpp.h"

#include <QBuffer>
#include <QTextDocument>
#include <QPrinter>
#include <QDateTime>
#include <QStandardPaths>
#include <QFile>

ResourceCreatorCpp::ResourceCreatorCpp(QObject *parent) :
    QObject(parent)

{

    // Main Document
    QString html =
        QString(R"(<!DOCTYPE html>
<html>
<head>
<style>
table {
    width: 100%;
    margin: 5px;
    border-collapse: collapse;
}

th {
    border: 1px solid #dddddd;
    text-align: left;
    padding: 4px;
    color: white;
    background-color:#26BCD5;
    font-family: "Roboto";
    font-size: 150px;
    border-collapse: collapse;
}

td {
  border: 1px solid #dddddd;
  border-collapse: collapse;
  text-align: center;
  padding: 4px;
  font-family: "Roboto";
  font-size: 100px;
}
</style>
</head>
<body>

<p style="font-size: 300px">%0</p>
<p style="font-size: 150px">%0</p>
<p style="font-size: 200px">%1</p>
<p style="font-size: 200px">%2</p>

</body>
</html>
)").arg("QtAndroidViewShareExample")
                       .arg("MAK")
                       .arg("LIBRARY");

    QTextDocument document;
    document.setHtml(html);

    // Create printer and prepare to print as pdf
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize::A4);

    QString path = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::DocumentsLocation);
    QString reportTime = QDateTime::currentDateTime().toString("yyyy.MM.dd_hh.mm.ss");
    QString file = path + QString("/QtAndroidViewShareExample%0.pdf").arg(reportTime);
    printer.setOutputFileName(file);
    printer.setPageMargins(QMarginsF(5, 10, 5, 10));

    m_pdfPath  = file;
    document.print(&printer);

    m_imgPath = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::PicturesLocation) + "/lenna.png";
    qDebug()<<Q_FUNC_INFO<<__LINE__<<QFile::copy(":/res/lenna.png", m_imgPath);
}

QString ResourceCreatorCpp::pdfPath() {
    return m_pdfPath;
}

QString ResourceCreatorCpp::imgPath() {
    return m_imgPath;
}

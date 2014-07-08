#include "reswareportform.h"
#include "ui_reswareportform.h"
#include <QTextDocument>
#include <QTextTableFormat>
#include <QGridLayout>
#include <QTextCursor>
#include <QPainter>
#include <QAbstractTextDocumentLayout>

ResWaReportForm::ResWaReportForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResWaReportForm)
{
    ui->setupUi(this);

    BuildReport();
}

ResWaReportForm::~ResWaReportForm()
{
    delete ui;
}

void ResWaReportForm::BuildReport()
{
    _report = new QTextDocument();
    QTextCursor cursor(_report);
    QTextTableFormat m_TableFormat;
    m_TableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
    m_TableFormat.setAlignment(Qt::AlignTop);
    m_TableFormat.setWidth(400);
    m_TableFormat.setHeight(400);
    cursor.insertTable(5,2,m_TableFormat);
    cursor.insertBlock();
    cursor.insertText("Text and stuff");

//    QGridLayout *gridLayout = new QGridLayout();
//    gridLayout->addWidget(_report);
//    setLayout(gridLayout);
    QPainter painter;
    painter.begin(ui->reportFrame);
    _report->documentLayout()->setPaintDevice(ui->reportFrame);
    _report->setTextWidth(ui->reportFrame->width());
    _report->drawContents(&painter);
    painter.drawText(200, 200, "GRRRRRRRR");
    painter.end();



    QImage img;
    img.setDotsPerMeterX(qRound(800 / 0.118)); // the CD label has a diameter of 118mm
    img.setDotsPerMeterY(qRound(800 / 0.118));
    QPainter p(&img);
    // p.translate to the right position
    _report->drawContents(&p);
    // compare with QPainter::drawText:
    p.setFont(_report->defaultFont());
    p.drawText(0, 0, QLatin1String("test text"));
    p.end();
    img.save("/tmp/check.png", "PNG");

}

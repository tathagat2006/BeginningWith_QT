#include "textfinder.h"
#include "ui_textfinder.h"
#include <QFile>
#include <QTextStream>

TextFinder::TextFinder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextFinder)
{
    ui->setupUi(this);
    loadTextFile();
}

TextFinder::~TextFinder()
{
    delete ui;
}

void TextFinder::loadTextFile(){
    QFile inputFile(":/input.txt");
    inputFile.open(QIODevice::ReadOnly);

    QTextStream in(&inputFile);
    QString line=in.readAll();
    inputFile.close();

    ui->textEdit->setPlainText(line);
    QTextCursor cursor=ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Start,QTextCursor::MoveAnchor,1);
}

void TextFinder::on_findButton_clicked()
{
    QString searchstring=ui->lineEdit->text();
    ui->textEdit->find(searchstring,QTextDocument::FindWholeWords);
}

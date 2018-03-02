/********************************************************************************
** Form generated from reading UI file 'textfinder.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTFINDER_H
#define UI_TEXTFINDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TextFinder
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *findButton;
    QTextEdit *textEdit;

    void setupUi(QWidget *TextFinder)
    {
        if (TextFinder->objectName().isEmpty())
            TextFinder->setObjectName(QStringLiteral("TextFinder"));
        TextFinder->resize(400, 300);
        verticalLayout = new QVBoxLayout(TextFinder);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(TextFinder);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(TextFinder);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        findButton = new QPushButton(TextFinder);
        findButton->setObjectName(QStringLiteral("findButton"));

        verticalLayout->addWidget(findButton);

        textEdit = new QTextEdit(TextFinder);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout->addWidget(textEdit);


        retranslateUi(TextFinder);

        QMetaObject::connectSlotsByName(TextFinder);
    } // setupUi

    void retranslateUi(QWidget *TextFinder)
    {
        TextFinder->setWindowTitle(QApplication::translate("TextFinder", "TextFinder", nullptr));
        label->setText(QApplication::translate("TextFinder", "Keyword", nullptr));
        findButton->setText(QApplication::translate("TextFinder", "FIND", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TextFinder: public Ui_TextFinder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTFINDER_H

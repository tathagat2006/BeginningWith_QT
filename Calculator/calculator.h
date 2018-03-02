#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>

class QLineEdit;
class Button;

namespace Ui {
class calculator;
}

class calculator : public QWidget
{
    Q_OBJECT

public:
    explicit calculator(QWidget *parent = 0);
    ~calculator();

private slots:

        void digitClicked();
        void unaryOperatorClicked();
        void additiveOperatorClicked();
        void multiplicativeOperatorClicked();
        void equalClicked();
        void pointClicked();
        void changeSignClicked();
        void backspaceClicked();
        void clear();
        void clearAll();
        void clearMemory();
        void readMemory();
        void setMemory();
        void addToMemory();

    private:
        Ui::calculator *ui;
        Button *createButton(const QString &text, const char *member);
        void abortOperation();
        bool calculate(double rightOperand, const QString &pendingOperator);

        double sumInMemory;
        double sumSoFar;
        double factorSoFar;
        QString pendingAdditiveOperator;
        QString pendingMultiplicativeOperator;
        bool waitingForOperand;

        QLineEdit *display;

        enum { NumDigitButtons = 10 };
        Button *digitButtons[NumDigitButtons];
};

#endif // CALCULATOR_H

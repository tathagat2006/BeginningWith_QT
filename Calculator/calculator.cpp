#include "calculator.h"
#include "ui_calculator.h"

#include "button.h"
#include <cmath>
#include <QtWidgets>

calculator::calculator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::calculator)
{
    ui->setupUi(this);
    sumInMemory=0.0;
    sumSoFar=0.0;
    factorSoFar=0.0;
    waitingForoperand=true;

    display=new QLineEdit("0");
    display->setReadonly(true);
    display->setAlingment(Qt::AlignRight);
    display->setMaxlength(15);

    QFont font=display->font();
    font.setPointSize(font.pointSize()+8);
    display->setfont(font);

    for(int i=0;i<NumDigitButtons;i++){
        digitButtons[i]=createButton(QString::number(i),SLOT(digitClicked()));
    }
     Button *pointButton=createButton(tr("."),SLOT(pointClicked()));
     Button *changeSignButton=createButton(tr("\302\261"),SLOT(changeSignClicked()));

     Button *backSpaceButton=createButton(tr("BackSpace"),SLOT(backSpaceClicked()));
     Button *clearButton=createButton(tr("Clear"),SLOT(clear()));
     Button *clearAllButton=createButton(tr("Clear All"),SLOT(clearAll()));

     Button *clearMemoryButton=createButton(tr("MC"),SLOT(clearMemory()));
     Button *readMemoryButton=createButton(tr("MR"),SLOT(readMemory()));
     Button *setMemoryButton=createButton(tr("MS"),SLOT(setemory()));
     Button *addToMemoryButton=createButton(tr("M+"),SLOT(addToMemory()));

     Button *divisionButton=createButton(tr("\303\267"),SLOT(multiplicativeOperatorClicked()));
     Button *timesButton=createButton(tr("\303\227"),SLOT(multiplicativeOperatorClicked()));
     Button * minusButton=createButton(tr("-"),SLOT(additiveOperatorClicked()));
     Button *plusButton=createButton(tr("+"),SLOT(additiveOperatorClicked()));

     Button *squareRootButton=createButton(tr("sqrt"),SLOT(unaryOperatorClicked()));
     Button *powerButton=createButton(tr("x\302\262"),SLOT(unaryOperatorClicked()));
     Button *reciprocalButton=createButton(tr("1/x"),SLOT(unaryOperatorClicked()));
     Button *equalButton=createButton(tr("="),SLOT(equalClicked()));

     QGridLayout *mainLayout=new QGridLayout;
     mainLayout->setSizeConstraint(QLayout::SetFixedSize);
     mainLayout->addWidget(display,0,01,6);
     mainLayout->addWidget(backSpaceButton,1,0,1,2);
     mainLayout->addWidget(clearButton,1,2,1,2);
     mainLayout->addWidget(clearAllButton,1,4,1,2);

     mainLayout->addWidget(clearMemoryButton,2,0);
     mainLayout->addWidget(readMemoryButton,3,0);
     mainLayout->addWidget(setMemoryButton,4,0);
     mainLayout->addWidget(addToMemoryButton,5,0);

     for(int i=1;i<NumDigitButtons;i++){
         int row=((9-i)/3)+2;
         int col=((i-1)%3)+1;
         mainLayout->addWidget(digitButtons[i],row,col);
     }

     mainLayout->addWidget(digitButtons[0],5,1);
     mainLayout->addWidget(pointButton,5,2);
     mainLayout->addWidget(changeSignButton,5,3);

     mainLayout->addWidget(divisionButton,2,4);
     mainLayout->addWidget(timesButton,3,4);
     mainLayout->addWidget(minusButton,4,4);
     mainLayout->addWidget(plusButton,5,4);

     mainLayout->addWidget(squareRootButton,2,5);
     mainLayout->addWidget(powerButton,3,5);
     mainLayout->addWidget(reciprocalButton,4,5);
     mainLayout->addWidget(equalButton,5,5);
     setLayout(mainLayout);

     setWindowTitle(tr("CROSS PLATFORM CALCI"));
}
calculator::~calculator()
{
    delete ui;
}

void calculator::digitClicked(){
    Button *clickedButton=qobject_cast<Button *>(sender());
    int digitValue=clickedButton->text().toInt();

    if(display->text() == "0" && digitValue == 0.0){
        return;
    }

    if(waitingForOperand){
        display->clear();
        waitingForOperand=false;
    }

    display->setText(display->text() +QString::number(digitValue) );
}

void calculator::unaryOperatorClicked(){
    Button *clickedButton=qobject_cast<Button *>(sender());
    QString clickedOperator=clickedButton->text();

    double operand=display->text().toDouble();
    double result=0.0;

    if(clickedOperator == tr("sqrt")){
        if(operand < 0.0){
            abortOperation();
            return;
        }
        result=std::sqrt(operand);
    }else if(clickedOperator == tr("x\302\262")){
        result=std::pow(operand,2.0);
    }else if(clickedOperator == tr("1/x")){
        if(operand == 0.0){
            abortOperation();
            return;
        }
        result=1.0/operand;
    }

    display->setText(QString::number(result));
    waitingForOperand=true;
}

void calculator::additiveOperator(){
    Button *clickedButton=qobject_cast<Button *>(sender());
    QString clickedOperator=clickedButton->text();
    double operand=display->text().toDouble();

    if(!pendingMultiplicativeOperator.isEmpty()){
        if(!calculate(operand,pendingMultiplicativeOperator)){
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
        operand=factorSoFar;
        factorSoFar=0.0;
        pendingMultiplicativeOperator.clear();
    }

    if(!pendingAdditiveOperator.isEmpty()){
        if(!calculate(operand,pendingAdditiveOperator)){
            abortOperation();
            return;
        }

        display->setText(QString::number(sumSoFar));
    }else{
        sumSoFar=operand;
    }

    pendingAdditiveOperator=clickedOperator;
    waitingForOperand=true;
}

void calculator::multiplicativeOperatorClicked(){
    Button *clickedButton=qobject_cast<Button *>(sender());
    QString clickedOperator=clickedButton->text();
    double operand=display->text().toDouble();

    if(!pendingMultiplicativeOperator.isEmpty()){
        if(!calculate(operand,pendingMultiplicativeOperatorClicked)){
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
    }else{
        factorSoFar=operand;
    }

    pendingMultiplicativeOperator=clickedOperator;
    waitingForOperand=true;
}

void calculator::equalClicked(){
    double operand=display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
            if (!calculate(operand, pendingMultiplicativeOperator)) {
                abortOperation();
                return;
            }
            operand = factorSoFar;
            factorSoFar = 0.0;
            pendingMultiplicativeOperator.clear();
        }
        if (!pendingAdditiveOperator.isEmpty()) {
            if (!calculate(operand, pendingAdditiveOperator)) {
                abortOperation();
                return;
            }
            pendingAdditiveOperator.clear();
        } else {
            sumSoFar = operand;
        }

        display->setText(QString::number(sumSoFar));
        sumSoFar = 0.0;
        waitingForOperand = true;
}

void calculator::pointClicked(){

    if (waitingForOperand)
        display->setText("0");
    if (!display->text().contains('.'))
        display->setText(display->text() + tr("."));
    waitingForOperand = false;
}

void calculator::changeSignClicked(){

    QString text = display->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    display->setText(text);
}

void calculator::backspaceClicked(){

    if (waitingForOperand)
        return;

    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    display->setText(text);
}

void calculator::clear(){

    if (waitingForOperand)
        return;

    display->setText("0");
    waitingForOperand = true;
}

void calculator::clearAll(){

    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}

void calculator::clearMemory(){

    sumInMemory = 0.0;
}


void calculator::readMemory(){

    display->setText(QString::number(sumInMemory));
    waitingForOperand = true;
}


void calculator::setMemory(){

    equalClicked();
    sumInMemory = display->text().toDouble();
}


void calculator::addToMemory(){

    equalClicked();
    sumInMemory += display->text().toDouble();
}


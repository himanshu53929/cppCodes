#include "GenerateBalanceSheet.h"
#include "ui_GenerateBalanceSheet.h"

GenerateBalanceSheet::GenerateBalanceSheet(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GenerateBalanceSheet)
{
    ui->setupUi(this);
}

GenerateBalanceSheet::~GenerateBalanceSheet()
{
    delete ui;
}

void GenerateBalanceSheet::on_pushButton_clicked()
{
    if(parentWidget()){
        parentWidget() -> show();
    }

    this -> close();
}


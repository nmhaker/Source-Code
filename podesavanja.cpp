#include "podesavanja.h"
#include "ui_podesavanja.h"

Podesavanja::Podesavanja(QWidget *parent) : QWidget(parent), ui(new Ui::Podesavanja)
{
    ui->setupUi(this);
    this->setGeometry(400,200, 800,600);
}

Podesavanja::~Podesavanja()
{
    delete ui;
}


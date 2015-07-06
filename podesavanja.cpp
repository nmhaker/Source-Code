#include "podesavanja.h"
#include "ui_podesavanja.h"

Podesavanja::Podesavanja(QWidget *parent) : QWidget(parent), ui(new Ui::Podesavanja)
{
    ui->setupUi(this);
    this->setGeometry(400,200, 800,600);

    connect(this->ui->pb_potvrdi, SIGNAL(clicked(bool)), this, SLOT(saljiPodatke()));
    connect(this->ui->pb_ponisti, SIGNAL(clicked(bool)), this, SLOT(close()));
}

Podesavanja::~Podesavanja()
{
    delete ui;
}

void Podesavanja::saljiPodatke()
{
    this->ime = this->ui->le_ime->text();
    this->prezime = this->ui->le_prezime->text();
    this->staraSifra = this->ui->le_ssifra->text();
    this->novaSifra = this->ui->le_nsifra->text();

    this->profilnaSlika = this->ui->wg_profilnaSlika->profileImage;

    emit(ime, prezime, staraSifra, novaSifra, profilnaSlika);
    this->close();
}


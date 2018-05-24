#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QMessageBox>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->spinBox_coluna_busca_2->setEnabled(false);
    ui->lineEdit_outro_separador->setEnabled(false);

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_arq_saida_clicked()
{
    box = new Box;


    QFileDialog diretorioDialog(this);
    diretorioDialog.setWindowModality(Qt::WindowModal);
    diretorioDialog.setAcceptMode(QFileDialog::AcceptSave);

    if(diretorioDialog.exec() != QDialog::Accepted)
    {
        qDebug() << "false";
    }
    else
    {

        this->box->setDirIn(QDir(ui->lineEdit_dir_in->text()));
        this->box->setFullPathArqOut(diretorioDialog.selectedFiles()[0]);
        tratarSeparador();
        tratarColBusca();
        tratarTipoArqs();

        qDebug() << diretorioDialog.selectedFiles()[0];

        if(this->box->processar())
        {
            QMessageBox::information(this, tr("Processamento"), tr("Processamento concluído!"));
        }
        else
        {
            QMessageBox::critical(this, tr("Erro de Processamento!"),
                                  tr("Muitos dados a serem processados ou \nimpossivel abrir algum arquivo no diretório de origem"));
        }

    }

    delete box;

}

void Dialog::on_pushButton_dir_in_clicked()
{
    QFileDialog diretorioDialog(this);

    QString path = diretorioDialog.getExistingDirectory(this, tr("Diretório de Origem"));

    qDebug() << path;

    if(path != "")
    {
        ui->lineEdit_dir_in->setText(path);
    }
}

void Dialog::on_checkBox_formar_chave_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->spinBox_coluna_busca_2->setEnabled(true);
        ui->spinBox_coluna_busca_2->setValue(ui->spinBox_coluna_busca->value() + 1);
    }
    else
    {
        ui->spinBox_coluna_busca_2->setEnabled(false);
    }

}

void Dialog::on_checkBox_outro_separador_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->comboBox_separador->setEnabled(false);
        ui->lineEdit_outro_separador->setEnabled(true);
    }
    else
    {
        ui->comboBox_separador->setEnabled(true);
        ui->lineEdit_outro_separador->setEnabled(false);
    }
}

void Dialog::tratarSeparador()
{
    if(ui->checkBox_outro_separador->checkState())
    {
        this->box->setSep(ui->lineEdit_outro_separador->text());
    }
    else
    {
        this->box->setSep(ui->comboBox_separador->currentText());
    }
}

void Dialog::tratarTipoArqs()
{
    this->box->setFiltro(QStringList(ui->comboBox_formato_in->currentText()));
}

void Dialog::tratarColBusca()
{
    if(ui->checkBox_formar_chave->checkState())
    {
        this->box->setColBusca(ui->spinBox_coluna_busca->value() - 1);
        this->box->setColBusca2(ui->spinBox_coluna_busca_2->value() - 1);
    }
    else
    {
        this->box->setColBusca(ui->spinBox_coluna_busca->value() - 1);
    }
}

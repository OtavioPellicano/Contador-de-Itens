#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QMessageBox>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_arq_saida_clicked()
{
    box = new Box;

    box->setDirIn(QDir(ui->lineEdit_dir_in->text()));
    box->setDirOut(QDir(ui->lineEdit_dir_out->text()));
    box->setColBusca(ui->spinBox_coluna_busca->value() - 1);
    box->setStrArqSaida(ui->lineEdit_arq_saida->text());

    if(box->processar())
    {
        QMessageBox::information(this, tr("Processamento"), tr("Processamento concluído!"));
    }
    else
    {
        QMessageBox::critical(this, tr("Erro de Processamento!"),
                              tr("Muitos dados a serem processados ou impossivel abrir algum arquivo no diretório de origem"));
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

void Dialog::on_pushButton_dir_out_clicked()
{
    QFileDialog diretorioDialog(this);
    QString path = diretorioDialog.getExistingDirectory(this, tr("Diretório de Destino"));

    qDebug() << path;

    if(path != "")
    {
        ui->lineEdit_dir_out->setText(path);
    }

}

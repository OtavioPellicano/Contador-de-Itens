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

    box->setDirIn(QDir(ui->lineEdit_dir_in->text()));
//    box->setDirOut(QDir(ui->lineEdit_dir_out->text()));
    box->setColBusca(ui->spinBox_coluna_busca->value() - 1);
//    box->setStrArqSaida(ui->lineEdit_arq_saida->text());

    QFileDialog diretorioDialog(this);
    diretorioDialog.setWindowModality(Qt::WindowModal);
    diretorioDialog.setAcceptMode(QFileDialog::AcceptSave);

    if(diretorioDialog.exec() != QDialog::Accepted)
    {
        qDebug() << "false";
    }
    else
    {
        box->setFullPathArqOut(diretorioDialog.selectedFiles()[0]);
        box->setFiltro(QStringList(ui->comboBox_formato_in->currentText()));
        qDebug() << diretorioDialog.selectedFiles()[0];

        if(box->processar())
        {
            QMessageBox::information(this, tr("Processamento"), tr("Processamento concluído!"));
        }
        else
        {
            QMessageBox::critical(this, tr("Erro de Processamento!"),
                                  tr("Muitos dados a serem processados ou impossivel abrir algum arquivo no diretório de origem"));
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

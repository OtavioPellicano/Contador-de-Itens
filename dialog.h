#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "Box.h"
#include <QFileDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_arq_saida_clicked();

    void on_pushButton_dir_in_clicked();

    void on_pushButton_dir_out_clicked();

private:
    Ui::Dialog *ui;
    Box *box;

};

#endif // DIALOG_H

#ifndef DIALOG_LEERE_UNTERURDNER_ENTFERNEN_H
#define DIALOG_LEERE_UNTERURDNER_ENTFERNEN_H

#include <QDialog>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QDirIterator>
#include "text_zeilenweise.h"
#include "bibiothek_oliver.h"

namespace Ui {
class Dialog_leere_unterurdner_entfernen;
}

class Dialog_leere_unterurdner_entfernen : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_leere_unterurdner_entfernen(QWidget *parent = 0);
    ~Dialog_leere_unterurdner_entfernen();

public slots:
    void slot_pfade(QString cnc, QString pios, QString sopti);

private slots:
    void on_pushButton_anderer_pfad_clicked();
    void on_lineEdit_anderer_pfad_editingFinished();
    void on_pushButton_start_clicked();

private:
    Ui::Dialog_leere_unterurdner_entfernen *ui;
    QString anderer_pfad;
    QString leere_unterordner_entfernen(QString pfad);

    QString info;//soll die Info speichern die dann im Mainwindow angezeigt wird

signals:
    void sig_anfrage_pfade();
    void sig_info(QString infotext);

};

#endif // DIALOG_LEERE_UNTERURDNER_ENTFERNEN_H

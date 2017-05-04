#include "dialog_leere_unterurdner_entfernen.h"
#include "ui_dialog_leere_unterurdner_entfernen.h"

Dialog_leere_unterurdner_entfernen::Dialog_leere_unterurdner_entfernen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_leere_unterurdner_entfernen)
{
    ui->setupUi(this);
}

Dialog_leere_unterurdner_entfernen::~Dialog_leere_unterurdner_entfernen()
{
    delete ui;
}

void Dialog_leere_unterurdner_entfernen::on_pushButton_anderer_pfad_clicked()
{
    if(anderer_pfad.isEmpty())
    {
        anderer_pfad = QDir::homePath();
    }
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Verzeichniss"), anderer_pfad);
    if(!tmp.isEmpty())
    {
        anderer_pfad = tmp;
        ui->lineEdit_anderer_pfad->setText(anderer_pfad);
    }
}

void Dialog_leere_unterurdner_entfernen::on_lineEdit_anderer_pfad_editingFinished()
{
    QString eingabe = ui->lineEdit_anderer_pfad->text();
    if(!QDir(eingabe).exists())
    {
        QMessageBox::warning(this,"Fehler","Verzeichniss \"" + eingabe + "\" nicht gefunden!",QMessageBox::Ok);
        ui->lineEdit_anderer_pfad->setText(anderer_pfad);
    }else
    {
        anderer_pfad = eingabe;
    }
}

void Dialog_leere_unterurdner_entfernen::on_pushButton_start_clicked()
{
    emit sig_anfrage_pfade();
}

void Dialog_leere_unterurdner_entfernen::slot_pfade(QString cnc, QString cnc2, QString pios, QString sopti)
{
    info = "";
    if(ui->checkBox_cnc->isChecked())
    {
        if(QDir(cnc).exists())
        {
            info += leere_unterordner_entfernen(cnc);
            info += "\n";
        }else
        {
            info += "Ganner CNC-Wurzelverzeichnis-Pfad ungueltig!";
            info += "\n";
        }

    }
    if(ui->checkBox_cnc2->isChecked())
    {
        if(QDir(cnc2).exists())
        {
            info += leere_unterordner_entfernen(cnc2);
            info += "\n";
        }else
        {
            info += "IMA CNC-Wurzelverzeichnis-Pfad ungueltig!";
            info += "\n";
        }

    }
    if(ui->checkBox_an_pios->isChecked())
    {
        if(QDir(pios).exists())
        {
            info += leere_unterordner_entfernen(pios);
            info += "\n";
        }else
        {
            info += "Auftraege an PIOS-Pfad ungueltig!";
            info += "\n";
        }
    }
    if(ui->checkBox_soptidat->isChecked())
    {
        if(QDir(sopti).exists())
        {
            info += leere_unterordner_entfernen(sopti);
            info += "\n";
        }else
        {
            info += "SOptiDat-Pfad ungueltig!";
            info += "\n";
        }
    }
    if(ui->checkBox_anderer_pfad->isChecked())
    {
        if(QDir(anderer_pfad).exists())
        {
            info += leere_unterordner_entfernen(anderer_pfad);
            info += "\n";
        }else
        {
            info += "\"anderer Pfad\" ungueltig!";
            info += "\n";
        }
    }
    emit sig_info(info);
}

QString Dialog_leere_unterurdner_entfernen::leere_unterordner_entfernen(QString pfad)
{
    if(!QDir(pfad).exists())
    {
        return "Fehler in Funktion \"leere_unterordner_entfernen\" !\nAngegebener Pfad existiert nicht!\n ("+ pfad + ")";
    }
    text_zeilenweise ordner;
    QDirIterator it(QDir(pfad), QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        QString tmp = it.next();
        ordner.zeile_anhaengen(tmp);
    }
    for(uint i=ordner.zeilenanzahl() ; i>0 ; i--)
    {
        QDir dir(ordner.zeile(i));
        if(dir.exists())
        {
            if(  dir.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() == 0  )//Wenn Verzeichnis leer ist
            {
                if(ordner.zeile(i) != pfad)
                {
                    dir.rmpath(ordner.zeile(i));
                }
            }
        }
    }
    QDir(pfad).mkpath(pfad);//Stammverzeichnis wieder erstellen (wird auch gelöscht, wenn es leer ist)
    QString retstr = "Im Verzeichnis \"" + pfad + "\" wurden alle leeren Ordner entfernt.";
    return retstr;
}

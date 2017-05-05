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
    QString info = "";
    if(ui->checkBox_cnc->isChecked())
    {
        if(QDir(cnc).exists())
        {
            info += int_zu_qstring(leere_unterordner_entfernen(cnc));
            info += " leere Ordner im CNC-Verzeichnis Ganner entfernt.";
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
            info += int_zu_qstring(leere_unterordner_entfernen(cnc2));
            info += " leere Ordner im CNC-Verzeichnis IMA entfernt.";
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
            info += int_zu_qstring(leere_unterordner_entfernen(pios));
            info += " leere Ordner im Auftraege an PIOS-Verzeichnis entfernt.";
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
            info += int_zu_qstring(leere_unterordner_entfernen(sopti));
            info += " leere Ordner im SOptiDat-Verzeichnis entfernt.";
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
            info += int_zu_qstring(leere_unterordner_entfernen(anderer_pfad));
            info += " leere Ordner im angegebenen Verzeichnis entfernt.";
            info += "\n";
        }else
        {
            info += "\"anderer Pfad\" ungueltig!";
            info += "\n";
        }
    }
    this->close();
    emit sig_info(info);
}

int Dialog_leere_unterurdner_entfernen::leere_unterordner_entfernen(QString pfad)
{

    int zaele_entfernte_Ordner = 0;
    QDir verzeichnis(pfad);
    if(!verzeichnis.exists())
    {
        return 0;
    }else
    {
        QStringList list = verzeichnis.entryList();
        for(int i = 0 ; i<list.count() ; i++)
        {
            if(  verzeichnis.rmdir(list.at(i))  )
            {
                zaele_entfernte_Ordner++;
            }else
            {
                if(list.at(i)!="."  &&  list.at(i)!="..")
                {
                    zaele_entfernte_Ordner += leere_unterordner_entfernen(pfad + QDir::separator() + list.at(i));
                }
                if(  verzeichnis.rmdir(list.at(i))  )   //erneut prüfen. Wenn Verzeichnis jetzt
                {                                       //leer ist kann es gelöscht werden
                    zaele_entfernte_Ordner++;
                }
            }
        }
    }
    return zaele_entfernte_Ordner;
}

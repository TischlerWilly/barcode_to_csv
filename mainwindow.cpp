#include "mainwindow.h"
#include "ui_mainwindow.h"

#define VERSIONSNUMMER  "2.2018.05.31"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    verzeichnis_quelle  = "";
    verzeichnis_ziel    = "";
    tz = QDir::separator(); //Systemspezifischer Separator (Linux: Ordner/Unterordner/...)
    setup();
    on_actionInfo_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup()
{
    bool inifile_gefunden = false;
    QDir programmordner("./");
    QStringList ordnerinhalt;
    ordnerinhalt = programmordner.entryList(QDir::Files);
    for(QStringList::iterator it = ordnerinhalt.begin() ; it!=ordnerinhalt.end() ; ++it)
    {
        QString name = *it;
        if(name.contains(INIFILE))
        {
            inifile_gefunden = true;
        }
    }
    if(inifile_gefunden == false)
    {
        QFile file(INIFILE);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff!",QMessageBox::Ok);
        }else
        {
            file.write("verzeichnis_quelle:");
            file.write("\n");

            file.write("verzeichnis_ziel:");
            file.write("\n");

            file.write("verzeichnis_root:");
            file.write("\n");

            file.write("verzeichnis_root2:");
            file.write("\n");

            file.write("verzeichnis_auftraege_an_pios:");
            file.write("\n");

            file.write("verzeichnis_soptidat:");
            file.write("\n");

            ui->checkBox_quelldateien_erhalten->setChecked(true);           
            file.write("quelldateien_erhalten:ja");
            file.write("\n");

            ui->checkBox_barcode_erzeugen->setChecked(false);
            file.write("barcode_erzeugen:ja");
            file.write("\n");

            ui->checkBox_unterordner_erstellen_cnc->setChecked(false);
            file.write("unterordner_erstellen_cnc:nein");
            file.write("\n");

            ui->checkBox_unterordner_erstellen_soptidat->setChecked(false);
            file.write("unterordner_erstellen_soptidat:nein");
            file.write("\n");

            ui->checkBox_gesamtliste->setChecked(false);
            file.write("gesamtliste_anlegen:nein");
            file.write("\n");

            ui->radioButton_csv_to_zielverz->setChecked(true);
            file.write("auswahl_zielverz:");
            file.write(AUSGABEPFAD_CSV_ZEILVERZEICHNIS);
            file.write("\n");
        }
        file.close();
    }else
    {
        QFile file(INIFILE);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff!",QMessageBox::Ok);
        }else
        {
            while(!file.atEnd())
            {
                QString zeile = QLatin1String(  file.readLine()  );
                if(zeile.contains("verzeichnis_quelle:"))
                {
                    verzeichnis_quelle = text_mitte(zeile, "verzeichnis_quelle:", "\n");
                    ui->lineEdit_quelle->setText(verzeichnis_quelle);
                }else if(zeile.contains("verzeichnis_ziel:"))
                {
                    verzeichnis_ziel = text_mitte(zeile, "verzeichnis_ziel:", "\n");
                    ui->lineEdit_ziel->setText(verzeichnis_ziel);
                }else if(zeile.contains("verzeichnis_root:"))
                {
                    verzeichnis_root = text_mitte(zeile, "verzeichnis_root:", "\n");
                    ui->lineEdit_root->setText(verzeichnis_root);
                }else if(zeile.contains("verzeichnis_root2:"))
                {
                    verzeichnis_root2 = text_mitte(zeile, "verzeichnis_root2:", "\n");
                    ui->lineEdit_root2->setText(verzeichnis_root2);
                }else if(zeile.contains("verzeichnis_auftraege_an_pios:"))
                {
                    verzeichnis_auftraege_an_pios = text_mitte(zeile, "verzeichnis_auftraege_an_pios:", "\n") ;
                    ui->lineEdit_auftraege_an_pios->setText(verzeichnis_auftraege_an_pios);
                }else if(zeile.contains("verzeichnis_soptidat:"))
                {
                    verzeichnis_soptidat = text_mitte(zeile, "verzeichnis_soptidat:", "\n");
                    ui->lineEdit_soptidat->setText(verzeichnis_soptidat);
                }else if(zeile.contains("quelldateien_erhalten:"))
                {
                    quelldateien_erhalten = text_mitte(zeile, "quelldateien_erhalten:", "\n");
                    if(quelldateien_erhalten == "ja")
                    {
                        ui->checkBox_quelldateien_erhalten->setChecked(true);
                    }else
                    {
                        ui->checkBox_quelldateien_erhalten->setChecked(false);
                    }
                }else if(zeile.contains("barcode_erzeugen:"))
                {
                    barcode_erzeugen = text_mitte(zeile, "barcode_erzeugen:", "\n");
                    if(barcode_erzeugen == "ja")
                    {
                        ui->checkBox_barcode_erzeugen->setChecked(true);
                    }else
                    {
                        ui->checkBox_barcode_erzeugen->setChecked(false);
                    }
                }else if(zeile.contains("unterordner_erstellen_cnc:"))
                {
                    unterordner_erstellen_cnc = text_mitte(zeile, "unterordner_erstellen_cnc:", "\n");
                    if(unterordner_erstellen_cnc == "ja")
                    {
                        ui->checkBox_unterordner_erstellen_cnc->setChecked(true);
                    }else
                    {
                        ui->checkBox_unterordner_erstellen_cnc->setChecked(false);
                    }
                }else if(zeile.contains("unterordner_erstellen_cnc2:"))
                {
                    unterordner_erstellen_cnc2 = text_mitte(zeile, "unterordner_erstellen_cnc2:", "\n");
                    if(unterordner_erstellen_cnc2 == "ja")
                    {
                        ui->checkBox_unterordner_erstellen_cnc2->setChecked(true);
                    }else
                    {
                        ui->checkBox_unterordner_erstellen_cnc2->setChecked(false);
                    }
                }else if(zeile.contains("unterordner_erstellen_soptidat:"))
                {
                    unterordner_erstellen_soptidat = text_mitte(zeile, "unterordner_erstellen_soptidat:", "\n");
                    if(unterordner_erstellen_soptidat == "ja")
                    {
                        ui->checkBox_unterordner_erstellen_soptidat->setChecked(true);
                    }else
                    {
                        ui->checkBox_unterordner_erstellen_soptidat->setChecked(false);
                    }
                }else if(zeile.contains("gesamtliste_anlegen:"))
                {
                    gesamtliste_anlegen = text_mitte(zeile, "gesamtliste_anlegen:", "\n");
                    if(gesamtliste_anlegen == "ja")
                    {
                        ui->checkBox_gesamtliste->setChecked(true);
                    }else
                    {
                        ui->checkBox_gesamtliste->setChecked(false);
                    }
                }else if(zeile.contains("auswahl_zielverz:"))
                {
                    auswahl_zielverz = text_mitte(zeile, "auswahl_zielverz:", "\n");
                    if(auswahl_zielverz == AUSGABEPFAD_CSV_ZEILVERZEICHNIS)
                    {
                        ui->radioButton_csv_to_zielverz->setChecked(true);
                    }else
                    {
                        ui->radioButton_csv_to_an_pios->setChecked(true);
                    }
                }
            }
        }
        file.close();

    }

    connect(&dia_leer_Ordn_entf, SIGNAL(sig_anfrage_pfade()), this, SLOT(slot_anfrage_pfade()) );
    connect(&dia_leer_Ordn_entf, SIGNAL(sig_info(QString)), this, SLOT(slot_info(QString)) );
}

void MainWindow::schreibe_ini()
{
    QFile file(INIFILE);
    file.remove();
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff!",QMessageBox::Ok);
    }else
    {
        file.write("verzeichnis_quelle:");
        file.write(verzeichnis_quelle.toUtf8());
        file.write("\n");

        file.write("verzeichnis_ziel:");
        file.write(verzeichnis_ziel.toUtf8());
        file.write("\n");

        file.write("verzeichnis_root:");
        file.write(verzeichnis_root.toUtf8());
        file.write("\n");

        file.write("verzeichnis_root2:");
        file.write(verzeichnis_root2.toUtf8());
        file.write("\n");

        file.write("verzeichnis_auftraege_an_pios:");
        file.write(verzeichnis_auftraege_an_pios.toUtf8());
        file.write("\n");

        file.write("verzeichnis_soptidat:");
        file.write(verzeichnis_soptidat.toUtf8());
        file.write("\n");

        file.write("auswahl_zielverz:");
        file.write(auswahl_zielverz.toUtf8());
        file.write("\n");

        file.write("quelldateien_erhalten:");
        file.write(quelldateien_erhalten.toUtf8());
        file.write("\n");

        file.write("barcode_erzeugen:");
        file.write(barcode_erzeugen.toUtf8());
        file.write("\n");

        file.write("unterordner_erstellen_cnc:");
        file.write(unterordner_erstellen_cnc.toUtf8());
        file.write("\n");

        file.write("unterordner_erstellen_cnc2:");
        file.write(unterordner_erstellen_cnc2.toUtf8());
        file.write("\n");

        file.write("unterordner_erstellen_soptidat:");
        file.write(unterordner_erstellen_soptidat.toUtf8());
        file.write("\n");

        file.write("gesamtliste_anlegen:");
        file.write(gesamtliste_anlegen.toUtf8());
        file.write("\n");

    }
    file.close();
}

void MainWindow::on_actionInfo_triggered()
{
    QString tmp;
    tmp = "Barcode to CSV / Version:  ";
    tmp += VERSIONSNUMMER;
    tmp +=" / Lizenz:  GPL\n";
    tmp += "\n";
    tmp +="WICHTIG: Barcode unterstuetzt die deutschen Umlaute nicht!\n";
    tmp += "\n";
    tmp +="Aufbau des Barcodes:\n";
    //tmp +="1. Projektgruppe\n";
    //tmp +="   z.B: UKB\n";
    tmp +="2. Projekt\n";
    tmp +="   z.B: UKB22\n";
    tmp +="3. Position(immer 4-stellig)\n";
    tmp +="   z.B: 1001 oder 0001 oder 0102,5\n";
    tmp +="4. ggf Schranknummer oder Baugruppe\n";
    tmp +="   z.B: #PAX oder S1\n";
    tmp +="5. Teilbezeichnung\n";
    tmp +="   z.B: Seite_li\n";
    tmp +="\n";
    tmp +="Verwendung von Schranknummern: S + Ziffer + ... + _";
    tmp +="\n";
    tmp +="Beispiel: S1_Seite_li  -->  UKB/UKB12/pos0001/S1/Seite_li";
    tmp +="\n";
    tmp +="Verwendung von Baugruppennummern: # + ... + _";
    tmp +="\n";
    tmp +="Beispiel: #PAX_Seite_li  -->  UKB/UKB12/pos0001/#PAX/Seite_li";

    ui->plainTextEdit_Meldungsfenster->setPlainText(tmp);
}



//-----------------------------------------------------------------------Pfade:
void MainWindow::on_lineEdit_quelle_editingFinished()
{
    QString eingabe = ui->lineEdit_quelle->text();
    if(!QDir(eingabe).exists())
    {
        QMessageBox::warning(this,"Fehler","Verzeichniss \"" + eingabe + "\" nicht gefunden!",QMessageBox::Ok);
        ui->lineEdit_quelle->setText(verzeichnis_quelle);
    }else
    {
        verzeichnis_quelle = eingabe;
    }
}

void MainWindow::on_lineEdit_ziel_editingFinished()
{
    QString eingabe = ui->lineEdit_ziel->text();
    if(!QDir(eingabe).exists())
    {
        QMessageBox::warning(this,"Fehler","Verzeichniss \"" + eingabe + "\" nicht gefunden!",QMessageBox::Ok);
        ui->lineEdit_ziel->setText(verzeichnis_ziel);
    }else
    {
        verzeichnis_ziel = eingabe;
    }
}

void MainWindow::on_lineEdit_root_editingFinished()
{
    QString eingabe = ui->lineEdit_root->text();
    if(!QDir(eingabe).exists())
    {
        QMessageBox::warning(this,"Fehler","Verzeichniss \"" + eingabe + "\" nicht gefunden!",QMessageBox::Ok);
        ui->lineEdit_root->setText(verzeichnis_root);
    }else
    {
        verzeichnis_root = eingabe;
    }
}

void MainWindow::on_lineEdit_root2_editingFinished()
{
    QString eingabe = ui->lineEdit_root2->text();
    if(!QDir(eingabe).exists())
    {
        QMessageBox::warning(this,"Fehler","Verzeichniss \"" + eingabe + "\" nicht gefunden!",QMessageBox::Ok);
        ui->lineEdit_root2->setText(verzeichnis_root2);
    }else
    {
        verzeichnis_root2 = eingabe;
    }
}

void MainWindow::on_lineEdit_auftraege_an_pios_editingFinished()
{
    QString eingabe = ui->lineEdit_auftraege_an_pios->text();
    if(!QDir(eingabe).exists())
    {
        QMessageBox::warning(this,"Fehler","Verzeichniss \"" + eingabe + "\" nicht gefunden!",QMessageBox::Ok);
        ui->lineEdit_auftraege_an_pios->setText(verzeichnis_auftraege_an_pios);
    }else
    {
        verzeichnis_auftraege_an_pios = eingabe;
    }
}

void MainWindow::on_lineEdit_soptidat_editingFinished()
{
    QString eingabe = ui->lineEdit_soptidat->text();
    if(!QDir(eingabe).exists())
    {
        QMessageBox::warning(this,"Fehler","Verzeichniss \"" + eingabe + "\" nicht gefunden!",QMessageBox::Ok);
        ui->lineEdit_soptidat->setText(verzeichnis_soptidat);
    }else
    {
        verzeichnis_soptidat = eingabe;
    }
}

//-----------------------------------------------------------------------Pfad-Buttons:
void MainWindow::on_pushButton_quelle_clicked()
{
    if(verzeichnis_quelle.isEmpty())
    {
        verzeichnis_quelle = "./";
    }
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Quellverzeichniss"), verzeichnis_quelle);
    if(!tmp.isEmpty())
    {
        verzeichnis_quelle = tmp;
        ui->lineEdit_quelle->setText(verzeichnis_quelle);
        schreibe_ini();
    }
}

void MainWindow::on_pushButton_ziel_clicked()
{
    if(verzeichnis_ziel.isEmpty())
    {
        verzeichnis_ziel = "./";
    }
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Zielverzeichniss"), verzeichnis_ziel);
    if(!tmp.isEmpty())
    {
        verzeichnis_ziel = tmp;
        ui->lineEdit_ziel->setText(verzeichnis_ziel);
        schreibe_ini();
    }
}

void MainWindow::on_pushButton_root_clicked()
{
    if(verzeichnis_root.isEmpty())
    {
        verzeichnis_root = "./";
    }
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Quellverzeichniss"), verzeichnis_root);
    if(!tmp.isEmpty())
    {
        verzeichnis_root = tmp;
        ui->lineEdit_root->setText(verzeichnis_root);
        schreibe_ini();
    }
}

void MainWindow::on_pushButton_root2_clicked()
{
    if(verzeichnis_root2.isEmpty())
    {
        verzeichnis_root2 = "./";
    }
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Quellverzeichniss"), verzeichnis_root2);
    if(!tmp.isEmpty())
    {
        verzeichnis_root2 = tmp;
        ui->lineEdit_root2->setText(verzeichnis_root2);
        schreibe_ini();
    }
}

void MainWindow::on_pushButton_auftraege_an_pios_clicked()
{
    if(verzeichnis_auftraege_an_pios.isEmpty())
    {
        verzeichnis_auftraege_an_pios = "./";
    }
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Quellverzeichniss"), verzeichnis_auftraege_an_pios);
    if(!tmp.isEmpty())
    {
        verzeichnis_auftraege_an_pios = tmp;
        ui->lineEdit_auftraege_an_pios->setText(verzeichnis_auftraege_an_pios);
        schreibe_ini();
    }
}

void MainWindow::on_pushButton_soptidat_clicked()
{
    if(verzeichnis_soptidat.isEmpty())
    {
        verzeichnis_soptidat = "./";
    }
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Quellverzeichniss"), verzeichnis_soptidat);
    if(!tmp.isEmpty())
    {
        verzeichnis_soptidat = tmp;
        ui->lineEdit_soptidat->setText(verzeichnis_soptidat);
        schreibe_ini();
    }
}

//-----------------------------------------------------------------------Buttons:
void MainWindow::on_pushButton_Dateien_auflisten_clicked()
{
    if(verzeichnis_quelle.isEmpty())
    {
        QMessageBox::warning(this,"Abbruch","Quellverzeichniss nicht angegeben!",QMessageBox::Ok);
        return;
    }
    QDir quelle(verzeichnis_quelle);
    QStringList dateiliste;
    dateiliste = quelle.entryList(QDir::Files);
    ui->plainTextEdit_Meldungsfenster->clear();
    for(QStringList::iterator it = dateiliste.begin() ; it!=dateiliste.end() ; ++it)
    {
        QString name = *it;
        QString alter_text = ui->plainTextEdit_Meldungsfenster->toPlainText();
        if(  !alter_text.isEmpty()  )
        {
            ui->plainTextEdit_Meldungsfenster->setPlainText(alter_text + "\n" + name);
        }else
        {
            ui->plainTextEdit_Meldungsfenster->setPlainText(name);
        }
    }
}

void MainWindow::on_pushButton_Barcode_erzeugen_clicked() //Button heißt jetzt Start
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    elementnumern.clear();
    fehler_elementnumern_doppelt = false;
    fehler_multiplexplatten_kante_ohne_kd = false;
    if(verzeichnis_quelle.isEmpty())
    {
        QMessageBox::warning(this,"Abbruch","Quellverzeichniss nicht angegeben!",QMessageBox::Ok);
        return;
    }
    if(verzeichnis_ziel.isEmpty())
    {
        QMessageBox::warning(this,"Abbruch","Zielverzeichniss nicht angegeben!",QMessageBox::Ok);
        return;
    }
    QDir quelle(verzeichnis_quelle);
    QStringList dateiliste;
    dateiliste = quelle.entryList(QDir::Files);
    ui->plainTextEdit_Meldungsfenster->clear();
    QString gesamtliste;
    int i=0;
    for(QStringList::iterator it = dateiliste.begin() ; it!=dateiliste.end() ; ++it)
    {
        QString name = *it;
        //Quelldatei öffnen und einlesen:
        QString alter_inhalt = "";
        QFile oldfile(verzeichnis_quelle + tz + name);
        if(!oldfile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff!",QMessageBox::Ok);
        }else
        {
            alter_inhalt = QString::fromLatin1(oldfile.readAll());
        }
        if(quelldateien_erhalten == "nein")
        {
            oldfile.remove();
        }
        oldfile.close();

       //Inhalt um Barcode ergänzen:
        QString neuer_inhalt = barcode_to_csv(alter_inhalt);

        if(gesamtliste_anlegen=="ja")
        {
            if(i==0)
            {
                gesamtliste = neuer_inhalt;
                i++;
            }else
            {
                text_zeilenweise tz;
                tz.set_text(neuer_inhalt);
                for(uint ii = 3 ; ii<=tz.zeilenanzahl() ; ii++)
                {
                    gesamtliste += "\n";
                    gesamtliste += tz.zeile(ii);
                }
            }
            QFile newfile(verzeichnis_ziel + QDir::separator() + "gesamtliste.csv");
            if(!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff!",QMessageBox::Ok);
            }else
            {
                //newfile.write(gesamtliste.toUtf8());
                newfile.write(gesamtliste.toLatin1());
            }
            newfile.close();
        }

        //Zieldatei speichern:
        if(barcode_erzeugen == "ja")
        {
            QString neuer_name = text_links(name, ".csv") + "_bc" + ".csv" ;
            QString alter_text = ui->plainTextEdit_Meldungsfenster->toPlainText();
            if(  alter_text.isEmpty()  )
            {
                ui->plainTextEdit_Meldungsfenster->setPlainText(name + "   -->   " + neuer_name);
            }else
            {
                ui->plainTextEdit_Meldungsfenster->setPlainText(alter_text + "\n" + name + "   -->   " + neuer_name);
            }
            QString zielverz = "";
            if(auswahl_zielverz == AUSGABEPFAD_CSV_ZEILVERZEICHNIS)
            {
                zielverz = verzeichnis_ziel + tz + neuer_name;
            }else
            {
                zielverz = pfad_an_pios + tz + neuer_name;
            }
            QFile newfile(zielverz);
            if(!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff!",QMessageBox::Ok);
            }else
            {
                //newfile.write(neuer_inhalt.toUtf8());
                newfile.write(neuer_inhalt.toLatin1());
            }
            newfile.close();
        }else
        {
            QString alter_text = ui->plainTextEdit_Meldungsfenster->toPlainText();
            if(  alter_text.isEmpty()  )
            {
                ui->plainTextEdit_Meldungsfenster->setPlainText(name);
            }else
            {
                ui->plainTextEdit_Meldungsfenster->setPlainText(alter_text + "\n" + name);
            }
        }
    }
    if(gesamtliste_anlegen == "ja")
    {
        QString alter_text = ui->plainTextEdit_Meldungsfenster->toPlainText();
        if(  alter_text.isEmpty()  )
        {
            ui->plainTextEdit_Meldungsfenster->setPlainText("Gesamtliste wurde im Zielverzeichnis gespeichert.");
        }else
        {
            ui->plainTextEdit_Meldungsfenster->setPlainText(alter_text + "\n" + "Gesamtliste wurde im Zielverzeichnis gespeichert.");
        }
    }
    if(fehler_elementnumern_doppelt == true)
    {
        QMessageBox mb;
        mb.setText("Achtung!\nElementnummern wurden mehrfach vergeben!\nMehrere Teile haben die selbe Elementnummer!");
        mb.exec();
    }
    if(fehler_multiplexplatten_kante_ohne_kd == true)
    {
        QMessageBox mb;
        mb.setText("Achtung!\nKantendicke an Multiplexteilen kontrollieren!\nEs sollte K10X oder K20X verwendet werden!");
        mb.exec();
    }
    QApplication::restoreOverrideCursor();
}

QString MainWindow::barcode_to_csv(QString alter_inhalt)
{
    text_zeilenweise a; //alter text
    a.set_text(alter_inhalt);
    text_zeilenweise n; //neuer text
    for(uint i = 1; i<a.zeilenanzahl() ; i++)
    {
        if(i==1)
        {
            n.set_text(a.zeile(i));
        }else if(i==2)
        {
            n.zeilen_anhaengen(a.zeile(i));
        }else
        {
            text_zeilenweise eintraege;
            eintraege.set_trennzeichen(';');
            eintraege.set_text(a.zeile(i));

            QString barcode="";                                       //Spalte19
            //Aufbau des Barcodes:
            //entfällt      Projektgruppe   (UKB)       Teil von "Auftrag"      Spalte 29(Teil)
            //      Projekt         (UKB12)     "Auftrag"               Spalte 29
            //      Position        (0001)      "Aufpos"                Spalte 4(immer 4-stellig)
            //      Baugruppe       (S1)        Teil von "Teilbez"      Spalte 5(Teil)/nicht bei jedem Teil
            //      Teilbezeichnung (Seite_li)  "Teilbez"               Spalte 5(immer ohne Baugruppe)
            QString tmp = eintraege.zeile(29);
            //Projektgruppe:
            /*
            for(int j = 0 ; j<tmp.length() ; j++)
            {
                if(tmp.at(j)!='0' && tmp.at(j)!='1' && tmp.at(j)!='2' && tmp.at(j)!='3' && tmp.at(j)!='4' && tmp.at(j)!='5' && tmp.at(j)!='6' && tmp.at(j)!='7' && tmp.at(j)!='8' && tmp.at(j)!='9')
                {
                    barcode += tmp.at(j);
                }else
                {
                    break;
                }
            }
            barcode += QDir::separator();
            */
            //Projekt:
            barcode += tmp;
            barcode += QDir::separator();
            //Position:
            //barcode += "pos";
            tmp = eintraege.zeile(4);
            if(tmp.contains(","))
            {
                QString li = text_links(tmp, ",");
                QString re = text_rechts(tmp, ",");
                if(li.length()==4)
                {
                    barcode += tmp;
                }else if(li.length()==3)
                {
                    barcode += "0";
                    barcode += li;
                    barcode += ",";
                    barcode += re;
                }else if(li.length()==2)
                {
                    barcode += "00";
                    barcode += li;
                    barcode += ",";
                    barcode += re;
                }else if(li.length()==1)
                {
                    barcode += "000";
                    barcode += li;
                    barcode += ",";
                    barcode += re;
                }
                barcode += QDir::separator();
            }else
            {
                if(tmp.length()==4)
                {
                    barcode += tmp;
                }else if(tmp.length()==3)
                {
                    barcode += "0";
                    barcode += tmp;
                }else if(tmp.length()==2)
                {
                    barcode += "00";
                    barcode += tmp;
                }else if(tmp.length()==1)
                {
                    barcode += "000";
                    barcode += tmp;
                }
                barcode += QDir::separator();
            }
            //Baugruppe + Teilbezeichnung:
            tmp = eintraege.zeile(5);
            if(tmp.contains("_"))
            {
                if(tmp.at(0)=='S')//Schranknummer
                {
                    if(tmp.at(1)=='0' || tmp.at(1)=='1' || tmp.at(1)=='2' || tmp.at(1)=='3' || tmp.at(1)=='4' || tmp.at(1)=='5' || tmp.at(1)=='6' || tmp.at(1)=='7' || tmp.at(1)=='8' || tmp.at(1)=='9')
                    {
                        barcode += text_links(tmp, "_");
                        barcode += QDir::separator();
                        barcode += text_rechts(tmp, "_");
                    }else
                    {
                        barcode += tmp;
                    }
                }else if(tmp.at(0)=='#')//Baugruppenbezeichung
                {
                    barcode += text_links(tmp, "_");
                    barcode += QDir::separator();
                    barcode += text_rechts(tmp, "_");
                }else
                {
                    barcode += tmp;
                }
            }else
            {
                barcode += tmp;
            }

            //QMessageBox mb;
            //mb.setText("zeile:\n"+eintraege.get_text()+"\nBez:\n"+tmp);

            //jetzt barcode ergänzen:
            eintraege.zeile_ersaetzen(19,barcode);
            //jetzt neue Zeile an n anhängen:
            n.zeile_anhaengen(eintraege.get_text());

            //Ordner für CNC anlegen:
            if(unterordner_erstellen_cnc == "ja")
            {
                if(!verzeichnis_root.isEmpty())
                {
                    char tz;
                    if(QDir::separator() == '/')
                    {
                        tz = '/';   //LINUX
                    }else
                    {
                        tz = '\\';  //Windows
                    }
                    text_zeilenweise p;
                    p.set_trennzeichen(tz);
                    p.set_text(barcode);
                    QString pfad;
                    for(uint x = 1; x<p.zeilenanzahl() ;x++)
                    {
                        pfad += p.zeile(x);
                        if(x<p.zeilenanzahl()-1)
                        {
                            pfad += QDir::separator();
                        }
                    }

                    QDir cncdir;
                    cncdir.mkpath(verzeichnis_root + QDir::separator() + pfad);
                }
            }

            //Ordner für CNC 2 anlegen:
            if(unterordner_erstellen_cnc2 == "ja")
            {
                if(!verzeichnis_root2.isEmpty())
                {
                    char tz;
                    if(QDir::separator() == '/')
                    {
                        tz = '/';   //LINUX
                    }else
                    {
                        tz = '\\';  //Windows
                    }
                    text_zeilenweise p;
                    p.set_trennzeichen(tz);
                    p.set_text(barcode);
                    QString pfad;
                    for(uint x = 1; x<p.zeilenanzahl() ;x++)
                    {
                        pfad += p.zeile(x);
                        if(x<p.zeilenanzahl()-1)
                        {
                            pfad += QDir::separator();
                        }
                    }

                    QDir cncdir;
                    cncdir.mkpath(verzeichnis_root2 + QDir::separator() + pfad);
                }
            }

            //Ordner in SOptiDat anlegen:
            if(unterordner_erstellen_soptidat == "ja")
            {
                QString pfad_soptidat = "";
                tmp = eintraege.zeile(29);
                //Projektgruppe:
                for(int j = 0 ; j<tmp.length() ; j++)
                {
                    if(tmp.at(j)!='0' && tmp.at(j)!='1' && tmp.at(j)!='2' && tmp.at(j)!='3' && tmp.at(j)!='4' && tmp.at(j)!='5' && tmp.at(j)!='6' && tmp.at(j)!='7' && tmp.at(j)!='8' && tmp.at(j)!='9')
                    {
                        pfad_soptidat += tmp.at(j);
                    }else
                    {
                        break;
                    }
                }
                pfad_soptidat += QDir::separator();
                //Projekt:
                pfad_soptidat += eintraege.zeile(29);
                //Ordner anlegen:
                QDir dir;
                dir.mkpath(verzeichnis_soptidat + QDir::separator() + pfad_soptidat);
            }

            //Ordner in Austräge an PIOS anlegen:
            if(  (auswahl_zielverz == AUSGABEPFAD_CSV_AUFTRAEGE_AN_POIS)  &&  (barcode_erzeugen=="ja")  )
            {
                QString pfad = "";

                tmp = eintraege.zeile(29);
                //Projektgruppe:
                for(int j = 0 ; j<tmp.length() ; j++)
                {
                    if(tmp.at(j)!='0' && tmp.at(j)!='1' && tmp.at(j)!='2' && tmp.at(j)!='3' && tmp.at(j)!='4' && tmp.at(j)!='5' && tmp.at(j)!='6' && tmp.at(j)!='7' && tmp.at(j)!='8' && tmp.at(j)!='9')
                    {
                        pfad += tmp.at(j);
                    }else
                    {
                        break;
                    }
                }
                pfad += QDir::separator();

                //Projekt:
                pfad += eintraege.zeile(29);
                //Ordner anlegen:
                pfad_an_pios = verzeichnis_auftraege_an_pios + QDir::separator() + pfad;
                QDir dir;
                dir.mkpath(pfad_an_pios);
            }
        }
    }

    //--------------------------------------Fehlersuche Elementnummern:
    for(uint i = 3; i<a.zeilenanzahl() ; i++)
    {
        text_zeilenweise eintraege;
        eintraege.set_trennzeichen(';');
        eintraege.set_text(a.zeile(i));
        QString neue_nummer = eintraege.zeile(3);

        for(uint ii=1; ii<=elementnumern.zeilenanzahl() ;ii++)
        {
            if(elementnumern.zeile(ii) == neue_nummer)
            {
                fehler_elementnumern_doppelt = true;
            }
        }

        elementnumern.zeile_anhaengen(neue_nummer);
    }
    //--------------------------------------Fehlersuche Kantendicke bei Multiplexplatten:
    for(uint i = 3; i<a.zeilenanzahl() ; i++)
    {
        text_zeilenweise eintraege;
        eintraege.set_trennzeichen(';');
        eintraege.set_text(a.zeile(i));
        QString material = eintraege.zeile(2);
        QString kante_li = eintraege.zeile(10);
        QString kante_re = eintraege.zeile(11);
        QString kante_ob = eintraege.zeile(12);
        QString kante_un = eintraege.zeile(13);
        QString kadi_li = eintraege.zeile(15);
        QString kadi_re = eintraege.zeile(16);
        QString kadi_ob = eintraege.zeile(17);
        QString kadi_un = eintraege.zeile(18);

        QString traegerplatte = material.at(3);
        traegerplatte += material.at(4);

        if(traegerplatte == "mx")//Multiplex
        {
            if(!kante_li.isEmpty()  && kadi_li == "0" && ist_ziffer(kante_li.at(0)))
            {
                fehler_multiplexplatten_kante_ohne_kd = true;
            }
            if(!kante_re.isEmpty()  && kadi_re == "0" && ist_ziffer(kante_re.at(0)))
            {
                fehler_multiplexplatten_kante_ohne_kd = true;
            }
            if(!kante_ob.isEmpty()  && kadi_ob == "0" && ist_ziffer(kante_ob.at(0)))
            {
                fehler_multiplexplatten_kante_ohne_kd = true;
            }
            if(!kante_un.isEmpty()  && kadi_un == "0" && ist_ziffer(kante_un.at(0)))
            {
                fehler_multiplexplatten_kante_ohne_kd = true;
            }
        }
    }
    //--------------------------------------
    return n.get_text();
}

//-----------------------------------------------------------------------Checkboxen:
void MainWindow::on_checkBox_quelldateien_erhalten_stateChanged()
{
    if(ui->checkBox_quelldateien_erhalten->isChecked() == true)
    {
        quelldateien_erhalten = "ja";
    }else
    {
        quelldateien_erhalten = "nein";
    }
    schreibe_ini();
}

void MainWindow::on_checkBox_unterordner_erstellen_cnc_stateChanged()
{
    if(ui->checkBox_unterordner_erstellen_cnc->isChecked() == true)
    {
        unterordner_erstellen_cnc = "ja";
    }else
    {
        unterordner_erstellen_cnc = "nein";
    }
    schreibe_ini();
}

void MainWindow::on_checkBox_unterordner_erstellen_cnc2_stateChanged()
{
    if(ui->checkBox_unterordner_erstellen_cnc2->isChecked() == true)
    {
        unterordner_erstellen_cnc2 = "ja";
    }else
    {
        unterordner_erstellen_cnc2 = "nein";
    }
    schreibe_ini();
}

void MainWindow::on_checkBox_barcode_erzeugen_stateChanged()
{
    if(ui->checkBox_barcode_erzeugen->isChecked() == true)
    {
        barcode_erzeugen = "ja";
    }else
    {
        barcode_erzeugen = "nein";
    }
    schreibe_ini();
}

void MainWindow::on_checkBox_unterordner_erstellen_soptidat_stateChanged()
{
    if(ui->checkBox_unterordner_erstellen_soptidat->isChecked() == true)
    {
        unterordner_erstellen_soptidat = "ja";
    }else
    {
        unterordner_erstellen_soptidat = "nein";
    }
    schreibe_ini();
}

void MainWindow::on_checkBox_gesamtliste_stateChanged()
{
    if(ui->checkBox_gesamtliste->isChecked() == true)
    {
        gesamtliste_anlegen = "ja";
    }else
    {
        gesamtliste_anlegen = "nein";
    }
    schreibe_ini();
}
//-----------------------------------------------------------------------Radio-Buttons:
void MainWindow::on_radioButton_csv_to_zielverz_toggled(bool checked)
{
    if(checked == true)
    {
        auswahl_zielverz = AUSGABEPFAD_CSV_ZEILVERZEICHNIS;
        schreibe_ini();
        ui->lineEdit_ziel->setEnabled(true);
        ui->lineEdit_auftraege_an_pios->setEnabled(false);
    }
}

void MainWindow::on_radioButton_csv_to_an_pios_toggled(bool checked)
{
    if(checked == true)
    {
        auswahl_zielverz = AUSGABEPFAD_CSV_AUFTRAEGE_AN_POIS;
        schreibe_ini();
        ui->lineEdit_ziel->setEnabled(false);
        ui->lineEdit_auftraege_an_pios->setEnabled(true);
    }
}

//-----------------------------------------------------------------------
QString MainWindow::selektiereEintrag(QString text, QString beginntMit, QString endetMit)
{
    QString returnText;
    int indexBegin;
    int indexEnde;
    int countetLetters;
    int lengthOf_beginntMit = beginntMit.length();

    if(!text.contains(beginntMit))
    {
        return "Fehler in Funktion \"selektiereEintrag\" bei Parameter \"beginntMit\"!";
    } else
    {
        indexBegin = text.indexOf(beginntMit);
        indexBegin += lengthOf_beginntMit-1;
    }

    if(!text.contains(endetMit))
    {
        return "Fehler in Funktion \"selektiereEintrag\" bei Parameter \"endetMit\"!";
    } else
    {
        indexEnde = text.indexOf(endetMit,indexBegin);
    }

    countetLetters = indexEnde - indexBegin -1;
    returnText = text.mid(indexBegin+1 , countetLetters);

    return returnText;
}

QString MainWindow::text_links(const QString text, const QString trenntext)
{
    if(!text.contains(trenntext))
    {
        return "";
    }
    int beginn_Trenntext = text.indexOf(trenntext);
    QString return_string = "";
    for(int i=0 ; i<beginn_Trenntext; i++)
    {
        return_string += text.at(i);
    }
    return return_string;
}

QString MainWindow::text_rechts(const QString text, const QString trenntext)
{
    if(!text.contains(trenntext))
    {
        return "";
    }
    int ende_Trenntext = text.indexOf(trenntext)+trenntext.length();
    QString return_string = "";
    for(int i=ende_Trenntext ; i<text.count(); i++)
    {
        return_string += text.at(i);
    }
    return return_string;
}

QString MainWindow::text_mitte(const QString text, const QString textDavor, const QString textDanach)
{
    QString tmp = text_rechts(text, textDavor);
    tmp = text_links( tmp, textDanach);
    return tmp;
}

//-----------------------------------------------------------------------public solts:
void MainWindow::slot_anfrage_pfade()
{
    disconnect(this, SIGNAL(signal_pfade(QString, QString,QString,QString)), &dia_leer_Ordn_entf, SLOT(slot_pfade(QString,QString,QString,QString)));
    connect(this, SIGNAL(signal_pfade(QString, QString,QString,QString)), &dia_leer_Ordn_entf, SLOT(slot_pfade(QString,QString,QString,QString)));
    emit signal_pfade(verzeichnis_root, verzeichnis_root2, verzeichnis_auftraege_an_pios, verzeichnis_soptidat);
}

void MainWindow::slot_info(QString infotext)
{
    if(!infotext.isEmpty())
    {
        ui->plainTextEdit_Meldungsfenster->setPlainText(infotext);
    }

}

//-----------------------------------------------------------------------Extras:
void MainWindow::on_actionLeere_Unterordner_entfernen_triggered()
{
    dia_leer_Ordn_entf.show();

}

void MainWindow::on_actionBIlddateilen_IMAWOP_entfernen_triggered()
{
    if(QDir(verzeichnis_root2).exists())//IMA-Verzeichnis
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QString info = int_zu_qstring(dateien_entfernen(verzeichnis_root2, ".EMF"));
        ui->plainTextEdit_Meldungsfenster->setPlainText(info + " Bilddateien wurden im IMA-Verzeichnis entfernt.");
        QApplication::restoreOverrideCursor();
    }else
    {
        ui->plainTextEdit_Meldungsfenster->setPlainText("IMA CNC-Wurzelverzeichnis-Pfad ungueltig!");
    }
}

int MainWindow::dateien_entfernen(QString pfad, QString dateiendung)
{
    int zaele_dateien = 0;
    QDir verzeichnis(pfad);
    if(!verzeichnis.exists())
    {
        return 0;
    }else
    {
        QStringList list = verzeichnis.entryList();
        for(int i = 0 ; i<list.count() ; i++)
        {
            QString name = list.at(i);
            if(  name.contains(dateiendung)  &&  (name == text_links(name, dateiendung)+dateiendung)  )
            {                                   //Wenn die Dateiendung auch wirklich am Ende steht
                QFile datei(pfad + QDir::separator() + name);
                if(datei.remove())
                {
                    zaele_dateien++;
                }
                QDir dir(pfad + QDir::separator() + list.at(i));
                if(  dir.exists()  )//Wenn es einen Ordner gibt mit dieser Dateiendung
                {
                    zaele_dateien += dateien_entfernen(pfad + QDir::separator() + list.at(i), dateiendung);
                }
            }else
            {
                QDir dir(pfad + QDir::separator() + list.at(i));
                if(  dir.exists()  && list.at(i)!="."  &&  list.at(i)!="..")
                {
                    zaele_dateien += dateien_entfernen(pfad + QDir::separator() + list.at(i), dateiendung);
                }
            }
        }
    }
    return zaele_dateien;
}

//-----------------------------------------------------------------------

bool MainWindow::ist_ziffer(const QChar zeichen)
{
    if(zeichen == '0' || zeichen == '1' || zeichen == '2' || zeichen == '2' || zeichen == '3' || zeichen == '4' || zeichen == '5' || zeichen == '6' || zeichen == '7' || zeichen == '8' || zeichen == '9')
    {
        return true;
    }else
    {
        return false;
    }
}








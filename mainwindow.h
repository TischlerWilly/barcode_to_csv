#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include "text_zeilenweise.h"
#include "dialog_leere_unterurdner_entfernen.h"


#ifndef INIFILE
#define INIFILE "barcodetocsv.ini"
#endif

#define AUSGABEPFAD_CSV_ZEILVERZEICHNIS     "zielverz"
#define AUSGABEPFAD_CSV_AUFTRAEGE_AN_POIS   "an_pios"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_Barcode_erzeugen_clicked();
    void on_pushButton_quelle_clicked();
    void on_pushButton_ziel_clicked();
    void on_pushButton_Dateien_auflisten_clicked();
    void on_checkBox_quelldateien_erhalten_stateChanged();
    void on_actionInfo_triggered();
    void on_lineEdit_quelle_editingFinished();
    void on_lineEdit_ziel_editingFinished();
    void on_pushButton_root_clicked();
    void on_checkBox_unterordner_erstellen_cnc_stateChanged();
    void on_lineEdit_root_editingFinished();
    void on_checkBox_barcode_erzeugen_stateChanged();
    void on_lineEdit_auftraege_an_pios_editingFinished();
    void on_lineEdit_soptidat_editingFinished();
    void on_pushButton_auftraege_an_pios_clicked();
    void on_pushButton_soptidat_clicked();
    void on_checkBox_unterordner_erstellen_soptidat_stateChanged();
    void on_radioButton_csv_to_zielverz_toggled(bool checked);
    void on_radioButton_csv_to_an_pios_toggled(bool checked);
    void on_actionLeere_Unterordner_entfernen_triggered();
    void on_lineEdit_root2_editingFinished();
    void on_pushButton_root2_clicked();
    void on_checkBox_unterordner_erstellen_cnc2_stateChanged();
    void on_checkBox_gesamtliste_stateChanged();

    void on_actionBIlddateilen_IMAWOP_entfernen_triggered();

private:
    Ui::MainWindow *ui;
    QString tz; //Trennzeichen für Pfade (Linux '/'  Windows '\')

    //Pfade:
    QString verzeichnis_quelle, verzeichnis_ziel, verzeichnis_root, verzeichnis_root2;
    QString verzeichnis_auftraege_an_pios, verzeichnis_soptidat;
    QString pfad_an_pios;//Dient der temporären Speicherung des Pfades in der Funktion "barcode_to_csv" an die Funktion ""on_pushButton_Barcode_erzeugen_clicked

    //Checkboxen:
    QString quelldateien_erhalten, barcode_erzeugen;
    QString unterordner_erstellen_cnc, unterordner_erstellen_cnc2, unterordner_erstellen_soptidat;
    QString gesamtliste_anlegen;

    //Radio-Buttons:
    QString auswahl_zielverz;

    //Dialoge:
    Dialog_leere_unterurdner_entfernen dia_leer_Ordn_entf;

    QString selektiereEintrag(QString text, QString beginntMit, QString endetMit);
    QString text_links(const QString text, const QString trenntext);
    QString text_rechts(const QString text, const QString trenntext);
    QString text_mitte(const QString text, const QString textDavor, const QString textDanach);

    void setup();
    void schreibe_ini();
    QString barcode_to_csv(QString alter_inhalt);
    int dateien_entfernen(QString pfad, QString dateiendung);

public slots:
    void slot_anfrage_pfade();
    void slot_info(QString infotext);

signals:
    void signal_pfade(QString cnc, QString cnc2, QString pios, QString sopti);
};

#endif // MAINWINDOW_H

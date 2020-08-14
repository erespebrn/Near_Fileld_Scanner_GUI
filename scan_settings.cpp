#include "scan_settings.h"
#include "ui_scan_settings.h"
#include <QHostAddress>
#include "scanner_gui.h"
#include "QPushButton"
#include <string>
#include <QDate>
#include <QTime>

int center_freq;
char center_freq_str[80];
int start_freq;
char start_freq_str[80];
char read_buffer[128];

scan_settings::scan_settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scan_settings), _socket_sa(this)
{
    ui->setupUi(this);

    connect(ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()), this ,SLOT(on_apply_click()));

    //Default settings for the scan settings window
    ui->referencelevel_spinbox->setEnabled(false);
    ui->leveloffset_spinbox->setEnabled(false);
    ui->attenuation_spinbox->setEnabled(false);
    ui->sweep_spinbox->setEnabled(false);
    ui->center_freq_spinbox->setEnabled(false);
    ui->spanfreq_spinbox->setEnabled(false);
    ui->frequency_dropdown_center->setEnabled(false);
    ui->frequency_dropdown_span->setEnabled(false);
}

scan_settings::~scan_settings()
{
    delete ui;
}

void scan_settings::on_center_span_radiobutton_clicked()
{
    ui->center_freq_spinbox->setEnabled(true);
    ui->spanfreq_spinbox->setEnabled(true);
    ui->frequency_dropdown_center->setEnabled(true);
    ui->frequency_dropdown_span->setEnabled(true);
    ui->start_freq_spinbox->setEnabled(false);
    ui->start_freq_dropdown->setEnabled(false);
    ui->stop_freq_spinbox->setEnabled(false);
    ui->stop_freq_dropdown->setEnabled(false);

}

void scan_settings::on_start_stop_radiobutton_clicked()
{
    //disabled
    ui->center_freq_spinbox->setEnabled(false);
    ui->spanfreq_spinbox->setEnabled(false);
    ui->frequency_dropdown_center->setEnabled(false);
    ui->frequency_dropdown_span->setEnabled(false);
    //enabled
    ui->start_freq_spinbox->setEnabled(true);
    ui->start_freq_dropdown->setEnabled(true);
    ui->stop_freq_spinbox->setEnabled(true);
    ui->stop_freq_dropdown->setEnabled(true);
   // ui->start_freq_spinbox
}

void scan_settings::on_apply_click()
{

    // MISSING SCOPE INIT!!!


    // Center frequency
    QString mystring = ":FREQuency:CENTer %1 %2";
    mystring = mystring.arg(QString::number(ui->center_freq_spinbox->value()), ui->start_freq_dropdown->currentText());
    _socket_sa.write(mystring.toLocal8Bit());       //if it doesn't work, try toUtf8()


    // Start frequency
    start_freq = ui->start_freq_spinbox->value();
    sprintf(start_freq_str, ":FREQuency:STARt %d Hz", start_freq);
    _socket_sa.write(QByteArray(start_freq_str));

    ui->start_freq_dropdown->currentText();
   // _socket_sa.write(":TRACe:DATA? 1"); // Send read request to the Spectrum analyzer
   // read_data = _socket_sa.readAll(); // Reads data
}




void scan_settings::on_referencelevel_checkbox_stateChanged(int arg1)
{
    if(arg1 == 0)
        ui->referencelevel_spinbox->setEnabled(false);
    else
        ui->referencelevel_spinbox->setEnabled(true);
}

void scan_settings::on_leveloffset_checkbox_stateChanged(int arg1)
{
    if(arg1 == 0)
        ui->leveloffset_spinbox->setEnabled(false);
    else
        ui->leveloffset_spinbox->setEnabled(true);
}

void scan_settings::on_attenuation_checkbox_stateChanged(int arg1)
{
    if(arg1 == 0)
        ui->attenuation_spinbox->setEnabled(false);
    else
        ui->attenuation_spinbox->setEnabled(true);
}

void scan_settings::on_sweep_checkbox_stateChanged(int arg1)
{
    if(arg1 == 0)
        ui->sweep_spinbox->setEnabled(false);
    else
        ui->sweep_spinbox->setEnabled(true);
}

void scan_settings::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->videoBW_spinbox->setEnabled(true);
        ui->videoBW_dropdown->setEnabled(true);
    }
    else
    {
        ui->videoBW_spinbox->setEnabled(false);
        ui->videoBW_dropdown->setEnabled(false);
    }
}














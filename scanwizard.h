#ifndef SCANWIZARD_H
#define SCANWIZARD_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class ScanWizard;
}

class ScanWizard : public QWidget
{
    Q_OBJECT

public:
    explicit ScanWizard(QWidget *parent = nullptr);
    ~ScanWizard();
signals:
    void detect_pcb(bool);
    void send_robot_to_origin(bool);

private slots:
    void on_Next_button_clicked();
    void pcb_found();
    void check_for_pcb();
    void take_coord(QPoint, QRect);

private:
    Ui::ScanWizard *ui;
    QTimer * timer;

    bool _pcb_found= false;

    QPoint pcb_corner;
    QRect pcb_size;
    uint8_t step = 0;
    uint8_t tries = 0;
    QWidget * par;
};

#endif // SCANWIZARD_H
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_hitButton_clicked();

    void on_standButton_clicked();

    void on_betSpinBox_valueChanged(int arg1);

    void on_confirmBetButton_clicked();

    void on_quitButton_clicked();

    void on_playAgainButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer* timer;

    void checkStatus();
    void handleDealerTurn();
};
#endif // MAINWINDOW_H

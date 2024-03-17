// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_a_random_g_clicked();

    void on_a_send_pg_clicked();

    void on_a_random_x_clicked();

    void on_b_random_y_clicked();

    void on_a_send_X_clicked();

    void on_b_send_Y_clicked();

    void on_calculate_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

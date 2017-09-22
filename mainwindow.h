#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileInfoList>
#include <QLabel>
#include <QPixmap>
#include <QTextStream>

#include "paintablelabel.h"

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
    void on_confirm_button_clicked();

    void on_next_button_clicked();

    void on_checkBox_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    QAction * open_action;
    QAction * save_action;
    QAction * save_path_choose_action;
    QAction * help_action;

    QString cur_path;
    QString save_path;
    QString progress;
    QDir * cur_dir;
    QFileInfoList * list;
    int iter = 0;
    PaintableLabel * pic_show_label;
    QImage * cur_img;

    QLabel *permanent = new QLabel(this);

    void open();
    void save();
    void editPath();
    void help();

    QList<Region>region_list;
};

#endif // MAINWINDOW_H

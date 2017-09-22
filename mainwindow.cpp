#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QAction>
#include <QmenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QFileInfoList>
#include <QImage>
#include <QMessageBox>
#include <QList>

#include <QDebug>

QTextStream & operator <<(QTextStream & o,Region & region)   //重载运算符"<<"以便写数据
{
    return o<<region.img_name<<" "<<region.start.x()<<" "<<region.start.y()<<" "<<region.end.x()<<" "<<region.end.y()<<endl;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Labeler");
    setWindowIcon(QIcon(":/images/demo_icon"));
    //this->setFixedSize(1280,600);
    open_action = new QAction(QIcon(":/images/file_icon"),tr("&Open..."),this);
    open_action->setShortcuts(QKeySequence::Open);
    open_action->setStatusTip("Open Flies...");
    connect(open_action,&QAction::triggered,this,&MainWindow::open);

    save_path_choose_action = new QAction(QIcon(":/images/edit_save_path"),tr("&Choose Save Path..."),this);
    save_path_choose_action ->setStatusTip("Edit Save Path...");
    connect(save_path_choose_action,&QAction::triggered,this,&MainWindow::editPath);

    save_action = new QAction(QIcon(":/images/save"),tr("&Save"),this);
    save_action->setShortcuts(QKeySequence::Save);
    save_action->setStatusTip("Save");
    connect(save_action,&QAction::triggered,this,&MainWindow::save);

    help_action = new QAction(QIcon(":/images/help"),tr("&Help"),this);
    help_action->setStatusTip("Help");
    connect(help_action,&QAction::triggered,this,&MainWindow::help);


    QMenu * menu = menuBar()->addMenu(tr("&Menu"));
    menu->addAction(open_action);
    menu->addAction(save_action);
    menu->addAction(save_path_choose_action);
    menu->addAction(help_action);

    QToolBar* toolbar = addToolBar(tr("&File"));
    toolbar->addAction(open_action);
    toolbar->addAction(save_action);
    toolbar->addAction(help_action);

    pic_show_label = new PaintableLabel;
//  QWidget * central = new QWidget;
//  setCentralWidget(central);

    //pic_show_label = new QLabel(centralWidget());
    //pic_show_label->setPixmap();
    cur_img = new QImage(":/images/background");
    pic_show_label->setPixmap(QPixmap::fromImage(*cur_img));
    pic_show_label->resize(QSize(cur_img->width(),cur_img->height()));
    //pic_show_label->show();
    //ui->scrollArea->setLayout();
    ui->scrollArea->setWidget(pic_show_label);

    ui->next_button->setFixedSize(100,25);
    ui->next_button->setText(tr("下一个"));

    ui->confirm_button->setFixedSize(100,25);
    ui->confirm_button->setText(tr("确认"));

    ui->checkBox->setText(tr("多区域模式"));

    progress = tr("请选择一个文件夹...");
    qDebug()<<progress<<endl;
    ui->statusBar->addPermanentWidget(permanent);
    permanent->setText(progress);
    cur_dir = new QDir;
    list = new QFileInfoList;

    statusBar();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete open_action;
    delete save_action;
    delete save_path_choose_action;

    delete cur_dir;
    delete list;
    delete pic_show_label;
    delete cur_img;
}

void MainWindow::open()
{
    cur_path = QFileDialog::getExistingDirectory(this,"请选择文件夹...","./");
    if(cur_path.isEmpty())
    {
         return;
    }else{
         qDebug() << cur_path << endl;
    }


    cur_dir->setPath(cur_path);
    QStringList filters;
    filters << "*.jpg"<<"*.jpeg"<<"*.png";//设置过滤类型
    cur_dir->setNameFilters(filters);//设置文件名的过滤
    *list = cur_dir->entryInfoList();
    iter = 0; //计数重置为0
//    if(list.length()!=0)
//            for (int i = 0; i < list.size(); ++i)
//            {
//                qDebug() << list.at(i).fileName();
//            }
//        else
//        {
//            qDebug()<<"no file";
//        }

    qDebug()<<list->at(0).absoluteFilePath()<<endl;
    qDebug()<<"this line exec"<<endl;
    delete(cur_img);
    cur_img = new QImage(list->at(0).absoluteFilePath());
    pic_show_label->setPixmap(QPixmap::fromImage(*cur_img));
    pic_show_label->resize(QSize(cur_img->width(),cur_img->height()));
    cur_file_name = list->at(iter).absoluteFilePath();

    progress = QString::number(iter)+"/"+QString::number(list->size())+" 已完成";
    permanent->setText(progress);

}

void MainWindow::on_confirm_button_clicked()
{
    Region temp;
//    if(mode)
//    {
//        foreach(temp,pic_show_label->returnList())
//        {
//            region_list.push_back(temp);
//        }

//        pic_show_label->returnList().clear();
//    }
//    else
//    {
//        temp.img_name = list->at(iter).absoluteFilePath();
//        temp.start = pic_show_label->startPoint();
//        temp.end = pic_show_label->endPoint();

//        region_list.push_back(temp);
//    }

    foreach(temp,pic_show_label->returnList())
    {
        region_list.push_back(temp);
    }
    pic_show_label->returnList().clear();
    on_next_button_clicked();
}

void MainWindow::on_next_button_clicked()
{
    iter++;
    if(iter>=list->size())
    {
        QMessageBox::information(this, tr("Information"), tr("已处理完所有图片，请选择下一个文件夹"));
        return;
    }

    else
    {
        delete(cur_img);
        cur_img = new QImage(list->at(iter).absoluteFilePath());
        pic_show_label->setPixmap(QPixmap::fromImage(*cur_img));
        pic_show_label->resize(QSize(cur_img->width(),cur_img->height()));
        cur_file_name = list->at(iter).absoluteFilePath();
        //qDebug()<<list->at(iter).absoluteFilePath()<<endl;
        progress = QString::number(iter)+"/"+QString::number(list->size())+" 已完成";
        permanent->setText(progress);
    }
}

void MainWindow::editPath()
{
    save_path = QFileDialog::getOpenFileName(this,"请选择一个文本文件来保存...","","*.txt");
    if(save_path.isEmpty())
    {
        return;
    }
    QMessageBox::information(this, tr("Information"), tr("文件路径已保存"));
    qDebug()<<save_path<<endl;
}

void MainWindow::save()
{
    qDebug()<<"save"<<endl;
    QFile save_file(save_path);
    if(save_file.exists())
    {
        if(!save_file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QMessageBox::information(this, tr("Information"), tr("无法打开文件"));
            return;
        }
        else
        {
            QTextStream stream(&save_file);
            stream.seek(save_file.size());                 //找到文件末尾
            //QList<Region>::iterator iterator_list = region_list.begin();
            Region temp;
            foreach (temp, region_list) {
                stream<<temp;
            }

            //QMessageBox::information(this, tr("Information"), tr("保存成功"));
            statusBar()->showMessage(tr("保存成功"));
            region_list.clear();
            save_file.close();
        }
    }
    else
    {
        QMessageBox::information(this, tr("Information"), tr("未选择保存位置，请创建一个文本文档来保存"));
        return;
    }
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    if(checked)
    {
        mode = true;

    }
    else
    {
        mode=false;
    }
}

void MainWindow::help()
{
    QMessageBox::information(this, tr("Help Information"), tr("点击Menu->Open选择一个文件夹以开始标注工作"));
    QMessageBox::information(this, tr("Help Information"), tr("点击Menu->Choose Save Path,选择一个文本文档保存数据"));
    QMessageBox::information(this, tr("Help Information"), tr("点击Menu->Save,选择一个文本文档保存数据"));
    QMessageBox::information(this, tr("Help Information"), tr("按住鼠标左键拖动画矩形以选定区域，点击右键可以取消"));
    QMessageBox::information(this, tr("Help Information"), tr("勾选左下角多区域模式可同时选取多个区域"));
    return;
}

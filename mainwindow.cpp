#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QWheelEvent>
#include <QGraphicsScene>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QStandardPaths>
#include <QStringList>
#include <QFileDialog>
#include <QMessageBox>
#ifdef DEBUG
#include <QDebug>
#endif
#define ERROR_MSG "<center><b>There is no image</b></center>"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("TeQtImageviewer");
    mScene = new QGraphicsScene(this);
    mLblInfo = new QLabel(ERROR_MSG, this);
    mLblScale = new QLabel("Scale:100%", this);
    mPixmapItem = new QGraphicsPixmapItem();
    mScene->addItem(mPixmapItem);
    ui->graphicsView->setScene(mScene);
    ui->statusBar->addPermanentWidget(mLblInfo);
    ui->statusBar->addPermanentWidget(mLblScale);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    auto delta = event->delta();
    if(delta > 0)
    {
        mScale *= 1.05f;
        ui->graphicsView->scale(1.05f, 1.05f);

    }
    else if(delta < 0)
    {
        mScale *= 0.95f;
        ui->graphicsView->scale(0.95f, 0.95f);
    }
    QString text;
    text.sprintf("Scale:%6.2f", mScale * 100);
    mLblScale->setText(text + "%");
}

void MainWindow::on_actionOPen_triggered()
{
    auto dir = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation)
            .value(0, QDir::homePath());
    QStringList images = QFileDialog::getOpenFileNames(this, "Open images", dir,
              "Images (*.png *.jpg *.jpeg *.bmp *.ico *.gif);;All files (*.*)");
    for(auto &imgPath: images)
    {
        if(imgPath.isEmpty())
            continue;
        QPixmap pixmap;
        if(!loadImage(imgPath, &pixmap))
            continue;
        ui->listWidget->addItem(new QListWidgetItem(QIcon(pixmap), imgPath));

    }
}

void MainWindow::on_actionQuit_triggered()
{
    auto reply = QMessageBox::question(this, "Quit confirmation",
                          "Dou you really want to quit?",
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        this->close();
    }
}

void MainWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this, "About Qt");
}

bool MainWindow::loadImage(const QString &path, QPixmap *pixmap)
{
    QPixmap image;
    if(!image.load(path))
    {
        mLblInfo->setText(ERROR_MSG);
        return false;
    }
    if(pixmap)
    {
        *pixmap = image;
    }
    mPixmapItem->setPixmap(image);
    mLblInfo->setText("<center><b>" + path + "</b></center>");
    return true;
}

void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    const auto imgPath = index.data().toString();
    loadImage(imgPath);
}

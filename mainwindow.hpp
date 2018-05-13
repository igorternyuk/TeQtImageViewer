#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPixmap>

namespace Ui
{
    class MainWindow;
}

class QGraphicsScene;
class QGraphicsPixmapItem;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void wheelEvent(QWheelEvent *event);

private slots:
    void on_actionOPen_triggered();
    void on_actionQuit_triggered();
    void on_actionAboutQt_triggered();

    void on_listWidget_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *mScene;
    QGraphicsPixmapItem *mPixmapItem;
    QLabel *mLblInfo, *mLblScale;
    qreal mScale = 1.0;
    bool loadImage(const QString &path, QPixmap *pixmap = nullptr);
};

#endif // MAINWINDOW_HPP

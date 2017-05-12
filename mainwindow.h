// This code is released in the Public Domain
// The Ahi Tuna! logo and icon (c)2017 Amos Brocco, amos.brocco@supsi.ch
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

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
    void updateTimeDisplay(qint64 value);
    void seekToTime(int secs);
    void playPause();
    void openStream();
    void openFile();
    void resetUI();

private:
    Ui::MainWindow *ui;
    QMediaPlayer* m_mp;
};

#endif // MAINWINDOW_H

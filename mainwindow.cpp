// This code is released in the Public Domain
// The Ahi Tuna! logo and icon (c)2017 Amos Brocco, amos.brocco@supsi.ch
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMediaContent>
#include <QInputDialog>
#include <QDir>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    ui{new Ui::MainWindow},
    m_mp{new QMediaPlayer{this}}
{
    ui->setupUi(this);
    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(playPause()));
    connect(m_mp, SIGNAL(positionChanged(qint64)), this, SLOT(updateTimeDisplay(qint64)));
    connect(ui->seekSlider, SIGNAL(valueChanged(int)), this, SLOT(seekToTime(int)));
    connect(ui->volumeDial, SIGNAL(valueChanged(int)), m_mp, SLOT(setVolume(int)));
    connect(ui->actionOpen_stream, SIGNAL(triggered(bool)), this, SLOT(openStream()));
    connect(ui->actionOpen_file, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    connect(m_mp, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(resetUI()));

    ui->volumeDial->setValue(m_mp->volume());

    resetUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTimeDisplay(qint64 value)
{
    long secs{value / 1000};
    long mins{secs / 60};
    long modulo{secs % 60};
    ui->minuteLCD->display(QString::number(mins));
    ui->secondsLCD->display(QString::number(modulo));
    ui->seekSlider->setMaximum(m_mp->duration() / 1000);
    ui->seekSlider->setValue(value / 1000);
}

void MainWindow::seekToTime(int secs)
{
    if (m_mp->isSeekable()) {
        if (secs != m_mp->position() / 1000) {
            m_mp->setPosition(secs*1000);
        }
    }
}

void MainWindow::playPause()
{
    if (m_mp->state() == QMediaPlayer::State::PlayingState) {
        ui->playButton->setIcon(QIcon(":/pixmaps/Note.png"));
        m_mp->pause();
    } else {
        ui->playButton->setIcon(QIcon(":/pixmaps/Cup.png"));
        m_mp->play();
        long secs{m_mp->duration() / 1000};
        long mins{secs / 60};
        long modulo{secs % 60};
        ui->lengthLCD->display(QString::number(mins) + ":" + QString::number(modulo));
    }
}

void MainWindow::openStream()
{
    bool ok;
    QString url{QInputDialog::getText(this, tr("Open Stream"),
                                        tr("Url"), QLineEdit::Normal,
                                        "", &ok)};
    if (ok && !url.isEmpty()) {
       m_mp->setMedia(QMediaContent{QUrl{url}});
       ui->playButton->setEnabled(true);
       resetUI();
       ui->playButton->setEnabled(true);
       setWindowTitle(this->windowTitle()+ " - " +url);
    }
}

void MainWindow::openFile()
{
    QString fileName{QFileDialog::getOpenFileName(this,
        tr("Open File"), QDir::home().absolutePath(), tr("Music (*.mp3 *.ogg)"))};

    if (fileName != "") {
        m_mp->setMedia(QMediaContent{QUrl{"file://"+fileName}});
        ui->playButton->setEnabled(true);
        resetUI();
        ui->playButton->setEnabled(true);
        setWindowTitle(this->windowTitle()+ " - " +fileName);
    }
}

void MainWindow::resetUI()
{
    m_mp->stop();
    ui->playButton->setIcon(QIcon(":/pixmaps/Note.png"));
    ui->playButton->setEnabled(false);
    setWindowTitle(tr("ahiTuna"));
    ui->lengthLCD->display("--:--");
    ui->seekSlider->setMaximum(0);
    ui->minuteLCD->display("--");
    ui->secondsLCD->display("--");
}

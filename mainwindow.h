#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMimeData>
#include <QProcess>
#include <QDebug>
#include <QException>
#include <QDesktopServices>
#include <QMessageBox>
#include <QSettings>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
  void rectos_filename_button_clicked();
  void versos_filename_button_clicked();
  void output_filename_button_clicked();
  void rectos_filename_dropped(QDropEvent *ev);
  void versos_filename_dropped(QDropEvent *ev);
  void start_button_clicked();

private:
  Ui::MainWindow *ui;
  QString pdftk_path;
  void shuffle();
  void display_final_file();
};

#endif // MAINWINDOW_H

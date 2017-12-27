#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  /* Setup UI */
  ui->setupUi(this);
  /* Load settings */
  QString settings_filename = QCoreApplication::applicationDirPath() + "/page-shuffler.ini";
  QSettings settings(settings_filename, QSettings::IniFormat);
  qDebug() << "settings filename: " << settings.fileName();
  qDebug() << "settings: " << settings.allKeys();
  pdftk_path = settings.value("paths/pdftk", "C:\\Program Files (x86)\\PDFtk\\bin\\pdftk.exe").toString();
  qDebug() << "pdftk_path: " << pdftk_path;
}

MainWindow::~MainWindow()
{
  delete ui;
}

#define ACTION_CLICKED(fct_name, edit_name, getFileName) \
  void MainWindow::fct_name() \
  { \
    auto filename = QFileDialog::getFileName(this, tr("Choix rectos"), "", tr("Fichier pdf (*.pdf)")); \
    if (!filename.isNull()) \
      this->ui->edit_name->setText(filename); \
  } \

ACTION_CLICKED(rectos_filename_button_clicked, rectos_filename_edit, getOpenFileName)
ACTION_CLICKED(versos_filename_button_clicked, versos_filename_edit, getOpenFileName)
ACTION_CLICKED(output_filename_button_clicked, output_filename_edit, getSaveFileName)

#define ACTION_DROPPED(fct_name, edit_name) \
  void MainWindow::fct_name(QDropEvent *ev) \
  { \
    /* If dropped event contains urls */ \
    if (ev->mimeData()->hasUrls()) { \
      QUrl url = ev->mimeData()->urls().first(); \
      qDebug() << "Drop event: " << url; \
      /* If url is a local file */ \
      if (url.isLocalFile()) { \
        QString filename = url.toLocalFile(); \
        /* If url is a pdf file */ \
        if (filename.endsWith(".pdf")) { \
          /* Store filename */ \
          ui->edit_name->setText(filename); \
        } \
      } \
    } \
  } \

ACTION_DROPPED(rectos_filename_dropped, rectos_filename_edit)
ACTION_DROPPED(versos_filename_dropped, versos_filename_edit)

QString escape(QString input)
{
  // return input.replace()
  return input;
}

void MainWindow::shuffle()
{
  /** Shuffle rectos and versos **/
  /* Select base command string depending on shuffle mode */
  qDebug() << "mode_combobox index: " << ui->mode_combobox->currentIndex();
  const char* base_command;
  if (ui->mode_combobox->currentIndex() == 0)
    base_command = "\"%1\" A=\"%2\" B=\"%3\" shuffle A Bend-1 output \"%4\"";
  else if (ui->mode_combobox->currentIndex() == 1)
    base_command = "\"%1\" A=\"%2\" B=\"%3\" shuffle A B output \"%4\"";
  else
    return;  // FIXME !!!!
  /* Build command string */
  QString command = QString(base_command) // FIXME ! Escaping.
      .arg(escape(pdftk_path))
      .arg(escape(ui->rectos_filename_edit->text()))
      .arg(escape(ui->versos_filename_edit->text()))
      .arg(escape(ui->output_filename_edit->text()));
  qDebug() << command;
  /* Run command string */
  QProcess process;
  process.start(command);
  process.waitForFinished(-1); // NO TIMEOUT !
}

void MainWindow::display_final_file()
{
  QDesktopServices::openUrl(ui->output_filename_edit->text());
}

void MainWindow::start_button_clicked()
{
  /* Check input data */
  if (ui->output_filename_edit->text().isEmpty())
  {
    QMessageBox::warning(this, tr("Rectos/Versos"),
                         tr("Préciser le fichier de sortie."));
    return;
  }
  /* Shuffle rectos and versos */
  shuffle();
  /* Displays final file */
  display_final_file();
}

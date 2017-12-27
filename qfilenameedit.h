#ifndef QFILENAMEEDIT_H
#define QFILENAMEEDIT_H

#include <QLineEdit>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>


class QFilenameEdit : public QLineEdit
{
  Q_OBJECT
public:
  QFilenameEdit();
  QFilenameEdit(QWidget *);
protected:
  void dropEvent(QDropEvent *ev);
  void dragEnterEvent(QDragEnterEvent *ev);
signals:
  void dropped(QDropEvent *ev);
};

#endif // QFILENAMEEDIT_H

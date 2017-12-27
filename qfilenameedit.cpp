#include "qfilenameedit.h"

QFilenameEdit::QFilenameEdit()
  : QLineEdit()
{
  setAcceptDrops(true);
}

QFilenameEdit::QFilenameEdit(QWidget *parent)
  : QLineEdit(parent)
{
  setAcceptDrops(true);
}

void QFilenameEdit::dropEvent(QDropEvent *ev)
{
  emit dropped(ev);
//   QList<QUrl> urls = ev->mimeData()->urls();
//   foreach(QUrl url, urls)
//   {
//       qDebug()<<url.toString();
//   }
}

void QFilenameEdit::dragEnterEvent(QDragEnterEvent *ev)
{
  setBackgroundRole(QPalette::Highlight);
  ev->accept();
}

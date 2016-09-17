#include <QDebug>
#include <QString>

#include "backup.h"
#include "backupcli.h"

QString backupcli::humanreadable(float number)
{
    QStringList list;
    list << "KB" << "MB" << "GB" << "TB";

    QStringListIterator i(list);
    QString unit("bytes");

    while(number >= 1024.0 && i.hasNext())
    {
        unit = i.next();
        number /= 1024.0;
    }
    return QString().setNum(number,'f',2)+" "+unit;
}

void backupcli::output(backup bk)
{
    qDebug() << QString(
    "**************** BACKUP ****************\n\n" \
    "Files included in this backup: %1 files\n" \
    "Size of this backup:           %2\n" \
    "Files backed up:               %3 files\n" \
    "Size if files backed up:       %4\n" \
    "\n" \
    "****************************************")
    .arg(bk.getBackupFullCount())
    .arg(this->humanreadable(bk.getBackupFullSize()))
    .arg(bk.getBackupCount())
    .arg(this->humanreadable(bk.getBackupSize()))
    .toLatin1().data();
}

backupcli::backupcli()
{
}

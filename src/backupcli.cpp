#include <QDebug>
#include <QString>
#include <QElapsedTimer>

#include "backup.h"
#include "backupcli.h"

QString backupcli::convertTimeFromMis(int time)
{
    QString string;

    int x = time / 1000;

    float seconds =  x % 60;
    x /= 60;
    float minutes = x % 60;
    x /= 60;
    int hours = x % 60;

    if(hours > 0) {
        string.append(QString::number(hours)).append("h");
    }

    if(hours > 0 && minutes > 0) {
        string.append(" ");
    }

    if(minutes > 0) {
        string.append(QString::number(minutes)).append("m");
    }

    if(minutes > 0 && seconds > 0) {
        string.append(" ");
    }

    if(seconds > 0) {
        string.append(QString::number(seconds)).append("s");
    }

    if(string.length() == 0) {
        string.append(QString::number(time / 1000.00)).append("s");
    }

    return string;
}

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
    "Prosess time:                  %5\n"\
    "File transfer time:            %6\n"\
    "\n" \
    "****************************************")
    .arg(bk.getBackupFullCount())
    .arg(this->humanreadable(bk.getBackupFullSize()))
    .arg(bk.getBackupCount())
    .arg(this->humanreadable(bk.getBackupSize()))
    .arg(this->convertTimeFromMis(bk.getBackupPrisessTimer()))
    .arg(this->convertTimeFromMis(bk.getBackupTrasferTimer()))
    .toLatin1().data();
}

backupcli::backupcli()
{
}

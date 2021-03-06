#include <QString>
#include <QMutableListIterator>
#include <QDirIterator>
#include <QDateTime>
#include <QList>
#include <QDebug>
#include <QPair>
#include <QElapsedTimer>

#include "backup.h"

backup::backup(QString destDir)
{
    this->backUpFileCount = 0;
    this->backUpFullFileCount = 0;
    this->backUpSize = 0;
    this->backUpFullSize = 0;
    this->backupDest = destDir;
    QElapsedTimer timer;
    this->timer = timer;
    this->timer.start();
}

void backup::backupFiles()
{
    this->prosessTime = this->timer.elapsed();
    this->timer.restart();

    QListIterator<QPair<QString, QString> > itr (this->backupFileList);
    while (itr.hasNext()) {

        QPair<QString, QString> current = itr.next();

        if(this->isFileNewOrChanged(current.first, current.second)) {
            QFileInfo fi(current.second);

            if(!fi.absoluteDir().exists()) {
                QDir dir;
                dir.mkpath(fi.absoluteDir().absolutePath());
            }

            QFile file(current.first);

            // todo add to a verbose option
            //qDebug() << "[" << this->backUpFileCount << "] " << current.second;
            // fprintf(stderr, QString("\r[%1 of %2]").arg(bkCount).arg(this->backUpFullFileCount).toLatin1().data());

            file.copy(current.second);
            this->backUpFileCount++;
            this->backUpSize += file.size();
        }
    }
    this->transferTime = this->timer.elapsed();
}

void backup::addDir(QString dir)
{
    QDirIterator it(dir, QDirIterator::Subdirectories);

    while (it.hasNext()) {
        //QString newFile = this->backupDest + it.filePath().replace(dir, QString(""));
        QString newFile = this->backupDest + it.fileInfo().absoluteFilePath();

        if(it.fileInfo().isFile()) {
            this->backupFileList.append(qMakePair(it.filePath(), newFile));
            this->backUpFullFileCount++;
            this->backUpFullSize += it.fileInfo().size();
        }
        it.next();
    }
}

void backup::removeDir(QString dir)
{
    QMutableListIterator<QPair<QString, QString> > itr (this->backupFileList);

    while (itr.hasNext()) {
        QPair<QString, QString> current = itr.next();

        if (current.first.contains(dir)) {
            QFileInfo fi(current.first);
            itr.remove();
            this->backUpFullSize -= fi.size();
            this->backUpFullFileCount--;
        }
    }
}

bool backup::isFileNewOrChanged(QString srcFilePath, QString destFilePath)
{
    return !QFile(destFilePath).exists() || QFileInfo(destFilePath).lastModified().secsTo(QFileInfo(srcFilePath).lastModified()) > 0;
}

int backup::getBackupCount()
{
    return this->backUpFileCount;
}

int backup::getBackupFullCount()
{
    return this->backUpFullFileCount;
}

int backup::getBackupSize()
{
    return this->backUpSize;
}

int backup::getBackupFullSize()
{
    return this->backUpFullSize;
}

QList<QPair<QString, QString> > backup::getBackupFileList()
{
    return this->backupFileList;
}

QString backup::getBackupDest()
{

    return this->backupDest;
}

float backup::getBackupPrisessTimer()
{
    return this->prosessTime;
}

float backup::getBackupTrasferTimer()
{
    return this->transferTime;
}

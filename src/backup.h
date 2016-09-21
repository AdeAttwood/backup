#ifndef BACKUP_H
#define BACKUP_H

class backup
{
    private:
        QList<QPair<QString, QString> > backupFileList;
        QString backupDest;
        QElapsedTimer timer;
        float prosessTime;
        float transferTime;
        int backUpFullFileCount;
        int backUpFullSize;
        int backUpFileCount;
        int backUpSize;
    public:
        backup(QString destDir);
        QString getBackupDest();
        QList<QPair<QString, QString> > getBackupFileList();
        bool isFileNewOrChanged(QString destFilePath, QString srcFilePath);
        int  getBackupSize();
        int  getBackupFullSize();
        int  getBackupCount();
        int  getBackupFullCount();
        float getBackupPrisessTimer();
        float getBackupTrasferTimer();
        void addDir(QString dir);
        void removeDir(QString dir);
        void backupFiles();
};

#endif // BACKUP_H

#include <QtTest/QtTest>
#include "../../src/backup.h"

class BackupTest: public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void testConstruct();
    void testAddDir();
    void testAddMutipleDirs();
    void testRemoveDir();
    void testBackupSize();
    void testRemoveDirBackupSize();
    void testMovingFiles();
    void testMovingFiles1();
    void cleanupTestCase();
};

// test cli output
//QProcess pingProsess;
//pingProcess.start(exec, QList << "params");
//pingProcess.waitForFinished(); // sets current thread to sleep and waits for pingProcess end
//QString output(pingProcess.readAllStandardOutput());

void BackupTest::initTestCase()
{
}

void BackupTest::cleanupTestCase()
{
    QDir dir("tests/assets/dest");
    dir.removeRecursively();
}

void BackupTest::testMovingFiles1()
{
    backup bk("tests/assets/dest");
    bk.addDir("tests/assets/src/cinnamon");
    bk.addDir("tests/assets/src/gnome-shell");
    bk.backupFiles();

    QCOMPARE(bk.getBackupFullCount(), 98);
    QCOMPARE(bk.getBackupCount(), 55);

}

void BackupTest::testMovingFiles()
{
    backup bk("tests/assets/dest");
    bk.addDir("tests/assets/src/cinnamon");
    bk.backupFiles();

    QCOMPARE(bk.getBackupFullCount(), 43);
    QCOMPARE(bk.getBackupCount(), 43);
}

void BackupTest::testRemoveDirBackupSize()
{
    int backupSize = 0;
    backup bk("tests/assets/dest");
    bk.addDir("tests/assets/src/cinnamon");
    bk.addDir("tests/assets/src/gnome-shell");
    bk.removeDir("tests/assets/src/gnome-shell");
    QListIterator<QPair<QString, QString> > itr (bk.getBackupFileList());
    while (itr.hasNext()) {
        QPair<QString, QString> current = itr.next();
        QFileInfo fi(current.first);
        backupSize = backupSize + fi.size();
    }
    QCOMPARE(backupSize, bk.getBackupFullSize());
}

void BackupTest::testBackupSize()
{
    int backupSize = 0;

    backup bk("tests/assets/dest");
    bk.addDir("tests/assets/src/cinnamon");
    QListIterator<QPair<QString, QString> > itr (bk.getBackupFileList());
    while (itr.hasNext()) {
        QPair<QString, QString> current = itr.next();
        QFileInfo fi(current.first);
        backupSize = backupSize + fi.size();
    }
    QCOMPARE(backupSize, bk.getBackupFullSize());
}

void BackupTest::testRemoveDir()
{
    backup bk("tests/assets/dest");
    bk.addDir("tests/assets/src/cinnamon");
    bk.addDir("tests/assets/src/gnome-shell");
    bk.removeDir("tests/assets/src/gnome-shell");
    QCOMPARE(bk.getBackupFullCount(), 43);
}

void BackupTest::testAddMutipleDirs()
{
    backup bk("tests/assets/dest");
    bk.addDir("tests/assets/src/cinnamon");
    QCOMPARE(bk.getBackupFullCount(), 43);
    bk.addDir("tests/assets/src/gnome-shell");
    QCOMPARE(bk.getBackupFullCount(), 98);
}

void BackupTest::testConstruct()
{
    backup bk("tests/assets/dest");
    QCOMPARE(bk.getBackupSize(), 0);
    QCOMPARE(bk.getBackupDest(), QString("tests/assets/dest"));
}

void BackupTest::testAddDir()
{
    backup bk("tests/assets/dest");
    bk.addDir("tests/assets/src/cinnamon");
    QCOMPARE(bk.getBackupFullCount(), 43);
}

QTEST_MAIN(BackupTest)
#include "build/backuptest.moc"

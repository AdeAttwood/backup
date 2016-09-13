#include <QtTest/QtTest>
#include "../src/backup.h"

class TestQString: public QObject
{
    Q_OBJECT
private slots:
    void testConstruct();
    void testAddDir();
    void testAddMutipleDirs();
    void testRemoveDir();
    void testBackupSize();
    void testRemoveDirBackupSize();
};

void TestQString::testRemoveDirBackupSize()
{
    int backupSize = 0;
    backup bk("assets/dest");
    bk.addDir("assets/src/cinnamon");
    bk.addDir("assets/src/gnome-shell");
    bk.removeDir("assets/src/gnome-shell");
    QListIterator<QPair<QString, QString> > itr (bk.getBackupFileList());
    while (itr.hasNext()) {
        QPair<QString, QString> current = itr.next();
        QFileInfo fi(current.first);
        backupSize = backupSize + fi.size();
    }
    QCOMPARE(backupSize, bk.getBackupFullSize());
}

void TestQString::testBackupSize()
{
    int backupSize = 0;

    backup bk("assets/dest");
    bk.addDir("assets/src/cinnamon");
    QListIterator<QPair<QString, QString> > itr (bk.getBackupFileList());
    while (itr.hasNext()) {
        QPair<QString, QString> current = itr.next();
        QFileInfo fi(current.first);
        backupSize = backupSize + fi.size();
    }
    QCOMPARE(backupSize, bk.getBackupFullSize());
}

void TestQString::testRemoveDir()
{
    backup bk("assets/dest");
    bk.addDir("assets/src/cinnamon");
    bk.addDir("assets/src/gnome-shell");
    bk.removeDir("assets/src/gnome-shell");
    QCOMPARE(bk.getBackupFullCount(), 43);
}

void TestQString::testAddMutipleDirs()
{
    backup bk("assets/dest");
    bk.addDir("assets/src/cinnamon");
    QCOMPARE(bk.getBackupFullCount(), 43);
    bk.addDir("assets/src/gnome-shell");
    QCOMPARE(bk.getBackupFullCount(), 98);
}

void TestQString::testConstruct()
{
    backup bk("assets/dest");
    QCOMPARE(bk.getBackupSize(), 0);
    QCOMPARE(bk.getBackupDest(), QString("assets/dest"));
}

void TestQString::testAddDir()
{
    backup bk("assets/dest");
    bk.addDir("assets/src/cinnamon");
    QCOMPARE(bk.getBackupFullCount(), 43);
}

QTEST_MAIN(TestQString)
#include "backuptest.moc"

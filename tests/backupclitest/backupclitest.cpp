#include <QtTest/QtTest>
#include "../../src/backup.h"
#include "../../src/backupcli.h"

class BackupCliTest: public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void testconvertfrommiliseconds();
    void testhumanreadable();
};

void BackupCliTest::testhumanreadable()
{
    backupcli cli;
    QCOMPARE(cli.humanreadable(25), QString("25.00 bytes"));
    QCOMPARE(cli.humanreadable(4000), QString("3.91 KB"));
    QCOMPARE(cli.humanreadable(4823449), QString("4.60 MB"));
    QCOMPARE(cli.humanreadable(9019431321), QString("8.40 GB"));
    QCOMPARE(cli.humanreadable(5970348138823), QString("5.43 TB"));
}

void BackupCliTest::testconvertfrommiliseconds()
{
    backupcli cli;
    QCOMPARE(cli.convertTimeFromMis(75), QString("0.075s"));
    QCOMPARE(cli.convertTimeFromMis(500), QString("0.5s"));
    QCOMPARE(cli.convertTimeFromMis(1000), QString("1s"));
    QCOMPARE(cli.convertTimeFromMis(6000), QString("6s"));
    QCOMPARE(cli.convertTimeFromMis(63000), QString("1m 3s"));
    QCOMPARE(cli.convertTimeFromMis(3600000), QString("1h"));
    QCOMPARE(cli.convertTimeFromMis(5400000), QString("1h 30m"));
    QCOMPARE(cli.convertTimeFromMis(5406000), QString("1h 30m 6s"));
}

void BackupCliTest::initTestCase()
{
}

QTEST_MAIN(BackupCliTest)
#include "build/backupclitest.moc"

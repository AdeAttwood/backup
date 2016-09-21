#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QElapsedTimer>

#include "backup.h"
#include "backupcli.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("backup");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addPositionalArgument("destination", QCoreApplication::translate("main", "(Requied) Destination directory."));

    QCommandLineOption versionOption("version",
        QCoreApplication::translate("main", "Print version number and exit."));
    parser.addOption(versionOption);

    QCommandLineOption includeDirOption(QStringList() << "i" << "include",
        QCoreApplication::translate("main", "(Requied) File path to include in your backup."),
        QCoreApplication::translate("main", "directory"));
    parser.addOption(includeDirOption);

    QCommandLineOption excludeDirOption(QStringList() << "e" << "exclude",
        QCoreApplication::translate("main", "File path to exclude in your backup."),
        QCoreApplication::translate("main", "directory"));
    parser.addOption(excludeDirOption);

    QCommandLineOption outputOption(QStringList() << "o" << "output",
        QCoreApplication::translate("main", "Output stats when the proces has finished."));
    parser.addOption(outputOption);

    parser.process(app);

    if (parser.isSet(versionOption)) {
        QString version = QCoreApplication::applicationName().append(" ").append(QCoreApplication::applicationVersion());
        qDebug() << version.toLatin1().data();
        return 0;
    }

    QStringList args = parser.positionalArguments();
    QList<QString> includeList = parser.values(includeDirOption);
    QList<QString> excludeList = parser.values(excludeDirOption);

    if(args.length() != 1) {
        qDebug() << QString("ERROR: Destanation directory is requied\nUse '%1 --help' for more information.").arg(QCoreApplication::applicationName()).toLatin1().data();
        return 0;
    }

    if(includeList.length() < 1) {
        qDebug() << QString("ERROR: You must supply at least on include directory\nUse '%1 --help' for more information.").arg(QCoreApplication::applicationName()).toLatin1().data();
        return 0;
    }

    backup bk(args.at(0));

    foreach(QString include, includeList) {
        bk.addDir(include);
    }

    foreach (QString exclude, excludeList) {
        bk.removeDir(exclude);
    }

    bk.backupFiles();

    if(parser.isSet(outputOption)) {
        backupcli cli;
        cli.output(bk);
    }

    return 0;
}

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include "backup.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("qt-backup-app");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addPositionalArgument("destination", QCoreApplication::translate("main", "(Requied) Destination directory."));

    QCommandLineOption includeDirOption(QStringList() << "i" << "include",
        QCoreApplication::translate("main", "(Requied) File path to include in your backup"),
        QCoreApplication::translate("main", "directory"));
    parser.addOption(includeDirOption);

    parser.process(app);
    QStringList args = parser.positionalArguments();
    QList<QString> includeList = parser.values(includeDirOption);

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

    bk.backupFiles();

    return app.exec();
}

#ifndef BACKUPCLI_H
#define BACKUPCLI_H

class backupcli
{
public:
    backupcli();
    void output(backup bk);
    QString humanreadable(float number);
    QString convertTimeFromMis(int time);
};

#endif // BACKUPCLI_H

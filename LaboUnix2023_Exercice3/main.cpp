#include "mainwindowex3.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    int fdLog;
    if((fdLog = open("Trace.log", O_RDWR|O_CREAT, 0666))== -1)
    {
      perror("erreur open");
    }
    int dupresult = dup2(fdLog, 2);
    QApplication a(argc, argv);
    MainWindowEx3 w;

    w.show();
    close(fdLog);
    return a.exec();
}

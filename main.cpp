#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <ncursesw/ncurses.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test.db");

    if (!db.open()) {
        return 1;
    }

    QSqlQuery query;
    query.exec("SELECT id, name FROM users");

    initscr();
    noecho();
    cbreak();

    mvprintw(0, 0, "ID   NAME");
    mvprintw(1, 0, "---------");

    int row = 2;

    while (query.next()) {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();

        mvprintw(
            row,
            0,
            "%-4d %s",
            id,
            name.toUtf8().constData()
        );

        row++;
    }

    refresh();
    getch();

    endwin();

    return 0;
}

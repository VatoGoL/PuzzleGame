#ifndef MODELFILEMANAGER_H
#define MODELFILEMANAGER_H
#include <QFile>
#include <QTextStream>
#include <QDataStream>

using namespace std;

struct level_save_t{
    QString name_level;
    int size_x;
    int size_y;
    int time_m;
    int time_s;
    QString path_to_image;
    int **game_table = nullptr;
};
enum {
    ERROR_OPEN_FILE = 0,
    WRITE_SUCCEFUL
};

class ModelFileManager
{
private:

    QTextStream *__text_stream = nullptr;
    QString __path_to_file;

    string __readBoxData(char separating_symbol = ' ');
    void __writeBoxData(string data, char separating_symbol = ' ', bool end_line = false);
public:

    ModelFileManager(QString path_to_file);

    void setPathToFile(QString path_to_file);
    QString getPathToFile();

    QString* readStartSettings(QString *array_tags, int size_array_tags, bool *array_statistic_search = nullptr);
    int saveStartSettings(QString **array_tags, int size_array_tags);

    struct level_save_t* readGameSave();
    int saveGameSave(struct level_save_t level_save);

    ~ModelFileManager();
};

#endif // MODELFILEMANAGER_H

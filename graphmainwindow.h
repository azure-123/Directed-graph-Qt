#ifndef GRAPHMAINWINDOW_H
#define GRAPHMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class GraphMainWindow;
}

class GraphMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphMainWindow(QWidget *parent = 0);
    ~GraphMainWindow();

private slots:
    void on_showLinklist_clicked();

    void on_showTopologicalSort_clicked();

    void on_showCriticalPath_clicked();

private:
    Ui::GraphMainWindow *ui;
};

#endif // GRAPHMAINWINDOW_H

#ifndef DEBUGPROZOR_H
#define DEBUGPROZOR_H

#include <QWidget>

namespace Ui {
class DebugProzor;
}

class DebugProzor : public QWidget
{
    Q_OBJECT

public:
    explicit DebugProzor(QWidget *parent = 0);
    ~DebugProzor();

private:
    Ui::DebugProzor *ui;

public slots:
    void updateCoordinates(int x, int y, int w, int h);
};

#endif // DEBUGPROZOR_H

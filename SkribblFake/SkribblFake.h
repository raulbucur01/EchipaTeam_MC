#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SkribblFake.h"

class SkribblFake : public QMainWindow
{
    Q_OBJECT

public:
    SkribblFake(QWidget *parent = nullptr);
    ~SkribblFake();

private:
    Ui::SkribblFakeClass ui;
};

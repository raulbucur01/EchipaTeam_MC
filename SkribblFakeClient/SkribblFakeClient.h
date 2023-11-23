#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SkribblFakeClient.h"

class SkribblFakeClient : public QMainWindow
{
    Q_OBJECT

public:
    SkribblFakeClient(QWidget *parent = nullptr);
    ~SkribblFakeClient();

private:
    Ui::SkribblFakeClientClass ui;
};

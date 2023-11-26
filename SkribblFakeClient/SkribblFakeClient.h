#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SkribblFakeClient.h"

class SkribblFakeClient : public QMainWindow
{
    Q_OBJECT

public:
    SkribblFakeClient(QWidget *parent = nullptr);
    ~SkribblFakeClient();
    
public slots:
    void on_pushButton_Login_clicked();
    void on_commandLinkButton_pressed();

private:
    Ui::SkribblFakeClientClass ui;
};

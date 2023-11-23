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

private:
    Ui::SkribblFakeClientClass ui;
};

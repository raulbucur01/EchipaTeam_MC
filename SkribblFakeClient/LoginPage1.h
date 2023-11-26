#pragma once

#include <QWidget>
#include "ui_SkribblFakeClient.h"

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    LoginPage(QWidget *parent = nullptr);
    ~LoginPage();
    
public slots:
    void on_pushButton_Login_clicked();
    void on_commandLinkButton_pressed();

private:
    Ui::SkribblFakeClientClass ui;
};

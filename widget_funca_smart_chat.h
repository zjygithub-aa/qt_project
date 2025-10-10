#ifndef WIDGET_FUNCA_SMART_CHAT_H
#define WIDGET_FUNCA_SMART_CHAT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include "button_chat_send.h"
#include "widget_smart_chat_message.h"

namespace Ui {
class Widget_funcA_Smart_chat;
}

class Widget_funcA_Smart_chat : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_funcA_Smart_chat(QWidget *parent = nullptr);
    ~Widget_funcA_Smart_chat();

protected slots:
    void Slota_Add_Send_Message();

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    Ui::Widget_funcA_Smart_chat *ui;
    QBoxLayout *Message_layout;
    QNetworkAccessManager *manager;
};

#endif // WIDGET_FUNCA_SMART_CHAT_H

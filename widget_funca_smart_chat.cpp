#include "widget_funca_smart_chat.h"
#include "ui_widget_funca_smart_chat.h"

Widget_funcA_Smart_chat::Widget_funcA_Smart_chat(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget_funcA_Smart_chat)
{
    ui->setupUi(this);

    ui->Button_send->setFixedSize(80 , 30);
    ui->textEdit->setStyleSheet("background: transparent; border: none;");
    ui->textEdit->setFont(QFont("楷体" , 13));

    Message_layout = new QVBoxLayout(ui->widget_show);

    connect(ui->Button_send , &Button_Cust_Base::signals_click ,
            this , &Widget_funcA_Smart_chat::Slota_Add_Send_Message);

    // ✅ 初始化网络管理器
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,
            this, &Widget_funcA_Smart_chat::onReplyFinished);

    qDebug() << "✅ 智能聊天窗口初始化完成";
}

Widget_funcA_Smart_chat::~Widget_funcA_Smart_chat()
{
    delete ui;
}

void Widget_funcA_Smart_chat::Slota_Add_Send_Message()
{
    QString userInput = ui->textEdit->toPlainText().trimmed();
    if (userInput.isEmpty()) return;

    qDebug() << "📝 用户输入:" << userInput;

    Widget_smart_chat_message *sendMsg = new Widget_smart_chat_message(ui->widget_show);
    Message_layout->addWidget(sendMsg);
    sendMsg->set_Send_Layout();
    sendMsg->set_Edit_Text(userInput);
    sendMsg->show();
    ui->textEdit->clear();

    QUrl url("https://open.bigmodel.cn/api/paas/v4/chat/completions");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer 02920344c0ba4322be305282ad4e05de.FxmlkIFqS0riG0CD");

    QJsonObject msg;
    msg["role"] = "user";
    msg["content"] = userInput;

    QJsonArray messages;
    messages.append(msg);

    QJsonObject thinking;
    thinking["type"] = "enabled";

    QJsonObject json;
    json["model"] = "glm-4-flash";          // 官方示例模型
    json["messages"] = messages;
    json["thinking"] = thinking;
    json["max_tokens"] = 65536;
    json["temperature"] = 1.0;

    QJsonDocument doc(json);
    qDebug() << "📡 发送请求JSON:" << doc.toJson();

    manager->post(request, doc.toJson());


}

void Widget_funcA_Smart_chat::onReplyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        // 网络层面的错误（如无法连接、超时等）
        qDebug() << "❌ 网络错误:" << reply->errorString();
        reply->deleteLater();
        return;
    }
    QByteArray response = reply->readAll();
    qDebug() << "🛰️ 返回内容:" << response;
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(response, &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject()) {
        // JSON格式错误或不是JSON对象
        qDebug() << "⚠️ JSON解析错误:" << err.errorString();
        reply->deleteLater();
        return;
    }
    QJsonObject responseObject = doc.object();
    // 1. 优先检查API是否返回了业务层面的错误
    if (responseObject.contains("error")) {
        QJsonObject errorObj = responseObject["error"].toObject();
        QString errorMessage = errorObj.value("message").toString();
        qDebug() << "❌ API业务错误:" << errorMessage;
        // 可以在这里创建一个消息气泡，将错误信息显示在聊天界面上
        // displayErrorMessage(errorMessage);
        reply->deleteLater();
        return;
    }
    // 2. 检查是否有choices字段
    if (!responseObject.contains("choices")) {
        qDebug() << "⚠️ 响应格式异常：缺少choices字段";
        reply->deleteLater();
        return;
    }
    QJsonValue choicesValue = responseObject.value("choices");
    if (!choicesValue.isArray()) {
        qDebug() << "⚠️ 响应格式异常：choices字段不是数组";
        reply->deleteLater();
        return;
    }
    QJsonArray choicesArray = choicesValue.toArray();
    if (choicesArray.isEmpty()) {
        qDebug() << "⚠️ 响应格式异常：choices数组为空";
        reply->deleteLater();
        return;
    }
    // 3. 安全地提取message内容
    QJsonObject firstChoice = choicesArray.first().toObject();
    if (!firstChoice.contains("message")) {
        qDebug() << "⚠️ 响应格式异常：choice中缺少message字段";
        reply->deleteLater();
        return;
    }
    QJsonObject messageObj = firstChoice.value("message").toObject();
    if (!messageObj.contains("content")) {
        qDebug() << "⚠️ 响应格式异常：message中缺少content字段";
        reply->deleteLater();
        return;
    }
    QString content = messageObj.value("content").toString();
        qDebug() << "💬 模型回复:" << content;

        // --- 重要：将模型回复显示在界面上 ---
        Widget_smart_chat_message *replyMsg = new Widget_smart_chat_message(ui->widget_show);
        Message_layout->addWidget(replyMsg);

        // 【添加这行】先设置接收消息的布局
        replyMsg->set_Recv_Layout();

        replyMsg->set_Edit_Text(content);
        replyMsg->show();

        reply->deleteLater();
}

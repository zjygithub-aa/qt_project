#include "widget_funcc_smart_home.h"
#include "ui_widget_funcc_smart_home.h"
#include <QDebug>
#include <QPixmap>
#include <QMediaContent>
#include <QSslSocket>
#include <QTextCodec>


// ---------------- MusicSearchDialog 实现 ----------------
MusicSearchDialog::MusicSearchDialog(QWidget *parent)
    : QDialog(parent),
      searchManager(new QNetworkAccessManager(this))
{
    setWindowTitle("搜索音乐");
    setFixedSize(350, 400);

    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("输入歌手/歌曲名搜索");
    searchEdit->setFixedHeight(35);

    searchBtn = new QPushButton("搜索", this);
    searchBtn->setFixedHeight(35);
    searchBtn->setStyleSheet("background-color:#165DFF; color:white; border:none; border-radius:4px;");

    resultList = new QListWidget(this);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(searchEdit);
    topLayout->addWidget(searchBtn);
    topLayout->setSpacing(10);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(resultList);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    connect(searchBtn, &QPushButton::clicked, this, &MusicSearchDialog::onSearchClicked);
    connect(searchEdit, &QLineEdit::returnPressed, this, &MusicSearchDialog::onSearchClicked);

    // 只 connect 一次 finished（避免重复连接）
    connect(searchManager, &QNetworkAccessManager::finished, this, &MusicSearchDialog::onSearchReplyFinished);

    // 点击列表项选择歌曲
    connect(resultList, &QListWidget::itemClicked, this, &MusicSearchDialog::onItemClicked);
}

void MusicSearchDialog::onSearchClicked()
{
    QString keyword = searchEdit->text().trimmed();
    if (keyword.isEmpty()) return;

    QUrl url("http://music.163.com/api/search/get/web");
    QUrlQuery query;
    query.addQueryItem("csrf_token", "");
    query.addQueryItem("hlpretag", "");
    query.addQueryItem("hlposttag", "");
    query.addQueryItem("s", keyword);
    query.addQueryItem("type", "1");
    query.addQueryItem("offset", "0");
    query.addQueryItem("total", "true");
    query.addQueryItem("limit", "10");
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setRawHeader("Referer", "https://music.163.com/");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) Chrome/91.0.4472.124 Safari/537.36");
    searchManager->get(request);
}

void MusicSearchDialog::onSearchReplyFinished(QNetworkReply *reply)
{
    // 确认这是本 searchManager 的回复（此对象只有一个 manager）
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            if (jsonObj.contains("result") && jsonObj["result"].isObject()) {
                QJsonObject resultObj = jsonObj["result"].toObject();
                if (resultObj.contains("songs") && resultObj["songs"].isArray()) {
                    QJsonArray songsArray = resultObj["songs"].toArray();
                    resultList->clear();

                    for (int i = 0; i < songsArray.size(); i++) {
                        QJsonObject songObj = songsArray[i].toObject();
                        QString songId = QString::number(songObj["id"].toInt());
                        QString songName = songObj["name"].toString();

                        QJsonArray arArray = songObj["ar"].toArray();
                        QString singer = "未知歌手";
                        if (!arArray.isEmpty()) {
                            singer = arArray[0].toObject()["name"].toString();
                        }

                        QString playUrl = QString("http://music.163.com/song/media/outer/url?id=%1.mp3").arg(songId);

                        QString displayText = QString("%1 - %2").arg(songName).arg(singer);
                        QListWidgetItem *item = new QListWidgetItem(displayText);
                        // 存储到 UserRole：[id, name, url]
                        QVariantList list;
                        list << songId << songName << playUrl;
                        item->setData(Qt::UserRole, list);
                        resultList->addItem(item);
                    }
                }
            }
        }
    } else {
        qDebug() << "搜索请求错误：" << reply->errorString();
    }
    reply->deleteLater();
}

void MusicSearchDialog::onItemClicked(QListWidgetItem *item)
{
    QVariantList songData = item->data(Qt::UserRole).toList();
    if (songData.size() >= 3) {
        emit songSelected(songData[0].toString(), songData[1].toString(), songData[2].toString());
    }
    close();
}

// ---------------- Widget_funcC_Smart_Home 实现 ----------------
Widget_funcC_Smart_Home::Widget_funcC_Smart_Home(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Widget_funcC_Smart_Home),
      lyricManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);


    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(player);
    player->setPlaylist(playlist);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    lyricTimer = new QTimer(this);
    lyricTimer->setInterval(100);
    connect(lyricTimer, &QTimer::timeout, this, &Widget_funcC_Smart_Home::updateLyric);

    searchDialog = new MusicSearchDialog(this);
    connect(searchDialog, &MusicSearchDialog::songSelected, this, &Widget_funcC_Smart_Home::onSongSelected);

    connect(lyricManager, &QNetworkAccessManager::finished, this, &Widget_funcC_Smart_Home::onLyricReplyFinished);

    ui->label_return_home->setPixmap(QPixmap(":/状态按钮_关"));
    ui->label_run_home->setPixmap(QPixmap(":/状态按钮_关"));

    // 你的按钮连接（保持原有逻辑）
    connect(ui->label_return_home , &Button_home_start::signals_start , this , &Widget_funcC_Smart_Home::slots_button_start);
    connect(ui->label_run_home , &Button_home_start::signals_start , this , &Widget_funcC_Smart_Home::slots_button_start);
    connect(ui->button_sleep, &Button_home_start::signals_start, this, &Widget_funcC_Smart_Home::slots_sleep_get_up);
    connect(ui->button_get_up, &Button_home_start::signals_start, this, &Widget_funcC_Smart_Home::slots_sleep_get_up);
    connect(ui->button_air_conditioner, &Button_home_start::signals_start, this, &Widget_funcC_Smart_Home::slots_air_conditioner);
    connect(ui->button_tv, &Button_home_start::signals_start, this, &Widget_funcC_Smart_Home::slots_tv);
    connect(ui->button_robot, &Button_home_start::signals_start, this, &Widget_funcC_Smart_Home::slots_robot);
    connect(ui->button_toaster, &Button_home_start::signals_start, this, &Widget_funcC_Smart_Home::slots_toaster);
    connect(ui->button_washing_machine, &Button_home_start::signals_start, this, &Widget_funcC_Smart_Home::slots_washing_machine);
    connect(ui->button_wifi, &Button_home_start::signals_start, this, &Widget_funcC_Smart_Home::slots_wifi);

    connect(player, &QMediaPlayer::stateChanged, this, &Widget_funcC_Smart_Home::mediaStateChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &Widget_funcC_Smart_Home::positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &Widget_funcC_Smart_Home::durationChanged);

    connect(ui->sliderProgress, &QSlider::sliderMoved, this, &Widget_funcC_Smart_Home::on_sliderProgress_sliderMoved);
    connect(ui->btnPrev, &QPushButton::clicked, this, &Widget_funcC_Smart_Home::on_btnPrev_clicked);
    connect(ui->btnNext, &QPushButton::clicked, this, &Widget_funcC_Smart_Home::on_btnNext_clicked);
    connect(ui->btnPlayPause, &QPushButton::clicked, this, &Widget_funcC_Smart_Home::on_btnPlayPause_clicked);
    connect(ui->btnCD, &QPushButton::clicked, this, &Widget_funcC_Smart_Home::on_btnCD_clicked);

    // --- ✅ 新增：TCP 客户端初始化 ---
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Widget_funcC_Smart_Home::onReadyRead);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &Widget_funcC_Smart_Home::onDisconnected);
    connectToServer();

}

Widget_funcC_Smart_Home::~Widget_funcC_Smart_Home()
{
    delete ui;
}

void Widget_funcC_Smart_Home::on_btnCD_clicked()
{
    searchDialog->exec();
}

void Widget_funcC_Smart_Home::onSongSelected(QString songId, QString songName, QString playUrl)
{
    // 验证 URL
    QUrl url = QUrl::fromUserInput(playUrl);
    if (!url.isValid()) {
        qDebug() << "无效的播放URL:" << playUrl;
        return;
    }

    // 安全获取新索引：先读当前数量作为新索引位置，然后 addMedia，再取 mediaCount()-1 保证正确
    int newIndex = playlist->mediaCount();
    playlist->addMedia(QMediaContent(url));
    int insertedIndex = playlist->mediaCount() - 1;
    if (insertedIndex < 0) {
        qDebug() << "添加歌曲到播放列表失败:" << songName;
        return;
    }

    // 同步 selectedSongs 列表
    SongInfo info;
    info.songId = songId;
    info.songName = songName;
    info.playUrl = playUrl;
    selectedSongs.append(info);

    // 保证歌词容器有对应 slot
    while (lyrics.size() <= insertedIndex) {
        lyrics.append(QList<QPair<int, QString>>());
    }

    // 切换到新添加的索引并播放
    playlist->setCurrentIndex(insertedIndex);
    ui->labelSongInfo->setText(songName);

    // 请求歌词
    QNetworkRequest request(QUrl(QString("https://music.163.com/api/song/lyric?id=%1&lv=1&kv=1&tv=-1").arg(songId)));
    request.setRawHeader("Referer", "https://music.163.com/");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) Chrome/91.0.4472.124 Safari/537.36");
    lyricManager->get(request);

    // 强制刷新播放（stop -> play）
    player->stop();
    player->play();
    lyricTimer->start();
}

void Widget_funcC_Smart_Home::on_sliderProgress_sliderMoved(int position)
{
    player->setPosition(static_cast<qint64>(position));
}

void Widget_funcC_Smart_Home::on_btnNext_clicked()
{
    int total = playlist->mediaCount();
    if (total == 0) return;

    int currentIndex = playlist->currentIndex();
    if (currentIndex < 0) currentIndex = 0;
    int nextIndex = (currentIndex + 1) % total;

    playlist->setCurrentIndex(nextIndex);

    if (nextIndex < selectedSongs.size()) {
        ui->labelSongInfo->setText(selectedSongs[nextIndex].songName);
        // 请求下一曲歌词（如果有）
        QString songId = selectedSongs[nextIndex].songId;
        QNetworkRequest request(QUrl(QString("https://music.163.com/api/song/lyric?id=%1&lv=1&kv=1&tv=-1").arg(songId)));
        request.setRawHeader("Referer", "https://music.163.com/");
        lyricManager->get(request);
    } else {
        ui->labelSongInfo->setText("未知歌曲");
    }

    player->stop();
    player->play();
}

void Widget_funcC_Smart_Home::on_btnPrev_clicked()
{
    int total = playlist->mediaCount();
    if (total == 0) return;

    int currentIndex = playlist->currentIndex();
    if (currentIndex < 0) currentIndex = 0;
    int prevIndex = (currentIndex - 1 + total) % total;

    playlist->setCurrentIndex(prevIndex);

    if (prevIndex < selectedSongs.size()) {
        ui->labelSongInfo->setText(selectedSongs[prevIndex].songName);
        QString songId = selectedSongs[prevIndex].songId;
        QNetworkRequest request(QUrl(QString("https://music.163.com/api/song/lyric?id=%1&lv=1&kv=1&tv=-1").arg(songId)));
        request.setRawHeader("Referer", "https://music.163.com/");
        lyricManager->get(request);
    } else {
        ui->labelSongInfo->setText("未知歌曲");
    }

    player->stop();
    player->play();
}

void Widget_funcC_Smart_Home::on_btnPlayPause_clicked()
{
    // 切换播放/暂停。注意：部分后端对网络流不支持 pause，这里若 pause 无效会 fallback 到 stop()
    if (player->state() == QMediaPlayer::PlayingState) {
        player->pause();
        // 异步 stateChanged，某些后端 pause 可能不生效，尝试在短时内 fallback（这里直接调用 stop 可能会中断但稳妥）
        // 不立即强制 stop，先暂停并停止歌词计时器；若你发现仍无法暂停，可把下一行取消注释以强制 stop：
        // player->stop();
        lyricTimer->stop();
    } else {
        if (playlist->currentIndex() == -1 && playlist->mediaCount() > 0) {
            playlist->setCurrentIndex(0);
        }
        player->play();
        lyricTimer->start();
    }
}

void Widget_funcC_Smart_Home::mediaStateChanged(QMediaPlayer::State state)
{
    ui->btnPlayPause->setText(state == QMediaPlayer::PlayingState ? "暂停" : "播放");
}

void Widget_funcC_Smart_Home::positionChanged(qint64 position)
{
    ui->sliderProgress->setValue(static_cast<int>(position));
}

void Widget_funcC_Smart_Home::durationChanged(qint64 duration)
{
    ui->sliderProgress->setRange(0, static_cast<int>(duration));
}

void Widget_funcC_Smart_Home::onLyricReplyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();

            // 当接口返回 code != 200 时处理
            if (jsonObj.contains("code") && jsonObj["code"].toInt() != 200) {
                qDebug() << "歌词请求失败，错误码：" << jsonObj["code"].toInt();
                int currentIndex = playlist->currentIndex();
                if (currentIndex >= 0) {
                    while (lyrics.size() <= currentIndex) lyrics.append(QList<QPair<int, QString>>());
                    lyrics[currentIndex].clear();
                    lyrics[currentIndex].append(QPair<int, QString>(0, "无法获取歌词"));
                }
                reply->deleteLater();
                return;
            }

            if (jsonObj.contains("lrc") && jsonObj["lrc"].isObject()) {
                QJsonObject lrcObj = jsonObj["lrc"].toObject();
                if (lrcObj.contains("lyric") && lrcObj["lyric"].isString()) {
                    QString lyricText = lrcObj["lyric"].toString();
                    QList<QPair<int, QString>> songLyrics;
                    QStringList lines = lyricText.split("\n");
                    QRegExp rx("\\[(\\d+):(\\d+).(\\d+)\\](.*)");

                    foreach (QString line, lines) {
                        if (rx.indexIn(line) != -1) {
                            int minute = rx.cap(1).toInt();
                            int second = rx.cap(2).toInt();
                            int msec = rx.cap(3).toInt() / 10;
                            int time = minute * 60 * 1000 + second * 1000 + msec;
                            QString lyric = rx.cap(4).trimmed();
                            if (!lyric.isEmpty()) {
                                songLyrics.append(QPair<int, QString>(time, lyric));
                            }
                        }
                    }

                    int currentIndex = playlist->currentIndex();
                    if (currentIndex >= 0) {
                        while (lyrics.size() <= currentIndex) lyrics.append(QList<QPair<int, QString>>());
                        lyrics[currentIndex] = songLyrics;
                        qDebug() << "解析歌词成功，共" << songLyrics.size() << "行";
                    }
                } else {
                    int currentIndex = playlist->currentIndex();
                    if (currentIndex >= 0) {
                        while (lyrics.size() <= currentIndex) lyrics.append(QList<QPair<int, QString>>());
                        lyrics[currentIndex].clear();
                        lyrics[currentIndex].append(QPair<int, QString>(0, "暂无歌词"));
                    }
                }
            }
        }
    } else {
        int currentIndex = playlist->currentIndex();
        if (currentIndex >= 0) {
            while (lyrics.size() <= currentIndex) lyrics.append(QList<QPair<int, QString>>());
            lyrics[currentIndex].clear();
            lyrics[currentIndex].append(QPair<int, QString>(0, "歌词加载失败"));
        }
        qDebug() << "歌词请求错误：" << reply->errorString();
    }
    reply->deleteLater();
}

void Widget_funcC_Smart_Home::updateLyric()
{
    int currentIndex = playlist->currentIndex();
    if (currentIndex < 0 || currentIndex >= lyrics.size()) {
        ui->labelLyric->setText("请选择歌曲");
        return;
    }

    qint64 currentTime = player->position();
    const QList<QPair<int, QString>>& currentLyrics = lyrics[currentIndex];

    if (currentLyrics.isEmpty()) {
        ui->labelLyric->setText("暂无歌词");
        return;
    }

    QString displayLyric = currentLyrics[0].second;
    for (int i = currentLyrics.size() - 1; i >= 0; i--) {
        if (currentLyrics[i].first <= currentTime) {
            displayLyric = currentLyrics[i].second;
            break;
        }
    }

    ui->labelLyric->setText(displayLyric);
}

// 其余智能家居槽按你原逻辑保持
void Widget_funcC_Smart_Home::slots_button_start(bool start)
{
    QObject * temp = sender();
    if(temp == ui->label_run_home)
    {
        ui->label_run_home->set_start(start);
        ui->label_return_home->set_start(!start);
    }
    if(temp == ui->label_return_home)
    {
        ui->label_return_home->set_start(start);
        ui->label_run_home->set_start(!start);
    }
}

void Widget_funcC_Smart_Home::slots_sleep_get_up(bool start)
{
    QObject *temp = sender();
    if (temp == ui->button_sleep)
    {
        ui->button_sleep->set_start(start);
        ui->button_get_up->set_start(!start);
    }
    if (temp == ui->button_get_up)
    {
        ui->button_get_up->set_start(start);
        ui->button_sleep->set_start(!start);
    }
}

void Widget_funcC_Smart_Home::connectToServer()
{
    if (tcpSocket->state() == QAbstractSocket::ConnectedState)
        return;

    qDebug() << "正在连接服务器..." << serverIP << ":" << serverPort;
    tcpSocket->connectToHost(QHostAddress(serverIP), serverPort);

    if (!tcpSocket->waitForConnected(3000)) {
        qDebug() << "连接服务器失败：" << tcpSocket->errorString();
    } else {
        qDebug() << "✅ 已连接服务器";
    }
}

void Widget_funcC_Smart_Home::onDisconnected()
{
    qDebug() << "⚠️ 服务器连接断开，尝试重连...";
    QTimer::singleShot(2000, this, &Widget_funcC_Smart_Home::connectToServer);
}

void Widget_funcC_Smart_Home::sendMessage(const QString &msg)
{
    if (tcpSocket->state() != QAbstractSocket::ConnectedState) {
        connectToServer();
        qDebug() << "服务器未连接，正在重连...";
        return;
    }

       QTextCodec *codec = QTextCodec::codecForName("GBK");  // 转GBK编码
       QByteArray data = codec->fromUnicode(msg + "\r\n");    // 加上换行，调试助手友好显示
       tcpSocket->write(data);
       tcpSocket->flush();
    qDebug() << "📤 已发送消息：" << msg;
}

void Widget_funcC_Smart_Home::onReadyRead()
{
    QByteArray data = tcpSocket->readAll();
    QTextCodec *codec = QTextCodec::codecForName("GBK");  // 按GBK解析
    QString msg = codec->toUnicode(data).trimmed();

    handleReceivedCommand(msg);
}


void Widget_funcC_Smart_Home::handleReceivedCommand(const QString &msg)
{
    QString text = msg;
    text.replace("\r", "").replace("\n", "").replace(" ", "");

    qDebug() << "📩 处理指令:" << text;

    bool on = false;
    if (text.contains(QRegExp("开|开启"))) on = true;
    if (text.contains(QRegExp("关|关闭"))) on = false;

    if (text.contains("空调")) ui->button_air_conditioner->set_start(on);
    else if (text.contains("电视")) ui->button_tv->set_start(on);
    else if (text.contains("机器人")) ui->button_robot->set_start(on);
    else if (text.contains("烤面包机")) ui->button_toaster->set_start(on);
    else if (text.contains("洗衣机")) ui->button_washing_machine->set_start(on);
    else if (text.contains("WIFI") || text.contains("wifi")) ui->button_wifi->set_start(on);
    else qDebug() << "⚠️ 未匹配到已知设备";
}






// ---------------- 家居功能按钮槽修改 ----------------
void Widget_funcC_Smart_Home::slots_air_conditioner(bool start)
{
    QString msg = QString("空调: %1").arg(start ? "开启" : "关闭");
    sendMessage(msg);
    qDebug() << msg;
}

void Widget_funcC_Smart_Home::slots_tv(bool start)
{
    QString msg = QString("电视: %1").arg(start ? "开启" : "关闭");
    sendMessage(msg);
    qDebug() << msg;
}

void Widget_funcC_Smart_Home::slots_robot(bool start)
{
    QString msg = QString("机器人: %1").arg(start ? "开启" : "关闭");
    sendMessage(msg);
    qDebug() << msg;
}

void Widget_funcC_Smart_Home::slots_toaster(bool start)
{
    QString msg = QString("烤面包机: %1").arg(start ? "开启" : "关闭");
    sendMessage(msg);
    qDebug() << msg;
}

void Widget_funcC_Smart_Home::slots_washing_machine(bool start)
{
    QString msg = QString("洗衣机: %1").arg(start ? "开启" : "关闭");
    sendMessage(msg);
    qDebug() << msg;
}

void Widget_funcC_Smart_Home::slots_wifi(bool start)
{
    QString msg = QString("WIFI: %1").arg(start ? "开启" : "关闭");
    sendMessage(msg);
    qDebug() << msg;
}

void Widget_funcC_Smart_Home::slots_button_send_message()
{
    // 预留函数
}

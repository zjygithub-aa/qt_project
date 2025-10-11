#ifndef WIDGET_FUNCC_SMART_HOME_H
#define WIDGET_FUNCC_SMART_HOME_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRegExp>
#include <QUrlQuery>
#include <QTcpSocket>
#include <QHostAddress>
#include <QLabel>
#include "button_home_start.h"

// 自定义歌曲信息结构体
struct SongInfo {
    QString songId;
    QString songName;
    QString playUrl;
};

namespace Ui {
class Widget_funcC_Smart_Home;
}

// 搜索对话框
class MusicSearchDialog : public QDialog {
    Q_OBJECT
public:
    explicit MusicSearchDialog(QWidget *parent = nullptr);
    ~MusicSearchDialog() = default;

signals:
    void songSelected(QString songId, QString songName, QString playUrl);

private slots:
    void onSearchClicked();
    void onSearchReplyFinished(QNetworkReply *reply);
    void onItemClicked(QListWidgetItem *item);

private:
    QLineEdit *searchEdit;
    QPushButton *searchBtn;
    QListWidget *resultList;
    QNetworkAccessManager *searchManager;
};

// 智能家居主界面
class Widget_funcC_Smart_Home : public QWidget {
    Q_OBJECT

public:
    explicit Widget_funcC_Smart_Home(QWidget *parent = nullptr);
    ~Widget_funcC_Smart_Home();

private slots:
    // 智能家居按钮槽函数
    void slots_button_start(bool start);
    void slots_button_send_message();
    void slots_sleep_get_up(bool start);
    void slots_air_conditioner(bool start);
    void slots_tv(bool start);
    void slots_robot(bool start);
    void slots_toaster(bool start);
    void slots_washing_machine(bool start);
    void slots_wifi(bool start);

    // 音乐相关槽函数
    void on_btnCD_clicked();
    void on_sliderProgress_sliderMoved(int position);
    void on_btnPrev_clicked();
    void on_btnNext_clicked();
    void on_btnPlayPause_clicked();
    void mediaStateChanged(QMediaPlayer::State state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void updateLyric();
    void onLyricReplyFinished(QNetworkReply *reply);
    void onSongSelected(QString songId, QString songName, QString playUrl);

    // TCP 相关
    void connectToServer();
    void onReadyRead();
    void onDisconnected();
    void handleReceivedCommand(const QString &msg);

private:
    Ui::Widget_funcC_Smart_Home *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QTimer *lyricTimer;
    QNetworkAccessManager *lyricManager;
    MusicSearchDialog *searchDialog;

    QList<SongInfo> selectedSongs;
    QList<QList<QPair<int, QString>>> lyrics;

    // TCP 控制核心
    QTcpSocket *tcpSocket;
    QString serverIP = "127.0.0.1";
    quint16 serverPort = 12345;

    void sendMessage(const QString &msg);

    // --- 新增：设备状态（保证来回切换） ---
    bool air_on = false;
    bool tv_on = false;
    bool robot_on = false;
    bool toaster_on = false;
    bool washing_on = false;
    bool wifi_on = false;
    bool home_on = true;
    bool led_on = true;

    // 图片更新函数（在 cpp 中实现）
    void updateDeviceIcon(QLabel *label, const QString &baseName, bool on);
    void updateSpecialIcon(QLabel *label, const QString &baseName, bool on);
    void toggleHome();
    void toggleLed();
    void initSpecialIcons();
};

#endif // WIDGET_FUNCC_SMART_HOME_H

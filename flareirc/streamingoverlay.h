#ifndef STREAMINGOVERLAY_H
#define STREAMINGOVERLAY_H

#include <QWidget>
#include <QTimer>
#include <QSettings>
#include <QFont>
#include <QHash>
#include <QStringList>

class QLabel;
class QPaintEvent;
class QMouseEvent;
class QPropertyAnimation;

struct AlertTypeInfo {
    QString icon;
    QString color;
    QString displayName;
};

class StreamingOverlay : public QWidget
{
    Q_OBJECT

public:
    explicit StreamingOverlay(QWidget *parent = 0);
    ~StreamingOverlay();

    void showAlert(const QString &type, const QString &user, const QString &message);

    void setOpacity(qreal opacity);
    void setFontSize(int pointSize);
    void setPosition(int x, int y);
    void setAlertTypes(const QStringList &types);

    qreal opacity() const { return m_opacity; }
    int fontSize() const { return m_fontSize; }
    QPoint position() const { return m_position; }
    QStringList alertTypes() const { return m_enabledAlertTypes; }

    void enableAlertType(const QString &type, bool enabled);
    bool isAlertTypeEnabled(const QString &type) const;

    void setEnabled(bool enabled);
    bool isEnabled() const { return m_enabled; }

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void onAlertTimeout();

private:
    void setupUI();
    void applyStyles();
    QWidget* createAlertWidget(const QString &type, const QString &user, const QString &message);
    void positionAlertWidget(QWidget *alert);
    void saveSettings();
    void loadSettings();

    QLabel *m_alertLabel;
    QTimer *m_alertTimer;
    int m_alertDuration;

    QSettings m_settings;

    bool m_enabled;
    qreal m_opacity;
    int m_fontSize;
    QPoint m_position;
    QStringList m_enabledAlertTypes;

    QHash<QString, AlertTypeInfo> m_alertTypeMap;
    QPoint m_dragPosition;
};

#endif // STREAMINGOVERLAY_H

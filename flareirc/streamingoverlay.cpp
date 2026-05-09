#include "streamingoverlay.h"
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QEasingCurve>

StreamingOverlay::StreamingOverlay(QWidget *parent)
    : QWidget(parent),
      m_alertLabel(0),
      m_alertTimer(new QTimer(this)),
      m_alertDuration(5000),
      m_enabled(true),
      m_opacity(0.85),
      m_fontSize(24),
      m_position(100, 100)
{
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);

    m_alertTypeMap["bits"] = { ":/icons/bits.png", "#9146FF", "Bits" };
    m_alertTypeMap["subscription"] = { ":/icons/sub.png", "#9447FF", "Subscription" };
    m_alertTypeMap["membership"] = { ":/icons/member.png", "#FF4500", "Membership" };
    m_alertTypeMap["donation"] = { ":/icons/donate.png", "#00CC66", "Donation" };

    m_enabledAlertTypes = m_alertTypeMap.keys();

    loadSettings();

    setWindowOpacity(m_opacity);
    resize(400, 100);
    move(m_position);

    setupUI();

    connect(m_alertTimer, SIGNAL(timeout()), this, SLOT(onAlertTimeout()));
}

StreamingOverlay::~StreamingOverlay()
{
    saveSettings();
}

void StreamingOverlay::setupUI()
{
    m_alertLabel = new QLabel(this);
    m_alertLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_alertLabel->setGeometry(10, 10, width() - 20, height() - 20);
    m_alertLabel->setWordWrap(true);
    m_alertLabel->setMargin(10);
    m_alertLabel->hide();

    applyStyles();
}

void StreamingOverlay::applyStyles()
{
    QFont font;
    font.setPointSize(m_fontSize);
    font.setBold(true);
    m_alertLabel->setFont(font);
}

void StreamingOverlay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (!m_alertLabel->isVisible())
        return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor bgColor(0, 0, 0, static_cast<int>(m_opacity * 200));
    QRect rect = m_alertLabel->geometry().adjusted(-5, -5, 5, 5);
    painter.setBrush(bgColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect, 10, 10);
}

void StreamingOverlay::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void StreamingOverlay::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - m_dragPosition);
        event->accept();
    }
}

void StreamingOverlay::showAlert(const QString &type, const QString &user, const QString &message)
{
    if (!m_enabled) {
        return;
    }

    if (!isAlertTypeEnabled(type)) {
        return;
    }

    m_alertTimer->stop();

    if (m_alertLabel->isVisible()) {
        m_alertLabel->hide();
    }

    AlertTypeInfo info = m_alertTypeMap[type];
    QString formattedText = QString("<html><body style='margin:0;padding:0;'>"
                                    "<span style='color:%1; font-weight:bold; font-size:%2pt;'>%3</span>"
                                    "<span style='color: white;'> - %4</span>"
                                    "</body></html>")
                                .arg(info.color)
                                .arg(m_fontSize + 4)
                                .arg(user)
                                .arg(message);

    m_alertLabel->setText(formattedText);
    m_alertLabel->adjustSize();

    int labelWidth = m_alertLabel->width();
    int labelHeight = m_alertLabel->height();

    int totalWidth = qMax(labelWidth + 40, 350);
    int totalHeight = qMax(labelHeight + 40, 80);

    resize(totalWidth, totalHeight);

    QWidget *parentWin = parentWidget();
    QPoint screenPos;
    if (parentWin) {
        screenPos = parentWin->mapToGlobal(QPoint(50, 50));
    } else {
        screenPos = QPoint(100, 100);
    }

    move(screenPos);

    setWindowOpacity(m_opacity);
    m_alertLabel->show();
    raise();
    activateWindow();

    m_alertTimer->start(m_alertDuration);
}

void StreamingOverlay::onAlertTimeout()
{
    m_alertTimer->stop();

    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(m_opacity);
    animation->setEndValue(0.0);
    animation->setEasingCurve(QEasingCurve::OutQuad);

    connect(animation, SIGNAL(finished()), this, SLOT(hide()));
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    m_alertLabel->hide();
}

void StreamingOverlay::setOpacity(qreal opacity)
{
    m_opacity = qBound(0.0, opacity, 1.0);
    setWindowOpacity(m_opacity);
    saveSettings();
}

void StreamingOverlay::setFontSize(int pointSize)
{
    m_fontSize = qMax(8, pointSize);
    applyStyles();
    saveSettings();
}

void StreamingOverlay::setPosition(int x, int y)
{
    m_position = QPoint(x, y);
    move(m_position);
    saveSettings();
}

void StreamingOverlay::setAlertTypes(const QStringList &types)
{
    m_enabledAlertTypes = types;
    saveSettings();
}

void StreamingOverlay::enableAlertType(const QString &type, bool enabled)
{
    if (m_enabledAlertTypes.contains(type) && !enabled) {
        m_enabledAlertTypes.removeAll(type);
    } else if (!m_enabledAlertTypes.contains(type) && enabled) {
        m_enabledAlertTypes.append(type);
    }
    saveSettings();
}

bool StreamingOverlay::isAlertTypeEnabled(const QString &type) const
{
    return m_enabledAlertTypes.contains(type);
}

void StreamingOverlay::setEnabled(bool enabled)
{
    m_enabled = enabled;
    if (!enabled && m_alertLabel->isVisible()) {
        m_alertLabel->hide();
        m_alertTimer->stop();
    }
    saveSettings();
}

void StreamingOverlay::saveSettings()
{
    m_settings.beginGroup("StreamingOverlay");
    m_settings.setValue("Enabled", m_enabled);
    m_settings.setValue("Opacity", m_opacity);
    m_settings.setValue("FontSize", m_fontSize);
    m_settings.setValue("PositionX", m_position.x());
    m_settings.setValue("PositionY", m_position.y());
    m_settings.setValue("EnabledAlertTypes", m_enabledAlertTypes);
    m_settings.endGroup();
}

void StreamingOverlay::loadSettings()
{
    m_settings.beginGroup("StreamingOverlay");
    m_enabled = m_settings.value("Enabled", true).toBool();
    m_opacity = m_settings.value("Opacity", 0.85).toReal();
    m_fontSize = m_settings.value("FontSize", 24).toInt();
    m_position = QPoint(
        m_settings.value("PositionX", 100).toInt(),
        m_settings.value("PositionY", 100).toInt()
    );
    m_enabledAlertTypes = m_settings.value("EnabledAlertTypes", m_alertTypeMap.keys()).toStringList();
    m_settings.endGroup();
}

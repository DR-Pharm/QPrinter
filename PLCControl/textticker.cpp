#include "textticker.h"
#include <QPainter>
#include <QTimer>
TextTicker::TextTicker(QWidget *parent)
    : QLabel(parent)
{
    setMinimumWidth(200);
    setMinimumHeight(40);
    m_curIndex = 0;//当前角码
    m_showText = QString::fromLocal8Bit("设备运行正常~");//显示的文字
    m_charWidth = 18;//fontMetrics().width("设备运行正常")/6;//每个字符的宽度
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TextTicker::updateIndex);
    timer->start(500);
}
TextTicker::~TextTicker()
{
}
void TextTicker::paintEvent(QPaintEvent *event)
{
    //__super::paintEvent(event);
    QPainter painter(this);
    painter.drawText(0, 30, m_showText.mid(m_curIndex));
    painter.drawText(width() - m_charWidth * m_curIndex, 30, m_showText.left(m_curIndex));
}
void TextTicker::updateIndex()
{
    update();
    m_curIndex++;
    if (m_curIndex*m_charWidth > width())
        m_curIndex = 0;
}

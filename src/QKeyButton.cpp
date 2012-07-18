#include "QKeyButton.h"

#include <QPainter>
#include <QSizePolicy>

QKeyButton::QKeyButton(QString firstLabel, QString secondLabel, QWidget *parent) :
    QAbstractButton(parent),
    m_firstLabel(firstLabel),
    m_secondLabel(secondLabel),
    m_switched(false)
{
    setText(m_firstLabel);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

bool QKeyButton::isSwitched()
{
    return m_switched;
}

void QKeyButton::switchLabel()
{
    if(m_switched)
        setText(m_firstLabel);
    else
        setText(m_secondLabel);

    m_switched = !m_switched;
}

void QKeyButton::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QFont font;
    font.setPointSize(18);
    painter.setFont(font);

    QRectF rect(0, 0, width() - 1, height() - 1);
    if(isDown())
    {
        painter.fillRect(rect, QColor(255, 255, 255));
        painter.setPen(QColor(0, 0, 0));
    }
    else
    {
        painter.fillRect(rect, QColor(0, 0, 0));
        painter.setPen(QColor(255, 255, 255));
    }

    painter.drawRect(rect);
    painter.drawText(rect, Qt::AlignCenter, text());
}

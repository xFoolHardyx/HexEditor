#include "hexeditui.h"

HexEditUI::HexEditUI(QWidget *parent) : QAbstractScrollArea(parent) {
    setFont(QFont("Courier", 10));

    m_nIndent = 0;
    m_nSpaceNewSymbol = (fontMetrics().width(QLatin1Char('9')) + 2) * 2 + 5;

    setHeaderLayout();
    setAddrLayout();
    setHexLayout();
    setAsciiLayout();
}

HexEditUI::~HexEditUI() {
}

void HexEditUI::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(viewport());
    if (m_HeaderArea.bIsSet) {
        paintLayout(painter, m_HeaderArea);
        painter.setPen(Qt::black);
        for (unsigned i = 0; i < 0xF; i++)
            painter.drawText(m_AddrArea.nWidth  + m_nSpaceNewSymbol * i, m_HeaderArea.nHeight - 3 , QString::number(i,16).toUpper());
    }
    if (m_AddrArea.bIsSet) paintLayout(painter, m_AddrArea);
    if (m_HexArea.bIsSet) paintLayout(painter, m_HexArea);
    if (m_AsciiArea.bIsSet) paintLayout(painter, m_AsciiArea);

    painter.drawLine(0, m_HeaderArea.nHeight, width(), m_HeaderArea.nHeight);
    painter.drawLine(m_AddrArea.nWidth, 0, m_AddrArea.nWidth, height());
    painter.drawLine(m_AddrArea.nWidth + m_HexArea.nWidth, 0, m_AddrArea.nWidth + m_HexArea.nWidth, height());
}

void HexEditUI::update() {
    viewport()->update();
}

void HexEditUI::paintLayout(QPainter &rPainter, Layout &rLayout) {
    rPainter.fillRect(rLayout.nPosX, rLayout.nPosY, rLayout.nWidth, rLayout.nHeight, rLayout.Color);
}

void HexEditUI::resizeEvent(QResizeEvent *event) {
    m_HeaderArea.nWidth = width();
    m_AddrArea.nHeight = height() - m_HeaderArea.nHeight;
    m_HexArea.nHeight = height() - m_HeaderArea.nHeight;
    m_AsciiArea.nHeight = height() - m_HeaderArea.nHeight;
    m_AsciiArea.nWidth = width() - m_AsciiArea.nWidth;
}

void HexEditUI::setHeaderLayout() {
    m_HeaderArea.Color = Qt::gray;
    m_HeaderArea.nPosX = 0;
    m_HeaderArea.nPosY = 0;
    m_HeaderArea.nHeight = fontMetrics().height() + m_nIndent;
    m_HeaderArea.bIsSet = true;
}

void HexEditUI::setAddrLayout()
{
    m_AddrArea.Color = Qt::lightGray;
    m_AddrArea.nPosX = 0;
    m_AddrArea.nPosY = m_HeaderArea.nHeight;
    m_AddrArea.nWidth = (fontMetrics().width(QLatin1Char('9')) + 1) * 10 + m_nIndent;
    m_AddrArea.bIsSet = true;
}

void HexEditUI::setHexLayout()
{
    m_HexArea.Color = Qt::white;
    m_HexArea.nPosX = m_AddrArea.nWidth;
    m_HexArea.nPosY = m_HeaderArea.nHeight;
    m_HexArea.nWidth = m_nSpaceNewSymbol * 0xF + m_nIndent;
    m_HexArea.bIsSet = true;
}

void HexEditUI::setAsciiLayout()
{
    m_AsciiArea.Color = Qt::lightGray;
    m_AsciiArea.nPosX = m_AddrArea.nWidth + m_HexArea.nWidth;
    m_AsciiArea.nPosY = m_HeaderArea.nHeight;
    m_AsciiArea.bIsSet = true;
}

#ifndef HEXEDITUI_H
#define HEXEDITUI_H

#include <QAbstractScrollArea>
#include <QPainter>
#include <QScrollBar>

struct Layout {
    int nPosX;
    int nPosY;
    int nHeight;
    int nWidth;
    bool bIsSet;
    QColor Color;
};

class HexEditUI : public QAbstractScrollArea
{
public:
    explicit HexEditUI(QWidget *parent = 0);
    ~HexEditUI();
    
signals:
    
public slots:

private:

    void paintEvent(QPaintEvent * event);
    void update();
    void paintLayout(QPainter & rPainter, Layout & rLayout);
    void resizeEvent(QResizeEvent * event);
    void setHeaderLayout();
    void setAddrLayout();
    void setHexLayout();
    void setAsciiLayout();


    unsigned m_nRowCountHexArea;
    unsigned m_nColCountHexArea;

    Layout m_HeaderArea;
    Layout m_AddrArea;
    Layout m_HexArea;
    Layout m_AsciiArea;

    unsigned m_nGlyphHeight;
    unsigned m_nGlyphWidth;

    int m_nIndent;
    int m_nSpaceNewSymbol;

};

#endif // HEXEDITUI_H

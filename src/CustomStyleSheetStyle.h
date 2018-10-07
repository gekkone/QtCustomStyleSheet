#ifndef CUSTOMSTYLESHEETSTYLE_H
#define CUSTOMSTYLESHEETSTYLE_H

#include <QStyleOption>
#include <QHash>
#include <QEvent>
#include <QVector>
#include <QApplication>
#include "CssParser.h"
#include <QBrush>
#include <QSet>
#include <QWindowsStyle>

class QRenderRule;
class QAbstractScrollArea;
class QStyleSheetStylePrivate;
class QStyleOptionTitleBar;

class CustomStyleSheetStyle : public QWindowsStyle
{
    typedef QWindowsStyle ParentStyle;

    Q_OBJECT
public:
    CustomStyleSheetStyle(QStyle *baseStyle = NULL);
    ~CustomStyleSheetStyle();

    void setRecursiveStyle(QWidget *_widget);

    void drawComplexControl(ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p,
                            const QWidget *w = 0) const;
    void drawControl(ControlElement element, const QStyleOption *opt, QPainter *p,
                     const QWidget *w = 0) const;
    void drawItemPixmap(QPainter *painter, const QRect &rect, int alignment, const QPixmap &pixmap) const;
    void drawItemText(QPainter *painter, const QRect& rect, int alignment, const QPalette &pal,
              bool enabled, const QString& text, QPalette::ColorRole textRole  = QPalette::NoRole) const;
    void drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p,
                       const QWidget *w = 0) const;
    QPixmap generatedIconPixmap(QIcon::Mode iconMode, const QPixmap &pixmap,
                                const QStyleOption *option) const;
    SubControl hitTestComplexControl(ComplexControl cc, const QStyleOptionComplex *opt,
                                     const QPoint &pt, const QWidget *w = 0) const;
    QRect itemPixmapRect(const QRect &rect, int alignment, const QPixmap &pixmap) const;
    QRect itemTextRect(const QFontMetrics &metrics, const QRect &rect, int alignment, bool enabled,
                       const QString &text) const;
    int pixelMetric(PixelMetric metric, const QStyleOption *option = 0, const QWidget *widget = 0) const;
    void polish(QWidget *widget);
    void polish(QApplication *app);
    void polish(QPalette &pal);
    QSize sizeFromContents(ContentsType ct, const QStyleOption *opt,
                           const QSize &contentsSize, const QWidget *widget = 0) const;
    QPalette standardPalette() const;
    QPixmap standardPixmap(StandardPixmap standardPixmap, const QStyleOption *option = 0,
                           const QWidget *w = 0 ) const;
    int layoutSpacing(QSizePolicy::ControlType control1, QSizePolicy::ControlType control2,
                          Qt::Orientation orientation, const QStyleOption *option = 0,
                          const QWidget *widget = 0) const;
    int styleHint(StyleHint sh, const QStyleOption *opt = 0, const QWidget *w = 0,
                  QStyleHintReturn *shret = 0) const;
    QRect subElementRect(SubElement r, const QStyleOption *opt, const QWidget *widget = 0) const;
    QRect subControlRect(ComplexControl cc, const QStyleOptionComplex *opt, SubControl sc,
                         const QWidget *w = 0) const;

    // These functions are called from QApplication/QWidget. Be careful.
    QStyle *baseStyle() const;
    void repolish(QWidget *widget);
    void repolish(QApplication *app);

    void unpolish(QWidget *widget);
    void unpolish(QApplication *app);

    QStyle *base;
    void ref() { ++refcount; }
    void deref() { Q_ASSERT(refcount > 0); if (!--refcount) delete this; }

    void updateStyleSheetFont(QWidget* w) const;
    void saveWidgetFont(QWidget* w, const QFont& font) const;
    void clearWidgetFont(QWidget* w) const;

    bool styleSheetPalette(const QWidget* w, const QStyleOption* opt, QPalette* pal);

    void setStyleSheet(const QString stylesheet);

protected Q_SLOTS:
    QIcon standardIconImplementation(StandardPixmap standardIcon, const QStyleOption *opt = 0,
                                     const QWidget *widget = 0) const;
    int layoutSpacingImplementation(QSizePolicy::ControlType control1,
                                    QSizePolicy::ControlType control2,
                                    Qt::Orientation orientation,
                                    const QStyleOption *option = 0,
                                    const QWidget *widget = 0) const;

protected:
    bool event(QEvent *e);

private:
    int refcount;

    friend class QRenderRule;
    int nativeFrameWidth(const QWidget *);
    QRenderRule renderRule(const QWidget *, int, quint64 = 0) const;
    QRenderRule renderRule(const QWidget *, const QStyleOption *, int = 0) const;
    QSize defaultSize(const QWidget *, QSize, const QRect&, int) const;
    QRect positionRect(const QWidget *, const QRenderRule&, const QRenderRule&, int,
                       const QRect&, Qt::LayoutDirection) const;
    QRect positionRect(const QWidget *w, const QRenderRule &rule2, int pe,
                       const QRect &originRect, Qt::LayoutDirection dir) const;

    mutable QCss::Parser parser;

    void setPalette(QWidget *);
    void unsetPalette(QWidget *);
    void setProperties(QWidget *);
    void setGeometry(QWidget *);
    QVector<QCss::StyleRule> styleRules(const QWidget *w) const;
    bool hasStyleRule(const QWidget *w, int part) const;

    QHash<QStyle::SubControl, QRect> titleBarLayout(const QWidget *w, const QStyleOptionTitleBar *tb) const;

//    QCss::StyleSheet getDefaultStyleSheet() const;

    static Qt::Alignment resolveAlignment(Qt::LayoutDirection, Qt::Alignment);
    static bool isNaturalChild(const QWidget *w);
    bool initWidget(const QWidget *w) const;
public:
    static int numinstances;

private:
    Q_DISABLE_COPY(CustomStyleSheetStyle)
//    Q_DECLARE_PRIVATE(QStyleSheetStyle)

    enum {
        windowsItemFrame        =  2, // menu item frame width
        windowsSepHeight        =  9, // separator item height
        windowsItemHMargin      =  3, // menu item hor text margin
        windowsItemVMargin      =  2, // menu item ver text margin
        windowsArrowHMargin     =  6, // arrow horizontal margin
        windowsRightBorder      = 15, // right border on windows
        windowsCheckMarkWidth   = 12  // checkmarks width on windows
    };

    QString m_stylesheet;
};



enum PseudoElement {
    PseudoElement_None,
    PseudoElement_DownArrow,
    PseudoElement_UpArrow,
    PseudoElement_LeftArrow,
    PseudoElement_RightArrow,
    PseudoElement_Indicator,
    PseudoElement_ExclusiveIndicator,
    PseudoElement_PushButtonMenuIndicator,
    PseudoElement_ComboBoxDropDown,
    PseudoElement_ComboBoxArrow,
    PseudoElement_Item,
    PseudoElement_SpinBoxUpButton,
    PseudoElement_SpinBoxUpArrow,
    PseudoElement_SpinBoxDownButton,
    PseudoElement_SpinBoxDownArrow,
    PseudoElement_GroupBoxTitle,
    PseudoElement_GroupBoxIndicator,
    PseudoElement_ToolButtonMenu,
    PseudoElement_ToolButtonMenuArrow,
    PseudoElement_ToolButtonDownArrow,
    PseudoElement_ToolBoxTab,
    PseudoElement_ScrollBarSlider,
    PseudoElement_ScrollBarAddPage,
    PseudoElement_ScrollBarSubPage,
    PseudoElement_ScrollBarAddLine,
    PseudoElement_ScrollBarSubLine,
    PseudoElement_ScrollBarFirst,
    PseudoElement_ScrollBarLast,
    PseudoElement_ScrollBarUpArrow,
    PseudoElement_ScrollBarDownArrow,
    PseudoElement_ScrollBarLeftArrow,
    PseudoElement_ScrollBarRightArrow,
    PseudoElement_SplitterHandle,
    PseudoElement_ToolBarHandle,
    PseudoElement_ToolBarSeparator,
    PseudoElement_MenuScroller,
    PseudoElement_MenuTearoff,
    PseudoElement_MenuCheckMark,
    PseudoElement_MenuSeparator,
    PseudoElement_MenuIcon,
    PseudoElement_MenuRightArrow,
    PseudoElement_TreeViewBranch,
    PseudoElement_HeaderViewSection,
    PseudoElement_HeaderViewUpArrow,
    PseudoElement_HeaderViewDownArrow,
    PseudoElement_ProgressBarChunk,
    PseudoElement_TabBarTab,
    PseudoElement_TabBarScroller,
    PseudoElement_TabBarTear,
    PseudoElement_SliderGroove,
    PseudoElement_SliderHandle,
    PseudoElement_SliderAddPage,
    PseudoElement_SliderSubPage,
    PseudoElement_SliderTickmark,
    PseudoElement_TabWidgetPane,
    PseudoElement_TabWidgetTabBar,
    PseudoElement_TabWidgetLeftCorner,
    PseudoElement_TabWidgetRightCorner,
    PseudoElement_DockWidgetTitle,
    PseudoElement_DockWidgetCloseButton,
    PseudoElement_DockWidgetFloatButton,
    PseudoElement_DockWidgetSeparator,
    PseudoElement_MdiCloseButton,
    PseudoElement_MdiMinButton,
    PseudoElement_MdiNormalButton,
    PseudoElement_TitleBar,
    PseudoElement_TitleBarCloseButton,
    PseudoElement_TitleBarMinButton,
    PseudoElement_TitleBarMaxButton,
    PseudoElement_TitleBarShadeButton,
    PseudoElement_TitleBarUnshadeButton,
    PseudoElement_TitleBarNormalButton,
    PseudoElement_TitleBarContextHelpButton,
    PseudoElement_TitleBarSysMenu,
    PseudoElement_ViewItem,
    PseudoElement_ViewItemIcon,
    PseudoElement_ViewItemText,
    PseudoElement_ViewItemIndicator,
    PseudoElement_ScrollAreaCorner,
    PseudoElement_TabBarTabCloseButton,
    NumPseudoElements
};

struct PseudoElementInfo {
    QStyle::SubControl subControl;
    const char *name;
};

static const PseudoElementInfo knownPseudoElements[NumPseudoElements] = {
    { QStyle::SC_None, "" },
    { QStyle::SC_None, "down-arrow" },
    { QStyle::SC_None, "up-arrow" },
    { QStyle::SC_None, "left-arrow" },
    { QStyle::SC_None, "right-arrow" },
    { QStyle::SC_None, "indicator" },
    { QStyle::SC_None, "indicator" },
    { QStyle::SC_None, "menu-indicator" },
    { QStyle::SC_ComboBoxArrow, "drop-down" },
    { QStyle::SC_ComboBoxArrow, "down-arrow" },
    { QStyle::SC_None, "item" },
    { QStyle::SC_SpinBoxUp, "up-button" },
    { QStyle::SC_SpinBoxUp, "up-arrow" },
    { QStyle::SC_SpinBoxDown, "down-button" },
    { QStyle::SC_SpinBoxDown, "down-arrow" },
    { QStyle::SC_GroupBoxLabel, "title" },
    { QStyle::SC_GroupBoxCheckBox, "indicator" },
    { QStyle::SC_ToolButtonMenu, "menu-button" },
    { QStyle::SC_ToolButtonMenu, "menu-arrow" },
    { QStyle::SC_None, "menu-indicator" },
    { QStyle::SC_None, "tab" },
    { QStyle::SC_ScrollBarSlider, "handle" },
    { QStyle::SC_ScrollBarAddPage, "add-page" },
    { QStyle::SC_ScrollBarSubPage, "sub-page" },
    { QStyle::SC_ScrollBarAddLine, "add-line" },
    { QStyle::SC_ScrollBarSubLine, "sub-line" },
    { QStyle::SC_ScrollBarFirst, "first" },
    { QStyle::SC_ScrollBarLast, "last" },
    { QStyle::SC_ScrollBarSubLine, "up-arrow" },
    { QStyle::SC_ScrollBarAddLine, "down-arrow" },
    { QStyle::SC_ScrollBarSubLine, "left-arrow" },
    { QStyle::SC_ScrollBarAddLine, "right-arrow" },
    { QStyle::SC_None, "handle" },
    { QStyle::SC_None, "handle" },
    { QStyle::SC_None, "separator" },
    { QStyle::SC_None, "scroller" },
    { QStyle::SC_None, "tearoff" },
    { QStyle::SC_None, "indicator" },
    { QStyle::SC_None, "separator" },
    { QStyle::SC_None, "icon" },
    { QStyle::SC_None, "right-arrow" },
    { QStyle::SC_None, "branch" },
    { QStyle::SC_None, "section" },
    { QStyle::SC_None, "down-arrow" },
    { QStyle::SC_None, "up-arrow" },
    { QStyle::SC_None, "chunk" },
    { QStyle::SC_None, "tab" },
    { QStyle::SC_None, "scroller" },
    { QStyle::SC_None, "tear" },
    { QStyle::SC_SliderGroove, "groove" },
    { QStyle::SC_SliderHandle, "handle" },
    { QStyle::SC_None, "add-page" },
    { QStyle::SC_None, "sub-page"},
    { QStyle::SC_SliderTickmarks, "tick-mark" },
    { QStyle::SC_None, "pane" },
    { QStyle::SC_None, "tab-bar" },
    { QStyle::SC_None, "left-corner" },
    { QStyle::SC_None, "right-corner" },
    { QStyle::SC_None, "title" },
    { QStyle::SC_None, "close-button" },
    { QStyle::SC_None, "float-button" },
    { QStyle::SC_None, "separator" },
    { QStyle::SC_MdiCloseButton, "close-button" },
    { QStyle::SC_MdiMinButton, "minimize-button" },
    { QStyle::SC_MdiNormalButton, "normal-button" },
    { QStyle::SC_TitleBarLabel, "title" },
    { QStyle::SC_TitleBarCloseButton, "close-button" },
    { QStyle::SC_TitleBarMinButton, "minimize-button" },
    { QStyle::SC_TitleBarMaxButton, "maximize-button" },
    { QStyle::SC_TitleBarShadeButton, "shade-button" },
    { QStyle::SC_TitleBarUnshadeButton, "unshade-button" },
    { QStyle::SC_TitleBarNormalButton, "normal-button" },
    { QStyle::SC_TitleBarContextHelpButton, "contexthelp-button" },
    { QStyle::SC_TitleBarSysMenu, "sys-menu" },
    { QStyle::SC_None, "item" },
    { QStyle::SC_None, "icon" },
    { QStyle::SC_None, "text" },
    { QStyle::SC_None, "indicator" },
    { QStyle::SC_None, "corner" },
    { QStyle::SC_None, "close-button" },
};


struct QStyleSheetBorderImageData : public QSharedData
{
    QStyleSheetBorderImageData()
        : horizStretch(QCss::TileMode_Unknown), vertStretch(QCss::TileMode_Unknown)
    {
        for (int i = 0; i < 4; i++)
            cuts[i] = -1;
    }
    int cuts[4];
    QPixmap pixmap;
    QImage image;
    QCss::TileMode horizStretch, vertStretch;
};

struct QStyleSheetBackgroundData : public QSharedData
{
    QStyleSheetBackgroundData(const QBrush& b, const QPixmap& p, QCss::Repeat r,
                              Qt::Alignment a, QCss::Origin o, QCss::Attachment t, QCss::Origin c)
        : brush(b), pixmap(p), repeat(r), position(a), origin(o), attachment(t), clip(c) { }

    bool isTransparent() const {
        if (brush.style() != Qt::NoBrush)
            return !brush.isOpaque();
        return pixmap.isNull() ? false : pixmap.hasAlpha();
    }
    QBrush brush;
    QPixmap pixmap;
    QCss::Repeat repeat;
    Qt::Alignment position;
    QCss::Origin origin;
    QCss::Attachment attachment;
    QCss::Origin clip;
};

struct QStyleSheetBorderData : public QSharedData
{
    QStyleSheetBorderData() : bi(0)
    {
        for (int i = 0; i < 4; i++) {
            borders[i] = 0;
            styles[i] = QCss::BorderStyle_None;
        }
    }

    QStyleSheetBorderData(int *b, QBrush *c, QCss::BorderStyle *s, QSize *r) : bi(0)
    {
        for (int i = 0; i < 4; i++) {
            borders[i] = b[i];
            styles[i] = s[i];
            colors[i] = c[i];
            radii[i] = r[i];
        }
    }

    int borders[4];
    QBrush colors[4];
    QCss::BorderStyle styles[4];
    QSize radii[4]; // topleft, topright, bottomleft, bottomright

    const QStyleSheetBorderImageData *borderImage() const
    { return bi; }
    bool hasBorderImage() const { return bi!=0; }

    QSharedDataPointer<QStyleSheetBorderImageData> bi;

    bool isOpaque() const
    {
        for (int i = 0; i < 4; i++) {
            if (styles[i] == QCss::BorderStyle_Native || styles[i] == QCss::BorderStyle_None)
                continue;
            if (styles[i] >= QCss::BorderStyle_Dotted && styles[i] <= QCss::BorderStyle_DotDotDash
                && styles[i] != QCss::BorderStyle_Solid)
                return false;
            if (!colors[i].isOpaque())
                return false;
            if (!radii[i].isEmpty())
                return false;
        }
        if (bi != 0 && bi->pixmap.hasAlpha())
            return false;
        return true;
    }
};


struct QStyleSheetOutlineData : public QStyleSheetBorderData
{
    QStyleSheetOutlineData()
    {
        for (int i = 0; i < 4; i++) {
            offsets[i] = 0;
        }
    }

    QStyleSheetOutlineData(int *b, QBrush *c, QCss::BorderStyle *s, QSize *r, int *o)
            : QStyleSheetBorderData(b, c, s, r)
    {
        for (int i = 0; i < 4; i++) {
            offsets[i] = o[i];
        }
    }

    int offsets[4];
};

struct QStyleSheetBoxData : public QSharedData
{
    QStyleSheetBoxData(int *m, int *p, int s) : spacing(s)
    {
        for (int i = 0; i < 4; i++) {
            margins[i] = m[i];
            paddings[i] = p[i];
        }
    }

    int margins[4];
    int paddings[4];

    int spacing;
};

struct QStyleSheetPaletteData : public QSharedData
{
    QStyleSheetPaletteData(const QBrush &fg, const QBrush &sfg, const QBrush &sbg,
                           const QBrush &abg)
        : foreground(fg), selectionForeground(sfg), selectionBackground(sbg),
          alternateBackground(abg) { }

    QBrush foreground;
    QBrush selectionForeground;
    QBrush selectionBackground;
    QBrush alternateBackground;
};

struct QStyleSheetGeometryData : public QSharedData
{
    QStyleSheetGeometryData(int w, int h, int minw, int minh, int maxw, int maxh)
        : minWidth(minw), minHeight(minh), width(w), height(h), maxWidth(maxw), maxHeight(maxh) { }

    int minWidth, minHeight, width, height, maxWidth, maxHeight;
};

struct QStyleSheetPositionData : public QSharedData
{
    QStyleSheetPositionData(int l, int t, int r, int b, QCss::Origin o, Qt::Alignment p, QCss::PositionMode m, Qt::Alignment a = 0)
        : left(l), top(t), bottom(b), right(r), origin(o), position(p), mode(m), textAlignment(a) { }

    int left, top, bottom, right;
    QCss::Origin origin;
    Qt::Alignment position;
    QCss::PositionMode mode;
    Qt::Alignment textAlignment;
};

struct QStyleSheetImageData : public QSharedData
{
    QStyleSheetImageData(const QIcon &i, Qt::Alignment a, const QSize &sz)
        : icon(i), alignment(a), size(sz) { }

    QIcon icon;
    Qt::Alignment alignment;
    QSize size;
};

class QRenderRule
{
public:
    QRenderRule() : features(0), hasFont(false), pal(0), b(0), bg(0), bd(0), ou(0), geo(0), p(0), img(0), clipset(0) { }
    QRenderRule(const QVector<QCss::Declaration> &, const QWidget *);
    ~QRenderRule() { }

    QRect borderRect(const QRect &r) const;
    QRect outlineRect(const QRect &r) const;
    QRect paddingRect(const QRect &r) const;
    QRect contentsRect(const QRect &r) const;

    enum { Margin = 1, Border = 2, Padding = 4, All=Margin|Border|Padding };
    QRect boxRect(const QRect &r, int flags = All) const;
    QSize boxSize(const QSize &s, int flags = All) const;
    QRect originRect(const QRect &rect, QCss::Origin origin) const;

    QPainterPath borderClip(QRect rect);
    void drawBorder(QPainter *, const QRect&);
    void drawOutline(QPainter *, const QRect&);
    void drawBorderImage(QPainter *, const QRect&);
    void drawBackground(QPainter *, const QRect&, const QPoint& = QPoint(0, 0));
    void drawBackgroundImage(QPainter *, const QRect&, QPoint = QPoint(0, 0));
    void drawFrame(QPainter *, const QRect&);
    void drawImage(QPainter *p, const QRect &rect);
    void drawRule(QPainter *, const QRect&);
    void configurePalette(QPalette *, QPalette::ColorGroup, const QWidget *, bool);
    void configurePalette(QPalette *p, QPalette::ColorRole fr, QPalette::ColorRole br);

    const QStyleSheetPaletteData *palette() const { return pal; }
    const QStyleSheetBoxData *box() const { return b; }
    const QStyleSheetBackgroundData *background() const { return bg; }
    const QStyleSheetBorderData *border() const { return bd; }
    const QStyleSheetOutlineData *outline() const { return ou; }
    const QStyleSheetGeometryData *geometry() const { return geo; }
    const QStyleSheetPositionData *position() const { return p; }

    bool hasPalette() const { return pal != 0; }
    bool hasBackground() const { return bg != 0 && (!bg->pixmap.isNull() || bg->brush.style() != Qt::NoBrush); }
    bool hasGradientBackground() const { return bg && bg->brush.style() >= Qt::LinearGradientPattern
                                                   && bg->brush.style() <= Qt::ConicalGradientPattern; }

    bool hasNativeBorder() const {
        return bd == 0
               || (!bd->hasBorderImage() && bd->styles[0] == QCss::BorderStyle_Native);
    }

    bool hasNativeOutline() const {
        return (ou == 0
                || (!ou->hasBorderImage() && ou->styles[0] == QCss::BorderStyle_Native));
    }

    bool baseStyleCanDraw() const {
        if (!hasBackground() || (background()->brush.style() == Qt::NoBrush && bg->pixmap.isNull()))
            return true;
        if (bg && !bg->pixmap.isNull())
            return false;
        if (hasGradientBackground())
            return features & QCss::StyleFeature_BackgroundGradient;
        return features & QCss::StyleFeature_BackgroundColor;
    }

    bool hasBox() const { return b != 0; }
    bool hasBorder() const { return bd != 0; }
    bool hasOutline() const { return ou != 0; }
    bool hasPosition() const { return p != 0; }
    bool hasGeometry() const { return geo != 0; }
    bool hasDrawable() const { return !hasNativeBorder() || hasBackground() || hasImage(); }
    bool hasImage() const { return img != 0; }

    QSize minimumContentsSize() const
    { return geo ? QSize(geo->minWidth, geo->minHeight) : QSize(0, 0); }
    QSize minimumSize() const
    { return boxSize(minimumContentsSize()); }

    QSize contentsSize() const
    { return geo ? QSize(geo->width, geo->height)
                 : ((img && img->size.isValid()) ? img->size : QSize()); }
    QSize contentsSize(const QSize &sz) const
    {
        QSize csz = contentsSize();
        if (csz.width() == -1) csz.setWidth(sz.width());
        if (csz.height() == -1) csz.setHeight(sz.height());
        return csz;
    }
    bool hasContentsSize() const
    { return (geo && (geo->width != -1 || geo->height != -1)) || (img && img->size.isValid()); }

    QSize size() const { return boxSize(contentsSize()); }
    QSize size(const QSize &sz) const { return boxSize(contentsSize(sz)); }
    QSize adjustSize(const QSize &sz)
    {
        if (!geo)
            return sz;
        QSize csz = contentsSize();
        if (csz.width() == -1) csz.setWidth(sz.width());
        if (csz.height() == -1) csz.setHeight(sz.height());
        if (geo->maxWidth != -1 && csz.width() > geo->maxWidth) csz.setWidth(geo->maxWidth);
        if (geo->maxHeight != -1 && csz.height() > geo->maxHeight) csz.setHeight(geo->maxHeight);
        csz=csz.expandedTo(QSize(geo->minWidth, geo->minHeight));
        return csz;
    }

    int features;
    QBrush defaultBackground;
    QFont font;
    bool hasFont;

    QHash<QString, QVariant> styleHints;
    bool hasStyleHint(const QString& sh) const { return styleHints.contains(sh); }
    QVariant styleHint(const QString& sh) const { return styleHints.value(sh); }

    void fixupBorder(int);

    QSharedDataPointer<QStyleSheetPaletteData> pal;
    QSharedDataPointer<QStyleSheetBoxData> b;
    QSharedDataPointer<QStyleSheetBackgroundData> bg;
    QSharedDataPointer<QStyleSheetBorderData> bd;
    QSharedDataPointer<QStyleSheetOutlineData> ou;
    QSharedDataPointer<QStyleSheetGeometryData> geo;
    QSharedDataPointer<QStyleSheetPositionData> p;
    QSharedDataPointer<QStyleSheetImageData> img;

    // Shouldn't be here
    void setClip(QPainter *p, const QRect &rect);
    void unsetClip(QPainter *);
    int clipset;
    QPainterPath clipPath;
};




class QStyleSheetStyleCaches : public QObject
{
    Q_OBJECT
public Q_SLOTS:
    void widgetDestroyed(QObject *);
    void styleDestroyed(QObject *);
public:
    QHash<const QWidget *, QVector<QCss::StyleRule> > styleRulesCache;
    QHash<const QWidget *, QHash<int, bool> > hasStyleRuleCache;
    typedef QHash<int, QHash<quint64, QRenderRule> > QRenderRules;
    QHash<const QWidget *, QRenderRules> renderRulesCache;
    QHash<const QWidget *, QPalette> customPaletteWidgets; // widgets whose palette we tampered
    QHash<const void *, QCss::StyleSheet> styleSheetCache; // parsed style sheets
    QSet<const QWidget *> autoFillDisabledWidgets;
};


#endif // CUSTOMSTYLESHEETSTYLE_H

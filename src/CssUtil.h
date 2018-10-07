#ifndef CSSUTIL_P_H
#define CSSUTIL_P_H

#include "QtCore/qglobal.h"

//#include "private/qcssparser_p.h"
#include "CssParser.h"
#include "QtCore/qsize.h"


class QPainter;

extern void qDrawEdge(QPainter *p, qreal x1, qreal y1, qreal x2, qreal y2, qreal dw1, qreal dw2,
                      QCss::Edge edge, QCss::BorderStyle style, QBrush c);

extern void qDrawRoundedCorners(QPainter *p, qreal x1, qreal y1, qreal x2, qreal y2,
                                const QSizeF& r1, const QSizeF& r2,
                                QCss::Edge edge, QCss::BorderStyle s, QBrush c);

extern void qDrawBorder(QPainter *p, const QRect &rect, const QCss::BorderStyle *styles,
                        const int *borders, const QBrush *colors, const QSize *radii);

extern void qNormalizeRadii(const QRect &br, const QSize *radii,
                            QSize *tlr, QSize *trr, QSize *blr, QSize *brr);


#endif // CSSUTIL_P_H

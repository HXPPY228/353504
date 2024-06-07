#include "inversestypefigure.h"

InverseSTypeFigure::InverseSTypeFigure(qreal qUnit, GameField* field, QPointF pos) : FigureItem(field, pos)
{
    this->setTransformOriginPoint(1.5 * qUnit, 1.5 * qUnit);
    this->setScale(0.9);

    this->field = field;
    this->qUnit = qUnit;
}

QRectF InverseSTypeFigure::boundingRect() const
{
    return QRectF(0, 0, 3 * qUnit, 3 * qUnit);
}

void InverseSTypeFigure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QColor("#4395FF"));
    painter->setPen(QPen(QColor("#0E77FF"), 3));


    painter->drawRect(2 * qUnit, 1 * qUnit, qUnit, qUnit);
    painter->drawRect(1 * qUnit, 1 * qUnit, qUnit, qUnit);
    painter->drawRect(1 * qUnit, 2 * qUnit, qUnit, qUnit);
    painter->drawRect(0 , 2 * qUnit, qUnit, qUnit);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

TypesOfFigures::type InverseSTypeFigure::getTypeOfFigure()
{
    return TypesOfFigures::type::InverseSType;
}

QPainterPath InverseSTypeFigure::shape() const
{
    QPainterPath path;
    path.addRect(2 * qUnit, 1 * qUnit, qUnit, qUnit);
    path.addRect(1 * qUnit, 1 * qUnit, qUnit, qUnit);
    path.addRect(1 * qUnit, 2 * qUnit, qUnit, qUnit);
    path.addRect(0 , 2 * qUnit, qUnit, qUnit);

    return path;
}

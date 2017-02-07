#ifndef QTELEMENTO_H
#define QTELEMENTO_H

#include <QObject>
#include <QColor>

class Patch;
struct Geometry;

//! [0]
class QtElemento : public QObject
{
public:
    explicit QtElemento(QObject *parent, qreal s = 1.0);
    ~QtElemento();
    void setColor(QColor c);
    void draw() const;
private:
    void buildGeometry(qreal s);

    QList<Patch *> parts;
    Geometry *geom;
};

#endif // ELEMENTO_H

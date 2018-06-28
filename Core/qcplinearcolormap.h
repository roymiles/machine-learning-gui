#ifndef QCPLINEARCOLORMAP_H
#define QCPLINEARCOLORMAP_H

#include <QColor>
#include <QList>

class QCPLinearColorMap
{
public:
  QCPLinearColorMap() {}
  ~QCPLinearColorMap() {}

  void addColorStop(const double &value, const QColor &color);
  QColor color(const double &vMin, const double &vMax, const double value);

private:
  struct ColorStop {
    ColorStop(const double &v, const QColor &c) : value(v), color(c) {}
    double value;
    QColor color;
  };

  QList<ColorStop> colorStops_;
};

#endif // QCPLINEARCOLORMAP_H

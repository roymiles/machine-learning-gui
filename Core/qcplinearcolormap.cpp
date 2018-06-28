#include "qcplinearcolormap.h"

void QCPLinearColorMap::addColorStop( const double &value, const QColor &color)
{
  colorStops_ << ColorStop( value, color);
}

QColor QCPLinearColorMap::color(const double &vMin, const double &vMax, const double value)
{
  if ( colorStops_.isEmpty()) {
    return QColor();
  }
  if ( colorStops_.count() == 1) {
    return colorStops_[0].color;
  }

  // Normalise value between 0 < x < 1.
  double x = ( value - vMin) / ( vMax - vMin);
  if ( x <= colorStops_.first().value) {
    return colorStops_.first().color;
  }
  if ( x >= colorStops_.last().value) {
    return colorStops_.last().color;
  }

  // Using linear search for closest colour stops rather than mid-point search.
  // It is unlikely there would be a large number of colour stops.
  int i = 0;
  while ( i < colorStops_.count() - 2 && x > colorStops_[i+1].value) {
    ++i;
  }

  // Interpolate between closest colour stops.
  ColorStop &c1 = colorStops_[i];
  ColorStop &c2 = colorStops_[i+1];
  double dx = c2.value - c1.value;
  double r1 = ( c2.value - x) / dx;
  double r2 = ( x - c1.value) / dx;

  int r = r1 * c1.color.red()   + r2 * c2.color.red();
  int g = r1 * c1.color.green() + r2 * c2.color.green();
  int b = r1 * c1.color.blue()  + r2 * c2.color.blue();

  return QColor( r, g, b);
}

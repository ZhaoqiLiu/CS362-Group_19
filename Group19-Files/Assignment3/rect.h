#ifndef GFX_RECT_H_INCLUDED
#define GFX_RECT_H_INCLUDED
#pragma once
namespace gfx {
template<typename T> class PointT;
template<typename T> class SizeT;
template<typename T> class BorderT;
template<typename T>
class RectT {
public:
  T x, y, w, h;
  T x2() const { return x+w; }
  T y2() const { return y+h; }
  RectT() : x(0), y(0), w(0), h(0) {
  }
  RectT(const T& w, const T& h) :
    x(0), y(0),
    w(w), h(h) {
  }
  explicit RectT(const SizeT<T>& size) :
    x(0), y(0),
    w(size.w), h(size.h) {
  }
  RectT(const RectT<T>& rect) :
    x(rect.x), y(rect.y),
    w(rect.w), h(rect.h) {
  }
  template<typename T2>
  RectT(const RectT<T2>& rect) :
    x(static_cast<T>(rect.x)), y(static_cast<T>(rect.y)),
    w(static_cast<T>(rect.w)), h(static_cast<T>(rect.h)) {
  }
  RectT(const PointT<T>& point, const SizeT<T>& size) :
    x(point.x), y(point.y),
    w(size.w), h(size.h) {
  }
  RectT(const PointT<T>& point1, const PointT<T>& point2) {
    PointT<T> leftTop = point1;
    PointT<T> rightBottom = point2;
    T t;
    if (leftTop.x > rightBottom.x) {
      t = leftTop.x;
      leftTop.x = rightBottom.x;
      rightBottom.x = t;
    }
    if (leftTop.y > rightBottom.y) {
      t = leftTop.y;
      leftTop.y = rightBottom.y;
      rightBottom.y = t;
    }
    this->x = leftTop.x;
    this->y = leftTop.y;
    this->w = rightBottom.x - leftTop.x;
    this->h = rightBottom.y - leftTop.y;
  }
  RectT(const T& x, const T& y, const T& w, const T& h) : x(x), y(y), w(w), h(h) {
  }
  bool isEmpty() const {
    return (w <= 0 || h <= 0);
  }
  PointT<T> center() const {
    return PointT<T>(x+w/2, y+h/2);
  }
  PointT<T> origin() const {
    return PointT<T>(x, y);
  }
  PointT<T> point2() const {
    return PointT<T>(x+w, y+h);
  }
  SizeT<T> size() const {
    return SizeT<T>(w, h);
  }
  RectT& setOrigin(const PointT<T>& pt) {
    x = pt.x;
    y = pt.y;
    return *this;
  }
  RectT& setSize(const SizeT<T>& sz) {
    w = sz.w;
    h = sz.h;
    return *this;
  }
  RectT& offset(const T& dx, const T& dy) {
    x += dx;
    y += dy;
    return *this;
  }
  RectT& offset(const PointT<T>& delta) {
    x += delta.x;
    y += delta.y;
    return *this;
  }
  RectT& inflate(const T& delta) {
    w += delta;
    h += delta;
    return *this;
  }
  RectT& inflate(const T& dw, const T& dh) {
    w += dw;
    h += dh;
    return *this;
  }
  RectT& inflate(const SizeT<T>& delta) {
    w += delta.w;
    h += delta.h;
    return *this;
  }
  RectT& enlarge(const T& unit) {
    x -= unit;
    y -= unit;
    w += unit<<1;
    h += unit<<1;
    return *this;
  }
  RectT& enlarge(const BorderT<T>& br) {
    x -= br.left();
    y -= br.top();
    w += br.left() + br.right();
    h += br.top() + br.bottom();
    return *this;
  }
  RectT& enlargeXW(const T& unit) {
    x -= unit;
    w += unit<<1;
    return *this;
  }
  RectT& enlargeYH(const T& unit) {
    y -= unit;
    h += unit<<1;
    return *this;
  }
  RectT& shrink(const T& unit) {
    x += unit;
    y += unit;
    w -= unit<<1;
    h -= unit<<1;
    return *this;
  }
  RectT& shrink(const BorderT<T>& br) {
    x += br.left();
    y += br.top();
    w -= br.left() + br.right();
    h -= br.top() + br.bottom();
    return *this;
  }
  bool contains(const PointT<T>& pt) const {
    return
      pt.x >= x && pt.x < x+w &&
      pt.y >= y && pt.y < y+h;
  }
  bool contains(const T& u, const T& v) const {
    return
      u >= x && u < x+w &&
      v >= y && v < y+h;
  }
  bool contains(const RectT& rc) const {
    if (isEmpty() || rc.isEmpty())
      return false;

    return
      rc.x >= x && rc.x+rc.w <= x+w &&
      rc.y >= y && rc.y+rc.h <= y+h;
  }
  bool intersects(const RectT& rc) const {
    if (isEmpty() || rc.isEmpty())
      return false;
    return
      rc.x < x+w && rc.x+rc.w > x &&
      rc.y < y+h && rc.y+rc.h > y;
  }
  RectT createUnion(const RectT& rc) const {
    if (isEmpty())
      return rc;
    else if (rc.isEmpty())
      return *this;
    else
      return RectT(PointT<T>(x < rc.x ? x: rc.x,
                             y < rc.y ? y: rc.y),
                   PointT<T>(x+w > rc.x+rc.w ? x+w: rc.x+rc.w,
                             y+h > rc.y+rc.h ? y+h: rc.y+rc.h));
  }
  RectT createIntersection(const RectT& rc) const {
    if (intersects(rc))
      return RectT(PointT<T>(x > rc.x ? x: rc.x,
                             y > rc.y ? y: rc.y),
                   PointT<T>(x+w < rc.x+rc.w ? x+w: rc.x+rc.w,
                             y+h < rc.y+rc.h ? y+h: rc.y+rc.h));
    else
      return RectT();
  }
  const RectT& operator+=(const BorderT<T>& br) {
    enlarge(br);
    return *this;
  }
  const RectT& operator-=(const BorderT<T>& br) {
    shrink(br);
    return *this;
  }
  RectT& operator*=(const int factor) {
    x *= factor;
    y *= factor;
    w *= factor;
    h *= factor;
    return *this;
  }
  RectT& operator/=(const int factor) {
    x /= factor;
    y /= factor;
    w /= factor;
    h /= factor;
    return *this;
  }
  RectT& operator*=(const SizeT<T>& size) {
    x *= size.w;
    y *= size.h;
    w *= size.w;
    h *= size.h;
    return *this;
  }
  RectT& operator/=(const SizeT<T>& size) {
    x /= size.w;
    y /= size.h;
    w /= size.w;
    h /= size.h;
    return *this;
  }
  const RectT& operator|=(const RectT& rc) {
    return *this = createUnion(rc);
  }
  const RectT& operator&=(const RectT& rc) {
    return *this = createIntersection(rc);
  }
  RectT operator+(const BorderT<T>& br) const {
    return RectT(*this).enlarge(br);
  }
  RectT operator-(const BorderT<T>& br) const {
    return RectT(*this).shrink(br);
  }
  RectT operator|(const RectT& other) const {
    return createUnion(other);
  }
  RectT operator&(const RectT& other) const {
    return createIntersection(other);
  }
  RectT operator*(const SizeT<T>& size) const {
    return RectT(x*size.w, y*size.h,
                 w*size.w, h*size.h);
  }
  RectT operator/(const SizeT<T>& size) const {
    return RectT(x/size.w, y/size.h,
                 w/size.w, h/size.h);
  }
  bool operator==(const RectT& rc) const {
    return
      x == rc.x && w == rc.w &&
      y == rc.y && h == rc.h;
  }
  bool operator!=(const RectT& rc) const {
    return
      x != rc.x || w != rc.w ||
      y != rc.y || h != rc.h;
  }
  RectT& fitIn(const RectT& bounds) {
    if (w < h) {
      w = w * bounds.h / h;
      x = bounds.x + bounds.w/2 - w/2;
      y = bounds.y;
      h = bounds.h;
    }
    else {
      h = h * bounds.w / w;
      y = bounds.y + bounds.h/2 - h/2;
      x = bounds.x;
      w = bounds.w;
    }
    return *this;
  }
};
typedef RectT<int> Rect;
typedef RectT<double> RectF;
} // namespace gfx
#endif

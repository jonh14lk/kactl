struct fraction {
  int x, y;  // x / y
  fraction() {}
  fraction(int x, int y) : x(x), y(y) {}
  bool operator==(fraction o) { return (x * o.y == o.x * y); }
  bool operator!=(fraction o) { return (x * o.y != o.x * y); }
  bool operator>(fraction o) { return (x * o.y > o.x * y); }
  bool operator>=(fraction o) { return (x * o.y >= o.x * y); }
  bool operator<(fraction o) { return (x * o.y < o.x * y); }
  bool operator<=(fraction o) { return (x * o.y <= o.x * y); }
  fraction operator+(fraction o) {
    fraction ans;
    ans.y = (y == o.y) ? y : y * o.y;
    ans.x = (x) * (ans.y / y) + (o.x) * (ans.y / o.y);
    // ans.simplify();
    return ans;
  }
  fraction operator*(fraction o) {
    fraction ans;
    ans.x = x * o.x;
    ans.y = y * o.y;
    // ans.simplify();
    return ans;
  }
  fraction inv() {
    fraction ans = fraction(x, y);
    swap(ans.x, ans.y);
    return ans;
  }
  fraction neg() {
    fraction ans = fraction(x, y);
    ans.x *= -1;
    return ans;
  }
  void simplify() {
    if (abs(x) > 1e9 || abs(y) > 1e9)  // slow simplification
    {
      int g = __gcd(y, x);
      x /= g;
      y /= g;
    }
  }
  // substraction and division can be easily done
};

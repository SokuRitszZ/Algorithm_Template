struct complex
{
  double x, y;
  complex(double x = 0, double y = 0): x(x), y(y){}
  complex operator + (const complex& rhs) {return complex(x + rhs.x, y + rhs.y);}
  complex operator - (const complex& rhs) {return complex(x - rhs.x, y - rhs.y);}
  complex operator * (const complex& rhs) {return complex(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x);}
};

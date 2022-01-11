//
//  CCVector.h
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CCVector__
#define __testcommand__CCVector__

#include <iostream>
#include <fstream>
using namespace std;
// CVector.h: interface for the CCVector class.
//
//////////////////////////////////////////////////////////////////////


class CCVector
{
public:
	long Readfile(CFile &file);
	void openfile(CFile& file);
	void savefile(CFile& file);
	CCVector(): r(0.0), g(0.0), b(0.0) {};
	virtual ~CCVector();
    CCVector(const CCVector& c) : r(c.r), g(c.g), b(c.b) {}
    CCVector(double _r, double _g, double _b) : r(_r), g(_g), b(_b) {}
	CCVector& operator=(const CCVector& c) {
        r = c.r;
        g = c.g;
        b = c.b;
        return *this;
    }
    
    CCVector& operator+=(const CCVector& c) {
        r += c.r; g += c.g; b += c.b;
        return *this;
    }
    
    CCVector& operator-=(const CCVector& c) {
        r -= c.r; g -= c.g; b -= c.b;
        return *this;
    }
    
    inline CCVector& operator*=(const CCVector& c) {
        r *= c.r; g *= c.g; b *= c.b;
        return *this;
    }
    CCVector& operator/=(const CCVector& c) {
        r /= c.r; g /= c.g; b /= c.b;
        return *this;
    }
    
    CCVector& operator*=(double s) {
        r *= s; g *= s; b *= s;
        return *this;
    }
    
    CCVector& operator/=(double s) {
        double is = 1.0 / s;
        r *= is; g *= is; b *= is;
        return *this;
    }
    
    CCVector operator-() const {
        return CCVector(-r, -g, -b);
    }
    CCVector operator+() const {
        return *this;
    }
    
    inline int toRGB() const {
        int red   = (int) (r * 255.0);
        int green = (int) (g * 255.0);
        int blue  = (int) (b * 255.0);
        
        if (red < 0)   red = 0;   else if (red > 255)   red = 255;
        if (green < 0) green = 0; else if (green > 255) green = 255;
        if (blue < 0)  blue = 0;  else if (blue > 255)  blue = 255;
        
        return (red << 16) | (green << 8) | blue;
    }
    
    double getMax() const {
        double max = (r > g) ? r : g;
        if (max < b)
            max = b;
        return max;
    }
    
    double getMin() const {
        double min = (r < g) ? r : g;
        if (min > b)
            min = b;
        return min;
    }
    
    double getAverage() const {
        return (r + g + b) / 3.0;
    }
    
    double r, g, b;
};

inline CCVector operator+(const CCVector& a, const CCVector& b) {
    return CCVector(a.r + b.r, a.g + b.g, a.b + b.b);
}

inline CCVector operator-(const CCVector& a, const CCVector& b) {
    return CCVector(a.r - b.r, a.g - b.g, a.b - b.b);
}

inline CCVector operator*(const CCVector& a, const CCVector& b) {
    return CCVector(a.r * b.r, a.g * b.g, a.b * b.b);
}

inline CCVector operator/(const CCVector& a, const CCVector& b) {
    return CCVector(a.r / b.r, a.g / b.g, a.b / b.b);
}

inline CCVector operator*(double s, const CCVector& c) {
    return CCVector(s * c.r, s * c.g, s * c.b);
}

inline CCVector operator*(const CCVector& c, double s) {
    return CCVector(s * c.r, s * c.g, s * c.b);
}

inline CCVector operator/(const CCVector& c, double s) {
    double is = 1.0 / s;
    return CCVector(is * c.r, is * c.g, is * c.b);
}

#endif /* defined(__testcommand__CCVector__) */

#pragma once
#ifndef UTILITIES
#define UTILITIES

#include "Line.h"
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

#define PI (2*acos(0.0))
#define EPS 1e-9
class Utilities
{
public:
	static float crossProduct( const Point& p1, const Point& p2, const Point& p3)
	{
		return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
	}

	static bool PointInTriangle( const Point& pt, const Point& v1, const Point& v2, const Point& v3)
	{
		bool b1, b2, b3;
		float f1, f2, f3;

		f1 = Utilities::crossProduct(pt, v1, v2);
		f2 = Utilities::crossProduct(pt, v2, v3);
		f3 = Utilities::crossProduct(pt, v3, v1);

		if(f1==0&&f2==0&&f3==0)//If all points are collinear
			return false;

		b1 = f1<0.0f;
		b2 = f2<0.0f;
		b3 = f3<0.0f;
		return ((b1 == b2) && (b2 == b3));
	}

	/*
		a        c
		 \      /								tan(@) = Cy/Cx
		  \    /								tan(#) = Ay/Ax
		   \# /									tan(#-@) = (tan @ - tan #)
	   _____\/@________ (Parallel to X-Axis)			   _______________
	        b												1-tan @ tan #
	*/
	static float getAngle3Points(const Point& a, const Point& b, const Point& c)
	{
		//Handle Zero Division
		float firstTan = tan(c.y/c.x);
		float secondTan = tan(a.y/a.x);
		float tanAngle = (firstTan - secondTan)/(1-firstTan*secondTan);
		return atan(tanAngle);
	}
	static float getAngle2Vectors(const Point& a, const Point& b, const Point& p, const Point& q)
	{
		Point v1 = Point(b.x-a.x,b.y-a.y);
		Point v2 = Point(q.x-p.x,q.y-p.y);
		//Todo: Handle Zero Division
		float t = (v1.x*v2.x + v1.y*v2.y)/(hypot(v1.x,v1.y)*hypot(v2.x,v2.y));
		return acos( t )*(180/PI);
	}
	static float getAngle2Vectors(const Line& v1, const Line& v2)
	{
		return getAngle2Vectors(v1.start,v1.end,v2.start,v2.end);
	}
	static float getLinePointDistance(const Line& l, const Point& p)
	{
		Point v(l.end.x - l.start.x, l.end.y - l.start.y);
		if(v.x+v.y==0)
			return hypot(l.start.x - p.x, l.start.y - p.y);

		return fabs(crossProduct(p,l.start,l.end)/hypot(v.x,v.y));
	}
};
struct AngleComparer
{
        static Point about;
		AngleComparer(){}
        AngleComparer(Point c) {
                about = c;
        }
        bool operator()(const Point& p, const Point& q) const
		{
			double cr = Utilities::crossProduct(about,p,q);
                if (fabs(cr) < EPS)
                        return make_pair(p.y, p.x) < make_pair(q.y, q.x);
                return cr > 0;
        }
};
#endif
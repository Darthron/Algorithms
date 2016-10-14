#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Line
{
    // y = a * x + b

    double a;
    double b;

    Line(double x,
         double y)
        : a(x),
          b(y)
    {

    }

    Line()
        : a(0),
          b(0)
    {

    }

};

using Point = Line;

struct PointPair
{
    uint u;
    uint v;
};

inline Line
getLine(Point u,
        Point v)
{
    return Line( (u.b - v.b) / (u.a - v.a),
                 ((-1) * v.a * ( (u.b - v.b) / (u.a - v.a) ) + v.b) );
}

inline double
getIntersectionWithVerticalLine(Line u,
                                double x)
{
    return (u.a * x + u.b);
}

// Assume there aren't two points with the same X,
// two points with the same Y and three collinear points
//
// left and right are in counter clockwise order, starting with the left-most point 
std::vector <Point>
mergeConvexHulls(std::vector <Point> left,
                 std::vector <Point> right)
{
    std::vector <Point> res;
    PointPair           upperTangent;
    PointPair           lowerTangent;
    double              xOfReferenceLine;
    int                leftRightMostPoint;
    int                 l;
    int                 r;

    if ( (1 == left.size()) and
         (1 == right.size()) )
    {
        res.push_back(left[0]);
        res.push_back(right[0]);

        return res;
    }
    else if ( (1 == left.size()) and
              (2 == right.size()) )
    {
        res.push_back(left[0]);

        if ( ((right[0].b > left[0].b) and
              (right[1].b < left[0].b)) or

             (right[0].b > right[1].b) )
        {
            res.push_back(right[1]);
            res.push_back(right[0]);
        }
        else
        {
            res.push_back(right[0]);
            res.push_back(right[1]);
        }

        return res;
    }
    else if ( (2 == left.size()) and
              (1 == right.size()) )
    {
        res.push_back(left[0]);
        if (left[1].b < right[0].b)
        {
            res.push_back(left[1]);
            res.push_back(right[0]);
        }
        else
        {
            res.push_back(right[0]);
            res.push_back(left[1]);
        }

        return res;
    }

    leftRightMostPoint = 1;
    while ( (leftRightMostPoint != left.size() - 1) and
            (left[leftRightMostPoint].a > left[leftRightMostPoint - 1].a) and
            (left[leftRightMostPoint].a < left[leftRightMostPoint + 1].a) )
    {
        leftRightMostPoint++;
    }

    // The vertical line between the two polygons
    xOfReferenceLine = left[leftRightMostPoint].a + (right[0].a - left[leftRightMostPoint].a) / 2;

    l = leftRightMostPoint;
    r = 0;
    // Get the points that make the upper tangent
    while ( (getIntersectionWithVerticalLine(getLine(left[l],
                                                     right[ ( ((r - 1) < 0) ? (r - 1) + right.size() : r - 1 ) ]),
                                             xOfReferenceLine) > getIntersectionWithVerticalLine(getLine(left[l],
                                                                                                         right[r]),
                                                                                                 xOfReferenceLine)) or
            (getIntersectionWithVerticalLine(getLine(left [ (l + 1) % left.size() ],
                                                     right[r]),
                                             xOfReferenceLine) > getIntersectionWithVerticalLine(getLine(left[l],
                                                                                                         right[r]),
                                                                                                 xOfReferenceLine)) )
    {
        if (getIntersectionWithVerticalLine(getLine(left[l],
                                                    right[ (((r - 1) < 0) ? (r - 1) + right.size() : r - 1 ) ]),
                                            xOfReferenceLine) > getIntersectionWithVerticalLine(getLine(left[l],
                                                                                                        right[r]),
                                                                                                xOfReferenceLine))
        {
            r = (((r - 1) < 0) ? (r - 1) + right.size() : r - 1 );
        }
        else
        {
            l = (l + 1) % left.size();
        }
    }

    upperTangent.u = l;
    upperTangent.v = r;

    // Get the points that make the upper tangent
    r = 0;
    l = leftRightMostPoint;
    while ( (getIntersectionWithVerticalLine(getLine(left[l],
                                                     right[ (r + 1) % right.size() ]),
                                             xOfReferenceLine) < getIntersectionWithVerticalLine(getLine(left[l],
                                                                                                         right[r]),
                                                                                                 xOfReferenceLine)) or
            (getIntersectionWithVerticalLine(getLine(left [ ( ((l - 1) < 0) ? l - 1 + left.size() : l - 1 ) ],
                                                     right[r]),
                                             xOfReferenceLine) < getIntersectionWithVerticalLine(getLine(left[l],
                                                                                                         right[r]),
                                                                                                 xOfReferenceLine)) )
    {
        if (getIntersectionWithVerticalLine(getLine(left[l],
                                                    right[ (r + 1) % right.size() ]),
                                            xOfReferenceLine) < getIntersectionWithVerticalLine(getLine(left[l],
                                                                                                        right[r]),
                                                                                                xOfReferenceLine))
        {
            r = (r + 1) % right.size();
        }
        else
        {
            l = ( ((l - 1) < 0) ? l - 1 + left.size() : l - 1 );
        }
    }

    lowerTangent.u = l;
    lowerTangent.v = r;

    // Get the hull
    l = 0;
    while (l != lowerTangent.u)
    {
        res.push_back(left[l]);
        l++;
    }
    res.push_back(left[lowerTangent.u]);
    r = lowerTangent.v;

    while (r != upperTangent.v)
    {
        res.push_back(right[r]);
        r = (r + 1) % right.size();
    }
    res.push_back(right[upperTangent.v]);
    l = upperTangent.u;

    while (l > 0)
    {
        res.push_back(left[l]);
        l = (l + 1) % left.size();
    }

    return res;
}

std::vector <Point>
getConvexHull(std::vector <Point> points)
{
    std::vector <Point> res;
    
    if (points.size() == 2)
    {
        res.push_back(points[0]);
        res.push_back(points[1]);

        return res;
    }
    else if (points.size() == 1)
    {
        res.push_back(points[0]);

        return res;
    }

    return mergeConvexHulls(getConvexHull(std::vector <Point> (points.begin(),
                                                               points.begin() + points.size() / 2)),
                            getConvexHull(std::vector <Point> (points.begin() + points.size() / 2,
                                                               points.end())));
}

int main()
{
    unsigned int        index;
    Point               point;
    std::vector <Point> points;
    unsigned int        N;
    
    std::ifstream mama("hull.in");
    std::ofstream tata("hull.out");

    mama >> N;
    
    for (index = 0; index < N; index++)
    {
        mama >> point.a;
        mama >> point.b;

        points.push_back(point);
    }

    sort(points.begin(),
         points.end(),
         [](const Point& p1,
            const Point& p2)
         {
            return p1.a < p2.a;
         });

    for (auto el : getConvexHull(points))
    {
        std::cout << el.a << " " << el.b << std::endl;
    }
    return 0;
}

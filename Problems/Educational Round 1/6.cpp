#include <iostream>
#include <vector>

const double INF = 1 << 30;

struct Line
{
    // y = a * x + b;

    double a;
    double b;

    double& x = a;
    double& y = b;

    Line(double p,
         double q)
        : a(p),
          b(q)
    {

    }

    Line()
    {

    }
};

struct Segment
{
    Line  line;
    Point p;
    Point q;

    Segment(Line l,
            Point r,
            Point s)
        : line(l),
          p(r),
          q(s)
    {

    }

    Segment()
    {

    }
};

using Point = Line;

Line
getLine(const Point& p,
        const Point& q)
{
    double slope;

    if (p.x == q.x)
    {
        return Line(p.x,
                    INF);
    }

    if (p.y == q.y)
    {
        return Line(0,
                    p.y);
    }

    /*
    a * x1 + b = y1;
    a * x2 + b = y2;
    */
    slope = (p.y - q.y) / (p.x - q.x);
    return Line(slope,
                p.y - slope * p.x);                
}

Segment
getSegment(const Point& p,
           const Point& q)
{
    return Segment(getLine(p, q),
                   p,
                   q);
}

Point
getIntersectionPoint(Segment segment,
                     Line l)
{
    double xOfIntersection;

    if(l == segment.line)
    {
        //TODO
        return Point();
    }

    // Parallel line
    if (l.a == segment.line.a)
    {
        return Point(INF,
                     INF);
    }

    // a1 * x + b1 = a2 * x + b2
    xOfIntersection = (segment.line.b - line.b) / (line.a - segment.line.a);

    if ( (xOfIntersection >= std::min(segment.p.x, segment.q.x) and
         (xOfIntersection <= std::max(segment.p.x, segment.q.x) )
    {
        return Point(xOfIntersection,
                     line.a * xOfIntersection + line.b);
    }

    // Not intersecting the segment
    return Point(INF,
                 INF);
}

int main()
{
    int                     N;
    int                     M;
    int                     index;
    Point                   tempPoint;
    Point                   tempPoint2;
    std::vector <Point>     polygonPoints;
    std::vector <Segment>   polygonSegments;
    std::vector <Point>     intersectionPoints;
    
    std::cin >> N;
    std::cin >> M;

    // Reading the n-gon points
    for (index = 0; index < N; ++index)
    {
        std::cin >> tempPoint.x;
        std::cin >> tempPoint.y;

        polygonPoints.push_back(tempPoint);
    }

    // Creating the n-gon segments
    for (index = 1; index < N; ++index)
    {
        polygonSegments.push_back(getSegment(polygonPoints[i - 1],
                                             polygonPoints[i]));
    }
    // The segment determined by the last point and the first one
    polygonSegments.push_backI(getSegment(polygonPoints[i - 1],
                                          polygonPoints[0]));

    // Reading the lines
    for (index = 0; index < M; ++index)
    {
        std::cin >> tempPoint.x;
        std::cin >> tempPoint.y;
        std::cin >> tempPoint2.x;
        std::cin >> tempPoint2.y;

        intersectionPoints.clear();
        for (const auto& segment : polygonSegments)
        {
            tempPoint = getIntersectionPoint(segment,
                                             getLine(tempPoint,
                                                     tempPoint2))
            if ( (tempPoint.x != INF) and
                 (tempPoint.y != INF) )
            {
                intersectionPoints.push_back(tempPoint);
            }
        }


    }

    
    return 0;
}

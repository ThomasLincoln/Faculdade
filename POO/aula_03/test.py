from point import Point, Square
import pytest

point1=Point(0,0)
point2=Point(2,0)
point3=Point(2,2)
point4=Point(0,2)

def test_distance():
    square = Square(point1, point2, point3, point4)
    a = square.area()
    assert a == 4
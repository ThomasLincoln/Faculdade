import math


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    def distance(self, other):
        return math.hypot(self.x - other.x, self.y - other.y)

class Square:
    def __init__ (self,ponto1, ponto2, ponto3,ponto4 ):
        self.x1 = ponto1.x
        self.y1 = ponto1.y
        self.x2 = ponto2.x
        self.y2 = ponto2.y
        self.x3 = ponto3.x
        self.y3 = ponto3.y
        self.x4 = ponto4.x
        self.y4 = ponto4.y
    def area(self):
        largura = self.x2 - self.x1
        altura = self.y4 - self.y1
        return largura * altura

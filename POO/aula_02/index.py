from math import hypot;

lucasLacerda = 'hello world!'
 
class ICarly:
    pass

class Point:
    def __init__(self, x, y):
        self.move(x, y)
        pass
    def move(self, x, y):
        self.x = x;
        self.y = y;
    # para colocar um atributo primeiro elemenro no parenteses é self
    def reset(self):
        self.x = 0;
        self.y = 0;
    def distance(self, otherPoint):
        return hypot(self.x - otherPoint.x, self.y - otherPoint.y);

    
seriePica = ICarly();

p1 = Point(3,5);
p1.reset();
p1.move(2,3)

p2 = Point(2,2);
p2.move(1,3);

print(p1.x, p1.y)

print(p2.x, p2.y);
print(p1.distance(p2))

# print(p1, p2)
# print(seriePica)
class Fila:
    def __init__(self):
        self.lista = [];
    def enqueue(self, number):
        self.lista.append(number);
    def dequeue(self):
        return self.lista.pop(0);
        

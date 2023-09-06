class Pilha:
    def __init__(self):
        self.lista = [];
    def add(self, number):
        self.lista.append(number);
    def remove(self):
        tamanho = len(self.lista);
        return self.lista.pop(tamanho-1);
        

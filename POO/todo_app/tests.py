from todoitem import TodoItem
from user import User
from todolist import TodoList


def test_categoria():
    item1 = TodoItem("Testar o código", 0);
    assert item1.nivel == 0;

def test_modify():
    item1 = TodoItem("Testar o código", 0);
    item1.modify(2)
    assert item1.nivel == 2;

def test_ordem():
    dono = User('Thomas', 'tho@mas.com')
    lista = TodoList(dono);
    # 0 = baixo, 1 = médio e 2 = alto
    item = TodoItem("fazer bolo", 0);
    item2 = TodoItem("comer alface", 2);
    item3 = TodoItem("Jogar xadrez", 1);
    lista.add(item);
    lista.add(item2);
    lista.add(item3);
    item.modify(1);
    lista.add(item);
    i =0;
    count = 1;
    for i in range(3):
        if(lista.list[i].nivel > lista.list[i+1].nivel):
            count = 1;
            break;
        else:
            count = 0;


    assert count == 0;



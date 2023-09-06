from stack import Pilha;
from fila import Fila

# def test_stack():
#     stack = Pilha();
#     stack.add(1);
#     stack.add(2);
#     p = stack.remove();
#     assert p == 2;

def test_queue():
    queue = Fila();
    queue.enqueue(42069);
    queue.enqueue(2);
    d = queue.dequeue();
    assert d == 42069;
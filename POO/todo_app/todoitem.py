class TodoItem:
    def __init__(self, description, nivel):
        self.description = description
        self.nivel = nivel
        self.done = False

    def complete(self):
        self.done = True

    def undo(self):
        self.done = False

    def is_done(self) -> bool:
        return self.done

    def change_description(self, description):
        self.description = description

    def modify(self, grau):
        self.nivel = grau;

    
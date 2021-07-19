class stack:
   def __init__(self, item):
      self.stk=[item]
   def push(self, item):
      self.stk.insert(0, item)
   def pop(self):
      return self.stk.pop(0)
   def top(self):
      return self.stk[0]

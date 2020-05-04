e = Entity.new()

e:setName("Test1")

print(e:getName())

e:setName("Test2")

print(e)

f = e:new()

f:setName("F")

print(f)

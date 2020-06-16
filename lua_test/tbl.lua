-- array
t = {}
for i = 0, 10 do
    t[i] = 0
end

print(t[4])
function f()
    print("Hello World.\n")
end

-- mult array
tt = {}
m = 0;
for i = 0, 10 do
    m = m + 1;
    tt[i] = {}
    for j = 0, 10 do
        tt[i][j] = 1
    end
end

--print(tt[0][0])
--print(tt[10][10])
--print(m)

-- list
print("list test")
list = nil
for i = 1, 10 do
    list = {next = list, value = i}
end
l = list
while l do
    print(l.value)
    l = l.next
end

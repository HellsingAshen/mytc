Set = {}
Set.mt = {} -- metatable for sets
function pt(t)
    print("Table is  " .. tostring(t))
    for k, v in pairs(t) do
        print(k, v)
    end
end


function Set.new (t)
    local set = {}
    setmetatable(set, Set.mt)
    for _, l in ipairs(t) do
        set[l] = true
    end
    return set
end
--t1 = {"a"}
--Set.new(t1)

function Set.union (a,b)
    local res = Set.new{}
    for k in pairs(a) do
        print("Set union a[" .. k .. "] is " .. k)
        res[k] = true
    end
    for k in pairs(b) do
        print("Set union b[" .. k .. "] is " .. k)
        res[k] = true
    end

    return res
end
ta= {1, 2, 3}
tb={4, 5, 6, 7}
tr = Set.union(ta, tb)
print("---------------")
pt(tr)


--function Set.intersection (a,b)
--    local res = Set.new{}
--    for k in pairs(a) do
--        res[k] = b[k]
--    end
--    return res
--end
--
--function Set.tostring (set)
--    local s = "{"
--    local sep = ""
--    for e in pairs(set) do
--        s = s .. sep .. e
--        sep = ", "
--    end
--    return s .. "}"
--end
--
--function Set.print (s)
--    print(Set.tostring(s))
--end
--
--
----
----a={1,2,3,4}
----b={nil,2,3}
----ret = Set.union(a, b)
----Set.print(ret)
----pt(ret)
--
--s1 = Set.new{10, 20, 30, 50}
--s2 = Set.new{30, 1}
--
--Set.mt.__add = Set.union
--s3 = s1 + s2;
--print(s3)
--print("-----------------------")
--Set.print(s3)
--print("###########")
--tt = {1,2,3, 10}
--tm = {2,3,4}
--tn = Set.union(tt, tm)
----print(tn)
--pt(tn)
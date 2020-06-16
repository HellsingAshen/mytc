function pt(t) do
    print("[", t, "]")
    for k,v in pairs(t) do
        print(k, v)
    end
end
end
local maxx = function (a, b)
    return ((a > b) and a) or b
end

--print(maxx(10, 11))

--print(debug.getinfo(maxx))

--pt(debug.getinfo(maxx))



debug.sethook(print, "l")

print("ashen");

function trace (event, line)
    local s = debug.getinfo(2).short_src
    print(s .. ":" .. line)
end

debug.sethook(trace, "l")


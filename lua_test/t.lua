--_G["shen"] = "SHEN"
--
--function getfield (f)
--	local v = _G
--	for w in string.gfind(f, "[%w_]+") do
--		v = v[w]
--		print(type(v), w, v)
--	end
--	return v
--end
--
--t = getfield("shen")
--
--print(t)
--

--local f="a.b.c.d.shen"
--
--function setfield1 (f, v)
--    local t = _G -- start with the table of globals
--    for w, d in string.gfind(f, "([%w_]+)(.?)") do
--        if d == "." then -- not last field?
--            --print("w , d is ", w, d)
--            t[w] = t[w] or {} -- create table if absent
--            t = t[w] -- get the table
--        else -- last field
--            t[w] = v -- do the assignment
--        end
--    end
--end
--
--setfield1(f, 10)
--local a = 1
function pt(a)
    --print(_G)
    ----setfenv(1, {})
    --setfenv(1, {_G=_G})
    ----print(_G)
    --_G.print(a)
    --_G.print(_G.a)
    print("table is ", a)
    for k, v in pairs(a) do
        print(k, v)
    end
    print("-------------")
end
----pt(a)
--
--a = 1 -- create a global variable
---- change current environment
--setfenv(1, {_G = _G})
--_G.print(a) --> nil
--_G.print(_G.a) --> 1

Account = {balance = 0}
--function Account.withdraw (self, v)
--    self.balance = self.balance - v
--end
--Account.withdraw(Account, 100);
--print(Account.balance)
--
----pt(Account)
--
--a = Account
--a.withdraw(a,10)
--print(a.balance)
--
--Account = nil
--a.withdraw(a,10)
--print(a.balance)

--function Account:withdraw(v)
--    self.balance = self.balance - v;
--end
--
--Account:withdraw(10)
--print(Account.balance)
--Account.withdraw(Account, 10)
--print(Account.balance)
a = {}
b = {}
setmetatable(a, b)
b.__mode = k
key = {} -- creates first key
a[key] = 1
key = {} -- creates second key
a[key] = 2
collectgarbage() -- forces a garbage collection cycle
for k, v in pairs(a) do print(v) end

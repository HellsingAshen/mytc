--local testa = {}
--local mt = {__mode = 'k'}
--setmetatable(testa,mt)
--
--tbl_key = {}
--g=tbl_key
--print(g, tbl_key)
--testa[tbl_key] = 1
--tbl_key = {}
--testa[tbl_key] = 2
---- l = tbl_key
----tbl_key = nil
--
----À¬»ø»ØÊÕ
--collectgarbage()
--
--local function PrintInfo()
--
--	for k, v in pairs(testa) do
--		print(k, "===", v)
--	end
--
--end

--PrintInfo()

local name = "shen"

name = name .. "jin"

print(name)

local fullname = name

fullname = fullname .. "xing"

print(fullname, name)


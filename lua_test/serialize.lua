--key = ""
--function PrintTable(table, level)
--    level = level or 1
--    local indent = ""
--    for i = 1, level do
--        indent = indent .. "  "
--    end
--
--    if key ~= "" then
--        print(indent .. key .. " " .. "=" .. " " .. "{")
--    else
--        print(indent .. "{")
--    end
--
--    key = ""
--    for k, v in pairs(table) do
--        if type(v) == "table" then
--            key = k
--            PrintTable(v, level + 1)
--        else
--            local content = string.format("%s%s = %s", indent .. "  ", tostring(k), tostring(v))
--            print(content)
--        end
--    end
--    print(indent .. "}")
--
--end
saved = {}

function basicSerialize (o)
    if type(o) == "number" then
        return tostring(o)
    else
        -- assume it is a string
        return string.format("%q", o)
    end
end

function save (name, value, saved)
    saved = saved or {} -- initial value
    io.write(name, " = ")
    if type(value) == "number" or type(value) == "string" then
        io.write(basicSerialize(value), "\n")
    elseif type(value) == "table" then
        if saved[value] then
            -- value already saved?
            -- use its previous name
            io.write(saved[value], "\n")
        else
            saved[value] = name -- save name for next time
            --print("t is ".. type(saved) .. " t is " .. type(value))
            io.write("{}\n") -- create a new table
            for k, v in pairs(value) do
                -- save its fields
                local fieldname = string.format("%s[%s]", name,
                        basicSerialize(k))
                save(fieldname, v, saved)
            end
        end
    else
        error("cannot save a " .. type(value))
    end
end

--[[
a = {x=1, y=2; {3,4,5}}
a[2] = a -- cycle
a.z = a[1] -- shared sub-table
save('a', a)
]]--

--b = { 1 }
--save("b", b, saved)
--save("b", b, saved)

b = {1, {2}}
save("b", b, saved)
save("b", b, saved)



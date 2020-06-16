
-- create co
--co = coroutine.create(function ()
--    print("hi")
--end)
--
--print(coroutine.status(co))
--
--coroutine.resume(co)
--
--print(coroutine.status(co))

--print("test co yield\n")
--co = coroutine.create(function()
--    for i=0, 10 do
--        print("i is " .. i .. "  co status is " .. coroutine.status(co))
--        coroutine.yield()
--    end
--end)
--
--coroutine.resume(co)
--coroutine.resume(co)
--coroutine.resume(co)

-- test co resume
--co = coroutine.create (function ()
--    print("co", coroutine.yield())
--end)
--
--coroutine.resume(co)
--coroutine.resume(co, 4, 5, 6)

-- test co yield
--i = nil
--j = nil
--k = nil
--co = coroutine.create(function (a,b)
--    for l=0, 10 do
--        i, j, k = coroutine.yield(a + b, a - b)
--        print(l, i, j, k)
--
--    end
--end)
--
--coroutine.resume(co, 20, 10)
--coroutine.resume(co, 20, 10)
--coroutine.resume(co, 20, 10)
--coroutine.resume(co, 20, 10)
--print(coroutine.resume(co, 20, 10))
--print(i, j, k)

-- test resume
--co = coroutine.create(function (a,b,c)
--    print("co", a,b,c)
--    --coroutine.yield(100)
--end)
--print(coroutine.resume(co, 1, 2, 3))
-- test co create and status
co = coroutine.create(function ()
    print("co start 0.")
    coroutine.yield();
    print("co start 1.")
end)
print(coroutine.status(co))

print("-----------------------------------")
coroutine.resume(co)
print(coroutine.status(co))
coroutine.resume(co)
print(coroutine.status(co))



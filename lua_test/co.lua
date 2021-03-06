-- p/s 1
print("test producer and consumer")
local p
function receive ()
    local status, value = coroutine.resume(p)
    return value
end

function send (x)
    coroutine.yield(x)
end

function producer()
    local x = 0;
    while x < 10 do
        x = x + 1;
        print("producer  " .. x)
        send(x)
    end
end

function consumer()
    while true do
        local x = receive()
        print("consumer " .. (x or "nil"))
        if (x == 9) then
            break;
        end
    end
end

p = coroutine.create(producer)
consumer()

-- p/s 2
print("test producer and consumer")
local pro = nil;

function receive (p)
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

function filter(p)
    while true do
        local x = receive(p);
        x = string.format("%d%d", x, x)
        print("filter " .. (x or "nil"))
        send(x)
    end
end

function consumer(p)
    while true do
        local x = receive(p)
        print("consumer " .. (x or "nil"))
    end
end

pro = coroutine.create(producer)
f = coroutine.create(filter(pro))
consumer(f)

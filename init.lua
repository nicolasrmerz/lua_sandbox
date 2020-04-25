hook = {}

hook.add = function(EventName, fn)
    print("Adding hook " .. EventName)
    hook[EventName] = fn
end

--CheckHook = function(EventName, ...)
--    if hook[EventName] == nil then
--        return false
--    else
--        return true
--    end
--end

--CallHook = function(EventName, ...)
--    print("In CallHook")
--    if hook[EventName] ~= nil then
--        print("ASDF")
--    end
--end

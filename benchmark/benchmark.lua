hook["unregisted"] = nil
function print_int(...)
    x = 5
end

hook.add("registered", print_int)

function CheckHook(hook_name)
    if (hook[hook_name] == nil) then
        return false
    else
        return true
    end
end

function CallHook(EventName, ...)
    return hook[EventName](arg)
end

function CheckCallHook(EventName, ...)
    if (CheckHook(EventName)) then
        return hook[EventName](arg)
    end
end

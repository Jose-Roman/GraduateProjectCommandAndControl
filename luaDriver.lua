local command = require("commandcore")
local request = command.send("PING")

print(request.message)
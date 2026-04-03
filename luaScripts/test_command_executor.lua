package.cpath = package.cpath .. ";../cmake-build-debug/?.dylib"

local executor = require("command_executor")

executor.initialize()

executor.set_duration(120)

executor.set_mission_location(1)

executor.execute_command("TEST_COMMAND")

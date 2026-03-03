import sys
sys.path.append("../cmake-build-debug")

import messaging_py as messaging
import geography_py as geo
import target_tracker_py as tracker
import command_executor_py as executor

print("command_executor_py module loaded")

# --------------------------------------------------
# Create system components
# --------------------------------------------------

msg_system = messaging.Messaging()

geography = geo.Geography()

target_tracker = tracker.TargetTracker(msg_system, geography)
target_tracker.initialize()

command_executor = executor.CommandExecutor(msg_system, target_tracker)
command_executor.initialize()

# --------------------------------------------------
# Subscribe to command status messages
# --------------------------------------------------

def status_callback(msg):
    print("\n[Python] Command Status Received")
    print("Topic:", msg.topic)
    print("Payload:", msg.payload)
    print("Source:", msg.source)

msg_system.subscribe("command.status", status_callback)

# --------------------------------------------------
# Create test command message
# --------------------------------------------------

test_msg = messaging.Message()
test_msg.topic = "command.execute"
test_msg.payload = "TestTargetPayload"
test_msg.timestamp = 0
test_msg.messageId = 0
test_msg.source = "PythonTest"

print("\n[Python] Publishing command.execute message")

msg_system.publish(test_msg)

print("\n---- Test Complete ----")

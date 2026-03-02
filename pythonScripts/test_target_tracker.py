import sys
sys.path.append("../cmake-build-debug")

import messaging_py as messaging
import geography_py as geo
import target_tracker_py as tracker

msg = messaging.Messaging()
g = geo.Geography()

t = tracker.TargetTracker(msg, g)

t.initialize()

target = tracker.Target()
target.id = 1
target.latitude = 34.05
target.longitude = -118.24
target.altitude = 20000
target.speed = 400

t.addActiveTrack(target)

active = t.getActiveTrack(1)

print("Target:", active.id, active.latitude, active.longitude)
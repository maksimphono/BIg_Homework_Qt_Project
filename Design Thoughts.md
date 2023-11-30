# Design thoughts

## Event pipe

So basically at every event loop iteration some objects will dispatch events with specified types, target objects and payloads. "Disparch" means push into the queue.
Later on the same iteration, I will pop events from the queue and for each event I will fire corresponding event handlers for specified target object, argument will be that popes event. 

### Advantages: 

Asynchronous behavour: I can limit time for each iteration, so when time limit will be exceeded, events, that were not handled will stay in the queue until next iteration, that will handle them, or until next and so on. So execution wont be blocked by some events.

## Game object status

Status is a string, that describes current status of the object (for example : idle, moved, created, deleted, etc.). It will be changed by events. It can be used to control behavour of an object, for example, to restrict objects with some status to perform some actions.
# CryptStalker – 3D Puzzle-Adventure Game
[Gameplay Video](https://www.youtube.com/watch?v=RNd0nUqskxs)

**Crypt Raider** is a first-person puzzle-adventure game built with C++ in Unreal Engine 5. The player explores ancient ruins, manipulates statues, activates pedestals, and opens passages using physics-based interaction and trap logic.

## Core Gameplay

- Physics-based object grabbing, movement, and placement using UPhysicsHandleComponent.
- Solving puzzles by placing statues on pedestals to unlock doors and pathways.
- Activating traps that create hidden hazards or open new areas.
- Dynamic environment interaction: movable walls, trap doors, and reactive platforms.
- First-person exploration and puzzle-solving inside ancient crypt environments.

## Implemented Features


###  C++-Driven Interaction System
- All core mechanics (grabbing, pedestal logic, movable structures, traps) are fully implemented in C++ without relying on Blueprints.

###  Physics-Based Grabbing System
- Realistic object pickup, movement, and placement using `UPhysicsHandleComponent`.

### Dynamic Pedestal Logic
- Pedestals automatically detect statues nearby and trigger events such as opening doors or activating traps.

### Movable Structures and Trap Activation
- Walls, doors, and trap mechanisms dynamically react based on pedestal states or trap triggers.


## Code Structure
| File | Purpose |
|:---|:---|
| `Grabber.cpp/.h` | Grabbing, releasing, and placing statues |
| `Pedestal.cpp/.h` | Pedestal behavior and statue detection |
| `Mover.cpp/.h` | Moving walls and doors based on triggers |
| `TriggerComponent.cpp/.h` | Custom trigger volumes for interaction |

## Controls

- `WASD` — Move  
- `LMB` — Grab / Release object  
- `E` — Interact with pedestal (place or take statue)  

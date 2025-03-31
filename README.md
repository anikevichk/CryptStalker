# Crypt Raider – 3D Puzzle-Adventure Game

**Crypt Raider** is a first-person puzzle-adventure game built with C++ in Unreal Engine 5. The player explores ancient ruins, manipulates statues, activates pedestals, and opens passages using physics-based interaction and trap logic.

## Core Gameplay

- **Grabber System**: Pick up, move, and release objects using a `UPhysicsHandleComponent`.
- **Pedestals**: Automatically detects nearby pedestals and places or removes statues.
- **Movable Walls & Doors**: React to the number of occupied pedestals or specific tags (e.g. `"pedestal_gold"`).
- **Trap Mechanics**: Triggered by special pedestals that control hidden trap doors or walls.
- **C++ Logic**: Includes component-based architecture, physics handling, tag-based interactions, and tracing.

## Code Structure

- `Grabber.cpp/.h` – Handles grabbing, releasing, placing, and retrieving statues.
- `Pedestal.cpp/.h` – Pedestal behavior, statue attachment, and occupancy check.
- `Mover.cpp/.h` – Moves walls or doors based on pedestal states or trap triggers.
- `TriggerComponent.cpp/.h` – Custom trigger volume for interactions.
- `Blueprints`, `Materials` – Assets from **Medieval Dungeon Pack**.

## Technologies Used

- Unreal Engine 5 (C++)
- Component system: `ActorComponent`, `StaticMeshComponent`, `PhysicsHandleComponent`
- Gameplay mechanics with `Tags`, `AttachToActor`, `SweepSingleByChannel`, `VInterpConstantTo`
- Debug tools using `DrawDebugHelpers`
- Optimized with `Tick`, `FindComponentByClass`, `GetAllActorsOfClass`

## Controls

- `WASD` — Move  
- `LMB` — Grab / Release object  
- `E` — Interact with pedestal (place or take statue)  
- `F` — Trigger trap (if implemented)


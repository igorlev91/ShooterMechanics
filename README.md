# ShooterMechanics

This demo project was born to experiment different kinds of movement mechanics and practice math applied to kinematics.
As a side effect, I ended up extending the Character Movement Component provided by Unreal Engine.
All the mechanics implemented are fully replicated and tested for multiplayer.

# Gameplay Overview

# Mechanics

* **Hook**
* **Rope**
* **Dive**
* **Sliding**

### Hook
Your character is equipped with a **grappling hook** so now you can move through the map using this fast-paced gadget. 
While you hold the button you go towards your destination but you can also leave it to just gain velocity in air and make some unexpected move :)

* You can tune how fast the hook should be and you can specify a curve defining it. 
* You can decide to handle or not a cable (`UCableComponent`) to simulate grappling hook visually.
* You can grapple to everything as long as it has the right **Tag**, which is tunable.
* You can specify how much **velocity** you **lose** after you reach your **destination** or you leave it mid-air (in percentage).
* You can enter a **montage** to animate the enter into **hook state**.

https://youtu.be/1t-Gxhfpkts

### Rope
You can attach to a **rope** and follow it until you reach the other end of it... or leave it earlier to surprise your enemy.

* This feature **overrides** the **jump** mechanic and **search** for a **rope**. If it doesn't find a rope you jump as usual.
* The **destination** is automatically **calculated**. 
* The player gets automatically **adjusted in the center of the rope**.
* You can adjust **how** much **high** you want to check for the **rope** (simulating a jump).
* You can **adjust** the position of the capsule **under the rope** (in percentage relative to capsule half height).
* You can tune how **fast** you want to **transition** to the **rope**.
* As for Hook, **everything** can be considered as a **rope** as long as it has the right **Tag**, which is tunable.
* As for Hook, you can tune the **max speed** and you can also define a **curve** for it.
* You can specify a **montage** to **jump** towards the rope.

[Showcase video](https://youtu.be/VwLMZ-khyDU)

### Dive
I implemented my version of the classical "**roll**" of souls-like games.
If you have enough velocity you go in a **dive roll**, otherwise you do a **back-dodge**.
If you're in air you gain a little boost in velocity simulating a **dash**.

[Showcase video](https://youtu.be/WYpVlWVFGNQ)

### Sliding
Using the **shift** button you can slide or crouch based on velocity. This limit is tunable.
Sliding is physics based so you gain or lose velocity on ramps depending which direction you're going.
You can also tune the braking deceleration speed.

[Showcase video](https://youtu.be/gp2dS-iwpRI)

### Multiplayer demonstration
In this video I briefly show all the mechanics implemented in a multiplayer environment with a listen-server and a client.

[Showcase video](https://youtu.be/Qg1kfCjp0oM)

### Future implementations
* Climbing ladders
* Vaulting
* Moving in cover
* Crawling

## The project

### Overview
This project is a single and multiplayer shooter that takes inspiration from various
games like Unreal Tournament, Ratchet And Clank and Call of Duty. Players can compete in various modes, both single player and multiplayer.


### Game Modes

These are the main game modes:
* **Wave Mode**: inspired by Call Of Duty Zombies round system. There will be an infinite number of rounds and players must survive as long as possible. 
You must eliminate every enemy to complete a round. At the end of the game (when the player dies) the current round will be added to a scoreboard.
This mode can be played in split screen.
* **Time Mode**: to win a game, the player must complete a limited number of rounds. 
Every round must be completed within a time limit. Every subsequent round will have a shorter time limit. 
At the end of the game (the player dies or wins the game) the current score will be added to a scoreboard. A score is defined by num. of rounds completed and total time.
This mode can be played in split screen.
* **Multiplayer**: when a new game starts all players must compete in a different number of rounds in different locations (arenas). 
Every round will be a free for all match. In order to win a round, a player must reach a certain number of eliminations. 
The player who wins most rounds will be entitled as **King of the Hill** (winner of the game).


### Enemies
Enemies should be scaled up based on what round the player is. So every round would spawn a bigger number of enemies which would also be more responsive and “smart”.

* **Zombie**: classical zombie enemy. They follow the player wherever he is and they will try to hit him with melee attacks. 
They will also be capable of jumping and avoiding traps based on the difficulty of the current round.
* **Agent**: they will be capable of searching and shooting the player with a weapon. 
Different kinds of agents (mesh) using different kinds of weapons.
* **[Still Evaluating] Boss**: big enemy spawned every x rounds capable of attacking the player using weapons or melee attacks (or also some special ability).

## Features highlight

### Shooting


Guns implemented: 
* Pistol (single-shot)
* Assault rifle (automatic fire)
* Burst rifle (burst fire)
* Launcher
* Shotgun (spread shot)

I've implemented shooting by creating a component, UWeaponFireComponent, which can be easily configured by designers. 
By configuring its properties you can create multiple kind of weapons without modifying any code.

![WeaponFireComponent.png](Screenshots/WeaponFireComponent.png)

### Throwable

Throwable objects implemented:
* Grenades, which explodes after few seconds
* Knives, which deals damage on hit someone
* Sticky bombs, which explodes as grenades bu can also sticks to surfaces

I created a base throwable class with some helper functions such as "Stick" and "Explode". 
The actual gameplay effects can be driven by designers using the Blueprint editor and some events I've exposed.

To help the player to throw objects I've implemented a visible trajectory to show where the object will lands.

Here's an example of how sticky bombs have been implemented. I launch an event when the bomb hit something and I call the **Stick** function exposed to blueprint from code.
Simultaneously, when the bomb is spawned, I start a timer and when it reaches the end the bombs "**detonate**". I launch an event and I call the **Explode** function to deal damage to near actors. 

### Aiming

In the first version I implemented aiming by simply increasing the FOV of the character camera but the result wasn't so satisfying so I decided to change it.

I created another Spring arm attached to the character and then I attached a new Camera to the new spring arm. 
So now I have two cameras attached to the player and I'm switching between them. 
Using this method I can change camera properties simply using blueprint and not from code.

I've also added other properties to give control to designers to change how much time is needed to aim and to return to hip fire. 
You can also specify a curve to switch between aiming and hip fire more gently.

![AimingConfiguration.png](Screenshots/AimingConfiguration.png)

### Aim assist

After improving aiming I decided to push even further by adding aim assist for controllers since it's a feature widely used in modern shooters.

### Multiplayer

Everything has been implemented using RPC and Replication in C++. Also working for local multiplayer.

Features working on multiplayer:
* Traps
* Health and Shield replica
* Every kind of pickable objects (health/shield regen, ammo, weapons, throwable objects)
* Shooting
* Throwable objects

### Alive UI Feeling

UI responds accordingly to player and camera movement by floating around the screen, giving a feel of an alive interface (Ratchet and Clank: Rift Apart as inspiration).

### Recoil

For guns like pistols and rifles every shot add a bits of recoil which causes a small deviation for the shot from the middle of the screen.
For shotguns recoil widens the angle which pellets will be spread.

Here's some of the properties which can be tuned.

* Recoil can be turned off/on
* Recoil Max Angle: 
  * Maximum angle within which shots can be deviated from the center of the screen
  * Maximum angle added to shotgun noise angle which pellets will be spread.
* Recoil Velocity: angle quantity added for each shot

![RecoilConfiguration.png](Screenshots/RecoilConfiguration.png)

## Features improvement

* Aim assist refinement; transitioning between aim assist active or not active using a curve to interpolate between rates of camera movement.

## All features implemented

* Player basic movement (move, look, jump, sprint)
* Player health and shield
* Shooting with various guns
* Recoil for different guns
* Different reticles for guns.
* Aiming and aim assist
* Gun inventory
* Ammo management
* Multiple throwable objects
* Predict trajectory for throwable objects
* Pickable objects on overlap, such as ammo, regen
* Pickable objects on interact, such as weapons and throwable objects
* UI health, shield, weapons, throwable objects, ammo, hit marker and kill count
* Random spawner which can generate stuff by configuring objects and probabilities
* Traps to deal damage to players
* Everything working on multiplayer and split-screen

## Currently WiP

* AI for Zombies (melee)

## Upcoming

* AI for Agents (shooting)
* New kind of traps
* Stands for directional sprints/jump
* Dash movement
* Damage direction indicator UI
* Ammo pickup UI
* Wave Mode
* Game loop completed (just for Wave mode)

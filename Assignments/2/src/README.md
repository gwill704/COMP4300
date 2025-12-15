# COMP 4300 Assignment 2 notes

## Submision 
For this assignment you will zip and submit the entire src foldesr of the assignment. 
You are NOT allowed to add any files in addition to the ones already in the src folder. 

YOU must include student name bla bla. 


## Program specification 

### Player:
- The player is represented by a shape which is defined in the config file
- The player must spawn in the center of the screen at the beginning and after dying. 
- The player moves bu a speed from config file: wasd up left down right
- The player is confined in the bounds of the window. 
- The player shoot a bulled toward the mouse pointer. Speed, size, lifespan of the bullets are
read from the config file,. 


### Special Ability
- You are free to come up with your own special move which is fired by the player when the right mouse button is clicked
This special ability must: 
    - Multiple entities (bullets etc) spawned by special weapon. 
    - Entities have some unique graphic associate with them. 
    - A unique game mechanic is introduced via a new component. 
    - A 'cooldown timer' must be implemented for the special weapon. 
the properties of the special move are not in the config file. 


### Enemies:
- Enemies will spawn random location every x frames. (config file)
- Enemies must not overlap the sides of the screen at the time of spawn. 
- Enemies shapes have random number of vertices, between a given minimum and maximum number, which is in config file. 
- Enemy shape radius will be specified in the config file
- Will be given a random color upon spawning
- Enemies have random speed upon spawning between a min and max in the config file.
- When an enemy collides with the edge of the window it should bounce in the opposite direction
- When (large) enemies collide with a bullet or player, they are destroyed, and N small enemies spawn in its place, where N is the number of vertices of the original enemy. Each small enemy must have the same number of vertices and color of the original enemy. These small entities travel outward at angles at a fixed intervals equal to (360 / vertices). For example, if the original enemy had 6 sides, the 6 smaller enemies will travel outward in intervals of (360/6) = 60 degress. Thesmaller enemies must have a radius equal to half of the original entity. 


### Score 
- Each time an enemy spawns, it is given a score component of N*100, where N is the number of vertices. Small enemies get double this value
- If a player bullet kills, the score is summed. 
- The font is displayed with the font specified on config. 


### Drawing
- All entities should be given a slow rotation, that makes the game looks a little nicer. 
- Bonus points if you add something. 
- Any Entity with a lifespan is currently alive, it should have its Color alpha channel set to ratio depending on how long it has left to live. For example, if an entity has a 100 frame life span, and it has been alive for 50 frames, its alpha value should be set to 0.5 * 255. The alpha should go from 255 when it is first spawned, to 0 on the last frame it is alive. 


### Misc:
- The P key should pause the game
- The Esc key should close the game


### Configuration file

The conf file have one line each specifying the window size, font format, player, bullet specification, and enemy specifications. 
Lines will be given in that order, with the following syntax:


#### Window W H FL FS
- This line declares that the SFML window must be constructed with width W and height H, each of which will be integers. FL is the frame limit that the window should be set to, and FS will be an integer which specifies whether to display the application in full-screen mode (1) or not (0)

#### Font F S R G B
- F font 
- S size
- RGB color

#### Player Specification 
- Player SR CR S FR FG FB OR OG OB OT V
Shape Radius SR int
Collision Radius CR int
Speed S float
Fill color FR, FG, FB int, int, int
Outline color OR, OG, OB int, int, int
Outline Thickness OT int
Shape Vertices V int

#### Enemy Specification
- Enemy SR CR SMIN SMAX OR OG OB OT VMIN VMAX L SI
Shape Radius SR int
Collision Radius CR int
Min / Max Speed SMIN, SMAX float, float
Outline Color OR, OG, OB int, int, int
Outline Thickness OT int
Min / Max Vertices VMIN, VMAX int, int
Small Lifespan L int
Spawn interval SI int

#### Bullet Specification
- Bullet SR CR S FR FG FB OR OG OB OT V L
Shape Radius SR int
Collision Radius CR int
Min / Max Speed SMIN, SMAX float, float
Outline Color OR, OG, OB int, int, int
Outline Thickness OT int
Shape Vertices V int
Small Lifespan L int



## Recommendation of approaching

0. Save the configuration file reading until later, after Entities implemented
1. Implement the Vec2 class, which you will use for all Components. 
2. Implement the basic functionality in the EntityManager class
    Implement the EntityManager's addEntity() and update() functions so you can start testing the Game class quicly. Don't worry about the update() function which deletes dead entities until later when you get more game mechanics working. 
3. Implement basics of the game class:
    a. Construct a player Entity using spawnPlayer() function
    b. Implement basic drawing of entities using the Game::sRender() function
    c. Construct some enemies using the spawnEnemy() function
    d. Construct a bullet using the spawnBullet() function. 
4. Implement Player Movement in Game::sUserInput and Game::sMovement
5. Implement the EntityManager::update() function so it deletes dead entities. 
6. Implement the EntityManager::getEntities(tag) functionality
7. Implement collisions in sCollision and entity.destroy() if it's dead.
8. Implement the rest of the game's functionality, including config file reading. 


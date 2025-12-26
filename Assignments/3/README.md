# Program specification

## Assets:
- Entities in the game will be rendered using various Textures and Animations which we will be calling Assets (along with Fonts)
- Assets are loaded once at the beginning of the program and stored in the Assets class
- All Assets are defined in assets.txt, with the syntax defined below

## Note:
- All entity positions denote the center of their rectangular sprite. It also denotes the center of the bounding box, if it has one. 
This is set via sprite.setOrigin() in the Animation class constructor. 

## Player
- The player Entity in the game is represented by Megaman, which has several different Animations: Stand, Run, and Air. You must determine which state the player is currently in and assign the correct Animation. 
- The player moves with the following controls:
Left: A key, Right: D key, Jump: W key, Shoot: Space key
- The player can only jump if it is currently standing on a tile. 
- If the jump key is held, the player should not continuously jump, bu instead it should only jump once per button press. If the player lets go of the jump key mid-jump, it should start falling back down immediately. 
- If the player moves left/right, the player's sprite will face in that direction until the other direction has been pressed. 
- Bullets shot by the player travel in the direction the player is facing. 
- The player collides with 'Tile' entities in the level (see level syntax) and cannot move through them. The player land on a Tile enitity and stand in place. 
- The player does not collide with 'Dec' (decoration) entities in the level
- If the player falls below the bottom of the screen, they respawn at the start. 
- The player should have a Gravity component which constantly accelerates it downward on the screen until it collides with a tile
- The player has a maximum speed specified in the level file (see below) which it should not exceed in either x or y direction  (should not be higher than a bounding box, to not travess it)
- The player will be given a CBoundingBox of a size specified in the level file. 
- The player's sprite and bounding box are centered on the player's position. 

## Animations:
- See below for Animation asset specification 
- Animations are implemented by storing multiple frames inside a texture
- The Animation class handles frame advancement based on animation speed
- You need to implement Animation::update() to properly progress animations. 
- Tou need to implement Animation::hasEnded() which returns true if an animation has finished its last frame, false otherwise. 
- Animations can be repeating (loop forever) or non-repeating (play once) 
- Any entity with non-repeating animation should be destroyed once its Animation's hasEnded() returns true (has finished cycle)

## Decoration Entities:
- Decoration entities ('Dec' in a level file) are simply drawn to the screen, and do not interact with any other entities in the game in any way. 
- Decorations can be given any Animation in the game, but intuitively they should be reserved for things like clouds, bushes, etc

## Tiles:
- Tiles are Entities that define the level geometry and interact with players. 
- Tiles can be given any Animation that is defined in the Assets file
- Tiles will be given a CBoundingBox equal to the size of the animation tile->get<CAnimation>().animation.getSize()
- The current animation displayed for a tile can be retrieved with:
tile->get<CAnimation>().animation.getName()
- Tiles have different behavior depending on which Animation they are given 

## Brick Tiles: 
- Brick tiles are given the 'Brick' Animation 
- When a brick tile collides with a bullet, or is hit by the player from below:
    - Its animation should change to 'Explosion' (non-repeat)
    - Non-repeating animation entities are destroyed when hasEnded() is true
    - Its CBoundingBox component should be removed

## Question Tiles: 
- Question tiles are given the 'Question' Animation when created
- When a Question tile is hit by a player from below, 2 things happen:
    - Its Animation changes to the darker 'Question2' animation
    - A temporary lifespan entity with the 'Coin' animation should appear for 30 frames, 64 pixels above the location of the Question entity

## GUI:
- You must construct a GUI using ImGui which has the following functionality:
- The GUI must display options to turn off each system independently 
- For each entity in the game, the GUI must list the ID, tag, and position of the entity. You must display a list of all entities, as well as lists of entities by their tag. You must also have some way of destroying a given entity by interacting with the UI element associated with it. (this is essentially the same as A2, to help you debugging the game).

## Rendering: 
- Entity rendering has been implemented for you
- Entities are rendered in the order they are stored in the EntityManager (basically puts the layers of the game)

## Bonus:
- Any special effects which do not alter the game play (visual)
- You may develop a 'special weapon'

## Misc:
- The 'P' key should pause the gmae
- T key toggles drawing textures
- C key toggles drawing bounding boxes of entities
- G key toggles drawing of the grid
- Esc key should go back to the Main menu, or quit if on the main menu


# Level Creation

You are required your own level (jetpack??)


# Config Files

There will be two configuration files in this assignment . The Assets file, and the Level configuration file. 


# Assets File Specification 
 
There will be three different line types in the Assets file, each of which correspond to a different type of Asset. They are as follows:

Texture Asset Specification
Texture N P
    Texture Name      N   std::string (it will have no spaces)
    Texture FilePath  P   std::string (no spaces)

Animation Asset Specification:
Animation N T F S 
    Animation Name      N   std::string (no spaces)
    Texture Name        T   std::string (refers to an existing texture)
    Frame Count         F   int (n. frames in Animation)
    Anim Speed          S   int (n. of game frames between anim frames)

Font Asset Specification:
Font N P
    Font Name           N   std::string (no space)
    Font File path      P   std::string (no space)


# Level Specification File

Game levels will be specified by a Level file, which will contain a list of entity specifications, one per line. It will also contain a single line which specifies properties of the player in that level. In this way, you can define an entire level in the data file, rather than in programming code. The syntax of the lines of the Level file are as follows. 

IMPORTANT NOTE:
    All (GX, GY) positions given in the level specification file are given in 'grid' coordinates. The 'grid' cells are of size 64x64 pixels, and the entity should be positioned such that the bottom left corner of its texture is aligned with the bottom left corner of the given grid coordinate. The grid starts at (0,0) in the bottom-left of the screen, and can be seen by pressing the 'G' key while the game is running. 

Tile Entity Specification:
Tile N GX GY
    Animation   Name    N   std::string (Animation asset name for the tile)
    GX Grid X   Pos     GX  float
    GY Grid Y   Pos     GY  float

Decoration Entity Specification:
Dec N X Y
    Animation Name  N   std::string (animation asset for this tile)
    X Position      X   float
    Y Position      Y  float

Player Specification
Player GX GY  CW CH SX SY SM GY B
    GX; GY Grid Pos  X, Y   float, float (starting position of player)
    BoundingBox W/H  CW, CH float, float
    Left/Right  Speed   SX  float
    Jump Speed          SY  float (initial jump speed)
    Max  Speed          SM  float 
    Gravity             GY  float
    Bullet Animation    B   std::string (Animation asset to use for bullets)


# Assignment hints

I recommend approaching the assignment in the following order, which will help you debug your program along the way with minimal errors. Remember, step to step and test every step. 

1. Rendering system has already been set up for you, to help you debug:
        T toggle textures.
        C toggle bounding boxes
        G toggle grid

2. Implement Animation::update() and Animation::hasEnded() at any time, it will not affect the gameplay mechanics whatsoever, just animations

3. Implement Scene_Play::loadLevel()
    Since rendering 

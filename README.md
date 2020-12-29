# cub3d

3D Game Using Raycast with C

***

#### How to play

1. how to build:

   ```
   make
   ```

2. how to play:

   ```
   ./cub3d 1.cub
   ```

3. how to play bonus mode:

   ```
   ./cub3d_bonus 2.cub
   ```

4. how to save screenshot:

   ```
   ./cub3d_bonus 2.cub --save
   ```

**Tips)**

* You can customize map file with `.cub` extensions.

  * The map file requires:

    * Screen Resolution

      ```
      R 640 640
      ```

    * Texture File paths

      ```
      NO ./textures/north.xpm
      SO ./textures/south.xpm
      EA ./textures/east.xpm
      WE ./textures/west.xpm
      ```

    * Sprite File path

      ````
      S ./textures/sprite.xpm
      ````

    * The texture, sprite file must be `.xpm` extension.

    * Floor and Ceiling Color in RGB Format

      ```
      F 0,200,100
      C 0,220,130
      ```

    * Map structure

      ```
      1111111111
      1110000001
      1000000111
      11N0000021
      1111111111
      ```

      * `0` means empty spot, `1` means wall, and `2` means sprite location.
      * The NSWE mean player's spawning directions.
      * The map has to be 'closed'.

  * If you run the program with invalid formatted map file, it will occur errors.

***

The goal of cub3d is to make something using raycast like Wolfenstein 3D, or Doom.

- Must use the miniLibX: Library for Graphic Activity in C (OpenGL or MMS based)
- Textured Wall Needed
- Display a item (sprite) 
- The left and right arrow keys of the keyboard must allow you to look left and right in the maze.
- Map File Parsing Required


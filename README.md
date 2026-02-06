
*This project has been created as part of the 42 curriculum by patquesa and adruz-to*

# cub3D

## Description

**cub3D** is a 42 School project inspired by the legendary Wolfenstein 3D game, considered the first FPS (First Person Shooter) in video game history. This project is an introduction to raycasting techniques and graphical programming.

The goal is to create a dynamic 3D view inside a maze from a first-person perspective using the **MLX42** graphics library. You'll navigate through a map defined in a `.cub` configuration file, with textured walls, floor and ceiling colors, and smooth player movement.

### Key Features

- **Raycasting engine** to render a 3D perspective from a 2D map
- **Textured walls** with different textures for each cardinal direction (North, South, East, West)
- **Floor and ceiling colors** customization
- **Smooth player controls** for movement and camera rotation
- **Collision detection** to prevent walking through walls
- **Window resolution**: 1280x720 pixels
- **Minimap display** (bonus)
- **Parsing system** for `.cub` configuration files with comprehensive validation

### Learning Objectives

- Understanding raycasting algorithms
- Working with graphics programming using MLX42
- File parsing and validation
- Mathematical calculations (trigonometry, vectors)
- Event handling and game loop implementation
- Memory management in C

## Instructions

### Prerequisites

- **Operating System**: Linux or macOS
- **Compiler**: cc
- **Make**: GNU Make
- **CMake**: For building MLX42
- **GLFW**: Graphics library dependency for MLX42
  - macOS: `brew install glfw` or `brew install cmake glfw`
  - Linux: `sudo apt-get install libglfw3-dev cmake` (Debian/Ubuntu)
- **MLX42**: Included as submodule in the project
- **Math library**: `-lm` flag for mathematical functions

### Compilation

Clone the repository and compile the project:

```bash
git clone <repository-url> cub3D
cd cub3D
make
```

The Makefile will automatically:
1. Compile the libft library
2. Build MLX42 using CMake
3. Compile all source files
4. Link everything to generate the `cub3D` executable

**Note**: The first compilation may take longer as MLX42 needs to be built.

### Available Make Commands

- `make` or `make all` - Compile the entire project
- `make clean` - Remove object files
- `make fclean` - Remove object files and executable
- `make re` - Recompile the entire project from scratch

### Running the Program

Execute the program with a map file:

```bash
./cub3D maps/valid/medium.cub
```

The project includes several test maps:
- **Valid maps**: `maps/valid/` - Properly formatted and playable maps
- **Invalid maps**: `maps/invalid/` - Maps for testing error handling

Try different maps to explore various scenarios!

### Controls

- **W / ↑**: Move forward
- **S / ↓**: Move backward
- **A**: Strafe left
- **D**: Strafe right
- **← (Left Arrow)**: Rotate camera left
- **→ (Right Arrow)**: Rotate camera right
- **ESC**: Exit the program
- **X (Window Close)**: Exit the program

## Map Configuration File Format

The `.cub` file defines the game environment with the following structure:

### Texture Paths

```
NO ./textures/north_wall.png
SO ./textures/south_wall.png
WE ./textures/west_wall.png
EA ./textures/east_wall.png
```

- `NO`: North wall texture
- `SO`: South wall texture
- `WE`: West wall texture
- `EA`: East wall texture

**Note**: MLX42 supports both `.png` and `.xpm` texture formats.

### Colors

```
F 220,100,0
C 225,30,0
```

- `F`: Floor color in RGB format (R,G,B)
- `C`: Ceiling color in RGB format (R,G,B)

### Map Layout

The map is composed of the following characters:

- `0`: Empty space (walkable)
- `1`: Wall
- `N`: Player starting position facing North
- `S`: Player starting position facing South
- `E`: Player starting position facing East
- `W`: Player starting position facing West
- ` ` (space): Void (outside the map)

### Example Map File

```
NO ./textures/north.png
SO ./textures/south.png
WE ./textures/west.png
EA ./textures/east.png

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Map Validation Rules

- The map must be surrounded by walls (`1`)
- The map must contain exactly one player starting position (`N`, `S`, `E`, or `W`)
- All configuration elements must be present and valid
- Texture files must exist and be in valid format (`.png` or `.xpm` for MLX42)
- RGB values must be in the range [0, 255]
- No invalid characters in the map
- The map must be the last element in the `.cub` file

## Project Structure

```
cub3D/
├── Makefile
├── README.md
├── include/
│   └── cub3d.h          # Main header file with structs and prototypes
├── src/
│   ├── main.c           # Entry point
│   ├── game_init.c      # Game initialization
│   ├── game_destroy.c   # Cleanup and memory management
│   ├── init/            # Initialization modules
│   ├── parser/          # Map and config parsing
│   ├── render/          # Graphics rendering and raycasting engine
│   ├── input/           # Player controls and input handling
│   └── utils/           # Utility functions
├── libft/               # Custom C library
├── MLX42/               # MLX42 graphics library
├── textures/            # Wall texture files (.png or .xpm)
└── maps/                # Map configuration files (.cub)
    ├── valid/           # Valid test maps
    └── invalid/         # Invalid maps for error testing
```

## Raycasting Algorithm

The raycasting technique works by:

1. **Casting rays** from the player's position for each vertical line on the screen
2. **Calculating distances** to walls using DDA (Digital Differential Analysis) algorithm
3. **Determining wall height** based on the distance from the player
4. **Selecting texture coordinates** based on where the ray hits the wall
5. **Rendering vertical stripes** of the appropriate texture to create a 3D effect

## Bonus Features

If you want to go further, you can implement:

- **Minimap** displayed on screen
- **Wall collisions** with sliding
- **Doors** that can open and close
- **Animated sprites**
- **Mouse rotation**
- **Floor and ceiling textures** instead of solid colors

## Testing Maps

The project includes comprehensive test maps for validation:

### Valid Maps (`maps/valid/`)
- `small_map.cub` / `small2_map.cub` - Minimal test maps
- `medium.cub` - Standard size map for testing
- `big.cub` / `big2.cub` - Large maps for performance testing
- `irregular.cub` - Map with irregular boundaries
- `short_line.cub` - Map with varying line lengths
- `customized.cub` - Custom configuration test

### Invalid Maps (`maps/invalid/`)
Error handling test cases:
- `0_border.cub` / `0_border2.cub` - Map not surrounded by walls
- `N_border.cub` - Player at border
- `open.cub` / `open_diagonal.cub` - Open map boundaries
- `2spawn.cub` - Multiple player positions
- `no_spawn.cub` - Missing player position
- `double_no.cub` / `double_color.cub` - Duplicate configuration
- `double_comma.cub` - Invalid color format
- `rgb_error.cub` - Invalid RGB values
- `no_color.cub` - Missing color configuration
- `bad_text.cub` / `rare_char.cub` - Invalid characters
- `extension.cuv` - Wrong file extension
- `empty.cub` / `no_line.cub` - Empty or incomplete files
- `line_after.cub` - Invalid content after map
- `zero_space.cub` - Spacing issues

Use these maps to verify your error handling and parsing logic.

## Exporting Configurations

To create your own maps:

1. Create a new `.cub` file
2. Define texture paths for all four directions
3. Set floor and ceiling colors
4. Design your map layout using the valid characters
5. Ensure the map is properly closed by walls
6. Place exactly one player starting position

## Submission Requirements

For 42 School submission:

- Code must be written in **C**
- Follow the **Norm** (42's coding standard)
- No memory leaks (check with `valgrind`)
- Handle errors gracefully
- Include a **Makefile** with rules: `all`, `clean`, `fclean`, `re`
- No use of prohibited functions

## Resources

### Raycasting Tutorials

- **Lode's Computer Graphics Tutorial**: [Raycasting](https://lodev.org/cgtutor/raycasting.html)
- **Permadi's Ray-Casting Tutorial**: [Ray-Casting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- **Guide by Jun Han NG**: Comprehensive cub3D walkthrough

### MLX42 Documentation

- [MLX42 GitHub Repository](https://github.com/codam-coding-college/MLX42)
- [MLX42 Documentation](https://github.com/codam-coding-college/MLX42/tree/master/docs)
- [Getting Started with MLX42](https://github.com/codam-coding-college/MLX42/blob/master/docs/Basics.md)

### Mathematical Concepts

- Trigonometry (sin, cos, tan)
- Vector mathematics
- DDA Algorithm
- Field of View (FOV) calculations

## Troubleshooting

### Common Issues

**Compilation errors with MLX42:**
- Ensure GLFW is installed: `brew install glfw` (macOS) or `sudo apt-get install libglfw3-dev` (Linux)
- Check if CMake is available: `cmake --version`
- Clean and rebuild: `make fclean && make`

**Black screen or no rendering:**
- Check if textures are loading correctly
- Verify texture file paths in the `.cub` file
- Ensure player position is valid in the map
- Check window dimensions (default: 1280x720)

**Segmentation fault:**
- Check array bounds in raycasting calculations
- Verify all malloc returns are checked
- Validate map parsing before rendering
- Use `valgrind` to detect memory leaks: `valgrind ./cub3D maps/valid/medium.cub`

**Texture distortion:**
- Review texture coordinate calculations
- Check texture file dimensions (should be power of 2 for best results)
- Verify texture loading in MLX42

**Slow performance:**
- Optimize raycasting calculations
- Reduce unnecessary rendering operations
- Check for infinite loops in game loop

**Map parsing errors:**
- Test with provided invalid maps in `maps/invalid/` to verify error handling
- Ensure proper validation of all configuration elements
- Check for duplicate or missing configuration lines

## Authors

- **patquesa** - 42 Málaga
- **adruz-to** - 42 Málaga

## Acknowledgments

- 42 School for the project subject
- 42 Málaga campus community
- Wolfenstein 3D by id Software for inspiration
- MLX42 developers at Codam Coding College
- The raycasting community for tutorials and resources

## License

This project is part of the 42 School curriculum and is intended for educational purposes.

---

*May your rays always hit their targets! 🎯*
**CUB3D** is a first-person 3D maze exploration game developed in C, inspired by the classic *Wolfenstein 3D*. This project serves as an introduction to raycasting techniques and graphical programming using the [MLX42](https://github.com/codam-coding-college/MLX42) library.

![Gameplay Demo](textures/video.gif)

## 🎯 Project Overview

The objective is to render a 3D environment from a 2D map using raycasting. Player can navigate through the maze, experiencing real-time rendering and interactions.

## 🛠️ Features

* Real-time 3D rendering using raycasting
* Player movement with keyboard controls
* Dynamic wall textures based on orientation
* Customizable floor and ceiling colors
* Map parsing with error handling
* Wall collision handling
* Minimap display

## 🚀 Getting Started

### Prerequisites

* C compiler (e.g., `gcc`)
* Make utility

### Installation

1. **Clone the repository:**

   ```bash
   git clone https://github.com/607mark/cub3d-42.git
   cd cub3d-42
   ```
2. **Build the project:**

   ```bash
   make
   ```

## 🎮 Usage

Run the game with a `.cub` map file:

```bash
./cub3d [path_to_map_file.cub]
```

### Controls

* **W/A/S/D**: Move forward/left/backward/right
* **Arrow Left/Right**: Rotate view
* **M**: Open/close minimap
* **ESC**: Exit the game


## 🧪 Testing and Debugging

* **Valgrind**: Use `valgrind` to check for memory leaks.
* **Suppression File**: A `suppression.supp` file is provided to suppress known false positives during Valgrind analysis.
* **Run Valgrind**:
  
  ```bash
  valgrind --suppressions=suppression.supp ./cub3d maps/sample_map.cub
  ```

### 🗺️ Map File Format

Map files define the game's environment and must follow a specific format:

```
NO ./textures/north_texture.png
SO ./textures/south_texture.png
WE ./textures/west_texture.png
EA ./textures/east_texture.png
F 220,100,0
C 225,30,0

111111
100001
1000N1
100001
111111
```

* **Texture Paths**: Specify the path to wall textures for each direction (NO, SO, WE, EA).
* **Floor and Ceiling Colors**: Defined in RGB format after `F` (floor) and `C` (ceiling).
* **Map Layout**:

  * `1`: Wall
  * `0`: Empty space
  * `N`, `S`, `E`, `W`: Player's starting position and orientation

Ensure the map is enclosed by walls and contains exactly one starting position.


### 🙏 Acknowledgments

* Inspired by the classic *Wolfenstein 3D* game.
* Developed as part of the 42 School curriculum.
* Utilizes the [MLX42](https://github.com/codam-coding-college/MLX42) graphics library.

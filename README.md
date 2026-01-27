# 🧱 Cub3D

A tiny 3D engine with big responsibilities — parse a world, validate it, and bring it to life with player movement and game logic.

Welcome to **Cub3D** — a 42 project inspired by early FPS games, focused on **parsing, validation, and core gameplay logic** that powers a raycasting-based renderer.

---

## 🚀 Project Overview

**cub3D** is part of the 42 school curriculum. The goal: build a simple **3D game engine** using raycasting techniques, similar to early first-person shooters like *Wolfenstein 3D*.

The project is split into multiple components:

* Parsing a custom configuration file (`.cub`)
* Validating the game map and assets
* Initializing player state
* Implementing movement, rotation, and collision logic
* Integrating with a rendering engine (MiniLibX)

---

## 🗺️ Map & Configuration Parsing

The game world is defined in a `.cub` file containing:

* Map layout
* Texture paths (N/S/E/W)
* Floor and ceiling colors
* Player start position and orientation

### Validation rules include:

* Map must be fully enclosed by walls
* Only valid characters are allowed
* Exactly one player starting position
* Correct and complete configuration data

All parsed data is stored in structured data models for safe access by the renderer and game logic.

---

## 🎮 Game Logic

The core gameplay logic handles:

* Player initialization (position and direction)
* Keyboard input handling
* Movement and rotation
* Collision detection with walls
* Continuous update of player state

This layer ensures smooth and realistic navigation through the game world while preventing invalid movement.

---

## 🧠 Key Concepts Covered

* File parsing and input validation
* Data structure design in C
* Game state management
* Collision detection
* Keyboard input handling
* Modular architecture and separation of concerns
* Collaboration with a rendering pipeline

---

## 🛠️ Technologies

* **Language:** C
* **OS:** Linux
* **Graphics Library:** MiniLibX
* **Build:** Makefile
* **Version Control:** Git

---

## 📦 How to Use

Clone the repository:

```bash
git clone https://github.com/your-username/cub3d.git
cd cub3d
```

Compile:

```bash
make
```

Run:

```bash
./cub3D maps/example.cub
```

---

## 🧪 Testing & Integration

* Created mock data and helper functions to test parsing and game logic independently of rendering
* Ensured clean integration between map data, player state, and the rendering layer
* Tested edge cases such as invalid maps and incorrect configurations

---

## 🧠 Challenges Faced

* Validating complex map structures reliably
* Ensuring accurate collision detection
* Designing data structures shared across modules
* Handling edge cases in parsing and configuration
* Coordinating logic with a separate rendering implementation

---

## 💡 Lessons Learned

* Strong validation prevents entire classes of runtime bugs
* Clean data structures simplify collaboration between modules
* Game logic and rendering must be clearly separated
* Early testing with mock data saves time later
* Small mistakes in parsing can break the entire pipeline

---

## **Division of Work**

### **Person 1: Map Parsing & Game Logic**
#### **Responsibilities:**
- **Parsing**
  - Parse the `.cub` file: extract map layout, texture paths, floor/ceiling colors.
  - Validate the map (closed walls, single player start, etc.).
  - Store map and config data in structures.
- **Game Logic**
  - Player initialization (position, direction).
  - Collision detection.
  - Key handling (movement/rotation logic).
- **Testing**
  - Provide mock data and functions for early testing of the rendering part.

---

### **Person 2: Raycasting & Rendering**
#### **Responsibilities:**
- **Raycasting**
  - Implement the raycasting algorithm.
  - Calculate wall distances and heights.
  - Handle horizontal/vertical intersections.
- **Rendering**
  - Set up MiniLibX window.
  - Draw walls, floor, ceiling (solid color at first, then add textures as a bonus).
  - Integrate with the map/player data from Person 1.
- **Graphics**
  - (Bonus) Add minimap.

---

## **Shared Tasks / Integration**
- **Testing and Debugging:** Regularly test integration between map logic and renderer.
- **Documentation:** Write simple README and code comments.


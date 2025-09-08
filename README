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
  - (Bonus) Add textures, minimap, sprites, etc.

---

## **Shared Tasks / Integration**
- **Testing and Debugging:** Regularly test integration between map logic and renderer.
- **Documentation:** Write simple README and code comments.
- **Bonus Features:** If base is complete, split up enhancements like textures, minimap, or door logic.

---

## **Sample Timeline**
1. **Week 1:**  
   - Person 1: Map parsing, validation, player structure.  
   - Person 2: Window setup, basic rendering (draw a static wall).
2. **Week 2:**  
   - Person 1: Player movement, collision, map utilities.  
   - Person 2: Raycasting, dynamic wall rendering.
3. **Week 3:**  
   - Integrate: Player moves, walls render correctly.  
   - Start on bonus features and polish.

---

## **How to Work Together**
- Define clear data structures for map and player—share header files early.
- Use stubs or mock functions to allow independent progress.
- Merge often and test as a team!

---

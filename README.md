# tetris-sfml
Group Project: Tetris Clone in C++ w/ SFML Graphics

## 📖 Project Overview

**Tetris**, originally created by Alexey Pajitnov in 1984, is a puzzle game where players arrange falling blocks (tetrominoes) to form and clear horizontal lines. Our version recreates the core mechanics while adding a modern interface and audio design using SFML.

### Key Features:
- **Main Menu** with “Start Game”, “Exit”, and an “Options” button (*placeholder for future expansion*)  
- **7 Tetromino Types** with smooth rotation and collision handling  
- **Scoring System**:
  - +100 points for each completed line  
  - +1 point per step for fast-dropping (↓ key)  
- **Next Piece Preview** window  
- **Timer-based Auto Drop** (every 450ms)  
- **Audio Feedback**:
  - Background music  
  - Sound effects for move, line-clear, placement, and menu selection

---

## 🛠️ How to Build & Run (Windows Only)

### ✅ Requirements:
- **Visual Studio 2019/2022** (Community or higher)  
- **SFML 2.5.1 or later** (linked statically or dynamically)  
- Windows 10/11 (x64)

### 🔧 Build Instructions:
1. Clone or download this repository.
2. Open the `.sln` solution file in Visual Studio.
3. Set configuration to `Release` and platform to `x64`.
4. Make sure the SFML include/lib paths are correctly set in project properties.
5. Build the project.
6. Run the generated EXE:  
   `./x64/Release/sfml-tetris.exe`


---

## 📦 Prebuilt Binary

- The compiled EXE is included in `x64/Release/`.  
- All required assets (`.ttf`, `.png`, `.mp3`, `.wav`) are in the root directory.  
- Just download the full folder, and **run `sfml-tetris.exe`** from `x64/Release`.

---

## 🤝 Project Contributors

| Name                      | Contribution Area                             |
|---------------------------|-----------------------------------------------|
| **Muhammad Husnain Fraz** | Game logic, scoring system, audio integration |
| **Syed Muhammad Saad**    | Block rendering, UI mechanics                 |
| **Alyan Shahid**          | Menu system, button interactions              |
| **Ahmad Zaheer**          | Visual Studio configuration, build setup      |

> All members collaborated on gameplay features, testing, and design polish.

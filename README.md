# 🌌 Solar System Simulation using OpenGL (C++ Project)

A 3D computer graphics project that simulates the solar system using **C++**, **OpenGL**, and **GLUT**. Explore rotating planets, moons, stars, and more with interactive camera controls, ambient lighting, and animated orbits.

---

## 🧠 Project Overview

This project creates an immersive virtual environment for visualizing the **solar system** in motion.

> 🌞 Observe the Sun, 🌍 orbit planets, 🌙 follow the Moon, and ✨ fly past stars & comets — all in real-time 3D!

---

## 🚀 Key Features

- 🌍 **Realistic Rendering** of the Sun, 8 planets, Moon, and Saturn’s rings  
- 🌀 **Animated Orbits** with accurate relative speeds and distances  
- 🧭 **Camera Controls** to rotate, zoom, and reset the view  
- 💡 **Ambient Lighting & Orbit Lines** toggle for immersive visuals  
- 🌠 **Shooting Stars & Comets** for dynamic background  
- ⚡ **Optimized Performance** using display lists

---

## 🎮 Controls

| Key | Function |
|-----|----------|
| `←` `→` `↑` `↓` | Rotate camera view |
| `i` / `o` | Zoom in / out |
| `m` | Toggle orbit lines |
| `n` | Toggle ambient lighting |
| `Home` | Reset to top view |
| `Left Mouse Click` | Switch to left-side view |

---

## 🛠 Technologies Used

- **Language**: C++
- **Graphics Library**: OpenGL (GLUT)
- **Environment**: Code::Blocks / g++ / Visual Studio
- **Concepts Applied**:
  - OpenGL Primitives
  - Lighting and Material Properties
  - Display Lists
  - Camera and View Transformations
  - Event-driven Programming (Keyboard & Mouse)

---

## 🧑‍💻 How to Run (Windows + Visual Studio 2022)

1. Install [FreeGLUT for Windows](http://www.transmissionzero.co.uk/software/freeglut-devel/)
2. In **Visual Studio 2022**:
   - Create an **Empty C++ Project**
   - Add `SolarSystem.cpp` to **Source Files**
3. Configure project:
   - **VC++ Directories → Include Directories**: Add the GLUT `include` path
   - **VC++ Directories → Library Directories**: Add the GLUT `lib` path
   - **Linker → Input → Additional Dependencies**:  
     ```
     opengl32.lib
     glu32.lib
     freeglut.lib
     ```
4. Copy GLUT `DLL` (e.g., `freeglut.dll`) into your executable's folder (or `C:\Windows\System32`)
5. Build and Run 🎉

> _Tested and working with Visual Studio 2022 on Windows 10/11_

---

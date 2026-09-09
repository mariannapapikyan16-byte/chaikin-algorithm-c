# Chaikin's Corner Cutting Algorithm Visualizer

An interactive graphical visualizer implemented in C/C++ using the `graphics.h` library to demonstrate real-time geometric refinement through **Chaikin's Corner Cutting Subdivision Algorithm**.

The algorithm recursively generates a smooth curve from a series of discrete control polygon vertices by replacing each corner with two new generated points along its adjacent edges.

---

## Features

- **Real-Time Interactive Rendering:** Visualizes the progressive subdivision step-by-step with configured frame delays.
- **Color-Coded Iterations:** 
  - **White:** Original input polygon vertices.
  - **Dark Red:** Intermediate subdivision iterations.
  - **Yellow:** Final fully smoothed output curve.
- **Floating-Point Precision:** Uses dedicated floating-point coordinate structures (`FPoint`) during subdivision calculations to prevent integer truncation errors before rasterization.
- **Configurable Subdivision Ratios:** Easily adjust iteration depth and cutting proportions (defaulted to $80\% / 20\%$).

## Technical Notes & Environment

* **Language & Paradigm:** Written strictly using standard C procedural paradigms (structs, primitive arrays, dynamic linear interpolation logic).
* **Compiler Convention:** Uses a `.cpp` source file convention to ensure seamless symbol linking and compatibility with the legacy `graphics.h` (WinBGIm) framework on modern compilers.
---

## How The Algorithm Works

For each edge defined by adjacent vertices $P_i$ and $P_{i+1}$, Chaikin's algorithm generates two new points ($Q_i$ and $R_i$) using configurable weights $a$ (higher ratio) and $b$ (lower ratio):

$$Q_i = a \cdot P_i + b \cdot P_{i+1}$$

$$R_i = b \cdot P_i + a \cdot P_{i+1}$$

Where $a + b = 1.0$ (standard ratio is $0.75 / 0.25$, tuned here to $0.8 / 0.2$).

---

## Project Structure

```text
├── chaikin.cpp      # Main source code containing algorithms and rendering loops
└── README.md        # Project documentation

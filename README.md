# Pacman

A simple ascii pacman game written in C++ using nurses for terminal based rendering.


<img width="910" height="720" alt="" src="https://github.com/user-attachments/assets/63783839-d122-4f07-8960-76c47f80d027" />

## Requirements

- A Unix-like system (Linux, macOS, or WSL on Windows)
- Ncurses library
- C++ compiler
- CMake

## Installation

### 1. Clone the repository

```bash
git clone https://github.com/elzren/Pacman.git
cd Pacman
```

### 2. Install dependencies

```bash
# Debian/Ubuntu
sudo apt install g++ cmake libncurses5-dev

# Fedora
sudo dnf install gcc-c++ cmake ncurses-devel

# Arch Linux
sudo pacman -S gcc cmake ncurses --needed

# macOS
brew install gcc cmake ncurses
```

### 3. Build the game

```bash
cmake -S . -B build
cmake --build build
```

### 4. Run the game

```bash
./build/pacman
```

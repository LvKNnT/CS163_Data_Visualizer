# CS163 Data Visualizer

An interactive desktop application for exploring common data structures and
watching their operations step by step. The project is written in C++ and uses
[raylib](https://www.raylib.com/) for graphics, audio, and input.

The application is presented as **Data Chelf** and was created for the CS163
course.

## Features

- Visualizes a singly linked list, hash table, AVL tree, and trie.
- Animates initialization, insertion, search, deletion, and update operations.
- Supports random input generation for quick demonstrations.
- Provides play/pause, replay, timeline, and animation-speed controls.
- Allows nodes to be repositioned by dragging them.
- Supports zooming and panning around the visualization canvas.
- Imports data from text files by drag-and-drop and exports the current state.
- Includes a resizable window, fullscreen mode, sound effects, music, and custom
  fonts.

> [!NOTE]
> MST and Dijkstra appear in the mode selector, but their visualizations are not
> implemented yet.

## Requirements

The supplied build script targets Windows and requires:

- Windows 10 or later
- A GCC-compatible C++ compiler (`g++`) available on `PATH`
- Git, if cloning the repository

The raylib headers and MinGW static library are already included in `include/`
and `lib/`, so a separate raylib installation is not required for the supplied
Windows build.

## Getting Started

The implementation currently lives on the `lvk` branch.

```powershell
git clone https://github.com/LvKNnT/CS163_Data_Visualizer.git
cd CS163_Data_Visualizer
git switch lvk
```

Build and launch the application from the `build` directory:

```powershell
cd build
.\build.bat
```

The script compiles every `.cpp` file under `src/`, creates `build/Game.exe`,
and launches it when compilation succeeds.

To run an existing build:

```powershell
cd build
.\Game.exe
```

Run the program from `build/`. Asset and save-file paths are resolved relative
to that directory.

## Usage

1. Select **Get started!** on the welcome screen.
2. Choose a supported data structure.
3. Use the controls on the right to initialize data or perform an operation.
4. Enter a value and select **ok**, or select **rd** to generate a random value.
5. Use the controls along the bottom to pause, replay, scrub through, or change
   the speed of an animation.

### Canvas Controls

| Input | Action |
| --- | --- |
| Left-click and drag a node | Reposition the node |
| Mouse wheel | Zoom in or out |
| Arrow keys | Pan the camera |
| `R` | Reset camera zoom and rotation |
| `Space` | Toggle fullscreen mode |

### Import and Export

To import data, drag a `.txt` file onto the application window and select
**Import**. The expected first-line content depends on the selected structure:

- Singly linked list and AVL tree: space-separated integers
- Trie: space-separated words
- Hash table: table data in the format produced by its **Export** action

Exports are written beneath `save/` in the selected structure's subdirectory.

## Project Structure

```text
CS163_Data_Visualizer/
|-- assets/        Fonts, music, sound effects, and UI textures
|-- build/         Windows build script and generated executable
|-- include/       Bundled raylib headers
|-- lib/           Bundled MinGW raylib library
|-- save/          Exported/sample data structure state
|-- src/           Application and data structure source code
|-- LICENSE
`-- README.md
```

## Current Limitations

- The supplied build setup is Windows-specific.
- MST and Dijkstra screens are placeholders.
- There is no automated test suite yet.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for
details.

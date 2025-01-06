# Paint Software - Digital Art Creation Tool

## About This Project
This project allows users to create digital art with a variety of tools, including brush pens, colors, erasers, and canvas layers. Users can create, modify, and manage layers, save and load projects, and export their creations as PNG or JPEG files.

### Key Features:
- **Brush Tools**: Pen, Eraser, Fill Bucket, Color Selection
- **Layer and Layer Management**:
  - Toggle layer visibility
  - Create, delete, and rename layers
  - Change layer opacity
  - Rearrange layers
- **File Management**:
  - Save projects to continue later
  - Load existing projects
  - Export artwork as image like PNG
- **Canvas Management**:
  - Resize canvas

## Built With:
- **Qt**: Framework for the graphical user interface (GUI).
- **C++**: Programming language used to build the system.
---

## Prerequisites
Before you can build and run the project, ensure you have the following installed:

- **Qt 5.15 or higher**: You can download and install Qt from [Qt's official website](https://www.qt.io/download).
- **C++ Compiler**: Ensure you have a compatible C++ compiler for your system. If you are on Linux, GCC is typically used. On Windows, Visual Studio or MinGW can be used.
- **CMake**: For building the project, ensure you have CMake installed. Download it from [CMake's official website](https://cmake.org/download/).

---

## Installation

### Clone the Repository:
To get started, clone the repository to your local machine in your terminal (bash).
```
git clone https://github.com/UWO-CS-3307/project-deliverable-2-hailey-s-painting-software.git
cd paint-software
```
## Build the Project:
1. Install Dependencies: Ensure that you have installed Qt and the necessary development tools on your machine.
2. Run CMake: Open a terminal in the root folder of the project and run the following commands:
  ```
  mkdir build
  cd build
  cmake ..
  ```
3. Compile the Project: After configuring with CMake, run the following command to build the project:
  ```
  make
  ```
If there is an issue with installation, you can pull the code files in this [repo](https://github.com/UWO-CS-3307/project-deliverable-2-hailey-s-painting-software)'s master branch and put the files in a new project folder and run manually.

## UI Overview: ##
- The main window contains the canvas where you can draw your artwork.
- A set of toolbar buttons on the side provides access to the brush tools, including pen and eraser.
- The layer manager allows you to control visibility, opacity, and order of the layers.
- Use the "Save/Save as" and "Load Project" options in the File menu to save and load your projects.
- You can export your project to PNG or JPEG format via the "Export Image" option and type one of the supported format at the end of your file name. (eg. example.png)

![image](https://github.com/user-attachments/assets/183666ea-c890-4811-9e3c-0ba838ef40e2)

## Creating and Editing Artwork:
- Select a brush from the toolbar and start drawing on the canvas.
- Use the eraser tool to remove parts of your artwork.
- Manage your layers from the "Layers" panel. You can create, delete, and adjust each layer’s opacity and visibility.
- When done, use the "File" menu to save your project or export it as an image file.

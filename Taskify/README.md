# Taskify – Smart Resource Scheduling Engine

Taskify is a C++ project designed to manage different types of resources (employees and servers) and automatically schedule tasks based on priority and requirements.
It demonstrates practical Object-Oriented Programming (OOP) concepts such as inheritance, polymorphism, abstract classes, and dynamic casting.

## Features

- Manage human resources with multiple skills.
- Manage server resources with CPU and RAM specifications.
- Priority-based task scheduling (High / Medium / Low).
- Automatic matching between tasks and suitable resources:
  - Skill-based matching for employees.
  - Hardware-based matching for servers.
- Clean separation between header and source files.
- Full educational version available in the `docs` folder.

## Project Structure

Taskify/
│
├── docs/
│   └── project_explanation.md
│
├── include/
│   ├── resource.h
│   ├── employee_resource.h
│   ├── server_resource.h
│   ├── task.h
│   └── scheduler.h
│
├── src/
│   ├── main.cpp
│   ├── resource.cpp
│   ├── employee_resource.cpp
│   ├── server_resource.cpp
│   ├── task.cpp
│   └── scheduler.cpp
│
└── README.md


## Build & Run

### Using g++

```bash
g++ src/*.cpp -I include -o taskify
./taskify

Educational Version
Inside the docs/ folder, you will find:

project_explanation.md

This file contains:

The original full project before splitting into headers and sources.

All detailed comments and explanations.

Notes about OOP concepts and dynamic casting.

A complete walkthrough of how the system works.

This version is for learning only and is not used in the build process.

Author

Sulaiman Al safadi
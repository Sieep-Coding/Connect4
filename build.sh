#!/bin/bash

# Exit on error
set -e

# Install dependencies (adjust according to your requirements)
echo "Installing dependencies..."
sudo apt-get update
sudo apt-get install -y build-essential cmake git

# Install Raylib
echo "Installing Raylib..."
if [ ! -d "raylib" ]; then
    git clone https://github.com/raysan5/raylib.git
fi
cd raylib
mkdir -p build
cd build
cmake ..
make
sudo make install
cd ../..

# Build the project
echo "Building the project..."
make

echo "Build completed successfully."

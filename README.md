# 3D t-SNE Plot with Mouse Control

An openFrameworks application that performs 3D t-SNE (t-Distributed Stochastic Neighbor Embedding) visualization of image datasets with interactive camera controls.

## Screenshots

![t-SNE Visualization Example](demo.jpg)

*Example of t-SNE visualization (actual application output will show image clustering in 3D space)*

## Overview

This application uses deep learning features extracted from images to create a 3D visualization where similar images are positioned closer together. The application demonstrates:

- Feature extraction from images using a pre-trained neural network (CCV)
- Dimensionality reduction using t-SNE algorithm
- 3D interactive visualization with automatic rotation
- Color-coding of different image classes

## Features

- **3D Visualization**: Images are plotted in 3D space based on their feature similarity
- **Automatic Rotation**: The plot automatically rotates for better visualization
- **Color-Coded Categories**: Different image categories are bordered with different colors:
  - Blue: Ants
  - Green: Bees
- **Interactive Controls**: GUI sliders to adjust scale and image size
- **Feature Export**: Saves extracted image features to a text file

## Dependencies

- [openFrameworks](https://openframeworks.cc/)
- ofxTSNE
- ofxGui
- ofxCcvThreaded

## How It Works

1. **Image Loading**: The application loads images from two categories (ants and bees)
2. **Feature Extraction**: Uses CCV (Convolutional Neural Network) to extract high-dimensional features from each image
3. **Dimensionality Reduction**: t-SNE algorithm reduces the high-dimensional features to 3D coordinates
4. **Visualization**: Images are rendered in 3D space with interactive controls

## Dataset

The code is configured to work with the Hymenoptera dataset (ants and bees), but can be adapted for other image collections.

## Installation

1. Clone this repository
2. Make sure you have openFrameworks and the required addons installed
3. Download the required model file (`image-net-2012.sqlite3`) for CCV
4. Update the image paths in `ofApp.cpp` to point to your dataset
5. Build and run the application

## Usage

- Use the camera controls to navigate the 3D space:
  - Click and drag to rotate the view
  - Scroll to zoom in/out
- Adjust the sliders in the GUI to change:
  - `scale`: Overall scale of the visualization
  - `imageSize`: Size of the displayed images

## Credits

Created by [bemoregt](https://github.com/bemoregt)

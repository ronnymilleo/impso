#!/usr/bin/env python3
"""
Convert PNG icon to ICO format for Windows executable.
"""

from PIL import Image
import os

def create_ico():
    # Load the main icon
    assets_dir = os.path.join(os.path.dirname(os.path.dirname(__file__)), 'assets')
    png_path = os.path.join(assets_dir, 'icon.png')
    
    if not os.path.exists(png_path):
        print(f"Error: {png_path} not found. Run generate_icon.py first.")
        return
    
    img = Image.open(png_path)
    
    # Create ICO with multiple resolutions
    icon_sizes = [(16, 16), (32, 32), (48, 48), (64, 64), (128, 128), (256, 256)]
    
    # Prepare all sizes
    icons = []
    for size in icon_sizes:
        # Resize the image
        resized = img.resize(size, Image.Resampling.LANCZOS)
        icons.append(resized)
    
    # Save as ICO
    ico_path = os.path.join(assets_dir, 'app_icon.ico')
    icons[5].save(ico_path, format='ICO', sizes=icon_sizes)
    print(f"ICO file created at: {ico_path}")
    
    return ico_path

if __name__ == "__main__":
    create_ico()

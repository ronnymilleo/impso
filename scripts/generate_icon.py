#!/usr/bin/env python3
"""
Generate a Particle Swarm Optimization (PSO) themed icon.
Creates an icon showing particles converging towards an optimum point.
"""

from PIL import Image, ImageDraw, ImageFont
import os
import math
import random

def create_icon():
    # Create a new image with a gradient background
    size = 256
    img = Image.new('RGBA', (size, size), (0, 0, 0, 0))
    draw = ImageDraw.Draw(img)
    
    # Create radial gradient background (dark blue to lighter blue)
    center_x, center_y = size // 2, size // 2
    for radius in range(size, 0, -2):
        # Calculate color based on distance from center
        intensity = int(255 * (1 - radius / size))
        color = (10 + intensity // 4, 20 + intensity // 3, 40 + intensity // 2, 255)
        draw.ellipse(
            [(center_x - radius, center_y - radius),
             (center_x + radius, center_y + radius)],
            fill=color
        )
    
    # Draw the global optimum (target) as a glowing point
    optimum_x, optimum_y = center_x, center_y
    
    # Draw glowing effect for optimum
    for glow_radius in range(30, 0, -2):
        alpha = int(100 * (1 - glow_radius / 30))
        glow_color = (255, 220, 100, alpha)
        draw.ellipse(
            [(optimum_x - glow_radius, optimum_y - glow_radius),
             (optimum_x + glow_radius, optimum_y + glow_radius)],
            fill=glow_color
        )
    
    # Draw the optimum point
    draw.ellipse(
        [(optimum_x - 8, optimum_y - 8),
         (optimum_x + 8, optimum_y + 8)],
        fill=(255, 200, 50, 255),
        outline=(255, 255, 255, 255),
        width=2
    )
    
    # Draw particles converging towards the optimum
    num_particles = 12
    random.seed(42)  # For consistent icon generation
    
    for i in range(num_particles):
        # Calculate particle position (arranged in a converging pattern)
        angle = (2 * math.pi * i) / num_particles
        
        # Create particles at different distances to show movement
        distance_factor = 0.6 + (i % 3) * 0.15
        distance = size * distance_factor / 2
        
        particle_x = center_x + int(distance * math.cos(angle))
        particle_y = center_y + int(distance * math.sin(angle))
        
        # Draw velocity vector (arrow pointing towards optimum)
        vector_length = 25
        dx = optimum_x - particle_x
        dy = optimum_y - particle_y
        norm = math.sqrt(dx**2 + dy**2)
        if norm > 0:
            dx, dy = dx/norm, dy/norm
            
            # Draw arrow line
            end_x = particle_x + int(vector_length * dx)
            end_y = particle_y + int(vector_length * dy)
            draw.line(
                [(particle_x, particle_y), (end_x, end_y)],
                fill=(100, 200, 255, 180),
                width=2
            )
            
            # Draw arrow head
            arrow_size = 6
            perpx, perpy = -dy, dx
            draw.polygon([
                (end_x, end_y),
                (end_x - int(arrow_size * dx) + int(arrow_size * perpx / 2),
                 end_y - int(arrow_size * dy) + int(arrow_size * perpy / 2)),
                (end_x - int(arrow_size * dx) - int(arrow_size * perpx / 2),
                 end_y - int(arrow_size * dy) - int(arrow_size * perpy / 2))
            ], fill=(100, 200, 255, 200))
        
        # Draw particle
        particle_size = 5 if i % 3 == 0 else 4
        draw.ellipse(
            [(particle_x - particle_size, particle_y - particle_size),
             (particle_x + particle_size, particle_y + particle_size)],
            fill=(150, 220, 255, 255),
            outline=(255, 255, 255, 200),
            width=1
        )
    
    # Add "PSO" text at the bottom
    try:
        # Try to use a font, fall back to default if not available
        font = ImageFont.truetype("arial.ttf", 32)
        font_small = ImageFont.truetype("arial.ttf", 18)
    except:
        font = ImageFont.load_default()
        font_small = ImageFont.load_default()
    
    text = "PSO"
    bbox = draw.textbbox((0, 0), text, font=font)
    text_width = bbox[2] - bbox[0]
    text_x = center_x - text_width // 2
    text_y = size - 50
    
    # Draw text with shadow
    draw.text((text_x + 2, text_y + 2), text, fill=(0, 0, 0, 128), font=font)
    draw.text((text_x, text_y), text, fill=(255, 255, 255, 255), font=font)
    
    return img

def main():
    # Create assets directory if it doesn't exist
    assets_dir = os.path.join(os.path.dirname(os.path.dirname(__file__)), 'assets')
    os.makedirs(assets_dir, exist_ok=True)
    
    # Generate and save icon
    icon = create_icon()
    icon_path = os.path.join(assets_dir, 'icon.png')
    icon.save(icon_path, 'PNG')
    print(f"Icon generated successfully at: {icon_path}")
    
    # Also create smaller versions for different uses
    for size in [64, 48, 32, 16]:
        small_icon = icon.resize((size, size), Image.Resampling.LANCZOS)
        small_path = os.path.join(assets_dir, f'icon_{size}.png')
        small_icon.save(small_path, 'PNG')
        print(f"Generated {size}x{size} icon at: {small_path}")

if __name__ == "__main__":
    main()

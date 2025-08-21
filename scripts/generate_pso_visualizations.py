#!/usr/bin/env python3
"""
Generate various PSO-related visualizations and images.
Creates illustrations showing PSO concepts like search spaces, convergence, and particle movement.
"""

from PIL import Image, ImageDraw, ImageFont
import os
import math
import random
import numpy as np

def create_optimization_landscape():
    """Create a 3D-looking optimization landscape visualization."""
    size = 512
    img = Image.new('RGBA', (size, size), (255, 255, 255, 255))
    draw = ImageDraw.Draw(img)
    
    # Create background gradient
    for y in range(size):
        intensity = int(240 - (y / size) * 60)
        draw.rectangle([(0, y), (size, y+1)], 
                      fill=(intensity, intensity, intensity + 10, 255))
    
    # Draw contour lines representing the optimization landscape
    center_x, center_y = size // 2, size // 2 + 50
    
    # Multiple local optima
    optima = [
        (center_x, center_y, 1.0),  # Global optimum
        (center_x - 120, center_y - 80, 0.7),  # Local optimum 1
        (center_x + 100, center_y - 60, 0.6),  # Local optimum 2
        (center_x + 80, center_y + 70, 0.5),   # Local optimum 3
        (center_x - 90, center_y + 60, 0.4),   # Local optimum 4
    ]
    
    # Draw contour rings for each optimum
    for opt_x, opt_y, strength in optima:
        max_radius = int(120 * strength)
        for radius in range(max_radius, 10, -5):
            # Calculate color intensity based on radius
            color_factor = 1 - (radius / max_radius)
            if strength == 1.0:  # Global optimum - golden color
                color = (
                    int(255 - 100 * color_factor),
                    int(200 - 50 * color_factor),
                    int(50 + 50 * color_factor),
                    int(100 + 155 * color_factor)
                )
            else:  # Local optima - blue tones
                color = (
                    int(100 + 100 * color_factor),
                    int(150 + 70 * color_factor),
                    int(200 + 55 * color_factor),
                    int(80 + 175 * color_factor)
                )
            
            # Draw ellipse to simulate 3D perspective
            draw.ellipse(
                [(opt_x - radius, opt_y - radius // 2),
                 (opt_x + radius, opt_y + radius // 2)],
                outline=color,
                width=2
            )
    
    # Draw particles exploring the landscape
    random.seed(123)
    num_particles = 20
    for i in range(num_particles):
        px = random.randint(50, size - 50)
        py = random.randint(100, size - 100)
        
        # Draw particle
        draw.ellipse(
            [(px - 4, py - 4), (px + 4, py + 4)],
            fill=(255, 100, 100, 255),
            outline=(200, 50, 50, 255),
            width=1
        )
        
        # Draw small trail
        for j in range(3):
            trail_x = px - (j + 1) * 8
            trail_y = py + (j + 1) * 3
            alpha = 255 - j * 60
            draw.ellipse(
                [(trail_x - 2, trail_y - 2), (trail_x + 2, trail_y + 2)],
                fill=(255, 150, 150, alpha)
            )
    
    # Add title
    try:
        font = ImageFont.truetype("arial.ttf", 24)
    except:
        font = ImageFont.load_default()
    
    draw.text((20, 20), "PSO Search Space", fill=(50, 50, 50, 255), font=font)
    
    return img

def create_convergence_graph():
    """Create a convergence graph showing fitness over iterations."""
    width, height = 600, 400
    img = Image.new('RGBA', (width, height), (245, 245, 245, 255))
    draw = ImageDraw.Draw(img)
    
    # Draw axes
    margin = 50
    axis_color = (50, 50, 50, 255)
    draw.line([(margin, height - margin), (width - margin, height - margin)], 
              fill=axis_color, width=2)  # X-axis
    draw.line([(margin, margin), (margin, height - margin)], 
              fill=axis_color, width=2)  # Y-axis
    
    # Generate convergence data (simulated)
    iterations = 100
    best_fitness = []
    avg_fitness = []
    
    # Simulate convergence behavior
    for i in range(iterations):
        # Best fitness improves rapidly at first, then plateaus
        best = 100 * math.exp(-i/20) + 5 + random.uniform(-2, 2)
        best_fitness.append(best)
        
        # Average fitness follows but with more variance
        avg = best + 20 * math.exp(-i/30) + random.uniform(-5, 5)
        avg_fitness.append(avg)
    
    # Normalize data to fit in graph
    max_val = max(max(best_fitness), max(avg_fitness))
    min_val = min(min(best_fitness), min(avg_fitness))
    
    def scale_y(val):
        return height - margin - int((val - min_val) / (max_val - min_val) * (height - 2 * margin))
    
    def scale_x(i):
        return margin + int(i / iterations * (width - 2 * margin))
    
    # Draw grid lines
    for i in range(0, 11):
        y = margin + i * (height - 2 * margin) // 10
        draw.line([(margin, y), (width - margin, y)], 
                  fill=(200, 200, 200, 100), width=1)
        
        x = margin + i * (width - 2 * margin) // 10
        draw.line([(x, margin), (x, height - margin)], 
                  fill=(200, 200, 200, 100), width=1)
    
    # Draw average fitness line
    for i in range(1, iterations):
        draw.line(
            [(scale_x(i-1), scale_y(avg_fitness[i-1])),
             (scale_x(i), scale_y(avg_fitness[i]))],
            fill=(150, 150, 250, 200),
            width=2
        )
    
    # Draw best fitness line
    for i in range(1, iterations):
        draw.line(
            [(scale_x(i-1), scale_y(best_fitness[i-1])),
             (scale_x(i), scale_y(best_fitness[i]))],
            fill=(50, 200, 50, 255),
            width=3
        )
    
    # Add labels
    try:
        font = ImageFont.truetype("arial.ttf", 14)
        font_small = ImageFont.truetype("arial.ttf", 12)
    except:
        font = ImageFont.load_default()
        font_small = ImageFont.load_default()
    
    # Title
    draw.text((width // 2 - 80, 10), "PSO Convergence", fill=(50, 50, 50, 255), font=font)
    
    # Axis labels
    draw.text((width // 2 - 30, height - 30), "Iterations", fill=(50, 50, 50, 255), font=font_small)
    
    # Rotated Y-axis label (simplified)
    draw.text((10, height // 2 - 20), "F", fill=(50, 50, 50, 255), font=font_small)
    draw.text((10, height // 2 - 5), "i", fill=(50, 50, 50, 255), font=font_small)
    draw.text((10, height // 2 + 10), "t", fill=(50, 50, 50, 255), font=font_small)
    
    # Legend
    legend_x = width - 150
    legend_y = margin + 20
    draw.line([(legend_x, legend_y), (legend_x + 30, legend_y)], 
              fill=(50, 200, 50, 255), width=3)
    draw.text((legend_x + 35, legend_y - 7), "Best Fitness", fill=(50, 50, 50, 255), font=font_small)
    
    draw.line([(legend_x, legend_y + 20), (legend_x + 30, legend_y + 20)], 
              fill=(150, 150, 250, 200), width=2)
    draw.text((legend_x + 35, legend_y + 13), "Avg Fitness", fill=(50, 50, 50, 255), font=font_small)
    
    return img

def create_particle_trajectory():
    """Create an image showing particle trajectories in 2D space."""
    size = 512
    img = Image.new('RGBA', (size, size), (20, 20, 30, 255))
    draw = ImageDraw.Draw(img)
    
    # Draw grid
    grid_color = (40, 40, 50, 100)
    for i in range(0, size, 32):
        draw.line([(i, 0), (i, size)], fill=grid_color, width=1)
        draw.line([(0, i), (size, i)], fill=grid_color, width=1)
    
    # Global best position
    gbest_x, gbest_y = size // 2, size // 2
    
    # Draw target (global best) with glow effect
    for radius in range(20, 0, -2):
        alpha = int(200 * (1 - radius / 20))
        draw.ellipse(
            [(gbest_x - radius, gbest_y - radius),
             (gbest_x + radius, gbest_y + radius)],
            fill=(255, 200, 100, alpha)
        )
    
    # Draw particles with trajectories
    random.seed(456)
    num_particles = 8
    colors = [
        (255, 100, 100),
        (100, 255, 100),
        (100, 100, 255),
        (255, 255, 100),
        (255, 100, 255),
        (100, 255, 255),
        (255, 180, 100),
        (180, 100, 255)
    ]
    
    for p in range(num_particles):
        # Generate trajectory points
        trajectory = []
        x = random.randint(50, size - 50)
        y = random.randint(50, size - 50)
        
        for step in range(15):
            trajectory.append((x, y))
            
            # Move towards global best with some randomness
            dx = (gbest_x - x) * 0.15 + random.uniform(-20, 20)
            dy = (gbest_y - y) * 0.15 + random.uniform(-20, 20)
            
            x = max(10, min(size - 10, x + int(dx)))
            y = max(10, min(size - 10, y + int(dy)))
        
        # Draw trajectory
        color = colors[p % len(colors)]
        for i in range(1, len(trajectory)):
            alpha = int(100 + (i / len(trajectory)) * 155)
            draw.line(
                [trajectory[i-1], trajectory[i]],
                fill=(*color, alpha),
                width=2
            )
        
        # Draw particle at final position
        final_x, final_y = trajectory[-1]
        draw.ellipse(
            [(final_x - 5, final_y - 5), (final_x + 5, final_y + 5)],
            fill=(*color, 255),
            outline=(255, 255, 255, 200),
            width=1
        )
        
        # Draw velocity vector
        if len(trajectory) >= 2:
            vx = trajectory[-1][0] - trajectory[-2][0]
            vy = trajectory[-1][1] - trajectory[-2][1]
            norm = math.sqrt(vx**2 + vy**2)
            if norm > 0:
                vx, vy = vx/norm * 20, vy/norm * 20
                draw.line(
                    [(final_x, final_y), 
                     (final_x + int(vx), final_y + int(vy))],
                    fill=(*color, 150),
                    width=2
                )
    
    # Add title
    try:
        font = ImageFont.truetype("arial.ttf", 20)
    except:
        font = ImageFont.load_default()
    
    draw.text((20, 20), "Particle Trajectories", fill=(255, 255, 255, 255), font=font)
    
    return img

def main():
    # Create assets directory if it doesn't exist
    assets_dir = os.path.join(os.path.dirname(os.path.dirname(__file__)), 'assets')
    os.makedirs(assets_dir, exist_ok=True)
    
    # Generate optimization landscape
    landscape = create_optimization_landscape()
    landscape_path = os.path.join(assets_dir, 'pso_landscape.png')
    landscape.save(landscape_path, 'PNG')
    print(f"PSO landscape visualization saved at: {landscape_path}")
    
    # Generate convergence graph
    convergence = create_convergence_graph()
    convergence_path = os.path.join(assets_dir, 'pso_convergence.png')
    convergence.save(convergence_path, 'PNG')
    print(f"PSO convergence graph saved at: {convergence_path}")
    
    # Generate particle trajectory visualization
    trajectory = create_particle_trajectory()
    trajectory_path = os.path.join(assets_dir, 'pso_trajectories.png')
    trajectory.save(trajectory_path, 'PNG')
    print(f"PSO particle trajectories saved at: {trajectory_path}")
    
    print("\nAll PSO visualizations generated successfully!")

if __name__ == "__main__":
    main()

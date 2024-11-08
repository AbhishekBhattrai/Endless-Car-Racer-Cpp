<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Endless Car Racer</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
            margin: 0;
            padding: 20px;
            background-color: #f4f4f4;
        }
        h1 {
            color: #333;
        }
        h2 {
            color: #555;
        }
        ul {
            margin: 10px 0;
            padding-left: 20px;
        }
        code {
            background-color: #f9f9f9;
            padding: 5px;
            border-radius: 4px;
            font-family: monospace;
        }
        .content {
            background-color: #fff;
            padding: 20px;
            border-radius: 8px;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
        }
        .section {
            margin-bottom: 20px;
        }
    </style>
</head>
<body>

<div class="content">
    <h1>Endless Car Racer</h1>
    <p><strong>Endless Car Racer</strong> is a fast-paced driving game built with the <a href="https://www.raylib.com/" target="_blank">raylib</a> library. Navigate through traffic, avoid collisions, and score points. The game offers simple controls and exciting gameplay.</p>

    <div class="section">
        <h2>Features</h2>
        <ul>
            <li><strong>Random Vehicles</strong>: Vehicles spawn randomly across lanes, increasing the challenge as the game progresses.</li>
            <li><strong>Score Tracking</strong>: Your score increases as you avoid vehicles and survive longer, with your highest score saved.</li>
            <li><strong>Responsive Controls</strong>: Use the arrow keys to move your car left or right to avoid other vehicles.</li>
            <li><strong>Game Over Screen</strong>: After a crash, view your score and high score, with options to restart or exit.</li>
        </ul>
    </div>

    <div class="section">
        <h2>Installation</h2>
        <h3>Prerequisites</h3>
        <ul>
            <li><strong>raylib</strong>: You need to have raylib installed on your system. Follow the installation guide for raylib based on your platform: <a href="https://www.raylib.com/" target="_blank">raylib installation</a>.</li>
            <li><strong>C++ Compiler</strong>: Ensure you have a C++ compiler like GCC or Clang.</li>
        </ul>

        <h3>Installing raylib</h3>
        <p>Follow the installation guide for your platform at <a href="https://www.raylib.com/" target="_blank">raylib installation guide</a>.</p>

        <h3>Clone the Repository</h3>
        <pre><code>git clone https://github.com/alintm4/Endless-Car-Racer-Cpp.git
cd endless-car-racer</code></pre>

        <h3>Build the Game</h3>
        <pre><code>g++ -o endless-car-racer main.cpp -lraylib -lm -lpthread -ldl -lrt -lX11</code></pre>

        <h3>Running the Game</h3>
        <pre><code>./endless-car-racer</code></pre>
    </div>

    <div class="section">
        <h2>How to Play</h2>
        <ul>
            <li><strong>Start the Game</strong>: Choose from the menu options to start the game, view instructions, or check your high score.</li>
            <li><strong>Control the Car</strong>: Use the left and right arrow keys to move your car between three lanes.</li>
            <li><strong>Avoid Collisions</strong>: Dodge the randomly spawning vehicles. If you collide with one, the game ends.</li>
            <li><strong>Score</strong>: Earn points by successfully avoiding vehicles. The speed of the game increases as your score grows.</li>
            <li><strong>Game Over</strong>: After a collision, your score will be displayed. Press Y to restart or N to exit.</li>
            <li><strong>High Score</strong>: Your highest score is saved and displayed in the High Score menu.</li>
        </ul>
    </div>

    <div class="section">
        <h2>Key Controls</h2>
        <ul>
            <li><strong>Arrow Keys</strong>: Move left or right between lanes.</li>
            <li><strong>Backspace</strong>: Return to the main menu.</li>
            <li><strong>Y</strong>: Restart after a game over.</li>
            <li><strong>N</strong>: Exit the game.</li>
        </ul>
    </div>

    <div class="section">
        <h2>Contributing</h2>
        <p>Feel free to fork the repository, make changes, and submit a pull request. Please ensure proper code formatting and add comments where necessary.</p>
    </div>

    <div class="section">
        <h2>License</h2>
        <p>This project is licensed under the MIT License. You can view or download the full license from the <a href="LICENSE" target="_blank">LICENSE file</a>.</p>
    </div>
</div>

</body>
</html>

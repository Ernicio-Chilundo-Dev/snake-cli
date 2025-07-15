# 🐍 Terminal Snake Game — C with ncurses

A classic **Snake game** implemented in C using the `ncurses` library.  
Play directly from the terminal with real-time keyboard controls and a growing snake tail!

---

## 🎮 Features

- ✅ Real-time gameplay with arrow key controls
- 🍎 Randomly placed food increases your score and tail
- ☠️ Collision detection with walls and the snake’s own body
- 🧠 Logic and drawing separated for clean architecture
- 📦 Terminal-based interface powered by `ncurses`

---

## 🛠 How to Compile and Run

Make sure you have `gcc` and `ncurses` installed:

### 📦 On Ubuntu/Linux:

```bash
sudo apt update
sudo apt install build-essential libncurses5-dev

🧪 Compile:
gcc -o snake_game snake_game.c -lncurses

▶️ Run:
./snake

🎮 Controls
Key	Action
Arrow Keys	Move the snake
X or x	Exit the game

📸 Preview (Text-based)

######################
#                    #
#   *                #
#                    #
#      @             #
#                    #
#                    #
#                    #
#                    #
######################
Score: 40

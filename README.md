# 🐟 Flappy Fish

A button-controlled arcade game inspired by Flappy Bird, built for embedded hardware.

**Made by:** Zaid Alrabaia & Arnob Dey Sarker

![C](https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=c&logoColor=black)
![Assembly](https://img.shields.io/badge/Assembly-6E4C13?style=for-the-badge&logo=assemblyscript&logoColor=white)
![PIC32](https://img.shields.io/badge/PIC32_Microcontroller-ED1C24?style=for-the-badge&logo=microchip&logoColor=white)

---

## Getting Started

### Prerequisites
- Windows OS
- `make` installed and available in your terminal

### Installation & Run

Navigate to the Flappy Fish directory and run:

```bash
make
make install
```

---

## How to Play

### Controls

| Button | Action |
|---|---|
| **Button 2** | Jump / Advance / Start game |
| **Button 3** | Scroll up / Return to home |
| **Button 4** | Scroll down / Move fish left |

---

### Game Flow

```
gamestate4 (Enter Initials) → gamestate0 (Home) → gamestate1 (Gameplay) → gamestate2 (Game Over)
```

#### 1. Enter Your Initials — `gamestate4`
Before playing, choose your three initials:
- **Button 4** — scroll down through characters
- **Button 3** — scroll up through characters
- **Button 2** — confirm and move to the next initial

After confirming the last initial, **Button 2** takes you to the home page.

#### 2. Home Page — `gamestate0`
- Displays the **top 3 highest scores** and their associated initials
- Press **Button 2** to start the game

#### 3. Gameplay — `gamestate1`
- Repeatedly press **Button 2** to make the fish jump and move forward
- Press **Button 4** to move the fish back along the x-axis
- The fish falls continuously if **Button 2** is not pressed
- Avoid obstacles — crashing ends the game and sends you to the Game Over page

#### 4. Game Over — `gamestate2`
- Shows your **score for the current round**
- Press **Button 3** to return to the home page and see if you've beaten a top 3 score

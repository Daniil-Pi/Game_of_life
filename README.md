# Game_of_life
Реализация игры "Жизнь" (Conway's Game of Life) с использованием библиотеки ncurses для отображения в терминале.


## **Сборка и запуск**

1. Клонируйте репозиторий:
   ```bash
   git clone https://github.com/ваш-username/Game_of_life.git
   cd Game_of_life
   ```

2. Скомпилируйте программу:
   ```bash
   gcc game_of_life -o game_of_life
   ```

3. Запустите программу, используя шаблоны из папки "data":
   ```bash
   ./game_of_life < data/название_шаблона.txt
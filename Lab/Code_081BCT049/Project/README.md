- macOS:
```bash
g++ -std=c++20 main.cpp -o clock_simulation -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system && ./clock_simulation
```

- Windows:
```bash
g++ -std=c++20 main.cpp -o clock_simulation.exe -IC:/SFML/include -LC:/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system && clock_simulation.exe
```

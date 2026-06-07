#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

// ====================== КОНСТАНТЫ ИГРЫ ======================
const int CELL_SIZE = 30;
const int MAP_WIDTH = 19;
const int MAP_HEIGHT = 21;
const int WINDOW_WIDTH = MAP_WIDTH * CELL_SIZE;
const int WINDOW_HEIGHT = MAP_HEIGHT * CELL_SIZE + 60;
const int GHOST_COUNT = 4;

// Направления движения
enum Direction { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_NONE };

// ====================== КАРТА ЛАБИРИНТА ======================
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,2,1},
    {1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,2,1},
    {1,2,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,1},
    {1,1,1,1,2,1,1,1,0,1,0,1,1,1,2,1,1,1,1},
    {0,0,0,1,2,1,0,0,0,0,0,0,0,1,2,1,0,0,0},
    {0,0,0,1,2,1,0,1,1,0,1,1,0,1,2,1,0,0,0},
    {0,0,0,1,2,0,0,1,0,0,0,1,0,0,2,1,0,0,0},
    {0,0,0,1,2,1,0,1,1,1,1,1,0,1,2,1,0,0,0},
    {0,0,0,1,2,1,0,0,0,0,0,0,0,1,2,1,0,0,0},
    {1,1,1,1,2,1,1,1,0,1,0,1,1,1,2,1,1,1,1},
    {1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,2,1},
    {1,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,2,1},
    {1,1,2,1,2,1,1,1,2,1,2,1,1,1,2,1,2,1,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// Оригинальная карта для рестарта
int originalMap[MAP_HEIGHT][MAP_WIDTH];

// ====================== ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ ======================
HWND hwndMain;
bool gameRunning = false;
bool inMainMenu = true;
bool gameWin = false;
int score = 0;

// Класс для кнопок
class ObjectButton {
public:
    int x, y, width, height;
    bool isHovered;

    ObjectButton(int w, int h, int posX, int posY) {
        width = w;
        height = h;
        x = posX;
        y = posY;
        isHovered = false;
    }

    bool isMouseOver(int mouseX, int mouseY) {
        return (mouseX >= x && mouseX <= x + width &&
            mouseY >= y && mouseY <= y + height);
    }
};

ObjectButton* btn_start = new ObjectButton(200, 50, 300, 250);
ObjectButton* btn_exit = new ObjectButton(200, 50, 300, 350);
ObjectButton* btn_restart = new ObjectButton(200, 50, 300, 250);

// ====================== ИГРОВЫЕ КЛАССЫ ======================
class GameObject {
public:
    int x, y;
    Direction dir;

    GameObject(int startX, int startY) : x(startX), y(startY), dir(DIR_NONE) {}
    virtual void draw(HDC hdc) = 0;
    virtual void update() = 0;
};

class PacMan : public GameObject {
private:
    int mouthAngle;
    bool opening;
    int animationCounter;

public:
    int lives;

    PacMan(int startX, int startY) : GameObject(startX, startY), lives(3) {
        mouthAngle = 45;
        opening = true;
        animationCounter = 0;
        dir = DIR_RIGHT;
    }

    void draw(HDC hdc) override {
        int centerX = x * CELL_SIZE + CELL_SIZE / 2;
        int centerY = y * CELL_SIZE + CELL_SIZE / 2;
        int radius = CELL_SIZE / 2 - 2;

        if (animationCounter++ > 3) {
            if (opening) {
                mouthAngle += 15;
                if (mouthAngle >= 75) opening = false;
            }
            else {
                mouthAngle -= 15;
                if (mouthAngle <= 15) opening = true;
            }
            animationCounter = 0;
        }

        double startAngle = 0, endAngle = 0;
        int angleOffset = mouthAngle;

        switch (dir) {
        case DIR_RIGHT:
            startAngle = -angleOffset;
            endAngle = angleOffset;
            break;
        case DIR_LEFT:
            startAngle = 180 - angleOffset;
            endAngle = 180 + angleOffset;
            break;
        case DIR_UP:
            startAngle = -90 - angleOffset;
            endAngle = -90 + angleOffset;
            break;
        case DIR_DOWN:
            startAngle = 90 - angleOffset;
            endAngle = 90 + angleOffset;
            break;
        default:
            startAngle = -angleOffset;
            endAngle = angleOffset;
        }

        HBRUSH brush = CreateSolidBrush(RGB(255, 255, 0));
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
        HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
        HPEN oldPen = (HPEN)SelectObject(hdc, pen);

        Pie(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius,
            centerX + radius * cos(startAngle * 3.14159 / 180),
            centerY + radius * sin(startAngle * 3.14159 / 180),
            centerX + radius * cos(endAngle * 3.14159 / 180),
            centerY + radius * sin(endAngle * 3.14159 / 180));

        SelectObject(hdc, oldPen);
        DeleteObject(pen);
        SelectObject(hdc, oldBrush);
        DeleteObject(brush);

        int eyeX = centerX, eyeY = centerY;
        switch (dir) {
        case DIR_RIGHT: eyeX += 5; eyeY -= 5; break;
        case DIR_LEFT: eyeX -= 5; eyeY -= 5; break;
        case DIR_UP: eyeX -= 3; eyeY -= 8; break;
        case DIR_DOWN: eyeX -= 3; eyeY -= 2; break;
        }

        brush = CreateSolidBrush(RGB(0, 0, 0));
        SelectObject(hdc, brush);
        Ellipse(hdc, eyeX - 3, eyeY - 3, eyeX + 2, eyeY + 2);
        SelectObject(hdc, oldBrush);
        DeleteObject(brush);
    }

    void update() override {
        int newX = x, newY = y;

        switch (dir) {
        case DIR_UP: newY--; break;
        case DIR_DOWN: newY++; break;
        case DIR_LEFT: newX--; break;
        case DIR_RIGHT: newX++; break;
        }

        if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT) {
            if (map[newY][newX] != 1) {
                x = newX;
                y = newY;

                if (map[y][x] == 2) {
                    map[y][x] = 0;
                }
            }
        }
    }

    bool canMove(Direction newDir) {
        int newX = x, newY = y;
        switch (newDir) {
        case DIR_UP: newY--; break;
        case DIR_DOWN: newY++; break;
        case DIR_LEFT: newX--; break;
        case DIR_RIGHT: newX++; break;
        }
        return (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT && map[newY][newX] != 1);
    }

    void resetAnimation() {
        mouthAngle = 45;
        opening = true;
        animationCounter = 0;
    }
};

class Ghost : public GameObject {
private:
    COLORREF color;
    int moveCounter;

    bool canSeePlayer(int playerX, int playerY) {
        int dist = abs(x - playerX) + abs(y - playerY);
        return dist <= 10;
    }

    Direction getDirectionToPlayer(int playerX, int playerY) {
        std::vector<Direction> possibleDirs;

        Direction dirs[] = { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT };
        int dx[] = { 0, 0, -1, 1 };
        int dy[] = { -1, 1, 0, 0 };

        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT && map[newY][newX] != 1) {
                possibleDirs.push_back(dirs[i]);
            }
        }

        if (possibleDirs.empty()) return DIR_NONE;

        int bestDist = 9999;
        Direction bestDir = possibleDirs[0];

        for (Direction d : possibleDirs) {
            int newX = x, newY = y;
            switch (d) {
            case DIR_UP: newY--; break;
            case DIR_DOWN: newY++; break;
            case DIR_LEFT: newX--; break;
            case DIR_RIGHT: newX++; break;
            }
            int dist = abs(newX - playerX) + abs(newY - playerY);
            if (dist < bestDist) {
                bestDist = dist;
                bestDir = d;
            }
        }

        return bestDir;
    }

public:
    Ghost(int startX, int startY, COLORREF ghostColor) : GameObject(startX, startY), color(ghostColor) {
        moveCounter = 0;
    }

    void draw(HDC hdc) override {
        int centerX = x * CELL_SIZE + CELL_SIZE / 2;
        int centerY = y * CELL_SIZE + CELL_SIZE / 2;
        int radius = CELL_SIZE / 2 - 2;

        HBRUSH brush = CreateSolidBrush(color);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

        Ellipse(hdc, centerX - radius, centerY - radius + 5, centerX + radius, centerY + radius);

        for (int i = -2; i <= 2; i++) {
            Ellipse(hdc, centerX + i * 8, centerY + radius - 5, centerX + i * 8 + 6, centerY + radius + 5);
        }

        SelectObject(hdc, oldBrush);
        DeleteObject(brush);

        brush = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, brush);
        Ellipse(hdc, centerX - 10, centerY - 5, centerX - 4, centerY + 1);
        Ellipse(hdc, centerX + 4, centerY - 5, centerX + 10, centerY + 1);
        SelectObject(hdc, oldBrush);
        DeleteObject(brush);

        brush = CreateSolidBrush(RGB(0, 0, 255));
        SelectObject(hdc, brush);

        if (dir == DIR_RIGHT || dir == DIR_NONE) {
            Ellipse(hdc, centerX - 5, centerY - 4, centerX - 1, centerY);
            Ellipse(hdc, centerX + 5, centerY - 4, centerX + 9, centerY);
        }
        else if (dir == DIR_LEFT) {
            Ellipse(hdc, centerX - 9, centerY - 4, centerX - 5, centerY);
            Ellipse(hdc, centerX + 1, centerY - 4, centerX + 5, centerY);
        }
        else {
            Ellipse(hdc, centerX - 8, centerY - 6, centerX - 4, centerY - 2);
            Ellipse(hdc, centerX + 4, centerY - 6, centerX + 8, centerY - 2);
        }

        SelectObject(hdc, oldBrush);
        DeleteObject(brush);
    }

    void update() override {
        extern PacMan* pacman;

        if (moveCounter++ < 15) return;
        moveCounter = 0;

        if (canSeePlayer(pacman->x, pacman->y)) {
            Direction chaseDir = getDirectionToPlayer(pacman->x, pacman->y);
            if (chaseDir != DIR_NONE) {
                int newX = x, newY = y;
                switch (chaseDir) {
                case DIR_UP: newY--; break;
                case DIR_DOWN: newY++; break;
                case DIR_LEFT: newX--; break;
                case DIR_RIGHT: newX++; break;
                }
                if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT && map[newY][newX] != 1) {
                    x = newX;
                    y = newY;
                    dir = chaseDir;
                    return;
                }
            }
        }

        std::vector<Direction> availableDirs;
        Direction dirs[] = { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT };

        for (int i = 0; i < 4; i++) {
            int newX = x, newY = y;
            switch (dirs[i]) {
            case DIR_UP: newY--; break;
            case DIR_DOWN: newY++; break;
            case DIR_LEFT: newX--; break;
            case DIR_RIGHT: newX++; break;
            }
            if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT && map[newY][newX] != 1) {
                if (availableDirs.size() > 1 && ((dir == DIR_UP && dirs[i] == DIR_DOWN) ||
                    (dir == DIR_DOWN && dirs[i] == DIR_UP) ||
                    (dir == DIR_LEFT && dirs[i] == DIR_RIGHT) ||
                    (dir == DIR_RIGHT && dirs[i] == DIR_LEFT))) {
                    continue;
                }
                availableDirs.push_back(dirs[i]);
            }
        }

        if (!availableDirs.empty()) {
            Direction newDir = availableDirs[rand() % availableDirs.size()];
            int newX = x, newY = y;
            switch (newDir) {
            case DIR_UP: newY--; break;
            case DIR_DOWN: newY++; break;
            case DIR_LEFT: newX--; break;
            case DIR_RIGHT: newX++; break;
            }
            if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT && map[newY][newX] != 1) {
                x = newX;
                y = newY;
                dir = newDir;
            }
        }
    }
};

// ====================== ИГРОВЫЕ ПЕРЕМЕННЫЕ ======================
PacMan* pacman;
Ghost* ghosts[GHOST_COUNT];
HDC hdcMem;
HBITMAP hbmMem;

// ====================== ФУНКЦИИ ИГРЫ ======================
void execute_application_position_and_size(HWND Form, int width, int height) {
    int screen_width = GetSystemMetrics(SM_CXSCREEN);
    int screen_height = GetSystemMetrics(SM_CYSCREEN);
    int program_left = (screen_width / 2) - (width / 2);
    int program_top = (screen_height / 2) - (height / 2);
    SetWindowPos(Form, HWND_TOP, program_left, program_top, width, height, SWP_ASYNCWINDOWPOS);
}

void SaveOriginalMap() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            originalMap[i][j] = map[i][j];
        }
    }
}

void ResetMap() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            map[i][j] = originalMap[i][j];
        }
    }
}

void UpdateScore() {
    int currentScore = 0;
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (map[i][j] == 2) currentScore += 10;
        }
    }
    score = 2440 - currentScore;
}

void ResetGame() {
    ResetMap();
    pacman->x = 9;
    pacman->y = 15;
    pacman->lives = 3;
    pacman->dir = DIR_RIGHT;
    pacman->resetAnimation();

    ghosts[0]->x = 9; ghosts[0]->y = 11; ghosts[0]->dir = DIR_NONE;
    ghosts[1]->x = 10; ghosts[1]->y = 11; ghosts[1]->dir = DIR_NONE;
    ghosts[2]->x = 8; ghosts[2]->y = 11; ghosts[2]->dir = DIR_NONE;
    ghosts[3]->x = 9; ghosts[3]->y = 10; ghosts[3]->dir = DIR_NONE;

    UpdateScore();
    gameRunning = true;
    gameWin = false;
}

void CheckCollisions() {
    for (int i = 0; i < GHOST_COUNT; i++) {
        if (pacman->x == ghosts[i]->x && pacman->y == ghosts[i]->y) {
            pacman->lives--;
            if (pacman->lives <= 0) {
                gameRunning = false;
                gameWin = false;
            }
            else {
                pacman->x = 9;
                pacman->y = 15;
                pacman->dir = DIR_RIGHT;
                ghosts[0]->x = 9; ghosts[0]->y = 11;
                ghosts[1]->x = 10; ghosts[1]->y = 11;
                ghosts[2]->x = 8; ghosts[2]->y = 11;
                ghosts[3]->x = 9; ghosts[3]->y = 10;
            }
            break;
        }
    }

    // Проверка победы
    int dotsLeft = 0;
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (map[i][j] == 2) dotsLeft++;
        }
    }
    if (dotsLeft == 0) {
        gameRunning = false;
        gameWin = true;
    }
}

void DrawMap(HDC hdc) {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            int x = j * CELL_SIZE;
            int y = i * CELL_SIZE;

            if (map[i][j] == 1) {
                HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));
                HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
                Rectangle(hdc, x, y, x + CELL_SIZE, y + CELL_SIZE);
                SelectObject(hdc, oldBrush);
                DeleteObject(brush);
            }
            else if (map[i][j] == 2) {
                HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
                HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
                Ellipse(hdc, x + CELL_SIZE / 2 - 3, y + CELL_SIZE / 2 - 3, x + CELL_SIZE / 2 + 3, y + CELL_SIZE / 2 + 3);
                SelectObject(hdc, oldBrush);
                DeleteObject(brush);
            }
        }
    }
}

void DrawUI(HDC hdc) {
    char buffer[100];
    sprintf_s(buffer, sizeof(buffer), "Score: %d", score);
    TextOutA(hdc, 10, WINDOW_HEIGHT - 50, buffer, (int)strlen(buffer));

    sprintf_s(buffer, sizeof(buffer), "Lives: ");
    TextOutA(hdc, 200, WINDOW_HEIGHT - 50, buffer, (int)strlen(buffer));

    HBRUSH brush = CreateSolidBrush(RGB(255, 255, 0));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
    for (int i = 0; i < pacman->lives; i++) {
        Ellipse(hdc, 260 + i * 30, WINDOW_HEIGHT - 60, 280 + i * 30, WINDOW_HEIGHT - 40);
    }
    SelectObject(hdc, oldBrush);
    DeleteObject(brush);
}

// ====================== ОБРАБОТЧИК ОКНА ======================
LRESULT CALLBACK GameWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        SetTimer(hwnd, 1, 50, NULL);
        SaveOriginalMap();
        pacman = new PacMan(9, 15);
        ghosts[0] = new Ghost(9, 11, RGB(255, 0, 0));
        ghosts[1] = new Ghost(10, 11, RGB(255, 184, 255));
        ghosts[2] = new Ghost(8, 11, RGB(0, 255, 255));
        ghosts[3] = new Ghost(9, 10, RGB(255, 184, 82));
        ResetGame();
        return 0;

    case WM_TIMER:
        if (gameRunning) {
            pacman->update();
            for (int i = 0; i < GHOST_COUNT; i++) {
                ghosts[i]->update();
            }
            UpdateScore();
            CheckCollisions();
            InvalidateRect(hwnd, NULL, FALSE);
        }
        break;

    case WM_KEYDOWN:
        if (gameRunning) {
            switch (wParam) {
            case VK_UP:
                if (pacman->canMove(DIR_UP)) pacman->dir = DIR_UP;
                break;
            case VK_DOWN:
                if (pacman->canMove(DIR_DOWN)) pacman->dir = DIR_DOWN;
                break;
            case VK_LEFT:
                if (pacman->canMove(DIR_LEFT)) pacman->dir = DIR_LEFT;
                break;
            case VK_RIGHT:
                if (pacman->canMove(DIR_RIGHT)) pacman->dir = DIR_RIGHT;
                break;
            case VK_ESCAPE:
                gameRunning = false;
                inMainMenu = true;
                ShowWindow(hwnd, SW_HIDE);
                ShowWindow(hwndMain, SW_SHOW);
                InvalidateRect(hwndMain, NULL, TRUE);
                break;
            }
        }
        break;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP hbmMem = CreateCompatibleBitmap(hdc, WINDOW_WIDTH, WINDOW_HEIGHT);
        HGDIOBJ oldBitmap = SelectObject(hdcMem, hbmMem);

        RECT rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
        HBRUSH bgBrush = CreateSolidBrush(RGB(0, 0, 0));
        FillRect(hdcMem, &rect, bgBrush);
        DeleteObject(bgBrush);

        DrawMap(hdcMem);

        for (int i = 0; i < GHOST_COUNT; i++) {
            ghosts[i]->draw(hdcMem);
        }

        pacman->draw(hdcMem);
        DrawUI(hdcMem);

        BitBlt(hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdcMem, 0, 0, SRCCOPY);

        SelectObject(hdcMem, oldBitmap);
        DeleteDC(hdcMem);
        DeleteObject(hbmMem);

        EndPaint(hwnd, &ps);
        break;
    }

    case WM_DESTROY:
        KillTimer(hwnd, 1);
        delete pacman;
        for (int i = 0; i < GHOST_COUNT; i++) delete ghosts[i];
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// ====================== ОБРАБОТЧИК ОКНА МЕНЮ ======================
LRESULT CALLBACK MenuWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE:
        execute_application_position_and_size(hWnd, 800, 600);
        SetWindowText(hWnd, L"Pacman Game");
        return 0;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        RECT rect;
        GetClientRect(hWnd, &rect);

        HBRUSH bgBrush = CreateSolidBrush(RGB(0, 0, 0));
        FillRect(hdc, &rect, bgBrush);
        DeleteObject(bgBrush);

        if (inMainMenu) {
            HFONT hFont = CreateFont(48, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_PITCH, L"Arial");
            HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
            SetTextColor(hdc, RGB(255, 255, 0));
            SetBkMode(hdc, TRANSPARENT);
            DrawText(hdc, L"PACMAN GAME", -1, &rect, DT_CENTER | DT_TOP);
            SelectObject(hdc, oldFont);
            DeleteObject(hFont);

            hFont = CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_PITCH, L"Arial");
            oldFont = (HFONT)SelectObject(hdc, hFont);

            RECT startRect = { btn_start->x, btn_start->y, btn_start->x + btn_start->width, btn_start->y + btn_start->height };
            HBRUSH btnBrush = CreateSolidBrush(btn_start->isHovered ? RGB(0, 100, 0) : RGB(0, 128, 0));
            FillRect(hdc, &startRect, btnBrush);
            DeleteObject(btnBrush);
            DrawText(hdc, L"START GAME", -1, &startRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            RECT exitRect = { btn_exit->x, btn_exit->y, btn_exit->x + btn_exit->width, btn_exit->y + btn_exit->height };
            btnBrush = CreateSolidBrush(btn_exit->isHovered ? RGB(100, 0, 0) : RGB(128, 0, 0));
            FillRect(hdc, &exitRect, btnBrush);
            DeleteObject(btnBrush);
            DrawText(hdc, L"EXIT", -1, &exitRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            SelectObject(hdc, oldFont);
            DeleteObject(hFont);
        }
        else {
            HFONT hFont = CreateFont(36, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_PITCH, L"Arial");
            HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
            SetTextColor(hdc, gameWin ? RGB(0, 255, 0) : RGB(255, 0, 0));
            SetBkMode(hdc, TRANSPARENT);
            const wchar_t* msg = gameWin ? L"YOU WIN!" : L"GAME OVER!";
            DrawText(hdc, msg, -1, &rect, DT_CENTER | DT_TOP);
            SelectObject(hdc, oldFont);
            DeleteObject(hFont);

            hFont = CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_PITCH, L"Arial");
            oldFont = (HFONT)SelectObject(hdc, hFont);

            RECT restartRect = { btn_restart->x, btn_restart->y, btn_restart->x + btn_restart->width, btn_restart->y + btn_restart->height };
            HBRUSH btnBrush = CreateSolidBrush(btn_restart->isHovered ? RGB(0, 100, 0) : RGB(0, 128, 0));
            FillRect(hdc, &restartRect, btnBrush);
            DeleteObject(btnBrush);
            DrawText(hdc, L"PLAY AGAIN", -1, &restartRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            RECT exitRect = { btn_exit->x, btn_exit->y + 100, btn_exit->x + btn_exit->width, btn_exit->y + 100 + btn_exit->height };
            btnBrush = CreateSolidBrush(btn_exit->isHovered ? RGB(100, 0, 0) : RGB(128, 0, 0));
            FillRect(hdc, &exitRect, btnBrush);
            DeleteObject(btnBrush);
            DrawText(hdc, L"EXIT", -1, &exitRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            SelectObject(hdc, oldFont);
            DeleteObject(hFont);

            wchar_t scoreText[50];
            swprintf(scoreText, 50, L"FINAL SCORE: %d", score);
            hFont = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_PITCH, L"Arial");
            oldFont = (HFONT)SelectObject(hdc, hFont);
            SetTextColor(hdc, RGB(255, 255, 255));
            RECT scoreRect = { 0, 200, rect.right, 250 };
            DrawText(hdc, scoreText, -1, &scoreRect, DT_CENTER);
            SelectObject(hdc, oldFont);
            DeleteObject(hFont);
        }

        EndPaint(hWnd, &ps);
        return 0;
    }

    case WM_MOUSEMOVE: {
        POINT pt;
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        if (inMainMenu) {
            btn_start->isHovered = btn_start->isMouseOver(pt.x, pt.y);
            btn_exit->isHovered = btn_exit->isMouseOver(pt.x, pt.y);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else {
            btn_restart->isHovered = btn_restart->isMouseOver(pt.x, pt.y);
            btn_exit->isHovered = btn_exit->isMouseOver(pt.x, pt.y - 100);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        return 0;
    }

    case WM_LBUTTONDOWN: {
        POINT pt;
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        if (inMainMenu) {
            if (btn_start->isMouseOver(pt.x, pt.y)) {
                inMainMenu = false;
                ShowWindow(hWnd, SW_HIDE);

                // Создаем окно игры
                WNDCLASSEX wc = {};
                wc.cbSize = sizeof(WNDCLASSEX);
                wc.lpfnWndProc = GameWndProc;
                wc.hInstance = GetModuleHandle(NULL);
                wc.lpszClassName = L"GameWindow";
                wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
                wc.hCursor = LoadCursor(NULL, IDC_ARROW);
                RegisterClassEx(&wc);

                HWND hwndGame = CreateWindowEx(0, L"GameWindow", L"Pac-Man Game",
                    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                    CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,
                    NULL, NULL, GetModuleHandle(NULL), NULL);

                ShowWindow(hwndGame, SW_SHOW);
                UpdateWindow(hwndGame);

                // Отдельный цикл сообщений для окна игры
                MSG msg;
                while (GetMessage(&msg, NULL, 0, 0)) {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                    if (!IsWindow(hwndGame)) break;
                }

                // Возвращаемся в меню
                inMainMenu = true;
                ShowWindow(hWnd, SW_SHOW);
                InvalidateRect(hWnd, NULL, TRUE);
            }
            else if (btn_exit->isMouseOver(pt.x, pt.y)) {
                PostQuitMessage(0);
            }
        }
        else {
            if (btn_restart->isMouseOver(pt.x, pt.y)) {
                inMainMenu = true;
                gameRunning = false;
                InvalidateRect(hWnd, NULL, TRUE);
            }
            else if (btn_exit->isMouseOver(pt.x, pt.y - 100)) {
                PostQuitMessage(0);
            }
        }
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

// ====================== ГЛАВНАЯ ФУНКЦИЯ ======================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    srand((unsigned int)time(NULL));

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = MenuWndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"PacmanMenuWindow";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx(&wcex);

    hwndMain = CreateWindow(L"PacmanMenuWindow", L"Pacman Game", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 800, 600, NULL, NULL, hInstance, NULL);

    if (!hwndMain) return FALSE;

    ShowWindow(hwndMain, nCmdShow);
    UpdateWindow(hwndMain);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

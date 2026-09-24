#include <raylib.h>

int main(void){
    int ballX{400}, ballY{300};
    Color green = {20, 160, 133, 255};

    // inicialização da tela com as medidas, o nome do programa e o fps
    constexpr int width{800}, height{600};
    InitWindow(width, height, "Game Test");
    SetTargetFPS(60);

    // Game Loop
    while (WindowShouldClose() == false) {
        // Event Handling
        if(IsKeyDown(KEY_D))
            ballX += 3;
        else if(IsKeyDown(KEY_A))
            ballX -= 3;
        else if(IsKeyDown(KEY_W))
            ballY -= 3;
        else if(IsKeyDown(KEY_S))
            ballY += 3;

        // Updating Positions


        // Drawing
        BeginDrawing();
            ClearBackground(green);
            DrawCircle(ballX, ballY, 20, WHITE);
        EndDrawing();
    }
    


    // fecha o programa e a janela
    CloseWindow();
    return 0;
}
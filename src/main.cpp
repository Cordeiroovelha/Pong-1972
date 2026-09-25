#include <raylib.h>

int player_score{0}, cpu_score{0};
Sound hit_sound;
Sound wall_sound;
Sound score_sound;
class Ball{
public:
    float x, y;
    int speed_x, speed_y, radius;

    void Draw(){
        DrawCircle(x, y, radius, WHITE);
    }

    void Updade(){
        x += speed_x;
        y += speed_y;

        if(y + radius >= GetScreenHeight() || y - radius <= 0){
            speed_y *= -1;
            PlaySound(wall_sound);
        }
            
        if(x + radius >= GetScreenWidth()){
            player_score++;
            PlaySound(score_sound);
            ResetBall();
        }
            
        if(x - radius <= 0){
            cpu_score++;
            PlaySound(hit_sound);
            ResetBall();
        }
            
    }

    void ResetBall(){
        x = GetScreenWidth()/2;
        y =GetScreenHeight()/2;

        int speed_choices[2] = {1, -1};
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
        
    }
};
class Player{
public:
    float x, y;
    float width, height;
    int speed;

    void Draw(){
        DrawRectangle(x, y, width, height, WHITE);
    }

    void Update(){
        if(IsKeyDown(KEY_UP))
            y = y-speed;
        if (IsKeyDown(KEY_DOWN))
            y = y + speed;
        
        LimitMovement();
    }

protected:
    void LimitMovement(){
        if(y <= 0)
            y = 0;
        if(y + height >= GetScreenHeight())
            y = GetScreenHeight() - height;
    }
};

class AI: public Player{
public:
    void Update(int ball_y){
        if(y + height/2 > ball_y)
            y = y - speed;
        if(y + height/2 <= ball_y)
            y = y + speed;
        
        LimitMovement();
    }
};

Ball ball;
Player player;
AI cpu;

int main(void){
    // inicialização da tela com as medidas, o nome do programa e o fps
    constexpr int scream_width{950}, scream_height{550};
    InitWindow(scream_width, scream_height, "Ping Pong");
    SetTargetFPS(60);

    //sound
    InitAudioDevice();
    hit_sound = LoadSound("src/hit_sound.ogg");
    wall_sound  = LoadSound("src/wall_sound.ogg");
    score_sound = LoadSound("src/score_sound.ogg");

    // check if sounds are ok
    if (!IsSoundValid(hit_sound))   TraceLog(LOG_WARNING, "hit_sound.ogg NAO carregado!");
    if (!IsSoundValid(wall_sound))  TraceLog(LOG_WARNING, "wall_sound.ogg NAO carregado!");
    if (!IsSoundValid(score_sound)) TraceLog(LOG_WARNING, "score_sound.ogg NAO carregado!");

    // Volume
    SetSoundVolume(hit_sound,   0.7f);
    SetSoundVolume(wall_sound,  0.5f);
    SetSoundVolume(score_sound, 0.9f);

    ball.radius = 20;
    ball.x = scream_width / 2;
    ball.y = scream_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width = 25;
    player.height = 120;
    player.x = 10;
    player.y = scream_height / 2 - player.height / 2;
    player.speed = 6;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = scream_width - cpu.width - 10;
    cpu.y = scream_height / 2 - cpu.height / 2;
    cpu.speed = 4;

    // Game Loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        // Event Handling


        // Updating Positions
        ball.Updade();
        player.Update();
        cpu.Update(ball.y);

        // checkiing for collisions
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,
            Rectangle{player.x, player.y, player.width, player.height}))
            ball.speed_x *= -1;
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,
            Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
            ball.speed_x *= -1;


        // Drawing
        
            ClearBackground(BLACK);
            DrawLine(scream_width / 2, 0,scream_width / 2, scream_height, WHITE);
            DrawText(TextFormat("%i",player_score), scream_width/4 -20, 20, 80, WHITE);
            DrawText(TextFormat("%i",cpu_score), 3 * scream_width/4 -20, 20, 80, WHITE);
            ball.Draw();
            player.Draw();
            cpu.Draw();
        EndDrawing();
    }
    // free the audio resources
    UnloadSound(hit_sound);
    UnloadSound(wall_sound);
    UnloadSound(score_sound);
    CloseAudioDevice();

    // fecha o programa e a janela
    CloseWindow();
    return 0;
}
#include "raylib.h"
#include <math.h>
#include <time.h>

typedef struct {
    int x;
    int y;
} Position;
Position get_coordinates_for_angle_rad(int posX, int posY, double hypotenuse_length, double angle_rad) { // posX and posY being the coordinates of the center of the angle
    double length_of_adjacent_side = hypotenuse_length * cos(angle_rad);
    double length_of_opposite_side = hypotenuse_length * sin(angle_rad);
    Position final_pos;
    final_pos.x = round(posX + length_of_adjacent_side);
    final_pos.y = round(posY + length_of_opposite_side);


    return final_pos;
}


void DrawSquareWithCenterPos (int posX, int posY, int length_side, Color colour) {
    int length_center_to_side = round(length_side / 2);
    int newPosX = posX - length_center_to_side;
    int newPosY = posY - length_center_to_side;
    DrawRectangle(newPosX, newPosY, length_side, length_side, colour);
}

Position get_coordinates_for_angle_deg(int posX, int posY, double hypotenuse_length, double angle_deg) {
    double angle_rad = angle_deg * PI / 180;
    Position final_pos = get_coordinates_for_angle_rad(posX, posY, hypotenuse_length, angle_rad);
    return final_pos;
}

void DrawWin1_0StyleHands(int centerX, int centerY, double hypotenuse_length, double angle_deg, Color colour, double diameter_core_left, double diameter_core_right, double diameter_core_back) {
    Position pos1 = get_coordinates_for_angle_deg(centerX, centerY, hypotenuse_length, angle_deg);
    Position pos2 = get_coordinates_for_angle_deg(centerX, centerY, diameter_core_left, angle_deg - 90);
    Position pos3 = get_coordinates_for_angle_deg(centerX, centerY, diameter_core_right, angle_deg + 90);
    Position pos4 = get_coordinates_for_angle_deg(centerX, centerY, diameter_core_back, angle_deg + 180);
    DrawLine(pos1.x, pos1.y, pos2.x, pos2.y, colour);
    DrawLine(pos2.x, pos2.y, pos4.x, pos4.y, colour);
    DrawLine(pos3.x, pos3.y, pos4.x, pos4.y, colour);
    DrawLine(pos3.x, pos3.y, pos1.x, pos1.y, colour);

}

void DrawDial(int centerX, int centerY, int sizeSquare, Color colourSquare, Color colourPixel) {
    int angle_dial = -90;

    Position dial;
    for (int i = 0; i < 12; i++) {
        angle_dial = (i * 30) - 90;
        dial = get_coordinates_for_angle_deg(centerX, centerY, 170, angle_dial);
        DrawSquareWithCenterPos(dial.x, dial.y, sizeSquare, colourSquare);

        for (int j = 1; j < 5; j++) { // to understand why j has to be 1, modify that value to 0 and see by yourself
            angle_dial = ((i * 30) + (j * 6)) - 90;
            dial = get_coordinates_for_angle_deg(centerX, centerY, 170, angle_dial);
            DrawPixel(dial.x, dial.y, colourPixel);
        }
    }
}

int main () {
    time_t time_raw;
    struct tm *human_readable_t;


    InitWindow(600, 480, "Kl0ck");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        time(&time_raw);
        human_readable_t = localtime(&time_raw);
        BeginDrawing();

        ClearBackground(WHITE);

        DrawDial(300, 240, 10, BLACK, BLACK);

        /* old int angle_dial = -90;

        Position dial;
        for (int i = 0; i < 12; i++) {
            angle_dial = (i * 30) - 90;
            dial = get_coordinates_for_angle_deg(300, 240, 170, angle_dial);
            DrawSquareWithCenterPos(dial.x, dial.y, 10, BLACK);

            for (int j = 1; j < 5; j++) { // to understand why j has to be 1, modify that value to 0 and see by yourself
                angle_dial = ((i * 30) + (j * 6)) - 90;
                dial = get_coordinates_for_angle_deg(300, 240, 170, angle_dial);
                DrawPixel(dial.x, dial.y, BLACK);
            }
        } */
        double angle_sec_deg = ((human_readable_t->tm_sec) * 6) - 90;
        double angle_min_deg = (((human_readable_t->tm_min) * 6)  + ((human_readable_t->tm_sec) * 0.1) - 90);
        double angle_hour_deg = (((human_readable_t->tm_hour)*30) + ((human_readable_t->tm_min) * 0.5) + ((human_readable_t->tm_sec) * 0.00833333333333) - 90);  // Pretty big calculations, huh
        Position hand1 = get_coordinates_for_angle_deg(300, 240, 150, angle_sec_deg);
        DrawLine(300, 240, hand1.x, hand1.y, RED);

        //old Position hand2 = get_coordinates_for_angle_deg(300, 240, 150, angle_min_deg);
        //old DrawLine(300, 240, hand2.x, hand2.y, BLACK);

        DrawWin1_0StyleHands(300, 240, 150, angle_min_deg, BLACK, 5, 5, 15);

        //old Position hand3 = get_coordinates_for_angle_deg(300, 240, 100, angle_hour_deg);
        //old DrawLine(300, 240, hand3.x, hand3.y, BLACK);

        DrawWin1_0StyleHands(300, 240, 100, angle_hour_deg, BLACK, 5, 5, 15);


        EndDrawing();
    }

    CloseWindow();

    return 0;
}

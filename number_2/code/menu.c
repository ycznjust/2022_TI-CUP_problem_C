/*
 * @Author: ksn
 * @Date: 2022-07-27 15:34:35
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-07-27 19:16:16
 */
#include "menu.h"
#include "psk_GPIO.h"
#include "psk_OLED.h"

#define KEY1 GPIO_READ(1, 1)
#define KEY2 GPIO_READ(1, 4)

uint8 pointer = 0;
uint8 speed = 0.0;

void KEY_INIT(void)
{
    GPIO_INIT_IN(1, 1);
    GPIO_INIT_IN(1, 4);
}

int KEY_Scan(void)
{
    while (1)
    {
        if (!KEY1)
        {
            while (1)
            {
                if (KEY1)
                {
                    return 1;
                }
            }
        }
        else if (!KEY2)
        {
            while (1)
            {
                if (KEY2)
                {
                    return 2;
                }
            }
        }
    }
}

void UI_MainMenu(void)
{
    OLED_Clear();
    OLED_ShowString(2, 0, "Mission 1", 8);
    OLED_ShowString(2, 1, "Mission 2", 8);
    OLED_ShowString(2, 2, "Mission 3", 8);
    OLED_ShowString(2, 3, "Mission 4", 8);
    OLED_ShowString(2, 4, "Mission 5", 8);

    OLED_ShowString(82, pointer, "<-", 8);
}
void CTRL_MainMenu(void)
{
    while (1)
    {
        UI_MainMenu();
        switch (KEY_Scan())
        {
        case 1:
            pointer = (pointer + 1) % 5;
            UI_MainMenu();
            break;
        case 2:
            switch (pointer)
            {
            case 0:
                OLED_Clear();
                OLED_ShowString(0, 3, "Mission running", 8);
                // Mission 1
                OLED_Clear();
                OLED_ShowString(0, 3, "Mission Complete", 8);
                delay_ms(2000);
                break;
            case 1:
                OLED_Clear();
                OLED_ShowString(0, 3, "Mission running", 8);
                // Mission 2
                OLED_Clear();
                OLED_ShowString(0, 3, "Mission Complete", 8);
                delay_ms(2000);
                break;
            case 2:
                UI_Mission3();
                CTRL_Mission3();
                break;
            case 3:
                OLED_Clear();
                OLED_ShowString(0, 3, "Mission running", 8);
                // Mission 4
                OLED_Clear();
                OLED_ShowString(0, 3, "Mission Complete", 8);
                delay_ms(2000);
                break;
            case 4:
                OLED_Clear();
                OLED_ShowString(0, 3, "Mission Running", 8);
                // Mission 5
                OLED_Clear();
                OLED_ShowString(0, 3, "Mission Complete", 8);
                delay_ms(2000);
                break;
            default:
                break;
            }
        default:
            break;
        }
    }
}

void UI_Mission3(void)
{
    OLED_Clear();
    OLED_ShowString(10, 3, "Speed: ", 8);
    OLED_ShowNum(64, 3, speed, 2, 8);
    OLED_ShowString(82, 3, "dm/s", 8);
}

void CTRL_Mission3(void)
{
    while (1)
    {
        switch (KEY_Scan())
        {
        case 1:
            speed = (speed + 1) % 11;
            UI_Mission3();
            break;
        case 2:
            OLED_Clear();
            OLED_ShowString(0, 3, "Mission Running", 8);
            // Mission3
            OLED_Clear();
            OLED_ShowString(0, 3, "Mission Complete", 8);
            delay_ms(2000);
            return;
            break;
        default:
            break;
        }
    }
}

#include <drive_speed.h>
#include <enc.h>
#include <odometry.h>
#include <sonar_sensors.h>

#define MIN_DIST 3.8
#define WHEEL_BASE 1.24
#define ARC_LENGTH 2.08


int main(void)
{
    chSysInit();
    halInit();
    drive_Speed_Init();
    lld_Odometry_Init();
    serial_Init();

    uint16_t distanceLeftSonar = 0, placeWidth = 0;
    float placeLength = 0, nowDist = 0;

    bool searchingPlace = true, parking1 = false, parking2 = false;

    uint16_t firstDistanceLeftSonar = get_sonar_dist(leftSonar, 4);

    while (true)
    {
        if(searchingPlace)
        {
            drive_Direction_Control(true);
            drive_Speed_Control(1.3);
            distanceLeftSonar = get_sonar_dist(leftSonar, 4);
            placeWidth = distanceLeftSonar - firstDistanceLeftSonar;
            if(placeWidth < 150)
            {
                enc_ticks = 0;
                dist = 0;
                prev_dist = 0;
            }
            else
            {
                placeLength = get_distance();
                if(placeLength > MIN_DIST)
                {
                    drive_Speed_Control(0);
                    JENYA_FUNCTION();

                    enc_ticks = 0;
                    dist = 0;
                    prev_dist = 0;

                    searchingPlace = false;
                    parking1 = true;
                }
            }
        }

        if(parking1)
        {
            KOLYA_FUNCTION();
            nowDist = get_distance();
            drive_Direction_Control(false);

            if(nowDist > -ARC_LENGTH)
            {
                drive_Speed_Control(1.3);
            }
            else
            {
                JENYA_FUNCTION();

                enc_ticks = 0;
                dist = 0;
                prev_dist = 0;

                parking1 = false;
                parking2 = true;
            }

        }

        if(parking2)
        {
            KOLYA_FUNCTION();
            nowDist = get_distance();
            drive_Direction_Control(false);

            if(nowDist > -ARC_LENGTH)
            {
                drive_Speed_Control(1.3);
            }
            else
            {
                JENYA_FUNCTION();

                enc_ticks = 0;
                dist = 0;
                prev_dist = 0;

                parking2 = false;

                KOLYA_FUNCTION();
            }
        }

    }
}

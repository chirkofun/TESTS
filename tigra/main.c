#include <drive_speed.h>
#include <enc.h>
#include <odometry.h>
#include <sonar_sensors.h>

#define MIN_DIST 3.8
#define


int main(void)
{
    chSysInit();
    halInit();
    drive_Speed_Init();
    lld_Odometry_Init();
    serial_Init();

    uint16_t distanceLeftSonar = 0, placeWidth = 0;
    float placeLength = 0;
    bool searchingPlace = true, parking = false;
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
                    searchingPlace = false;
                    parking = true;
                }
            }
        }

        if(parking)
        {
            KOLYA_FUNCTION();
            drive_Direction_Control(false);
            drive_Speed_Control(1.3);

        }

    }
}

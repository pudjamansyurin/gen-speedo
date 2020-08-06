#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

#ifdef SIMULATOR
/* Macro prototypes ------------------------------------------------------- */
#define MCU_SPEED_MAX             (uint8_t) 255
#define MCU_RPM_MAX              (uint32_t) 99999
#define VCU_ODOMETER_MAX         (uint32_t) 99999

/* Enum prototypes ------------------------------------------------------- */
typedef enum {
    SW_M_DRIVE = 0,
    SW_M_TRIP,
    SW_M_REPORT,
    SW_M_MAX = 2
} SW_MODE;

typedef enum {
    SW_M_DRIVE_ECONOMY = 0,
    SW_M_DRIVE_STANDARD,
    SW_M_DRIVE_SPORT,
    SW_M_DRIVE_PERFORMANCE,
    SW_M_DRIVE_MAX = 3,
} SW_MODE_DRIVE;

typedef enum {
    SW_M_TRIP_A = 0,
    SW_M_TRIP_B,
    SW_M_TRIP_ODO,
    SW_M_TRIP_MAX = 2,
} SW_MODE_TRIP;

typedef enum {
    SW_M_REPORT_RANGE = 0,
    SW_M_REPORT_AVERAGE,
    SW_M_REPORT_MAX = 1,
} SW_MODE_REPORT;

/* Struct prototypes ------------------------------------------------------- */
typedef struct {
    struct {
        uint8_t signal;
        uint8_t speed;
        uint32_t odometer;
    } d;
} vcu_t;

typedef struct {
    struct {
        uint32_t rpm;
        uint32_t temperature;
    }  d;
} mcu_t;

typedef struct {
    struct {
        uint8_t soc;
    } d;
} bms_t;

typedef struct {
    struct {
        struct {
            char mode[SW_M_DRIVE_MAX+1][12];
        } drive;
        struct {
            char mode[SW_M_TRIP_MAX+1][7];
        } trip;
        struct {
            char mode[SW_M_REPORT_MAX+1][6];
            char unit[SW_M_REPORT_MAX+1][11];
        } report;
    } ref;
    struct {
        struct {
            uint8_t abs;
            uint8_t mirror;
            uint8_t lamp;
            uint8_t warning;
            uint8_t overheat;
            uint8_t finger;
            uint8_t keyless;
            uint8_t daylight;
            uint8_t sein_left;
            uint8_t sein_right;
        } status;
        struct {
            uint8_t reverse;
            uint8_t hide;
            SW_MODE sel;

            uint8_t val[SW_M_MAX+1];
            uint8_t report;
            uint32_t trip;
        } mode;
    } d;
} hmi1_t;
#endif

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();
protected:
    uint32_t ticker;
};

#endif // SCREEN1VIEW_HPP

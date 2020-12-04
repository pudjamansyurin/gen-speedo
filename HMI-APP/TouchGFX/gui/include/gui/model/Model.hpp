#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdint.h>
#include <stdlib.h>

//#define LCD_TESTING
//#define SIMULATOR

#if !defined(SIMULATOR) || defined(LCD_TESTING)
#include "_defines_shared.h"
#endif

/* Exported enum  ------------------------------------------------------------*/
typedef enum {
	INDICATOR_REVERSE = 0,
	INDICATOR_GO,
	INDICATOR_ABS,
	INDICATOR_MIRRORING,
	INDICATOR_LAMP,
	INDICATOR_WARNING,
	INDICATOR_OVERHEAT,
	INDICATOR_FINGER,
  INDICATOR_UNKEYLESS,
	INDICATOR_LOWBAT,
	INDICATOR_MAX = 9
} INDICATOR;

#if defined(SIMULATOR) && !defined(LCD_TESTING)
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
    SW_M_TRIP_ODO = 0,
    SW_M_TRIP_A,
    SW_M_TRIP_B,
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
            uint8_t abs;
            uint8_t mirroring;
            uint8_t lamp;
            uint8_t warning;
            uint8_t overheat;
            uint8_t finger;
            uint8_t keyless;
            uint8_t daylight;
        } status;
        struct {
            uint8_t left;
            uint8_t right;
        } sein;
        struct {
            uint8_t reverse;
            uint8_t hide;
            uint8_t sel;

            uint8_t val[SW_M_MAX+1];
            uint8_t report;
            uint32_t trip;
        } mode;
    } d;
} hmi1_t;
#endif

class ModelListener;

class Model
{
public:
	Model();

	void bind(ModelListener *listener)
			{
		modelListener = listener;
	}

	void tick();

	uint8_t readCurrentIndicator();
	uint8_t readIndicatorState(uint8_t index);
	void generateRandomIndicators();
	void reloadIndicators();
	void swipeIndicator();
	protected:
	ModelListener *modelListener;
	uint32_t ticker;
	uint8_t indicator;
	uint8_t indicators[INDICATOR_MAX + 1];
};

#endif // MODEL_HPP

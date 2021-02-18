#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdint.h>
#include <stdlib.h>

#if !defined(SIMULATOR)
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
  INDICATOR_UNREMOTE,
  INDICATOR_LOWBAT,
  INDICATOR_MAX = 9
} INDICATOR;

#if defined(SIMULATOR)
/* Macro prototypes ------------------------------------------------------- */
#define MCU_SPEED_MAX             (uint8_t) 150
#define MCU_RPM_MAX              (uint32_t) 99999
#define VCU_ODOMETER_MAX         (uint32_t) 99999

/* Enum prototypes ------------------------------------------------------- */
typedef enum {
  HBAR_M_DRIVE = 0,
  HBAR_M_TRIP,
  HBAR_M_REPORT,
  HBAR_M_MAX = 3
} HBAR_MODE;

typedef enum {
  HBAR_M_DRIVE_ECONOMY = 0,
  HBAR_M_DRIVE_STANDARD,
  HBAR_M_DRIVE_SPORT,
  HBAR_M_DRIVE_PERFORMANCE,
  HBAR_M_DRIVE_MAX = 4,
} HBAR_MODE_DRIVE;

typedef enum {
  HBAR_M_TRIP_A = 0,
  HBAR_M_TRIP_B,
	HBAR_M_TRIP_ODO,
  HBAR_M_TRIP_MAX = 3,
} HBAR_MODE_TRIP;

typedef enum {
  HBAR_M_REPORT_RANGE = 0,
  HBAR_M_REPORT_AVERAGE,
  HBAR_M_REPORT_MAX = 2,
} HBAR_MODE_REPORT;

/* Struct prototypes ------------------------------------------------------- */
typedef struct {
  struct {
    uint8_t signal;
    uint8_t speed;
  } d;
} vcu_t;

typedef struct {
  struct {
    uint32_t rpm;
    uint32_t temperature;
  } d;
} mcu_t;

typedef struct {
  struct {
    uint8_t soc;
  } d;
} bms_t;

typedef struct {
	uint8_t mode[HBAR_M_MAX];
	uint8_t report;
	uint32_t trip;
} hbar_data_t;

typedef struct {
  uint8_t m;
  hbar_data_t d;
	uint8_t reverse;
	uint8_t hide;
} hbar_t;

typedef struct {
	hbar_t hbar;
  struct {
    struct {
      uint8_t abs;
      uint8_t mirroring;
      uint8_t lamp;
      uint8_t warning;
      uint8_t overheat;
      uint8_t unfinger;
      uint8_t unremote;
      uint8_t daylight;
    } state;
    struct {
      uint8_t left;
      uint8_t right;
    } sein;
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

#if defined(SIMULATOR)
  void generateRandomIndicators();
#endif
  uint8_t readCurrentIndicator();
  uint8_t readIndicatorState(uint8_t index);
  void reloadIndicators();
  void swipeIndicator();
  protected:
  ModelListener *modelListener;
  uint32_t ticker;
  uint8_t indicator;
  uint8_t indicators[INDICATOR_MAX + 1];
};

#endif // MODEL_HPP

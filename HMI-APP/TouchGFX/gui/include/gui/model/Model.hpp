#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdint.h>
#include <stdlib.h>

#if !defined(SIMULATOR)
#include "_defs_shared.h"
#endif

/* Exported enum  ------------------------------------------------------------*/
typedef enum {
  INDICATOR_REVERSE = 0,
  INDICATOR_GO,
  INDICATOR_NONE,
  INDICATOR_ABS,
  INDICATOR_MIRRORING,
  INDICATOR_LAMP,
  INDICATOR_WARNING,
  INDICATOR_OVERHEAT,
  INDICATOR_FINGER,
  INDICATOR_UNREMOTE,
  INDICATOR_LOWBAT,
  INDICATOR_MAX = 10
} INDICATOR;

#if defined(SIMULATOR)
/* Macro prototypes ------------------------------------------------------- */
#define MCU_SPEED_MAX_KPH ((uint8_t)140)
#define MCU_DISCUR_MAX ((uint8_t)220)
#define BMS_LOWBAT_PERCENT ((uint8_t)20)

/* Enum prototypes ------------------------------------------------------- */
typedef enum {
  HBAR_M_DRIVE = 0,
  HBAR_M_TRIP,
  HBAR_M_PREDICTION,
  HBAR_M_MAX = 3
} HBAR_MODE;

typedef enum {
  HBAR_M_DRIVE_ECONOMY = 0,
  HBAR_M_DRIVE_STANDARD,
  HBAR_M_DRIVE_SPORT,
  HBAR_M_DRIVE_MAX = 3,
} HBAR_MODE_DRIVE;

typedef enum {
  HBAR_M_TRIP_A = 0,
  HBAR_M_TRIP_B,
  HBAR_M_TRIP_ODO,
  HBAR_M_TRIP_MAX = 3,
} HBAR_MODE_TRIP;

typedef enum {
  HBAR_M_PREDICTION_RANGE = 0,
  HBAR_M_PREDICTION_EFFICIENCY,
  HBAR_M_PREDICTION_MAX = 2,
} HBAR_MODE_PREDICTION;

/* Struct prototypes ------------------------------------------------------- */
typedef struct {
  uint8_t run;
  uint8_t soc;
} bms_data_t;

typedef struct {
  uint8_t run;
  float discur;
  uint8_t speed;
} mcu_data_t;

typedef struct {
  uint8_t connected;
  uint32_t tick;
  uint8_t signal;
  int8_t state;
  bms_data_t bms;
  mcu_data_t mcu;
} vcu_data_t;

typedef struct {
  vcu_data_t d;
} vcu_t;

typedef struct {
  uint8_t mode[HBAR_M_MAX];
  uint8_t prediction;
  uint16_t trip;
} hbar_data_t;

typedef struct {
  uint8_t m;
  hbar_data_t d;
  uint8_t reverse;
  uint8_t listening;
} hbar_t;

typedef struct {
  struct {
    uint8_t abs;
    uint8_t mirroring;
    uint8_t lamp;
    uint8_t warning;
    uint8_t overheat;
    uint8_t unfinger;
    uint8_t unremote;
    uint8_t daylight;
    uint8_t scanning;
  } state;
  struct {
    uint8_t left;
    uint8_t right;
  } sein;
} hmi1_data_t;

typedef struct {
  hbar_t hbar;
  hmi1_data_t d;
} hmi1_t;
#endif

class ModelListener;

class Model {
 public:
  Model();

  void bind(ModelListener *listener) { modelListener = listener; }

  void tick();

#if defined(SIMULATOR)
  void setDefaultData();
  void generateRandomIndicators();
  void generateRandomData();
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

#endif  // MODEL_HPP

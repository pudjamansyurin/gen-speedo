#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

/* Enum prototypes ------------------------------------------------------- */
typedef enum {
    SW_M_DRIVE = 0,
    SW_M_TRIP,
    SW_M_REPORT,
    SW_M_MAX = 2
} sw_mode_t;

typedef enum {
    SW_M_TRIP_A = 0,
    SW_M_TRIP_B,
	SW_M_TRIP_ODO,
    SW_M_TRIP_MAX = 2,
} sw_mode_trip_t;

typedef enum {
    SW_M_REPORT_RANGE = 0,
    SW_M_REPORT_EFFICIENCY,
    SW_M_REPORT_MAX = 1,
} sw_mode_report_t;

typedef enum {
    SW_M_DRIVE_E = 0,
    SW_M_DRIVE_S,
    SW_M_DRIVE_P,
    SW_M_DRIVE_D,
    SW_M_DRIVE_MAX = 3,
} sw_mode_drive_t;

/* Exported struct -----------------------------------------------------------*/
typedef struct {
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
		uint8_t hide;
		sw_mode_t sel;
		
		struct {
			sw_mode_drive_t sel;
		} drive;
		struct {
			sw_mode_trip_t sel;
			uint32_t val;
		} trip;
		struct {
			sw_mode_report_t sel;
			uint8_t val;
		} report;
	} mode;
} hmi1_data_t;

typedef struct {
    struct {
        char mode[SW_M_DRIVE_MAX+1][9];
    } drive;
	struct {
		char mode[SW_M_TRIP_MAX+1][6];
	} trip;
    struct {
        char mode[SW_M_REPORT_MAX+1][6];
        char unit[SW_M_REPORT_MAX+1][11];
    } report;
} collection_t;

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
    uint32_t _tripValue;
    uint32_t _engineValue;
    uint8_t _batteryValue;
    uint8_t _signalValue;
    uint8_t _speedValue;
};

#endif // SCREEN1VIEW_HPP

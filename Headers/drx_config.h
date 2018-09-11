#pragma once

typedef enum On_Duration_Timer
{
	psf1,
	psf2,
	psf3,
	psf4,
	psf5,
	psf6,
	psf8,
	psf10,
	psf20,
	psf30,
	psf40,
	psf50,
	psf60,
	psf80,
	psf100,
	psf200
} On_Duration_Timer;

typedef enum DRX_Inactivity_Timer
{
	psf1,
	psf2,
	psf3,
	psf4,
	psf5,
	psf6,
	psf8,
	psf10,
	psf20,
	psf30,
	psf40,
	psf50,
	psf60,
	psf80,
	psf100,
	psf200,
	psf300,
	psf500,
	psf750,
	psf1280,
	psf1920,
	psf2560,
	spare10,
	spare9,
	spare8,
	spare7,
	spare6,
	spare5,
	spare4,
	spare3,
	spare2,
	spare1
} DRX_Inactivity_Timer;

typedef enum DRX_Retransmission_Timer
{
	psf1,
	psf2,
	psf4,
	psf6,
	psf8,
	psf16,
	psf24,
	psf33
} DRX_Retransmission_Timer;

typedef enum Long_DRX_Cycle_Start_Offset_Label
{
	sf10,
	sf20,
	sf32,
	sf40,
	sf64,
	sf80,
	sf128,
	sf160,
	sf256,
	sf320,
	sf512,
	sf640,
	sf1024,
	sf1280,
	sf2048,
	sf2560
} Long_DRX_Cycle_Start_Offset_Label;

typedef struct Long_DRX_Cycle_Start_Offset
{
	Long_DRX_Cycle_Start_Offset_Label label;
	int value;
} Long_DRX_Cycle_Start_Offset;

typedef enum Short_DRX_Cycle
{
	sf2,
	sf5,
	sf8,
	sf10,
	sf16,
	sf20,
	sf32,
	sf40,
	sf64,
	sf80,
	sf128,
	sf160,
	sf256,
	sf320,
	sf512,
	sf640
} Short_DRX_Cycle;

typedef struct Short_DRX
{
	Short_DRX_Cycle cycle;
	int DRX_Short_Cycle_Timer;
} Short_DRX;

struct DRX_Config
{
	On_Duration_Timer on_duration_timer;
	DRX_Inactivity_Timer drx_inactivity_timer;
	DRX_Retransmission_Timer drx_retransmission_timer;
	Long_DRX_Cycle_Start_Offset long_drx_cycle_start_offset;
	Short_DRX short_drx;
};
#pragma once



class Config
{
public:
	Config(){}

	void load(const char* config_file);
	
	//TODO: describe meaning of the following variables
	int t_day_low;
	int t_day_middle;
	int t_day_high;

	int t_night_high;
	int t_night_middle;
	int t_night_low;
	
	int t_generate;
	int t_discharge;
	int t_consume;
	
	int p_sunny;
	int p_middle;
	int p_cloudy;
	
	int energy_sunny;
	int energy_middle;
	int energy_cloudy;
	
	int reservoir_capacity;
	int reservoir_init;
	int pump_efficiency;
	int turbine_efficiency;
	
	int high_consume;
	int middle_consume;
	int low_consume;

};

extern Config config;

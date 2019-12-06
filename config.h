#pragma once



class Config
{
public:
	Config(){}

	void load(const char* config_file);
	
	//TODO: describe meaning of the following variables
	int t_day_high;
	int t_day_low;
	int t_night_high;
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
	int battery_capacity;
	int battery_init;
	int battery_efficiency;
	int high_consume;
	int low_consume;

};

extern Config config;

#include "config.h"

#include "config4cpp/Configuration.h"

using namespace config4cpp;

Config config;

void Config::load(const char* config_file)
{
    Configuration* cfg = Configuration::create();
    cfg->parse(config_file);
    
    t_day_low = cfg->lookupInt("", "t_day_low");
    t_day_middle = cfg->lookupInt("", "t_day_middle");
    t_day_high = cfg->lookupInt("", "t_day_high");
    
    t_night_high = cfg->lookupInt("", "t_night_high");
    t_night_middle = cfg->lookupInt("", "t_night_middle");
    t_night_low = cfg->lookupInt("", "t_night_low");
    
    t_generate = cfg->lookupInt("", "t_generate");
    t_discharge = cfg->lookupInt("", "t_discharge");
    t_consume = cfg->lookupInt("", "t_consume");
    
    p_sunny = cfg->lookupInt("", "p_sunny");
    p_middle = cfg->lookupInt("", "p_middle");
    p_cloudy = cfg->lookupInt("", "p_cloudy");
    
    energy_sunny = cfg->lookupInt("", "energy_sunny");
    energy_middle = cfg->lookupInt("", "energy_middle");
    energy_cloudy = cfg->lookupInt("", "energy_cloudy");
    
    reservoir_capacity = cfg->lookupInt("", "reservoir_capacity");
    reservoir_init = cfg->lookupInt("", "reservoir_init");
    pump_efficiency = cfg->lookupInt("", "pump_efficiency");
    turbine_efficiency = cfg->lookupInt("", "turbine_efficiency");
    
    high_consume = cfg->lookupInt("", "high_consume");
    middle_consume = cfg->lookupInt("", "middle_consume");
    low_consume = cfg->lookupInt("", "low_consume");
}
